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
#include "PermissionMgr.h"
#include <alljoyn/AllJoynStd.h>

#define QCC_MODULE "PERMISSION_MGR"

namespace ajn {

QStatus TransportPermission::FilterTransports(BusEndpoint& srcEp, const qcc::String& sender, TransportMask& transports, const char* callerName)
{
    QCC_UNUSED(srcEp);
    QCC_UNUSED(sender);
    QCC_UNUSED(transports);
    QCC_UNUSED(callerName);
    return ER_OK;
}

uint32_t PermissionMgr::AddAliasUnixUser(BusEndpoint& srcEp, qcc::String& sender, uint32_t origUID, uint32_t aliasUID)
{
    QCC_UNUSED(srcEp);
    QCC_UNUSED(sender);
    QCC_UNUSED(origUID);
    QCC_UNUSED(aliasUID);
    return ALLJOYN_ALIASUNIXUSER_REPLY_NO_SUPPORT;
}

QStatus PermissionMgr::CleanPermissionCache(BusEndpoint& endpoint)
{
    QCC_UNUSED(endpoint);
    return ER_OK;
}

} // namespace ajn {
