# Contributed by Qualcomm Connected Experiences, Inc.,
# with authorization from the AllSeen Alliance, Inc.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# 
# Pursuant to Section 1 of the License, the work of authorship constituting
# a Work and any Contribution incorporated in the Work shall mean only that
# Contributor's code submissions authored by that Contributor.  Any rights
# granted under the License are conditioned upon acceptance of these
# clarifications.
#ifndef _ALLJOYN_CREDENTIAL_ACCESSOR_H
#define _ALLJOYN_CREDENTIAL_ACCESSOR_H
/**
 * @file
 * This file defines the CredentialAccessor class that provides the interface to
 * access and manage the set credentials used in the authentication
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

#ifndef __cplusplus
#error Only include PasswordManager.h in C++ code.
#endif

#include <qcc/platform.h>
#include <qcc/String.h>
#include <qcc/GUID.h>
#include <qcc/KeyBlob.h>
#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include "KeyStore.h"

namespace ajn {


/**
 * Class to allow the application to get access the authentication credentials.
 */

class CredentialAccessor {
  public:

    /**
     * Constructor
     *
     * @param keyStore  the key store
     */
    CredentialAccessor(BusAttachment& bus);

    /**
     * virtual destructor
     */
    virtual ~CredentialAccessor() { }

    /**
     * Return the Auth GUID
     * @param[out] guid object holding the auth GUID for this application
     * @return
     *      - ER_OK on success
     *      - ER_BUS_KEY_STORE_NOT_LOADED if the GUID is not available
     */
    QStatus GetGuid(qcc::GUID128& guid);

    /**
     * Return the Peer Auth GUID
     * @param peerName the peer bus name
     * @param[out] guid object holding the peerAuth GUID
     * @return
     *      - ER_OK on success
     *      - ER_BUS_NO_PEER_GUID if the GUID is not available
     */
    QStatus GetPeerGuid(qcc::String& peerName, qcc::GUID128& guid);

    /**
     * Get the key store key to index a local key blob.
     *
     * @param keyType     The key blob type
     * @param[out] key   The matching key
     * @return
     *      - ER_OK if successful
     *      - ER_CRYPTO_KEY_UNAVAILABLE if key is unavailable
     */
    QStatus GetLocalKey(qcc::KeyBlob::Type keyType, KeyStore::Key& key);

    /**
     * Get a key blob
     *
     * @param key  The unique identifier for the key
     * @param[out] keyBlob   The key blob to get
     * @return
     *      - ER_OK if successful
     *      - ER_CRYPTO_KEY_UNAVAILABLE if key is unavailable
     */
    QStatus GetKey(const KeyStore::Key& key, qcc::KeyBlob& keyBlob);

    /**
     * Delete a key blob
     *
     * @param key  The unique identifier for the key
     * @return
     *      - ER_OK if successful if the key is deleted or not found
     *      - ER_FAIL if the operation fails
     */
    QStatus DeleteKey(const KeyStore::Key& key);

    /**
     * Add an associated key.
     *
     * @param headerKey   The header key to associate with
     * @param key         The key to store
     * @param keyBlob     The key blob to store
     * @return
     *      - ER_OK if successful
       m range
     *      - ER_FAIL if operation fails
     */
    QStatus AddAssociatedKey(KeyStore::Key& headerKey, KeyStore::Key& key, qcc::KeyBlob& keyBlob);

    /**
     * Get the list of keys associated with the given header key.
     * @param headerKey  The header key where the keys are associated with
     * @param[out] list  The output list of key.  This list must be delete[]'d
     *                   after used.
     * @param[out] numItems The output size of the list
     * @return
     *      - ER_OK if successful
     *      - ER_FAIL if operation fails
     */
    QStatus GetKeys(const KeyStore::Key& headerKey, KeyStore::Key** list, size_t* numItems);

    /**
     * store a key blob.
     * @param key         The index
     * @param keyBlob     The key blob to store
     * @return
     *      - ER_OK if successful
       m range
     *      - ER_FAIL if operation fails
     */
    QStatus StoreKey(KeyStore::Key& key, qcc::KeyBlob& keyBlob);

  private:
    BusAttachment& bus;

};

}
#endif
