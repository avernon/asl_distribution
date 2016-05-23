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
#ifndef _ALLJOYN_PEERSTATE_H
#define _ALLJOYN_PEERSTATE_H

#ifndef __cplusplus
#error Only include PeerState.h in C++ code.
#endif

#include <qcc/platform.h>

#include <map>
#include <limits>
#include <assert.h>

#include <alljoyn/Message.h>

#include <qcc/String.h>
#include <qcc/GUID.h>
#include <qcc/KeyBlob.h>
#include <qcc/ManagedObj.h>
#include <qcc/Mutex.h>
#include <qcc/Event.h>
#include <qcc/time.h>
#include <qcc/CertificateECC.h>

#include <alljoyn/Status.h>
#include <alljoyn/PermissionPolicy.h>

namespace ajn {

/* Forward declaration */
class _PeerState;

/**
 * Enumeration for the different peer keys.
 */
typedef enum {
    PEER_SESSION_KEY = 0, /**< Unicast key for secure point-to-point communication */
    PEER_GROUP_KEY   = 1  /**< broadcast key for secure point-to-multipoint communication */
} PeerKeyType;

/**
 * PeerState is a reference counted (managed) class that keeps track of state information for other
 * peers that this peer communicates with.
 */
typedef qcc::ManagedObj<_PeerState> PeerState;

/**
 * This class maintains state information about peers connected to the bus and provides helper
 * functions that check and update various state information.
 */
class _PeerState {

    friend class AllJoynPeerObj;

  public:

    /**
     * Key Exchange mode masks
     */
    const static uint8_t KEY_EXCHANGE_NONE = 0x00;       /* no key exchange */
    const static uint8_t KEY_EXCHANGE_INITIATOR = 0x01;  /* in a key exchange as an initiator */
    const static uint8_t KEY_EXCHANGE_RESPONDER = 0x02;  /* in a key exchange as as responder */

    PermissionPolicy::Rule* manifest;
    size_t manifestSize;

    struct GuildMetadata {
        std::vector<qcc::CertificateX509*> certChain;

        GuildMetadata()
        {
        }

        ~GuildMetadata()
        {
            for (std::vector<qcc::CertificateX509*>::iterator it = certChain.begin(); it != certChain.end(); it++) {
                delete *it;
            }
            certChain.clear();
        }

    };

    typedef std::map<const qcc::String, GuildMetadata*> GuildMap;

    /**
     * Default constructor
     */
    _PeerState() :
        manifest(NULL),
        manifestSize(0),
        guildArgsSentCount(0),
        isLocalPeer(false),
        clockOffset((std::numeric_limits<int32_t>::max)()),
        firstClockAdjust(true),
        lastDriftAdjustTime(0),
        isSecure(false),
        authEvent(NULL),
        prevSerial(0),
        flagWindow(0),
        initiatorHash(NULL),
        responderHash(NULL),
        initiatorHashLock(),
        responderHashLock(),
        keyExchangeMode(KEY_EXCHANGE_NONE)
    {
        ::memset(authorizations, 0, sizeof(authorizations));
    }

    ~_PeerState()
    {
        ClearGuildMap(guildMap);
        ClearGuildArgs(guildArgs);
        delete [] manifest;
    }

    /**
     * Get the (estimated) timestamp for this remote peer converted to local host time. The estimate
     * is updated based on the timestamp recently received.
     *
     * @param[in] remoteTime  The timestamp received in a message from the remote peer.
     *
     * @return   The estimated timestamp for the remote peer.
     */
    uint32_t EstimateTimestamp(uint32_t remoteTime);

    /**
     * This method is called whenever a message is unmarshaled. It checks that the serial number is
     * valid by comparing against the last N serial numbers received from this peer. Secure messages
     * have additional checks for replay attacks. Unreliable messages are checked for in-order
     * arrival.
     *
     * @param[in] serial      The serial number being checked.
     * @param[in] secure      The message was flagged as secure
     * @param[in] unreliable  The message is flagged as unreliable.
     *
     * @return  Returns true if the serial number is valid.
     */
    bool IsValidSerial(uint32_t serial, bool secure, bool unreliable);

    /**
     * Gets the GUID for this peer.
     *
     * @return  Returns the GUID for this peer.
     */
    const qcc::GUID128& GetGuid() { return guid; }

