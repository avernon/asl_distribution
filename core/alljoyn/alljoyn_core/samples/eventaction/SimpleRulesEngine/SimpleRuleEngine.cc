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

#include "SimpleRuleEngine.h"

using namespace std;
using namespace ajn;
using namespace qcc;

QStatus SimpleRuleEngine::initialize(const char* engineName, BusAttachment* bus)
{
    QCC_UNUSED(engineName);
    QCC_UNUSED(bus);
    QStatus status = ER_OK;
    mRulePersister.loadRules();
    return status;
}

QStatus SimpleRuleEngine::addRule(Rule* rule, bool persist)
{
    QStatus status = ER_OK;
    if (rule->actionReady() == 0) {
        rule->setActionPort(mNearbyAppMap[rule->getActionSessionName()]->port);
        rule->addToAction(mNearbyAppMap[rule->getActionSessionName()]->deviceId, mNearbyAppMap[rule->getActionSessionName()]->appId);
    }
    if (rule->eventReady() == 0) {
        if (mNearbyAppMap[rule->getEventSessionName()] != NULL) {
            rule->setEventPort(mNearbyAppMap[rule->getEventSessionName()]->port);
            rule->addToEvent(mNearbyAppMap[rule->getEventSessionName()]->deviceId, mNearbyAppMap[rule->getEventSessionName()]->appId);
        }
    }
    rule->enable();
    mRules.push_back(rule);
    if (persist) {
        mRulePersister.saveRule(rule);
    }
    return status;
}

QStatus SimpleRuleEngine::removeRule(Rule* rule)
{
    QCC_UNUSED(rule);
    QStatus status = ER_OK;

    return status;
}

QStatus SimpleRuleEngine::removeAllRules()
{
    QStatus status = ER_OK;
    for (std::vector<Rule*>::iterator it = mRules.begin(); it != mRules.end(); ++it) {
        (*it)->disable();
        delete (*it);
    }
    mRules.clear();
    mRulePersister.clearRules();
    return status;
}

Rule* SimpleRuleEngine::getRules(size_t& len)
{
    QCC_UNUSED(len);
    return NULL;
}

QStatus SimpleRuleEngine::shutdown()
{
    QStatus status = ER_OK;

    return status;
}

void SimpleRuleEngine::Announce(const char* busName, uint16_t version,
                                SessionPort port, const MsgArg& objectDescriptionArg,
                                const MsgArg& aboutDataArg)
{
    QCC_UNUSED(version);
    QCC_UNUSED(objectDescriptionArg);
    NearbyAppInfo* nearbyAppInfo = new NearbyAppInfo();
    AboutData aboutData(aboutDataArg);
    char* deviceName;
    aboutData.GetDeviceName(&deviceName);
    nearbyAppInfo->friendlyName = deviceName;
    char* deviceId;
    aboutData.GetDeviceId(&deviceId);
    nearbyAppInfo->deviceId = deviceId;

    uint8_t* appIdBuffer;
    size_t numElements;
    aboutData.GetAppId(&appIdBuffer, &numElements);
    char temp[(numElements + 1) * 2];               //*2 due to hex format
    for (size_t i = 0; i < numElements; i++) {
        sprintf(temp + (i * 2), "%02x", appIdBuffer[i]);
    }
    temp[numElements * 2] = '\0';
    nearbyAppInfo->appId = temp;

    nearbyAppInfo->port = port;
    mNearbyAppMap.insert(std::pair<qcc::String, NearbyAppInfo*>(busName, nearbyAppInfo));

    //Search rules for a deviceId and appId that matches, if so update sessionName with busName
    for (std::vector<Rule*>::iterator it = mRules.begin(); it != mRules.end(); ++it) {
        if ((*it)->isEventMatch(nearbyAppInfo->deviceId, nearbyAppInfo->appId)) {
            (*it)->modifyEventSessionName(busName);
        }
        if ((*it)->isActionMatch(nearbyAppInfo->deviceId, nearbyAppInfo->appId)) {
            (*it)->modifyActionSessionName(busName);
        }
    }
}


