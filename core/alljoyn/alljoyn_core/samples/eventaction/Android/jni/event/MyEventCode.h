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

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/ProxyBusObject.h>
#include <alljoyn/DBusStd.h>
#include <alljoyn/AllJoynStd.h>
#include <alljoyn/SessionPortListener.h>
#include <alljoyn/SessionListener.h>
#include <alljoyn/Session.h>
#include <qcc/String.h>
#include <stdio.h>
#include <map>
#include <qcc/platform.h>
#include "../Constants.h"
#include "EventInfo.h"
#include "ActionInfo.h"
#include "PresenceDetection.h"

#include <alljoyn/AboutData.h>
#include <alljoyn/AboutListener.h>
#include <alljoyn/AboutObjectDescription.h>
#include <alljoyn/AboutProxy.h>

#ifndef _MY_EVENT_CODE_
#define _MY_EVENT_CODE_

class MyEventCode;

class MyEventCode :
    public ajn::AboutListener,
    public ajn::BusAttachment::JoinSessionAsyncCB,
    public ajn::MessageReceiver,
    public ajn::SessionListener {
  public:
    /**
     * Construct a MyEventCode object
     *
     */
    MyEventCode(JavaVM* vm, jobject jobj)
        : vm(vm), jobj(jobj), mPresenceDetection(NULL), mBusAttachment(NULL)
    { };

    /**
     * Destructor
     */
    virtual ~MyEventCode() {
        shutdown();
    };

    /**
     * Setup AllJoyn, creating the objects needed and registering listeners.
     *
     * @param packageName	This value is provided to the BusAttachment constructor to name the application
     *
     */
    void initialize(const char* packageName);

    /**
     * Join an AllJoyn session.
     *
     * @param sessionName	The busName/Wellknown name to join
     * @param port			The port value that the remote side has bound a session
     *
     */
    void joinSession(const char* sessionName, short port);

    /**
     * Leave an AllJoyn session.
     *
     * @param sessionId	The ID of the session to leave
     *
     */
    void leaveSession(int sessionId);

    /**
     * Perform an IntrospectionWithDescription request over AllJoyn
     *
     * @param sessionName	The busName/Wellknown name to introspect
     * @param path			introspect this specific path
     * @param sessionId		The ID of the session that the is established with sessionName
     *
     *
     */
    char* introspectWithDescriptions(const char* sessionName, const char* path, int sessionId);

    void callAction(ActionInfo* action);

    void InformFound(char* sessionName, int sessionId, char* friendly);

    bool enableEvent(EventInfo* event);

    /**
     * Free up and release the objects used
     */
    void shutdown();

    /* From About */
    void Announced(const char* busName, uint16_t version, ajn::SessionPort port,
                   const ajn::MsgArg& objectDescriptionArg, const ajn::MsgArg& aboutDataArg);

    void EventHandler(const ajn::InterfaceDescription::Member* member, const char* srcPath, ajn::Message& msg);

    /* For MethodCallAsync */
    void AsyncCallReplyHandler(ajn::Message& msg, void* context);

    /* From SessionListener */
    virtual void SessionLost(ajn::SessionId sessionId);

    /** JoinSessionAsync callback */
    virtual void JoinSessionCB(QStatus status, ajn::SessionId sessionId, const ajn::SessionOpts& opts, void* context);

  private:
    JavaVM* vm;
    jobject jobj;

    std::map<qcc::String, qcc::String> mBusFriendlyMap;
    std::map<qcc::String, int> mBusSessionMap;
    std::map<qcc::String, short> mBusPortMap;

    PresenceDetection* mPresenceDetection;
    ajn::BusAttachment* mBusAttachment;
};

#endif //_MY_EVENT_CODE_