    /**
     * Gets the authentication version number for this peer.
     *
     * @return  Returns the authentication version for this peer.
     */
    uint32_t GetAuthVersion() { return authVersion; }

    /**
     * Sets the GUID for and authentication version this peer.
     */
    void SetGuidAndAuthVersion(const qcc::GUID128& guid, uint32_t authVersion) {
        this->guid = guid;
        this->authVersion = authVersion;
    }

    /**
     * Sets the session key for this peer
     *
     * @param[in] key        The session key to set.
     * @param[in] keyType    Indicate if this is the unicast or broadcast key.
     */
    void SetKey(const qcc::KeyBlob& key, PeerKeyType keyType) {
        keys[keyType] = key;
        isSecure = key.IsValid();
    }

    /**
     * Gets the session key for this peer.
     *
     * @param[in] key    [out]Returns the session key.
     *
     * @return  - ER_OK if there is a session key set for this peer.
     *          - ER_BUS_KEY_UNAVAILABLE if no session key has been set for this peer.
     *          - ER_BUS_KEY_EXPIRED if there was a session key but the key has expired.
     */
    QStatus GetKey(qcc::KeyBlob& key, PeerKeyType keyType) {
        if (isSecure) {
            key = keys[keyType];
            if (key.HasExpired()) {
                ClearKeys();
                return ER_BUS_KEY_EXPIRED;
            } else {
                return ER_OK;
            }
        } else {
            return ER_BUS_KEY_UNAVAILABLE;
        }
    }

    /**
     * Clear the keys for this peer.
     */
    void ClearKeys() {
        keys[PEER_SESSION_KEY].Erase();
        keys[PEER_GROUP_KEY].Erase();
        isSecure = false;
    }

    /**
     * Tests if this peer is secure.
     *
     * @return  Returns true if a session key has been set for this peer.
     */
    bool IsSecure() { return isSecure; }

    /**
     * Returns the auth event for this peer. The auth event is set by the peer object while the peer
     * is being authenticated and is used to prevent multiple threads from attempting to
     * simultaneously authenticate the same peer.
     *
     * @return  Returns the auth event for this peer.
     */
    qcc::Event* GetAuthEvent() { return authEvent; }

    /**
     * Set the auth event for this peer. The auth event is set by the peer object while the peer
     * is being authenticated and is used to prevent multiple threads from attempting to
     * simultaneously authenticate the same peer.
     *
     * @param[in] event  The event to set or NULL if the event is being cleared.
     */
    void SetAuthEvent(qcc::Event* event) { authEvent = event; }

    /**
     * Notify all the waiting threads on auth event.
     */

    void NotifyAuthEvent();

    /**
     * Tests if this peer is the local peer.
     *
     * @return  Returns true if this PeerState instance is for the local peer.
     */
    bool IsLocalPeer() { return isLocalPeer; }

    /**
     * Returns window size for serial number validation. Used by unit tests.
     *
     * @return Size of the serial number validation window.
     */
    size_t SerialWindowSize() { return 64; }

    static const uint8_t ALLOW_SECURE_TX = 0x01; /* Transmit authorization */
    static const uint8_t ALLOW_SECURE_RX = 0x02; /* Receive authorization */

    /**
     * Check if the peer is authorized to send or or receive a message of the specified
     * type.
     *
     * @param[in] msgType  The type of message that is being authorized.
     * @param[in] access   The access type being checked
     *
     * @return Return true if the message type is authorized.
     */
    bool IsAuthorized(AllJoynMessageType msgType, uint8_t access) {
        if (msgType == MESSAGE_INVALID) {
            return false;
        } else {
            return isSecure ? (authorizations[(uint8_t)msgType - 1] & access) == access : true;
        }
    }

    /**
     * Set or clear an authorization.
     *
     * @param[in] msgType  The type of message that is being authorized.
     * @param[in] access   The access type to authorize, zero to clear.
     */
    void SetAuthorization(AllJoynMessageType msgType, uint8_t access) {
        if (msgType != MESSAGE_INVALID) {
            if (access) {
                authorizations[(uint8_t)msgType - 1] |= access;
            } else {
                authorizations[(uint8_t)msgType - 1] = 0;
            }
        }
    }


    /**
     * Set the guild metadata indexed by the serial number and the issuer.
     * @param[in] serial the membership certificate serial number
     * @param[in] issuerAki the membership certificate issuer authority key id
     * @param[in] guild the guild metadata
     */
    void SetGuildMetadata(const qcc::String& serial, const qcc::String& issuerAki,        GuildMetadata* guild);

