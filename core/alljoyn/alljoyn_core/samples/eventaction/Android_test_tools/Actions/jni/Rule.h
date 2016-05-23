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

#ifndef _RULE_
#define _RULE_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/ProxyBusObject.h>
#include <alljoyn/Session.h>
#include <qcc/String.h>
#include "RuleInfo.h"
#include <qcc/Mutex.h>

class Rule : public ajn::SessionListener, public ajn::MessageReceiver {
  public:
    Rule(ajn::BusAttachment* bus, RuleInfo* event, RuleInfo* action)
        : mBus(bus), mEvent(event), mAction(action), eventMember(NULL), mSessionId(0), actionObject(NULL), mLock()
    { };

    virtual ~Rule();

    QStatus enable();
    QStatus disable();

    qcc::String toString() {
        qcc::String ret = "";
        ret.append(mEvent->toString());
        ret.append("|");
        ret.append(mAction->toString());
        return ret;
    }

    uint8_t actionReady() {
        return mAction->mPort != 0;
    }

    uint8_t eventReady() {
        return mEvent->mPort != 0;
    }

    const char* getActionSessionName() { return mAction->mUniqueName.c_str(); }
    const char* getEventSessionName() { return mEvent->mUniqueName.c_str(); }

    uint8_t isEventMatch(qcc::String deviceId, qcc::String appId) {
        return mEvent->mDeviceId.compare(deviceId) == 0 && mEvent->mAppId.compare(appId) == 0;
    }

    uint8_t isActionMatch(qcc::String deviceId, qcc::String appId) {
        return mAction->mDeviceId.compare(deviceId) == 0 && mAction->mAppId.compare(appId) == 0;
    }

    void setActionPort(short port) { mAction->mPort = port; }
    void setEventPort(short port) { mEvent->mPort = port; }

    void addToEvent(qcc::String deviceId, qcc::String appId) { mEvent->setSenderInfo(deviceId, appId); }
    void addToAction(qcc::String deviceId, qcc::String appId) { mAction->setSenderInfo(deviceId, appId); }

    void modifyEventSessionName(const char*sessionName);
    void modifyActionSessionName(const char*sessionName);


  private:

    /* From SessionListener */
    virtual void SessionLost(ajn::SessionId sessionId);

    virtual void SessionMemberAdded(ajn::SessionId sessionId, const char*uniqueName);

    virtual void SessionMemberRemoved(ajn::SessionId sessionId, const char*uniqueName);

    void EventHandler(const ajn::InterfaceDescription::Member* member, const char* srcPath, ajn::Message& msg);

    void callAction();
    void AsyncCallReplyHandler(ajn::Message& msg, void* context);

    const ajn::InterfaceDescription::Member* eventMember;
    ajn::SessionId mSessionId;
    ajn::ProxyBusObject* actionObject;

    ajn::BusAttachment*mBus;

    RuleInfo* mEvent;
    RuleInfo* mAction;
    qcc::Mutex mLock;
};

#endif //_RULE_

