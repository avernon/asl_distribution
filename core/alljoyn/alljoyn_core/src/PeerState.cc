/**
 * @file
 * This class maintains information about peers connected to the bus.
 */

/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Contributed by Qualcomm Connected Experiences, Inc.,
 *    with authorization from the AllSeen Alliance, Inc.
 *    
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *    
 *        http://www.apache.org/licenses/LICENSE-2.0
 *    
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 *    
 *    Pursuant to Section 1 of the License, the work of authorship constituting
 *    a Work and any Contribution incorporated in the Work shall mean only that
 *    Contributor's code submissions authored by that Contributor.  Any rights
 *    granted under the License are conditioned upon acceptance of these
 *    clarifications.
 ******************************************************************************/

#include <qcc/platform.h>

#include <algorithm>
#include <limits>

#include <qcc/Debug.h>
#include <qcc/Crypto.h>
#include <qcc/time.h>
#include <qcc/Util.h>
#include <qcc/Thread.h>

#include "PeerState.h"
#include "AllJoynCrypto.h"

#include <alljoyn/Status.h>

#define QCC_MODULE "ALLJOYN"

using namespace std;
using namespace qcc;

namespace ajn {

/*
 * At the beginning of time, find the difference between the timestamp of the
 * remote system when it marshaled the message and the timestamp of the local
 * system when it unmarshaled the message.  This number is the difference
 * between the offsets of the clocks on the two systems and the time it took for
 * the message to get from one to the other.
 *
 * Each time a message with a timestamp is unmarshaled, we look at a new
 * calculation of the same time.  Presumably the times will be different because
 * of clock drift and the change in the time it took to get the message through
 * the network.
 *
 * If the old number is bigger than the new number, it means that the latest
 * offset between the systems is smaller which, in turn, means the network is
 * faster this time around or the remote clock is running faster than the local
 * clock.  In this case, we set the clamp the new offset to the difference.
 *
 * If the old number is less than the new number, it means that the latest
 * offset between the systems is larger which, in turn, means that the network
 * is getting slower or the remote clock is running slower (earlier time that
 * expected) than the local clock.  In this case, we increment the offset one
 * millisecond every ten seconds to increase the offset slowly in order to seek
 * the increased difference.
 *
 * We expect these numbers to be dominated by network delays since clocks on a
 * host should be running within about 10 PPM for a decent quartz oscillator.
 *
 * The upshot is that this method is really seeking the offset between the
 * machines' clocks and the fastest message delivery time.  This is not a
 * problem if TTL >> fastest network delay over which the message is sent.
 */
uint32_t _PeerState::EstimateTimestamp(uint32_t remote)
{
    uint32_t local = qcc::GetTimestamp();
    int32_t delta = static_cast<int32_t>(local - remote);
    int32_t oldOffset = clockOffset;

    /*
     * Clock drift adjustment. Make remote re-confirm minimum occasionally.
     * This will adjust for clock drift that is less than 100 ppm.
     */
    if ((local - lastDriftAdjustTime) > 10000) {
        lastDriftAdjustTime = local;
        ++clockOffset;
    }

    if (((oldOffset - delta) > 0) || firstClockAdjust) {
        QCC_DbgHLPrintf(("Updated clock offset old %d, new %d", clockOffset, delta));
        clockOffset = delta;
        firstClockAdjust = false;
    }

    return remote + static_cast<uint32_t>(clockOffset);
}

static uint32_t wrapped_offset(uint32_t a, uint32_t b)
{
    uint32_t offset;
    if (b <= a) {
        offset = a - b;
    } else {
        offset = (0xFFFFFFFFUL - b) + a + 1;
    }

    return offset;
}

bool _PeerState::IsValidSerial(uint32_t serial, bool secure, bool unreliable)
{
    QCC_UNUSED(secure);
    QCC_UNUSED(unreliable);

    uint32_t offset;
    uint64_t mask;

    if (serial == 0) {
        /* 0 is never a valid serial number */
        QCC_DbgHLPrintf(("_PeerState::IsValidSerial: 0 is invalid\n"));
        return false;
    }

    if (prevSerial == 0) {
        offset = 0;
        flagWindow = 0;
    } else {
        offset = wrapped_offset(serial, prevSerial);
        if (0 == offset) {
            /* Current serial number matches highest recent serial */
            QCC_DbgHLPrintf(("_PeerState::IsValidSerial: Repeated serial %x %x %llx\n", serial, prevSerial, flagWindow));
            return false;
        } else if (0xFFFFFFC0UL < offset) {
            /* Current serial number is in the recent past. Check mask but don't move the window */
            offset = (0xFFFFFFFFUL - offset) + 1;
            mask = ((uint64_t) 1) << offset;
            if (mask & flagWindow) {
                QCC_DbgHLPrintf(("_PeerState::IsValidSerial: Repeated serial %x %x %llx\n", serial, prevSerial, flagWindow));
                return false;
            }
            /* Switch this mask on to mark this serial number as "seen" */
            flagWindow |= mask;
            return true;
        } else if (0x80000000UL <= offset) {
            /* Too far in the past */
            QCC_DbgHLPrintf(("_PeerState::IsValidSerial: Invalid serial %x %x %llx\n", serial, prevSerial, flagWindow));
            return false;
        }

        /* Moving window ahead. */
        if (offset < 64) {
            flagWindow <<= offset;
        } else {
            flagWindow = 0;
        }
    }

    prevSerial = serial;
    flagWindow |= 1;
    return true;

}

bool _PeerState::IsConversationHashInitialized(bool initiator)
{
    return GetConversationHash(initiator) != NULL;
}

void _PeerState::InitializeConversationHash(bool initiator)
{
    GetConversationHashLock(initiator).AssertOwnedByCurrentThread();
    ConversationHash* hashUtil = new ConversationHash();
    QCC_VERIFY(ER_OK == hashUtil->Init());
    if (initiator) {
        delete initiatorHash;
        initiatorHash = hashUtil;
        AddKeyExchangeModeMask(KEY_EXCHANGE_INITIATOR);
    } else {
        delete responderHash;
        responderHash = hashUtil;
        AddKeyExchangeModeMask(KEY_EXCHANGE_RESPONDER);
    }
}

void _PeerState::FreeConversationHash(bool initiator)
{
    GetConversationHashLock(initiator).AssertOwnedByCurrentThread();
    if (initiator) {
        QCC_ASSERT(NULL != initiatorHash);
        delete initiatorHash;
        initiatorHash = NULL;
        ClearKeyExchangeModeMask(KEY_EXCHANGE_INITIATOR);
    } else {
        QCC_ASSERT(NULL != responderHash);
        delete responderHash;
        responderHash = NULL;
        ClearKeyExchangeModeMask(KEY_EXCHANGE_RESPONDER);
    }
}

/**
 * Helper function to determine if the current authentication version used for this peer should
 * include elements in the conversation hash for the indicated conversation version.
 *
 * @param[in] conversationVersion Version of the conversation, usually a constant supplied at development time
 * @param[in] currentAuthVersion The current authentication version for a given peer
 * @return true if conversation version does not apply, false if it does
 */
static inline bool ConversationVersionDoesNotApply(uint32_t conversationVersion, uint32_t currentAuthVersion)
{
    assert((CONVERSATION_V1 == conversationVersion) || (CONVERSATION_V4 == conversationVersion));

    if (CONVERSATION_V4 == conversationVersion) {
        return ((currentAuthVersion >> 16) != CONVERSATION_V4);
    } else {
        return ((currentAuthVersion >> 16) >= CONVERSATION_V4);
    }
}

void _PeerState::AcquireConversationHashLock(bool initiator)
{
    GetConversationHashLock(initiator).Lock(MUTEX_CONTEXT);
}

void _PeerState::ReleaseConversationHashLock(bool initiator)
{
    GetConversationHashLock(initiator).Unlock(MUTEX_CONTEXT);
}

void _PeerState::UpdateHash(bool initiator, uint32_t conversationVersion, uint8_t byte)
{
    GetConversationHashLock(initiator).AssertOwnedByCurrentThread();
    /* In debug builds, a NULL hashUtil is probably a caller bug, so assert.
     * In release, it probably means we've gotten a message we weren't expecting.
     * Log this as unusual but do nothing.
     */
    ConversationHash* hashUtil = GetConversationHash(initiator);
    QCC_ASSERT(NULL != hashUtil);
    if (NULL == hashUtil) {
        QCC_LogError(ER_CRYPTO_ERROR, ("UpdateHash called when a conversation is not in progress"));
        return;
    }
    if (ConversationVersionDoesNotApply(conversationVersion, GetAuthVersion())) {
        return;
    }
    QCC_VERIFY(ER_OK == hashUtil->Update(&byte, sizeof(byte)));
}

void _PeerState::UpdateHash(bool initiator, uint32_t conversationVersion, const uint8_t* buf, size_t bufSize)
{
    GetConversationHashLock(initiator).AssertOwnedByCurrentThread();
    ConversationHash* hashUtil = GetConversationHash(initiator);
    QCC_ASSERT(NULL != hashUtil);
    if (NULL == hashUtil) {
        QCC_LogError(ER_CRYPTO_ERROR, ("UpdateHash called when a conversation is not in progress"));
        return;
    }
    if (ConversationVersionDoesNotApply(conversationVersion, GetAuthVersion())) {
        return;
    }
    if (conversationVersion >= CONVERSATION_V4) {
        uint32_t bufSizeLE = htole32(bufSize);
        QCC_VERIFY(ER_OK == hashUtil->Update((const uint8_t*)&bufSizeLE, sizeof(bufSizeLE)));
    }
    QCC_VERIFY(ER_OK == hashUtil->Update(buf, bufSize));
}

void _PeerState::UpdateHash(bool initiator, uint32_t conversationVersion, const qcc::String& str)
{
    UpdateHash(initiator, conversationVersion, (const uint8_t*)str.data(), str.size());
}

void _PeerState::UpdateHash(bool initiator, uint32_t conversationVersion, const Message& msg)
{
    if (ConversationVersionDoesNotApply(conversationVersion, GetAuthVersion())) {
        return;
    }

    UpdateHash(initiator, conversationVersion, msg->GetBuffer(), msg->GetBufferSize());
}

void _PeerState::GetDigest(bool initiator, uint8_t* digest, bool keepAlive)
{
    GetConversationHashLock(initiator).AssertOwnedByCurrentThread();
    ConversationHash* hashUtil = GetConversationHash(initiator);
    QCC_ASSERT(NULL != hashUtil);
    if (NULL == hashUtil) {
        /* This should never happen, but if it does, return all zeroes. */
        QCC_LogError(ER_CRYPTO_ERROR, ("GetDigest called while conversation is not in progress"));
        memset(digest, 0, Crypto_SHA256::DIGEST_SIZE);
    } else {
        QCC_VERIFY(ER_OK == hashUtil->GetDigest(digest, keepAlive));
    }
}

void _PeerState::SetConversationHashSensitiveMode(bool initiator, bool mode)
{
    GetConversationHashLock(initiator).AssertOwnedByCurrentThread();
    ConversationHash* hashUtil = GetConversationHash(initiator);
    QCC_ASSERT(NULL != hashUtil);
    if (NULL == hashUtil) {
        QCC_LogError(ER_CRYPTO_ERROR, ("SetConversationHashSensitiveMode called while conversation is not in progress"));
    } else {
        hashUtil->SetSensitiveMode(mode);
    }
}

_PeerState::~_PeerState()
{
    ClearGuildMap(guildMap);
    ClearGuildArgs(guildArgs);
    delete [] manifest;
    delete initiatorHash;
    delete responderHash;
}

PeerStateTable::PeerStateTable()
{
    Clear();
}

PeerState PeerStateTable::GetPeerState(const qcc::String& busName, bool createIfUnknown)
{
    lock.Lock(MUTEX_CONTEXT);
    std::map<const qcc::String, PeerState>::iterator iter = peerMap.find(busName);
    QCC_DbgHLPrintf(("PeerStateTable::GetPeerState() %s state for %s", (iter == peerMap.end()) ? "no" : "got", busName.c_str()));
    if (iter != peerMap.end() || createIfUnknown) {
        PeerState result = peerMap[busName];
        lock.Unlock(MUTEX_CONTEXT);
        return result;
    }

    lock.Unlock(MUTEX_CONTEXT);
    return PeerState();
}

PeerState PeerStateTable::GetPeerState(const qcc::String& uniqueName, const qcc::String& aliasName)
{
    assert(uniqueName[0] == ':');
    PeerState result;
    lock.Lock(MUTEX_CONTEXT);
    std::map<const qcc::String, PeerState>::iterator iter = peerMap.find(uniqueName);
    if (iter == peerMap.end()) {
        QCC_DbgHLPrintf(("PeerStateTable::GetPeerState() no state stored for %s aka %s", uniqueName.c_str(), aliasName.c_str()));
        result = peerMap[aliasName];
        peerMap[uniqueName] = result;
    } else {
        QCC_DbgHLPrintf(("PeerStateTable::GetPeerState() got state for %s aka %s", uniqueName.c_str(), aliasName.c_str()));
        result = iter->second;
        peerMap[aliasName] = result;
    }
    lock.Unlock(MUTEX_CONTEXT);
    return result;
}

void PeerStateTable::DelPeerState(const qcc::String& busName)
{
    lock.Lock(MUTEX_CONTEXT);
    QCC_DbgHLPrintf(("PeerStateTable::DelPeerState() %s for %s", peerMap.count(busName) ? "remove state" : "no state to remove", busName.c_str()));
    peerMap.erase(busName);
    lock.Unlock(MUTEX_CONTEXT);
}

void PeerStateTable::GetGroupKey(qcc::KeyBlob& key)
{
    PeerState groupPeer = GetPeerState("");
    /*
     * The group key is carried by the null-name peer
     */
    groupPeer->GetKey(key, PEER_SESSION_KEY);
    /*
     * Access rights on the group peer always allows signals to be encrypted.
     */
    groupPeer->SetAuthorization(MESSAGE_SIGNAL, _PeerState::ALLOW_SECURE_TX);
}

void PeerStateTable::Clear()
{
    qcc::KeyBlob key(0);  /* use version 0 to exchange with older clients that send keyblob instead of key data */
    lock.Lock(MUTEX_CONTEXT);
    peerMap.clear();
    PeerState nullPeer;
    QCC_DbgHLPrintf(("Allocating group key"));
    key.Rand(Crypto_AES::AES128_SIZE, KeyBlob::AES);
    key.SetTag("GroupKey", KeyBlob::NO_ROLE);
    nullPeer->SetKey(key, PEER_SESSION_KEY);
    peerMap[""] = nullPeer;
    lock.Unlock(MUTEX_CONTEXT);
}

PeerStateTable::~PeerStateTable()
{
    lock.Lock(MUTEX_CONTEXT);
    peerMap.clear();
    lock.Unlock(MUTEX_CONTEXT);
}

static String GenGuildMetadataKey(const qcc::String& serial, const qcc::String& issuerAki)
{
    return serial + "::" + issuerAki;
}

void _PeerState::SetGuildMetadata(const qcc::String& serial, const qcc::String& issuerAki, GuildMetadata* guild)
{
    String key = GenGuildMetadataKey(serial, issuerAki);
    GuildMap::iterator iter = guildMap.find(key);
    if (iter != guildMap.end()) {
        /* found existing one */
        delete iter->second;
        guildMap.erase(key);
    }
    guildMap[key] = guild;
}

_PeerState::GuildMetadata* _PeerState::GetGuildMetadata(const qcc::String& serial, const String& issuerAki)
{
    String key = GenGuildMetadataKey(serial, issuerAki);
    GuildMap::iterator iter = guildMap.find(key);
    if (iter != guildMap.end()) {
        return iter->second;  /* direct hit at the leaf cert */
    }

    /* the <serial,issuer> pair may be of a cert in the chain */
    for (GuildMap::iterator it = guildMap.begin(); it != guildMap.end(); it++) {
        GuildMetadata* meta = it->second;
        for (std::vector<CertificateX509*>::iterator ccit = meta->certChain.begin(); ccit != meta->certChain.end(); ccit++) {
            if (((*ccit)->GetSerialLen() == serial.size()) &&
                (memcmp((*ccit)->GetSerial(), serial.data(), serial.size()) == 0) &&
                ((*ccit)->GetAuthorityKeyId() == issuerAki)) {
                return meta;
            }
        }
    }

    return NULL;
}

void _PeerState::NotifyAuthEvent()
{
    if (GetAuthEvent() == NULL) {
        return;
    }
    while (GetAuthEvent()->GetNumBlockedThreads() > 0) {
        GetAuthEvent()->SetEvent();
        qcc::Sleep(10);
    }
}

uint8_t _PeerState::GetKeyExchangeMode() const
{
    return keyExchangeMode;
}

void _PeerState::SetKeyExchangeMode(uint8_t mode)
{
    keyExchangeMode = mode;
}

bool _PeerState::IsInKeyExchangeMode(uint8_t mask) const
{
    return (keyExchangeMode & mask) == mask;
}

void _PeerState::AddKeyExchangeModeMask(uint8_t mask)
{
    SetKeyExchangeMode(GetKeyExchangeMode() | mask);
}

void _PeerState::ClearKeyExchangeModeMask(uint8_t mask)
{
    SetKeyExchangeMode(GetKeyExchangeMode() & ~mask);
}

ConversationHash* _PeerState::GetConversationHash(bool initiator) const
{
    if (initiator) {
        return initiatorHash;
    }
    return responderHash;
}

qcc::Mutex& _PeerState::GetConversationHashLock(bool initiator)
{
    if (initiator) {
        return initiatorHashLock;
    }
    return responderHashLock;
}

}
