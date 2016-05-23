/**
 * @file
 * This class is to manage the permission of an endpoint on using transports or invoking method/signal calls on another peer.
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
#ifndef _PERMISSION_MGR_H
#define _PERMISSION_MGR_H

#include "LocalTransport.h"
#include "TransportList.h"
#include <qcc/ThreadPool.h>

namespace ajn {

#define MAX_PERM_CHECKEDCALL_SIZE (512)

class TransportPermission {
  public:
    /**
     * Filter out transports that the endpoint has no permissions to use
     * @param   srcEp         The source endpoint
     * @param   sender        The sender's well-known name string
     * @param   transports    The transport mask
     * @param   callerName    The caller that invokes this method
     */
    static QStatus FilterTransports(BusEndpoint& srcEp, const qcc::String& sender, TransportMask& transports, const char* callerName);
};

class PermissionMgr {
  public:
    /**
     * Add an alias ID to a UnixEndpoint User ID
     * @param srcEp     The source endpoint
     * @param origUID   The unique User ID
     * @param aliasUID  The alias User ID
     */
    static uint32_t AddAliasUnixUser(BusEndpoint& srcEp, qcc::String& sender, uint32_t origUID, uint32_t aliasUID);

    /**
     * Cleanup the permission information cache of an enpoint before it exits.
     */
    static QStatus CleanPermissionCache(BusEndpoint& endpoint);

};

} // namespace ajn

#endif //_PERMISSION_MGR_H
