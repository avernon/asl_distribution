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

#include <alljoyn/gateway/AnnouncedApp.h>
#include "Constants.h"
#include <alljoyn/gateway/LogModule.h>
#include <qcc/Debug.h>

namespace ajn {
namespace gwc {

using namespace gwcConsts;

QStatus AnnouncedApp::init(const qcc::String& busName, const qcc::String& appName, const uint8_t*appId, uint32_t appIdLength, const qcc::String& deviceName, const qcc::String& deviceId)
{

    if ((busName == qcc::String::Empty) ||
        (appName == qcc::String::Empty) ||
        (deviceName == qcc::String::Empty) ||
        (deviceId == qcc::String::Empty) ||
        (appId == NULL) ||
        (appIdLength == 0)) {
        return ER_FAIL;
    }
    m_AppIdLength = appIdLength;
    m_BusName = busName;
    m_AppName  = appName;
    m_DeviceName = deviceName;
    m_DeviceId = deviceId;
    return setAppId(appId, appIdLength);
}

QStatus AnnouncedApp::init(const qcc::String& busName, ajn::services::AboutClient::AboutData const& aboutData)
{
    ajn::services::AboutClient::AboutData::const_iterator itr = aboutData.find("AppId");

    if (itr == aboutData.end()) {
        QCC_LogError(ER_FAIL, ("AppId missing in about structure, bus name is '%s'", busName.c_str()));
        return ER_FAIL;
    }

    const MsgArg*value = &itr->second;


    uint8_t* appIdBin = NULL;
    size_t len;
    QStatus status = value->Get("ay", &len, &appIdBin);
    if (status != ER_OK) {
        QCC_LogError(status, ("Get appID failed"));
        return status;
    }

    return init(busName, getAboutDataEntry(aboutData, "AppName"), appIdBin, len, getAboutDataEntry(aboutData, "DeviceName"), getAboutDataEntry(aboutData, "DeviceId"));
}


qcc::String AnnouncedApp::getAboutDataEntry(ajn::services::AboutClient::AboutData const& aboutData, const qcc::String& key)
{
    ajn::services::AboutClient::AboutData::const_iterator itr = aboutData.find(key);
    if (itr == aboutData.end()) {
        QCC_LogError(ER_FAIL, ("Called GetAboutDataEntry but couldn't find the key '%s' requested", key.c_str()));
        return "";
    }

    const MsgArg*value = &itr->second;

    if (value->typeId == ALLJOYN_STRING) {
        return value->v_string.str;
    }

    QCC_LogError(ER_FAIL, ("Called GetAboutDataEntry on a key '%s' that is not an ALLJOYN_STRING", key.c_str()));

    return "";
}

/**
 * Destructor
 */
AnnouncedApp::~AnnouncedApp()
{
}

const qcc::String& AnnouncedApp::getBusName() const
{
    return m_BusName;
}


const qcc::String& AnnouncedApp::getAppName() const
{
    return m_AppName;
}

const uint8_t*AnnouncedApp::getAppId() const
{
    return m_AppId;
}

uint32_t AnnouncedApp::getAppIdLength() const
{
    return m_AppIdLength;
}


const qcc::String& AnnouncedApp::getDeviceName() const
{
    return m_DeviceName;
}

const qcc::String& AnnouncedApp::getDeviceId() const
{
    return m_DeviceId;
}

void AnnouncedApp::setBusName(const qcc::String& busName)
{
    m_BusName = busName;
}


void AnnouncedApp::setAppName(const qcc::String& appName)
{
    m_AppName = appName;
}

QStatus AnnouncedApp::setAppId(const uint8_t*appId, size_t len)
{
    if (appId) {
        if (len <= UUID_LENGTH) {

            memcpy(m_AppId, appId, len);
            return ER_OK;
        }
        return ER_BAD_ARG_2;
    }

    return ER_BAD_ARG_1;
}

void AnnouncedApp::setDeviceName(const qcc::String& deviceName)
{
    m_DeviceName = deviceName;
}

void AnnouncedApp::setDeviceId(const qcc::String& deviceId)
{
    m_DeviceId = deviceId;
}
}
}
