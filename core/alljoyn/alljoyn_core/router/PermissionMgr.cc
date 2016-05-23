/**
 * @file
 * This class is to manage the permission of an endpoint on using transports or invoking method/signal calls on another peer
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

#include <alljoyn/AllJoynStd.h>
#include "ConfigDB.h"
#include "PermissionMgr.h"
#include "RemoteEndpoint.h"

#define QCC_MODULE "PERMISSION_MGR"

namespace ajn {

PermissionMgr::DaemonBusCallPolicy PermissionMgr::GetDaemonBusCallPolicy(BusEndpoint sender)
{
    static bool enableRestrict = ConfigDB::GetConfigDB()->GetFlag("restrict_untrusted_clients");

    QCC_DbgTrace(("PermissionMgr::GetDaemonBusCallPolicy(send=%s)", sender->GetUniqueName().c_str()));
    DaemonBusCallPolicy policy = STDBUSCALL_ALLOW_ACCESS_SERVICE_ANY;
    if (enableRestrict) {
        if (sender->GetEndpointType() == ENDPOINT_TYPE_NULL || sender->GetEndpointType() == ENDPOINT_TYPE_LOCAL) {
            policy = STDBUSCALL_ALLOW_ACCESS_SERVICE_ANY;
        } else if (sender->GetEndpointType() == ENDPOINT_TYPE_REMOTE) {
            RemoteEndpoint rEndpoint = RemoteEndpoint::cast(sender);
            QCC_DbgPrintf(("This is a RemoteEndpoint. ConnSpec = %s", rEndpoint->GetConnectSpec().c_str()));

            if ((rEndpoint->GetConnectSpec() == "unix") || (rEndpoint->GetConnectSpec() == "localhost") || (rEndpoint->GetConnectSpec() == "slap")) {
                policy = STDBUSCALL_ALLOW_ACCESS_SERVICE_ANY;
            } else if (rEndpoint->GetConnectSpec() == "tcp") {
                if (!rEndpoint->IsTrusted()) {
                    policy = STDBUSCALL_ALLOW_ACCESS_SERVICE_LOCAL;
                } else {
                    policy = STDBUSCALL_ALLOW_ACCESS_SERVICE_ANY;
                }
            } else {
                policy = STDBUSCALL_SHOULD_REJECT;
                QCC_LogError(ER_FAIL, ("Unrecognized connect spec for endpoint:%s. connectspec=%s", sender->GetUniqueName().c_str(), rEndpoint->GetConnectSpec().c_str()));
            }
        } else if (sender->GetEndpointType() == ENDPOINT_TYPE_BUS2BUS || sender->GetEndpointType() == ENDPOINT_TYPE_VIRTUAL) {
            policy = STDBUSCALL_SHOULD_REJECT;
            QCC_LogError(ER_FAIL, ("Bus-to-bus endpoint(%s) is not ALLOW_ACCESSed to invoke daemon standard method call", sender->GetUniqueName().c_str()));
        } else {
            policy = STDBUSCALL_SHOULD_REJECT;
            QCC_LogError(ER_FAIL, ("Unexpected endponit type(%d)", sender->GetEndpointType()));
        }
    }
    return policy;
}

} // namespace ajn {
