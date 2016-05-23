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

#include <alljoyn/gateway/RuleObjectDescription.h>
#include <alljoyn/gateway/LogModule.h>


namespace ajn {
namespace gwc {

RuleInterface::RuleInterface(const qcc::String& name, const qcc::String& friendlyName, bool isSecured) : m_Name(name), m_FriendlyName(friendlyName), m_IsSecured(isSecured)
{
}

const qcc::String& RuleInterface::getName() const
{
    return m_Name;
}

const qcc::String& RuleInterface::getFriendlyName() const
{
    return m_FriendlyName;
}

bool RuleInterface::isSecured() const
{
    return m_IsSecured;
}

bool RuleInterface::operator<(const RuleInterface to) const
{
    const bool ALessThanB = getName().operator<(to.getName());

    return ALessThanB;
}


RuleObjectPath::RuleObjectPath(const qcc::String& objectPath, const qcc::String& friendlyName, bool isPrefix, bool isPrefixAllowed) : m_ObjectPath(objectPath), m_FriendlyName(friendlyName), m_IsPrefix(isPrefix), m_isPrefixAllowed(isPrefixAllowed)
{
}

RuleObjectPath::~RuleObjectPath()
{
}

const qcc::String& RuleObjectPath::getPath() const
{
    return m_ObjectPath;
}

const qcc::String& RuleObjectPath::getFriendlyName()
{
    return m_FriendlyName;
}

bool RuleObjectPath::isPrefix() const
{
    return m_IsPrefix;
}

void RuleObjectPath::setPrefix(bool isPrefix)
{
    m_IsPrefix = isPrefix;
}

bool RuleObjectPath::isPrefixAllowed() const {
    return m_isPrefixAllowed;
}

void RuleObjectPath::setPrefixAllowed(bool isPrefixAllowed) {
    m_isPrefixAllowed = isPrefixAllowed;
}

RuleObjectDescription::RuleObjectDescription(const RuleObjectPath& objectPath, std::set<RuleInterface> interfaces) : m_IsConfigured(false), m_Interfaces(interfaces)
{
    m_ObjectPath = new RuleObjectPath(objectPath);
}

RuleObjectDescription::RuleObjectDescription(const RuleObjectPath& objectPath, std::set<RuleInterface> interfaces, bool isConfigured) : m_IsConfigured(isConfigured), m_Interfaces(interfaces)
{
    m_ObjectPath = new RuleObjectPath(objectPath);
}

RuleObjectDescription::~RuleObjectDescription()
{

}

RuleObjectPath* RuleObjectDescription::getObjectPath() const
{
    return m_ObjectPath;
}

const std::set<RuleInterface>* RuleObjectDescription::getInterfaces() const
{
    return &m_Interfaces;
}

bool RuleObjectDescription::isConfigured() const
{
    return m_IsConfigured;

}

void RuleObjectDescription::setConfigured(bool configured)
{
    m_IsConfigured = configured;

}



QStatus RuleObjectDescription::release()
{
    if (m_ObjectPath) {
        delete m_ObjectPath;
        m_ObjectPath = NULL;
    }
    return ER_OK;
}
}
}
