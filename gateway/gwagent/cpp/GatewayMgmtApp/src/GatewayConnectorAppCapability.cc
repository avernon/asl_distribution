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

#include <alljoyn/gateway/GatewayConnectorAppCapability.h>

namespace ajn {
namespace gw {

GatewayConnectorAppCapability::GatewayConnectorAppCapability() : m_ObjectPath(""), m_ObjectPathFriendlyName(""), m_IsObjectPathPrefix(false)
{

}

GatewayConnectorAppCapability::GatewayConnectorAppCapability(qcc::String const& objectPath, qcc::String const& objectPathFriendly, bool isPrefix,
                                                             std::vector<InterfaceDesc> const& interfaces) : m_ObjectPath(objectPath),
    m_ObjectPathFriendlyName(objectPathFriendly), m_IsObjectPathPrefix(isPrefix), m_Interfaces(interfaces)
{

}

GatewayConnectorAppCapability::~GatewayConnectorAppCapability()
{
}

const qcc::String& GatewayConnectorAppCapability::getObjectPath() const
{
    return m_ObjectPath;
}

const qcc::String& GatewayConnectorAppCapability::getObjectPathFriendlyName() const
{
    return m_ObjectPathFriendlyName;
}

bool GatewayConnectorAppCapability::getIsObjectPathPrefix() const {
    return m_IsObjectPathPrefix;
}

const std::vector<GatewayConnectorAppCapability::InterfaceDesc>& GatewayConnectorAppCapability::getInterfaces() const
{
    return m_Interfaces;
}

void GatewayConnectorAppCapability::setIsObjectPathPrefix(bool isObjectPathPrefix)
{
    m_IsObjectPathPrefix = isObjectPathPrefix;
}

void GatewayConnectorAppCapability::setInterfaces(const std::vector<InterfaceDesc>& interfaces)
{
    m_Interfaces = interfaces;
}

void GatewayConnectorAppCapability::setObjectPathFriendlyName(const qcc::String& objectPathFriendlyName)
{
    m_ObjectPathFriendlyName = objectPathFriendlyName;
}

void GatewayConnectorAppCapability::setObjectPath(const qcc::String& objectPath)
{
    m_ObjectPath = objectPath;
}

} /* namespace gw */
} /* namespace ajn */
