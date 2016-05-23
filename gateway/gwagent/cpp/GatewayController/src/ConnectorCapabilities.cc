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

#include <alljoyn/gateway/ConnectorCapabilities.h>
#include <alljoyn/gateway/LogModule.h>

#include "PayloadAdapter.h"

namespace ajn {
namespace gwc {



QStatus ConnectorCapabilities::init(const ajn::MsgArg*manifRulesAJ)
{
    QStatus status;

    status = PayloadAdapter::FillRuleObjectDescriptionVector(&manifRulesAJ[0], m_ExposedServices);

    if (status != ER_OK) {
        QCC_LogError(status, ("Filling m_ExposedServices failed"));
        return status;
    }

    status = PayloadAdapter::FillRuleObjectDescriptionVector(&manifRulesAJ[1], m_RemotedServices);

    if (status != ER_OK) {
        QCC_LogError(status, ("Filling m_RemotedServices failed"));
        return status;
    }

    return ER_OK;
}

ConnectorCapabilities::~ConnectorCapabilities()
{

}

const std::vector<RuleObjectDescription*>& ConnectorCapabilities::getExposedServices() const
{
    return m_ExposedServices;
}

const std::vector<RuleObjectDescription*>& ConnectorCapabilities::getRemotedServices() const
{
    return m_RemotedServices;
}


void ConnectorCapabilities::emptyVectors()
{
    for (size_t indx = 0; indx < m_ExposedServices.size(); indx++) {
        QStatus status = m_ExposedServices[indx]->release();

        if (status != ER_OK) {
            QCC_LogError(status, ("Could not release object"));
        }
        delete m_ExposedServices[indx];
    }

    m_ExposedServices.clear();


    for (size_t indx = 0; indx < m_RemotedServices.size(); indx++) {
        QStatus status = m_RemotedServices[indx]->release();

        if (status != ER_OK) {
            QCC_LogError(status, ("Could not release object"));
        }
        delete m_RemotedServices[indx];
        m_RemotedServices[indx] = NULL;
    }

    m_RemotedServices.clear();

}


QStatus ConnectorCapabilities::release()
{
    emptyVectors();

    return ER_OK;
}
}
}