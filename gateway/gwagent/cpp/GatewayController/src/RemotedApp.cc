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

#include <alljoyn/gateway/RemotedApp.h>
#include <alljoyn/gateway/LogModule.h>
#include <qcc/StringUtil.h>

#include "PayloadAdapter.h"
#include "Constants.h"

namespace ajn {
namespace gwc {

using namespace gwcConsts;

QStatus RemotedApp::init(const qcc::String& busUniqueName, const qcc::String& appName, uint8_t*appId, const qcc::String& deviceName, const qcc::String& deviceId, const std::vector<RuleObjectDescription*>& ruleObjDescriptions)
{
    m_RuleObjDescriptions = ruleObjDescriptions;

    setAppId(appId, UUID_LENGTH);
    setBusName(busUniqueName);
    setAppName(appName);
    setDeviceId(deviceId);
    setDeviceName(deviceName);

    return ER_OK;
}

QStatus RemotedApp::init(ajn::services::AboutClient::AboutData const& aboutData, const std::vector<RuleObjectDescription*>& ruleObjDescriptions)
{
    m_RuleObjDescriptions = ruleObjDescriptions;

    return AnnouncedApp::init("", aboutData);
}

QStatus RemotedApp::init(const ajn::MsgArg*remotedAppInfo, const std::vector<RuleObjectDescription*>& ruleObjDescriptions, const std::map<qcc::String, qcc::String>& internalMetadata)
{
    char*DeviceId;
    const ajn::MsgArg* ObjDescRulesArray;
    size_t ObjDescRulesCount;

    uint8_t* AppIdBuffer;
    size_t len;

    QStatus status = remotedAppInfo->Get("(saya(obas))", &DeviceId, &len, &AppIdBuffer, &ObjDescRulesCount, &ObjDescRulesArray);
    if (status != ER_OK) {
        QCC_LogError(status, ("Failed getting interface object"));
        return status;
    }

    setDeviceId(DeviceId);

    setAppId(AppIdBuffer, len);

    qcc::String AppId;

    AppId = qcc::BytesToHexString(AppIdBuffer, len);

    qcc::String keyPrefix = getDeviceId() + "_" + AppId;

    qcc::String key =  keyPrefix + AJSUFFIX_APP_NAME;

    std::map<qcc::String, qcc::String>::const_iterator itr = internalMetadata.find(key);

    if (itr != internalMetadata.end()) {
        setAppName(itr->second);
    }


    key = keyPrefix + AJSUFFIX_DEVICE_NAME;

    itr = internalMetadata.find(key);

    if (itr != internalMetadata.end()) {
        setDeviceName(itr->second);
    }

    for (size_t i = 0; i != ObjDescRulesCount; i++) {

        RuleObjectDescription* objDescRule = PayloadAdapter::unmarshalObjectDescriptionsWithoutNames(&ObjDescRulesArray[i], ruleObjDescriptions, status);
        if (status != ER_OK) {
            QCC_LogError(status, ("unmarshalObjectDesciptionsWithoutNames failed"));
            return status;
        }

        m_RuleObjDescriptions.push_back(objDescRule);
    }

    return ER_OK;
}


QStatus RemotedApp::init(AnnouncedApp* announcedApp, const std::vector<RuleObjectDescription*>& ruleObjDescriptions)
{
    m_RuleObjDescriptions = ruleObjDescriptions;

    AnnouncedApp::init(announcedApp->getBusName(),
                       announcedApp->getAppName(),
                       announcedApp->getAppId(),
                       announcedApp->getAppIdLength(),
                       announcedApp->getDeviceName(),
                       announcedApp->getDeviceId());

    return ER_OK;
}

RemotedApp::~RemotedApp()
{

}

const std::vector<RuleObjectDescription*>& RemotedApp::getRuleObjDesciptions()        {
    return m_RuleObjDescriptions;
}

void RemotedApp::emptyVector()
{
    for (size_t indx = 0; indx < m_RuleObjDescriptions.size(); indx++) {
        QStatus status = m_RuleObjDescriptions[indx]->release();

        if (status != ER_OK) {
            QCC_LogError(status, ("Could not release object"));
        }
        delete m_RuleObjDescriptions[indx];
    }

    m_RuleObjDescriptions.clear();
}


QStatus RemotedApp::release()
{
    emptyVector();

    return ER_OK;

}
}
}
