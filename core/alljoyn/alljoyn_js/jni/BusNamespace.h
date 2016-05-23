/*
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
 */
#ifndef _BUSNAMESPACE_H
#define _BUSNAMESPACE_H

#include "BusAttachmentInterface.h"
#include "BusErrorInterface.h"
#include "CredentialsInterface.h"
#include "MessageInterface.h"
#include "Plugin.h"
#include "ScriptableObject.h"
#include "IfcSecurityInterface.h"
#include "SessionLostReasonInterface.h"
#include "SessionOptsInterface.h"
#include "SocketFdInterface.h"
#include "VersionInterface.h"
#include <map>
#include <qcc/ManagedObj.h>

class _BusNamespace : public ScriptableObject {
  public:
    static std::map<qcc::String, int32_t>& Constants();
    _BusNamespace(Plugin& plugin);
    virtual ~_BusNamespace();

  private:
    static std::map<qcc::String, int32_t> constants;

    BusAttachmentInterface busAttachmentInterface;
    BusErrorInterface busErrorInterface;
    CredentialsInterface credentialsInterface;
    IfcSecurityInterface ifcSecurityInterface;
    MessageInterface messageInterface;
    SessionLostReasonInterface sessionLostReasonInterface;
    SessionOptsInterface sessionOptsInterface;
    SocketFdInterface socketFdInterface;
    VersionInterface versionInterface;
    bool getBusAttachment(NPVariant* result);
    bool getBusError(NPVariant* result);
    bool getCredentials(NPVariant* result);
    bool getIfcSecurity(NPVariant* result);
    bool getMessage(NPVariant* result);
    bool getSessionOpts(NPVariant* result);
    bool getSessionLostReason(NPVariant* result);
    bool getSocketFd(NPVariant* result);
    bool getVersion(NPVariant* result);

    /*
     * Fallback for FeaturePermissions APIs.
     * (http://dev.w3.org/2009/dap/perms/FeaturePermissions.html).
     */
    bool getPrivilegedFeatures(NPVariant* result);
    bool permissionLevel(const NPVariant* args, uint32_t argCount, NPVariant* result);
    bool requestPermission(const NPVariant* args, uint32_t argCount, NPVariant* result);
};

typedef qcc::ManagedObj<_BusNamespace> BusNamespace;

#endif // _BUSNAMESPACE_H
