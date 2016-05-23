/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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

#ifndef GATEWAYCTRLSESSIONHANDLER_H_
#define GATEWAYCTRLSESSIONHANDLER_H_

#include <alljoyn/BusAttachment.h>
#include <alljoyn/SessionListener.h>

namespace ajn {
namespace gwc {

class GatewayMgmtApp;

/**
 * class SessionHandler
 */
class SessionHandler : public ajn::BusAttachment::JoinSessionAsyncCB, public ajn::SessionListener {
  public:

    /**
     * Constructor for SessionHandler
     */
    SessionHandler(GatewayMgmtApp* gateway);

    /**
     * Destructor for SessionHandler
     */
    virtual ~SessionHandler();

    /**
     * SessionLost called when a session is lost
     * @param sessionId - the session Id of the lost session
     */
    void SessionLost(ajn::SessionId sessionId);


    /**
     * Called when JoinSessionAsync() completes.
     *
     * @param status       ER_OK if successful
     * @param sessionId    Unique identifier for session.
     * @param opts         Session options.
     * @param context      User defined context which will be passed as-is to callback.
     */
    void JoinSessionCB(QStatus status, ajn::SessionId id, const ajn::SessionOpts& opts, void* context);

    /**
     * getSessionId
     * @return SessionId
     */
    ajn::SessionId getSessionId() const;

  private:

    /**
     * SessionId for this Device
     */
    ajn::SessionId m_SessionId;

    /**
     * The device of this Session Handler
     */
    GatewayMgmtApp* m_Gateway;

};

}     /* namespace gwc */
} /* namespace ajn */

#endif /* GATEWAYCTRLSESSIONHANDLER_H_ */
