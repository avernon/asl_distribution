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
#ifndef _ALLJOYN_KEYINFO_HELPER_H
#define _ALLJOYN_KEYINFO_HELPER_H
/**
 * @file
 * This file defines the helper function for KeyInfo data
 */

/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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
#error Only include KeyInfoHelper.h in C++ code.
#endif

#include <qcc/KeyInfoECC.h>
#include <alljoyn/MsgArg.h>

namespace ajn {

class KeyInfoHelper {

  public:
    /**
     * Helper function to determine whether the keyInfo object is an instance of a KeyInfoNISTP256 object.
     * @param keyInfo the KeyInfoECC object
     * @return true if the keyInfo object is a KeyInfoNISTP256 object; false, otherwise.
     */

    static bool InstanceOfKeyInfoNISTP256(const qcc::KeyInfoECC& keyInfo);

    /**
     * Helper function to generate a MsgArg for KeyInfoNISTP256 object.
     * @param keyInfo the KeyInfoNISTP256 object
     * @param[out] variant the output message arg.
     */

    static void KeyInfoNISTP256ToMsgArg(const qcc::KeyInfoNISTP256& keyInfo, MsgArg& variant);

    /**
     * Helper function to load a KeyInfoNISTP256 object using data from the message arg.
     * @param variant the input message arg.
     * @param[out] keyInfo the output KeyInfoNISTP256 object
     * @return ER_OK if successful; otherwise, error code.
     */
    static QStatus MsgArgToKeyInfoNISTP256(const MsgArg& variant, qcc::KeyInfoNISTP256& keyInfo);

    /**
     * Helper function to generate a MsgArg for KeyInfoNISTP256 public key.
     * @param keyInfo the KeyInfoNISTP256 object
     * @param[out] msgArg the output message arg.
     * @param setKeyId set the keyId value
     */
    static void KeyInfoNISTP256PubKeyToMsgArg(const qcc::KeyInfoNISTP256& keyInfo, MsgArg& msgArg, bool setKeyId = false);

    /**
     * Helper function to load a KeyInfoNISTP256 public key using data from the
     * message arg.
     * @param msgArg the input message arg.
     * @param[out] keyInfo the output KeyInfoNISTP256 object
     * @param retrieveKeyId retrieve the keyId value
     * @return ER_OK if successful; otherwise, error code.
     */
    static QStatus MsgArgToKeyInfoNISTP256PubKey(const MsgArg& msgArg, qcc::KeyInfoNISTP256& keyInfo, bool retrieveKeyId = false);

    /**
     * Helper function to load an authority key id using data from the
     * message arg.
     * @param msgArg the input message arg.
     * @param[in,out] keyInfo the keyInfo object
     * @return ER_OK if successful; otherwise, error code.
     */
    static QStatus MsgArgToKeyInfoKeyId(const MsgArg& msgArg, qcc::KeyInfoNISTP256& keyInfo);

    /**
     * Helper function to generate a MsgArg for authority key id.
     * @param keyInfo the keyInfo object
     * @param[out] arg the output message arg.
     */
    static void KeyInfoKeyIdToMsgArg(const qcc::KeyInfoNISTP256& keyInfo, MsgArg& msgArg);

    /**
     * Helper function to generate the key id using the authority
     * key id generation algorithm.
     * @param[in,out] keyInfo the key info object
     * @return ER_OK if successfull; otherwise, error code.
     */
    static QStatus GenerateKeyId(qcc::KeyInfoNISTP256& keyInfo);

    /**
     * Helper function to export the ECC public key to coordinates.
     * @param[in] publicKey the ECC public key
     * @param[out] xData the buffer to hold the x coordinate
     * @param[in] xSize the size of the x coordinate buffer
     * @param[out] yData the buffer to hold the y coordinate
     * @param[in] ySize the size of the y coordinate buffer
     * @return ER_OK if successfull; otherwise, error code.
     */
    static QStatus ExportCoordinates(const qcc::ECCPublicKey& publicKey, uint8_t* xData, const size_t xSize, uint8_t* yData, const size_t ySize);
};

}
#endif
