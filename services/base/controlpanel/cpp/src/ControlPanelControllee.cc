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

#ifdef _WIN32
/* Disable deprecation warnings */
#pragma warning(disable: 4996)
#endif

#include <alljoyn/controlpanel/ControlPanelControllee.h>
#include <alljoyn/controlpanel/ControlPanelService.h>
#include "ControlPanelConstants.h"
#include <alljoyn/controlpanel/LogModule.h>

namespace ajn {
namespace services {
using namespace cpsConsts;

ControlPanelControllee::ControlPanelControllee()
{
}

ControlPanelControllee::~ControlPanelControllee()
{

}

QStatus ControlPanelControllee::registerObjects(BusAttachment* bus)
{
    QStatus status = ER_OK;

    for (size_t indx = 0; indx < m_Units.size(); indx++) {
        status = m_Units[indx]->registerObjects(bus);
        if (status != ER_OK) {
            QCC_LogError(status, ("Could not register Objects for the Units"));
            return status;
        }
    }
    return status;
}

QStatus ControlPanelControllee::unregisterObjects(BusAttachment* bus)
{
    QStatus returnStatus = ER_OK;

    for (size_t indx = 0; indx < m_Units.size(); indx++) {
        QStatus status = m_Units[indx]->unregisterObjects(bus);
        if (status != ER_OK) {
            QCC_LogError(status, ("Could not register Objects for the Units"));
            returnStatus = status;
        }
    }

    return returnStatus;
}

QStatus ControlPanelControllee::addControlPanelUnit(ControlPanelControlleeUnit* unit)
{
    if (!unit) {
        QCC_DbgHLPrintf(("Could not add a NULL unit"));
        return ER_BAD_ARG_1;
    }

    m_Units.push_back(unit);
    return ER_OK;
}

const std::vector<ControlPanelControlleeUnit*>& ControlPanelControllee::getControlleeUnits() const
{
    return m_Units;
}

} /* namespace services */
} /* namespace ajn */
