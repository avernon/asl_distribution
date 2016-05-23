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

#include "RuleBusObject.h"

using namespace std;
using namespace ajn;
using namespace qcc;

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

RuleBusObject::RuleBusObject(BusAttachment* busAttachment, const char* path, SimpleRuleEngine* ruleEngine) : BusObject(path), mBusAttachment(busAttachment), mRuleEngine(ruleEngine)
{
    QStatus status;
    InterfaceDescription* ruleEngineIntf = NULL;
    if (!mBusAttachment->GetInterface("org.allseen.sample.rule.engine")) {
        status = mBusAttachment->CreateInterface("org.allseen.sample.rule.engine", ruleEngineIntf);

        //Add BusMethods
        ruleEngineIntf->AddMethod("addRule", "(sssssssq)(sssssssq)b", "", "event,action,persist", 0);
        ruleEngineIntf->AddMethod("deleteAllRules", "", "", "", 0);

        if (ER_OK == status) {
            ruleEngineIntf->Activate();
        } else {
        }
    }

    /* Add the service interface to this object */
    const InterfaceDescription* ruleEngineTestIntf = mBusAttachment->GetInterface("org.allseen.sample.rule.engine");
    assert(ruleEngineTestIntf);
    AddInterface(*ruleEngineTestIntf, ANNOUNCED);
    const MethodEntry methodEntries[] = {
        { ruleEngineTestIntf->GetMember("addRule"), static_cast<MessageReceiver::MethodHandler>(&RuleBusObject::addRule) },
        { ruleEngineTestIntf->GetMember("deleteAllRules"), static_cast<MessageReceiver::MethodHandler>(&RuleBusObject::deleteAllRules) },
    };
    status = AddMethodHandlers(methodEntries, ARRAY_SIZE(methodEntries));
}

void RuleBusObject::addRule(const InterfaceDescription::Member* member, Message& msg)
{
    QCC_UNUSED(member);
    const ajn::MsgArg* args = 0;
    size_t numArgs = 0;
    msg->GetArgs(numArgs, args);
    if (numArgs == 3) {
        char* eUniqueName;
        char* ePath;
        char* eIface;
        char* eMember;
        char* eSig;
        char* eDeviceId;
        char* eAppId;
        uint16_t ePort;
        args[0].Get("(sssssssq)", &eUniqueName, &ePath, &eIface, &eMember, &eSig, &eDeviceId, &eAppId, &ePort);
        RuleInfo* event = new RuleInfo(eUniqueName, ePath, eIface, eMember, eSig, eDeviceId, eAppId, ePort);

        char* aUniqueName;
        char* aPath;
        char* aIface;
        char* aMember;
        char* aSig;
        char* aDeviceId;
        char* aAppId;
        uint16_t aPort;
        args[1].Get("(sssssssq)", &aUniqueName, &aPath, &aIface, &aMember, &aSig, &aDeviceId, &aAppId, &aPort);
        RuleInfo* action = new RuleInfo(aUniqueName, aPath, aIface, aMember, aSig, aDeviceId, aAppId, aPort);

        Rule* rule = new Rule(mBusAttachment, event, action);
        mBusAttachment->EnableConcurrentCallbacks();
        mRuleEngine->addRule(rule, args[2].v_bool);
        LOGTHIS("Added rule");
    } else {
        LOGTHIS("Incorrect number of args!");
    }
    QStatus status = MethodReply(msg);
    if (ER_OK != status) {
        printf("addRule: Error sending reply.\n");
    }
}

void RuleBusObject::deleteAllRules(const InterfaceDescription::Member* member, Message& msg)
{
    QCC_UNUSED(member);
    LOGTHIS("Removing all rules");
    mBusAttachment->EnableConcurrentCallbacks();
    mRuleEngine->removeAllRules();
    QStatus status = MethodReply(msg);
    if (ER_OK != status) {
        printf("addRule: Error sending reply.\n");
    }
}
