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

#include <alljoyn/gateway/GatewayAclRules.h>

namespace ajn {
namespace gw {
using namespace qcc;

GatewayAclRules::GatewayAclRules()
{

}

GatewayAclRules::~GatewayAclRules() {

}

const GatewayRuleObjectDescriptions& GatewayAclRules::getExposedServicesRules() const
{
    return m_ExposedServicesRules;
}

void GatewayAclRules::setExposedServicesRules(const GatewayRuleObjectDescriptions& exposedServicesRules)
{
    m_ExposedServicesRules = exposedServicesRules;
}

const GatewayRemoteAppRules& GatewayAclRules::getRemoteAppRules() const
{
    return m_RemoteAppRules;
}

void GatewayAclRules::setRemoteAppRules(const GatewayRemoteAppRules& remoteAppRules)
{
    m_RemoteAppRules = remoteAppRules;
}

} /* namespace gw */
} /* namespace ajn */
