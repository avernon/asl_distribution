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
#include <alljoyn/AboutData.h>
#include <alljoyn/AboutListener.h>
#include <alljoyn/AboutObj.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/ProxyBusObject.h>
#include <alljoyn/BusObject.h>
#include <alljoyn/DBusStd.h>
#include <alljoyn/AllJoynStd.h>
#include <alljoyn/SessionPortListener.h>
#include <alljoyn/SessionListener.h>
#include <qcc/String.h>
#include <stdio.h>
#include <qcc/platform.h>

#include "../SimpleRuleEngine.h"
#include "OptParser.h"
#include "RuleBusObject.h"

#ifndef _MY_ALLJOYN_CODE_
#define _MY_ALLJOYN_CODE_

class MyAllJoynCode;

class MyAllJoynCode :
    public ajn::AboutListener,
    public ajn::SessionPortListener,
    public ajn::SessionListener {
  public:
    /**
     * Construct a MyAllJoynCode object
     *
     */
    MyAllJoynCode()
        : aboutData(), aboutObj(NULL), mBusAttachment(NULL), ruleEngine(), ruleBusObject(NULL)
    { };

    /**
     * Destructor
     */
    ~MyAllJoynCode() {
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
     * Free up and release the objects used
     */
    void shutdown();

  private:

    /* From About */
    void Announced(const char* busName, uint16_t version, ajn::SessionPort port, const ajn::MsgArg& objectDescriptionArg, const ajn::MsgArg& aboutDataArg);

    /* From SessionPortListener */
    virtual bool AcceptSessionJoiner(ajn::SessionPort sessionPort, const char* joiner, const ajn::SessionOpts& opts);

    virtual void SessionJoined(ajn::SessionPort sessionPort, ajn::SessionId id, const char* joiner);

    /* From SessionListener */
    virtual void SessionLost(ajn::SessionId sessionId);

    virtual void SessionMemberAdded(ajn::SessionId sessionId, const char*uniqueName);

    virtual void SessionMemberRemoved(ajn::SessionId sessionId, const char*uniqueName);

    char HexToChar(char c);

    void HexStringToBytes(const qcc::String& hex, uint8_t* outBytes, size_t len);

  private:
    std::map<qcc::String, qcc::String> mBusFriendlyMap;

    ajn::AboutData aboutData;
    ajn::AboutObj* aboutObj;
    ajn::BusAttachment* mBusAttachment;

    SimpleRuleEngine ruleEngine;
    RuleBusObject* ruleBusObject;
};

#endif //_MY_ALLJOYN_CODE_
