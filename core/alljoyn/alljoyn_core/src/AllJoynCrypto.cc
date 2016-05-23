/**
 * @file
 * Class for encapsulating message encryption and decryption operations.
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

#include <string.h>

#include <qcc/Debug.h>
#include <qcc/Crypto.h>
#include <qcc/KeyBlob.h>
#include <qcc/Util.h>
#include <qcc/StringUtil.h>

#include <alljoyn/Status.h>

#include "AllJoynCrypto.h"

#define QCC_MODULE "ALLJOYN_AUTH"

using namespace std;
using namespace qcc;

namespace ajn {

const size_t Crypto::MACLength = 8;

QStatus Crypto::Encrypt(const _Message& message, const KeyBlob& keyBlob, uint8_t* msgBuf, size_t hdrLen, size_t& bodyLen)
{
    QStatus status;
    switch (keyBlob.GetType()) {
    case KeyBlob::AES:
        {
            uint8_t* body = msgBuf + hdrLen;
            uint8_t nd[5];
            uint32_t serial = message.GetCallSerial();

            nd[0] = (uint8_t)keyBlob.GetRole();
            nd[1] = (uint8_t)(serial >> 24);
            nd[2] = (uint8_t)(serial >> 16);
            nd[3] = (uint8_t)(serial >> 8);
            nd[4] = (uint8_t)(serial);
            KeyBlob nonce(nd, sizeof(nd), KeyBlob::GENERIC);

            // Patch up the body length in header before encrypting
            _Message::MessageHeader* msgHdr = (_Message::MessageHeader*)msgBuf;
            msgHdr->bodyLen = bodyLen + extraNonceLen + macLen;

            QCC_DbgHLPrintf(("bodyLen in %d", bodyLen));

            if (message.endianSwap) {
                msgHdr->bodyLen = EndianSwap32(msgHdr->bodyLen);
            }

            QCC_DbgHLPrintf(("     Header: %s", BytesToHexString(msgBuf, sizeof(_Message::MessageHeader)).c_str()));
            QCC_DbgHLPrintf(("Encrypt key: %s", BytesToHexString(keyBlob.GetData(), keyBlob.GetSize()).c_str()));
            QCC_DbgHLPrintf(("      nonce: %s", BytesToHexString(nonce.GetData(), nonce.GetSize()).c_str()));
            Crypto_AES aes(keyBlob, Crypto_AES::CCM);
            status = aes.Encrypt_CCM(body, body, bodyLen, nonce, msgBuf, hdrLen, macLen);

            bodyLen += extraNonceLen;

            QCC_DbgHLPrintf(("        MAC: %s", BytesToHexString(body + bodyLen - macLen - extraNonceLen, macLen).c_str()));
            QCC_DbgHLPrintf(("extra nonce: %s", BytesToHexString(body + bodyLen - extraNonceLen, extraNonceLen).c_str()));

            QCC_DbgHLPrintf(("bodyLen out %d", bodyLen));
        }
        break;

    default:
        status = ER_BUS_KEYBLOB_OP_INVALID;
        QCC_LogError(status, ("Key type %d not supported for message encryption", keyBlob.GetType()));
        break;
    }
    return status;
}

QStatus Crypto::Decrypt(const _Message& message, const KeyBlob& keyBlob, uint8_t* msgBuf, size_t hdrLen, size_t& bodyLen)
{
    QStatus status;
    switch (keyBlob.GetType()) {
    case KeyBlob::AES:
        {
            uint8_t* body = msgBuf + hdrLen;
            uint8_t nd[5];
            uint32_t serial = message.GetCallSerial();

            nd[0] = (uint8_t)keyBlob.GetAntiRole();
            nd[1] = (uint8_t)(serial >> 24);
            nd[2] = (uint8_t)(serial >> 16);
            nd[3] = (uint8_t)(serial >> 8);
            nd[4] = (uint8_t)(serial);
            KeyBlob nonce(nd, sizeof(nd), KeyBlob::GENERIC);

            if (MIN_AUTH_VERSION_USE_CRYPTO_VALUE <= message.GetAuthVersion()) {
                extraNonceLen = GetExtraNonceLength(message);

                assert(extraNonceLen <= (MaxNonceLength - PreviousNonceLength));
                if (MaxNonceLength < (extraNonceLen + PreviousNonceLength)) {
                    status = ER_CRYPTO_ILLEGAL_PARAMETERS;
                    break;
                }

                memcpy(&nd[PreviousNonceLength], body + bodyLen - extraNonceLen, extraNonceLen);
            }

            KeyBlob nonce(nd, min(sizeof(nd), GetNonceLength(message)), KeyBlob::GENERIC);

            QCC_DbgHLPrintf(("bodyLen in %d", bodyLen));
            bodyLen -= extraNonceLen;

            QCC_DbgHLPrintf(("     Header: %s", BytesToHexString(msgBuf, sizeof(_Message::MessageHeader)).c_str()));
            QCC_DbgHLPrintf(("Decrypt key: %s", BytesToHexString(keyBlob.GetData(), keyBlob.GetSize()).c_str()));
            QCC_DbgHLPrintf(("      nonce: %s", BytesToHexString(nonce.GetData(), nonce.GetSize()).c_str()));
            QCC_DbgHLPrintf(("        MAC: %s", BytesToHexString(body + bodyLen - macLen, macLen).c_str()));
            QCC_DbgHLPrintf(("extra nonce: %s", BytesToHexString(body + bodyLen, extraNonceLen).c_str()));

            Crypto_AES aes(keyBlob, Crypto_AES::CCM);
            status = aes.Decrypt_CCM(body, body, bodyLen, nonce, msgBuf, hdrLen, macLen);
            QCC_DbgHLPrintf(("bodyLen out %d", bodyLen));
        }
        break;

    default:
        status = ER_BUS_KEYBLOB_OP_INVALID;
        QCC_LogError(status, ("Key type %d not supported for message decryption", keyBlob.GetType()));
        break;
    }
    if (status != ER_OK) {
        status = ER_BUS_MESSAGE_DECRYPTION_FAILED;
    }
    return status;
}

}