    /**
     * Retrieve the guild metadata indexed by the serial number and the issuer.
     * @param[in] serial the membership certificate serial number
     * @param[in] issuerAki the membership certificate issuer authority key id
     * @return the guild metadata
     */
    GuildMetadata* GetGuildMetadata(const qcc::String& serial, const qcc::String& issuerAki);

    /**
     * Mapping table for guild memberships
     */
    GuildMap guildMap;

    /**
     * Clear the guild map and its members
     */
    static void ClearGuildMap(GuildMap& guildMap)
    {
        for (GuildMap::iterator it = guildMap.begin(); it != guildMap.end(); it++) {
            delete it->second;
        }
        guildMap.clear();
    }

    /**
     * Clear the list of guild message args
     */

    static void ClearGuildArgs(std::vector<std::vector<MsgArg*> >& args)
    {
        for (std::vector<std::vector<MsgArg*> >::iterator i = args.begin(); i != args.end(); i++) {
            for (std::vector<MsgArg*>::iterator j = (*i).begin(); j != (*i).end(); j++) {
                delete *j;
            }
            (*i).clear();
        }
        args.clear();
    }

    /**
     * The list of membership data msg args to reply to the peer
     */
    std::vector<std::vector<MsgArg*> > guildArgs;
    /**
     * The number of membership data msg args already replied to the peer
     */
    uint8_t guildArgsSentCount;

    /**
     * Update the conversation hash with a single byte
     * InitializeConversationHash must first be called before calling this method.
     * The hash lock must be acquired via AcquireConversationHashLock prior to calling this method.
     * The hash lock must be released via ReleaseConversationHashLock after calling this method.
     * @param[in] initiator key exchange started as initiator
     * @param[in] conversationVersion The minimum auth version required for this to be included in the hash.
     * @param[in] byte Byte with which to update the hash.
     */
    void UpdateHash(bool initiator, uint32_t conversationVersion, uint8_t byte);

    /**
     * Update the conversation hash with a byte array.
     * InitializeConversationHash must first be called before calling this method.
     * The hash lock must be acquired via AcquireConversationHashLock prior to calling this method.
     * The hash lock must be released via ReleaseConversationHashLock after calling this method.
     * @param[in] initiator key exchange started as initiator
     * @param[in] conversationVersion The minimum auth version required for this to be included in the hash.
     * @param[in] buf Data with which to update the hash.
     * @param[in] bufSize Size of buf.
     */
    void UpdateHash(bool initiator, uint32_t conversationVersion, const uint8_t* buf, size_t bufSize);

    /**
     * Update the conversation hash with a string. String will be converted to its
     * underlying byte array and used to update.
     * InitializeConversationHash must first be called before calling this method.
     * The hash lock must be acquired via AcquireConversationHashLock prior to calling this method.
     * The hash lock must be released via ReleaseConversationHashLock after calling this method.
     * @param[in] initiator key exchange started as initiator
     * @param[in] conversationVersion The minimum auth version required for this to be included in the hash.
     * @param[in] str String with data with which to update the hash.
     */
    void UpdateHash(bool initiator, uint32_t conversationVersion, const qcc::String& str);

    /**
     * Update the conversation hash with a Message. This extracts the raw message buffer
     * from the Message and updates the hash with that.
     * InitializeConversationHash must first be called before calling this method.
     * The hash lock must be acquired via AcquireConversationHashLock prior to calling this method.
     * The hash lock must be released via ReleaseConversationHashLock after calling this method.
     * @param[in] initiator key exchange started as initiator
     * @param[in] conversationVersion The minimum auth version required for this to be included in the hash.
     * @param[in] msg A Message object whose arguments will be added to the hash.
     */
    void UpdateHash(bool initiator, uint32_t conversationVersion, const Message& msg);

    /**
     * Initialize the conversation hash to start a new conversation. Any previous
     * conversation hash is lost. This must be called before any calls to UpdateHash or GetDigest.
     * The hash lock must be acquired via AcquireConversationHashLock prior to calling this method.
     * The hash lock must be released via ReleaseConversationHashLock after calling this method.
     * @param[in] initiator key exchange started as initiator
     */
    void InitializeConversationHash(bool initiator);

