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
#ifndef _ALLJOYN_PASSWORDMANAGER_H
#define _ALLJOYN_PASSWORDMANAGER_H
/**
 * @file
 * This file defines the PasswordManager class that provides the interface to
 * set credentials used for the authentication of thin clients.
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
#include <alljoyn/Status.h>
namespace ajn {

/**
 * Class to allow the user or application to set credentials used for the authentication
 * of thin clients.
 * Before invoking Connect() to BusAttachment, the application should call SetCredentials
 * if it expects to be able to communicate to/from thin clients.
 * The bundled router will start advertising the name as soon as it is started and MUST have
 * the credentials set to be able to authenticate any thin clients that may try to use the
 * bundled router to communicate with the app.
 */

class PasswordManager {
  public:
    /**
     * @brief Set credentials used for the authentication of thin clients.
     *
     * @param authMechanism  Mechanism to use for authentication.
     * @param password       Password to use for authentication.
     *
     * @return   Returns ER_OK if the credentials was successfully set.
     */
    static QStatus SetCredentials(qcc::String authMechanism, qcc::String password) {
        *PasswordManager::authMechanism = authMechanism;
        *PasswordManager::password = password;
        return ER_OK;
    }

    /// @cond ALLJOYN_DEV
    /**
     * @internal
     * Get the password set by the user/app
     *
     * @return Returns the password set by the user/app.
     */
    static qcc::String GetPassword() { return *password; }

    /**
     * @internal
     * Get the authMechanism set by the user/app
     *
     * @return Returns the authMechanism set by the user/app.
     */
    static qcc::String GetAuthMechanism() { return *authMechanism; }
    /// @endcond
  private:
    static void Init();
    static void Shutdown();
    friend class StaticGlobals;

    static qcc::String* authMechanism;           /**< The auth mechanism selected by the user/app */
    static qcc::String* password;                /**< The password selected by the user/app */
};

}
#endif
