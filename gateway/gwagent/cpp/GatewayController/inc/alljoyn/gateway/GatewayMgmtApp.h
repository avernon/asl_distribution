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

#ifndef GatewayMgmtApp_H
#define GatewayMgmtApp_H

#include <map>
#include <vector>
#include <qcc/String.h>
#include <alljoyn/about/AboutClient.h>
#include <alljoyn/gateway/AnnouncedApp.h>
#include <alljoyn/gateway/ConnectorApp.h>
#include <alljoyn/gateway/SessionListener.h>
#include <alljoyn/gateway/SessionHandler.h>
#include <alljoyn/about/AboutClient.h>


namespace ajn {
namespace gwc {
typedef  struct  {
    /**
     * Status of joining session
     */
    QStatus m_status;

    /**
     * Session id
     */
    int m_sid;

} SessionResult;

class GatewayMgmtApp : public AnnouncedApp {
  public:

    /**
     * Constructor
     */
    GatewayMgmtApp() : AnnouncedApp(), m_SessionHandler(NULL) { }

    /**
     * init
     * @param busName The name of the {@link BusAttachment} of the gateway management app that sent
     * the Announcement
     * @param aboutData The data sent with the Announcement
     * @return {@link QStatus}
     */
    QStatus init(const qcc::String& gwBusName, ajn::services::AboutClient::AboutData const& aboutData);

    /**
     * Destructor
     */
    virtual ~GatewayMgmtApp();

    /**
     * Retrieve the list of applications installed on the gateway identified by the given gwBusName
     * @param sessionId The id of the session established with the gateway
     * @param connectorApps A reference to a vector of {@link ConnectorApp} objects
     * @return {@link QStatus}
     */
    QStatus retrieveConnectorApps(SessionId sessionId, std::vector<ConnectorApp*>& connectorApps);


    /**
     * Join session synchronously with the given gateway identified by the gwBusName.
     * This method doesn't require {@link SessionListener}. Use this method
     * when there is no need to receive any session related event.
     * @param gwBusName The bus name of the gateway to connect to.
     * @return {@link SessionResult}
     */
    SessionResult joinSession();

    /**
     * Join session synchronously with the given gateway identified by the gwBusName.
     * The session related events will be sent to the given listener.
     * @param gwBusName The bus name of the gateway to connect to.
     * @param listener The listener is used to be notified about the session related events
     * @return {@link SessionResult}
     */
    SessionResult joinSession(SessionListener*listener);

    /**
     * Join session asynchronously with the given gwBusName.
     * @param listener The listener is used to be notified about the session related events
     * @return {@link QStatus}
     */
    QStatus joinSessionAsync(SessionListener*listener);

    /**
     * Disconnect the given session
     * @return Returns the leave session {@link QStatus}
     */
    QStatus leaveSession();


    /**
     * Get the Listener defined for this SessionHandler
     * @return {@link SessionListener}
     */
    SessionListener* getListener() const;




    /**
     * release allocations and empty object. must be called before deletion of object.
     * @return {@link QStatus}
     */
    QStatus release();

  private:

    void emptyVector();

    std::vector<ConnectorApp*> m_InstalledApps;

    SessionHandler m_SessionHandler;

    SessionListener*m_Listener;
};
}
}
#endif /* defined(GatewayMgmtApp_H) */