    /**
     * Returns true if the conversation hash has been initalized, false otherwise.
     * @param[in] initiator key exchange started as initiator
     * @see void InitializeConversationHash()
     */
    bool IsConversationHashInitialized(bool initiator);

    /**
     * Free the conversation hash when it's no longer needed. After this, any new calls
     * to UpdateHash or GetDigest must be preceded by a call to InitializeConversationHash.
     * The hash lock must be acquired via AcquireConversationHashLock prior to calling this method.
     * The hash lock must be released via ReleaseConversationHashLock after calling this method.
     * @param[in] initiator key exchange started as initiator
     * @see void InitializeConversationHash()
     */
    void FreeConversationHash(bool initiator);

    /**
     * Get the current conversation hash digest.
     * InitializeConversationHash must first be called before calling this method.
     * The hash lock must be acquired via AcquireConversationHashLock prior to calling this method.
     * The hash lock must be released via ReleaseConversationHashLock after calling this method.
     * @param[in] initiator key exchange started as initiator
     * @param[out] digest A buffer of appropriate size to receive the digest. Currently
     *                    only SHA-256 is used, and so 32 bytes will be returned.
     * @param[in] keepAlive Whether or not to keep the hash alive for continuing hash.
     */
    void GetDigest(bool initiator, uint8_t* digest, bool keepAlive = false);

    /**
     * Acquire the lock to conversation hash with the intention to call
     * UpdateHash, GetDigest, InitializeConversationHash, or
     * FreeConversationHash.
     * In some cases like in MethodReply() with a reply message, the issuer of
     * ReplyMethod wishes to aquire an early lock to the conversation hash to
     * prevent any other thread from updating the conversation hash while it
     * is waiting for the MethodRely() to return.
     * @param[in] initiator key exchange started as initiator
     */

    void AcquireConversationHashLock(bool initiator);

    /**
     * release the conversation hash lock.
     * @param[in] initiator key exchange started as initiator
     */

    void ReleaseConversationHashLock(bool initiator);

    /**
     * Enable or disable "sensitive mode," where byte arrays that get hashed aren't
     * logged verbatim. When enabled, calling the overload of Update that takes a byte array will
     * log the size of the data, but then log secret data was hashed without showing the data.
     *
     * Logging for Update for a single byte or GetDigest is unaffected.
     * @param[in] initiator key exchange started as initiator
     * @param[in] mode true to enable sensitive mode; false to disable it.
     */
    void SetConversationHashSensitiveMode(bool initiator, bool mode);

    /**
     * Get the key exchange mode.  A peer can be in a key exchange as an initiator or a responder or both.
     * @return the key exchange mode
     */
    uint8_t GetKeyExchangeMode() const;

    /**
     * Set the key exchange mode. A peer can be in a key exchange as an
     * initiator or a responder or both.
     * @param[in] mode the key exchange mode.
     */
    void SetKeyExchangeMode(uint8_t mode);

    /**
     * Enable the key exchange mode mask. A peer can be in a key exchange as
     * an initiator or a responder or both.
     * @param[in] mask the mask to enable in the key exchange mode.
     */
    void AddKeyExchangeModeMask(uint8_t mask);

    /**
     * Clear the key exchange mode mask. A peer can be in a key exchange as
     * an initiator or a responder or both.
     * @param[in] mask the mask to clear in the key exchange mode.
     */
    void ClearKeyExchangeModeMask(uint8_t mask);

    /*
     * Is the peer in this key exchange mode?
     * @param[in] mask the key exchange code mask
     * @return true if so; false, otherwise.
     */
    bool IsInKeyExchangeMode(uint8_t mask) const;

    /*
     * Destructor
     */
    ~_PeerState();

  private:
    /**
     * private assignment operator to prevent double freeing of memory
     */
    _PeerState& operator=(const _PeerState& other);

    /**
     * private copy constructor to prevent double freeing of memory
     */
    _PeerState(const _PeerState& other);

    /**
     * Get the conversation hash
     * @param[in] initiator key exchange started as initiator
     */
    ConversationHash* GetConversationHash(bool initiator) const;

    /**
     * Get the conversation hash lock
     * @param[in] initiator key exchange started as initiator
     */
    qcc::Mutex& GetConversationHashLock(bool initiator);

    /**
     * True if this peer state is for the local peer.
     */
    bool isLocalPeer;

    /**
     * The estimated clock offset between the local peer and the remote peer. This is used to
     * convert between remote and local timestamps.
     */
    int32_t clockOffset;

