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
#ifndef _ALLJOYN_PERMISSION_MANAGER_H
#define _ALLJOYN_PERMISSION_MANAGER_H
/**
 * @file
 * This file defines the hook to validate whether a message is authorized by the Permission DB.
 */

/******************************************************************************
 * Copyright (c) 2014-2015, AllSeen Alliance. All rights reserved.
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
#error Only include PermissionManager.h in C++ code.
#endif

#include <alljoyn/PermissionPolicy.h>
#include "PermissionMgmtObj.h"

namespace ajn {

class PermissionManager {

  public:

    /**
     * Constructor
     *
     */
    PermissionManager() : policy(NULL), permissionMgmtObj(NULL)
    {
    }

    /**
     * virtual destructor
     */
    virtual ~PermissionManager()
    {
        delete policy;
    }

    /**
     * Set the permission policy.
     * @param   policy   the permission policy.  It must be new'd by the caller and and will be deleted by this object.
     */

    void SetPolicy(PermissionPolicy* policy)
    {
        delete this->policy;
        this->policy = policy;
    }

    /**
     * Retrieve the permission policy.
     * @return the permission policy.
     */
    const PermissionPolicy* GetPolicy() const
    {
        return policy;
    }

    /**
     * Authorize a message.  Make sure there is a proper permission is setup for this type of message.
     * @param outgoing indicating whether is a outgoing or incoming
     * @param msg the target message
     * @param peerState the peer's PeerState object
     * @param authenticated flag indicating the message is authenticated
     * @return
     *  - ER_OK: authorized
     *  - ER_PERMISSION_DENIED: permission denied
     */
    QStatus AuthorizeMessage(bool outgoing, Message& msg, PeerState& peerState, bool authenticated = true);

    /**
     * Authorize a Get Property message.  Make sure there is a proper permission is setup for this type of message.
     * @param objPath the object path
     * @param ifcName the interface name
     * @param propName the property name
     * @param peerState the peer's PeerState object
     * @return
     *  - ER_OK: authorized
     *  - ER_PERMISSION_DENIED: permission denied
     */
    QStatus AuthorizeGetProperty(const char* objPath, const char* ifcName, const char* propName, PeerState& peerState);

    void SetPermissionMgmtObj(PermissionMgmtObj* permissionMgmtObj)
    {
        this->permissionMgmtObj = permissionMgmtObj;
    }

    PermissionMgmtObj* GetPermissionMgmtObj()
    {
        return permissionMgmtObj;
    }

  private:
    /* Private assigment operator to prevent double freeing of memory */
    PermissionManager& operator=(const PermissionManager& src);
    /* Private copy constructor to prevent double freeing of memory */
    PermissionManager(const PermissionManager& src);

    bool AuthorizePermissionMgmt(bool outgoing, const char* iName, const char* mbrName, bool& authorized);

    PermissionPolicy* policy;
    PermissionMgmtObj* permissionMgmtObj;
};

}
#endif
