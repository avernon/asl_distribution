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

#include <alljoyn/gateway/GatewayAppIdentifier.h>
#include <qcc/StringUtil.h>

namespace ajn {
namespace gw {

GatewayAppIdentifier::GatewayAppIdentifier(qcc::String const& appId, qcc::String const& deviceId) :
    m_AppId(appId), m_DeviceId(deviceId)
{
    memset(m_AppIdHex, 0, APPID_LENGTH);
    qcc::HexStringToBytes(appId, m_AppIdHex, APPID_LENGTH);
}

GatewayAppIdentifier::GatewayAppIdentifier(uint8_t* appId, size_t appIdLen, qcc::String const& deviceId) :
    m_DeviceId(deviceId)
{
    memset(m_AppIdHex, 0, APPID_LENGTH);
    memcpy(m_AppIdHex, appId, appIdLen > APPID_LENGTH ? APPID_LENGTH : appIdLen);
    m_AppId = qcc::BytesToHexString(appId, APPID_LENGTH);
}

GatewayAppIdentifier::~GatewayAppIdentifier()
{
}

bool GatewayAppIdentifier::operator<(const GatewayAppIdentifier& other) const
{
    if (m_AppId.compare(other.m_AppId) == 0) {
        return (m_DeviceId.compare(other.m_DeviceId) < 0);
    }

    return (m_AppId.compare(other.m_AppId) < 0);
}

bool GatewayAppIdentifier::operator==(const GatewayAppIdentifier& other) const
{
    if (m_AppId.compare(other.m_AppId) != 0) {
        return false;
    }

    return (m_DeviceId.compare(other.m_DeviceId) == 0);
}

const qcc::String& GatewayAppIdentifier::getAppId() const
{
    return m_AppId;
}

const uint8_t* GatewayAppIdentifier::getAppIdHex() const
{
    return m_AppIdHex;
}

const qcc::String& GatewayAppIdentifier::getDeviceId() const
{
    return m_DeviceId;
}

size_t GatewayAppIdentifier::getAppIdHexLength() const
{
    return APPID_LENGTH;
}

} /* namespace gw */
} /* namespace ajn */
