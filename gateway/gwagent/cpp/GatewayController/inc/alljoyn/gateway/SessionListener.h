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

#ifndef SessionListener_H
#define SessionListener_H

#include <alljoyn/SessionListener.h>
#include <alljoyn/SessionPortListener.h>

namespace ajn {
namespace gwc {

class GatewayMgmtApp;

/**
 *  This class is responsible for handling session related events from the AllJoyn system.
 *  Extend this class to receive the events of:
 *      - sessionEstablished
 *      - sessionLost
 *
 *  The events are called on the AllJoyn thread, so avoid blocking them with
 *  long running tasks.
 */
class SessionListener {
  public:

    /**
     * Constructor for SessionListener
     */
    SessionListener() { };

    /**
     * Destructor for SessionListener
     */
    virtual ~SessionListener() { };

    /**
     * sessionEstablished - callback when a session is established with a device
     * @param gatewayMgmtApp - the gateway that the session was established with
     */
    virtual void sessionEstablished(GatewayMgmtApp* gatewayMgmtApp) = 0;

    /**
     * sessionLost - callback when a session is lost with a device
     * @param gatewayMgmtApp - the gateway that the session was lost with
     */
    virtual void sessionLost(GatewayMgmtApp* gatewayMgmtApp) = 0;
};
}
}
#endif /* defined(SessionListener_H) */
