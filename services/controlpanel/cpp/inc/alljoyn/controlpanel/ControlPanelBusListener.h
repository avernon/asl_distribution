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

#ifndef CONTROLPANELBUSLISTENER_H_
#define CONTROLPANELBUSLISTENER_H_

#include <alljoyn/BusListener.h>
#include <alljoyn/SessionPortListener.h>
#include <vector>

namespace ajn {
namespace services {

/**
 * Class that implements BusListener, SessionPortListener and SessionListener
 */
class ControlPanelBusListener : public BusListener, public SessionPortListener,
    public SessionListener {

  public:

    /**
     * Constructor of ControlPanelBusListener
     */
    ControlPanelBusListener();

    /**
     * Destructor of ControlPanelBusListener
     */
    ~ControlPanelBusListener();

    /**
     * Set the Value of the SessionPort associated with this SessionPortListener
     * @param sessionPort
     */
    void setSessionPort(SessionPort sessionPort);

    /**
     * Get the SessionPort of the listener
     * @return
     */
    SessionPort getSessionPort();

    /**
     * AcceptSessionJoiner - Receive request to join session and decide whether to accept it or not
     * @param sessionPort - the port of the request
     * @param joiner - the name of the joiner
     * @param opts - the session options
     * @return true/false
     */
    bool AcceptSessionJoiner(SessionPort sessionPort, const char* joiner, const SessionOpts& opts);

    /**
     * SessionJoined
     * @param sessionPort
     * @param sessionId
     * @param joiner
     */
    void SessionJoined(SessionPort sessionPort, SessionId sessionId, const char* joiner);

    /**
     * SessionMemberAdded
     * @param sessionId
     * @param uniqueName
     */
    void SessionMemberAdded(SessionId sessionId, const char* uniqueName);

    /**
     * SessionMemberRemoved
     * @param sessionId
     * @param uniqueName
     */
    void SessionMemberRemoved(SessionId sessionId, const char* uniqueName);

    /**
     * SessionLost
     * @param sessionId
     * @param reason
     */
    void SessionLost(SessionId sessionId, SessionLostReason reason);

    /**
     * Get the SessionIds associated with this Listener
     * @return vector of sessionIds
     */
    const std::vector<SessionId>& getSessionIds() const;

  private:

    /**
     * The port used as part of the join session request
     */
    SessionPort m_SessionPort;

    /**
     * The sessionIds for the port
     */
    std::vector<SessionId> m_SessionIds;
};
}
}

#endif /* CONTROLPANELBUSLISTENER_H_ */
