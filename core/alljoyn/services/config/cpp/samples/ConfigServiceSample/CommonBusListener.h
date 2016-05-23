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

#ifndef COMMONBUSLISTENER_H_
#define COMMONBUSLISTENER_H_

#include <alljoyn/BusAttachment.h>
#include <alljoyn/BusListener.h>
#include <alljoyn/SessionPortListener.h>
#include <vector>

#if defined(QCC_OS_GROUP_WINDOWS)
/* Disabling warning C 4100. Function doesnt use all passed in parameters */
#pragma warning(push)
#pragma warning(disable: 4100)
#endif

/**
 * class CommonBusListener
 */
class CommonBusListener : public ajn::BusListener, public ajn::SessionPortListener, public ajn::SessionListener {

  public:

    /**
     * Constructor of CommonBusListener
     * @param bus - used to set a session Listener
     * @param daemonDisconnectCB - used to set a callback for when the daemon is disconnected
     */
    CommonBusListener(ajn::BusAttachment* bus = NULL, void(*daemonDisconnectCB)() = NULL);

    /**
     * Destructor of CommonBusListener
     */
    ~CommonBusListener();

    /**
     * AcceptSessionJoiner - Receive request to join session and decide whether to accept it or not
     * @param sessionPort - the port of the request
     * @param joiner - the name of the joiner
     * @param opts - the session options
     * @return true/false
     */
    bool AcceptSessionJoiner(ajn::SessionPort sessionPort, const char* joiner, const ajn::SessionOpts& opts);

    /**
     * Set the Value of the SessionPort associated with this SessionPortListener
     * @param sessionPort
     */
    void setSessionPort(ajn::SessionPort sessionPort);

    /**
     * Callback when Session is joined
     * @param sessionPort - port of session
     * @param id - sessionId of session
     * @param joiner - name of joiner
     */
    void SessionJoined(ajn::SessionPort sessionPort, ajn::SessionId id, const char* joiner);

    /**
     * Callback for when Session is lost
     * @param sessionId
     * @param reason for session lost
     */
    void SessionLost(ajn::SessionId sessionId, SessionLostReason reason);

    /**
     * Get the SessionPort of the listener
     * @return
     */
    ajn::SessionPort getSessionPort();

    /**
     * Get the SessionIds associated with this Listener
     * @return vector of sessionIds
     */
    const std::vector<ajn::SessionId>& getSessionIds() const;

    /**
     * Function when Bus has been disconnected
     */
    void BusDisconnected();

  private:

    /**
     * The port used as part of the join session request
     */
    ajn::SessionPort m_SessionPort;

    /**
     * The busAttachment to use
     */
    ajn::BusAttachment* m_Bus;

    /**
     * The sessionIds for the port
     */
    std::vector<ajn::SessionId> m_SessionIds;

    /**
     * Callback when daemon is disconnected
     */
    void (*m_DaemonDisconnectCB)();

};

#endif /* COMMONBUSLISTENER_H_ */