    /**
     * Flag to indicate if clockOffset has been properly initialized.
     */
    bool firstClockAdjust;

    /**
     * Time of last clock drift adjustment.
     */
    uint32_t lastDriftAdjustTime;

    /**
     * Set to true if this peer has keys.
     */
    bool isSecure;

    /**
     * Event used to prevent simultaneous authorization requests to this peer.
     */
    qcc::Event* authEvent;

    /**
     * The GUID for this peer.
     */
    qcc::GUID128 guid;

    /**
     * The authentication version number for this peer
     */
    uint32_t authVersion;

    /**
     * Array of message type authorizations.
     */
    uint8_t authorizations[4];

    /**
     * The session keys (unicast and broadcast) for this peer.
     */
    qcc::KeyBlob keys[2];

    /**
     * The previous serial number seen from this peer.
     * Used by IsValidSerial() to detect replay attacks.
     */
    uint32_t prevSerial;

    /**
     * This contains flags indicating if the serial number was received
     * for each of the last 64 serial numbers from this peer.
     * Bit 0 indicates whether the prevSerial number was seen from this peer.
     * i.e. value of 0 indicates no messages were received from this peer.
     * Bit 1 indicates whether prevSerial - 1 was received from this peer and so on.
     * Used by IsValidSerial() to detect replay attacks.
     */
    uint64_t flagWindow;

    /**
     * The initiator conversation hash.
     */
    ConversationHash* initiatorHash;

    /**
     * The responder conversation hash.
     */
    ConversationHash* responderHash;

    /**
     * Mutex to protect the initiator conversation hash
     */
    qcc::Mutex initiatorHashLock;

    /**
     * Mutex to protect the responder conversation hash
     */
    qcc::Mutex responderHashLock;

    /**
     * The key exchange mode
     */
    uint8_t keyExchangeMode;
};


/**
 * This class is a container for managing state information about remote peers.
 */
class PeerStateTable {

  public:

    /**
     * Constructor
     */
    PeerStateTable();

    /**
     * Get the peer state for given a bus name.
     *
     * @param[in] busName         The bus name for a remote connection
     * @param[in] createIfUnknown true to create a PeerState if the peer is unknown
     *
     * @return  The peer state.
     */
    PeerState GetPeerState(const qcc::String& busName, bool createIfUnknown = true);

    /**
     * Fnd out if the bus name is for a known peer.
     *
     * @param[in] busName   The bus name for a remote connection
     *
     * @return  Returns true if the peer is known.
     */
    bool IsKnownPeer(const qcc::String& busName) {
        lock.Lock(MUTEX_CONTEXT);
        bool known = peerMap.count(busName) > 0;
        lock.Unlock(MUTEX_CONTEXT);
        return known;
    }

    /**
     * Get the peer state looking the peer state up by a unique name or a known alias for the peer.
     *
     * @param[in] uniqueName  The bus name for a remote connection
     * @param[in] aliasName   An alias bus name for a remote connection
     *
     * @return  The peer state.
     */
    PeerState GetPeerState(const qcc::String& uniqueName, const qcc::String& aliasName);

    /**
     * Are two bus names known to refer to the same peer.
     *
     * @param[in] name1  The first bus name
     * @param[in] name2  The second bus name
     *
     * @return  Returns true if the two bus names are known to refer to the same peer.
     */
    bool IsAlias(const qcc::String& name1, const qcc::String& name2) {
        return (name1 == name2) || (GetPeerState(name1).iden(GetPeerState(name2)));
    }

    /**
     * Delete peer state for a busName that is no longer in use
     *
     * @param[in] busName  The bus name that may was been previously associated with peer state.
     */
    void DelPeerState(const qcc::String& busName);

    /**
     * Gets the group (broadcast) key for the local peer. This is used to encrypt
     * broadcast messages sent by this peer.
     *
     * @param[in] key   [out]Returns the broadcast key.
     */
    void GetGroupKey(qcc::KeyBlob& key);

    /**
     * Clear all peer state.
     */
    void Clear();

    /**
     * Destructor
     */
    ~PeerStateTable();

  private:

    /**
     * Mapping table from bus names to peer state.
     */
    std::map<const qcc::String, PeerState> peerMap;

    /**
     * Mutex to protect the peer table
     */
    qcc::Mutex lock;

};

}

#undef QCC_MODULE

#endif
