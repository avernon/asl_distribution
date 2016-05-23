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

#include <alljoyn/controlpanel/ControlPanelControlleeUnit.h>
#include <alljoyn/controlpanel/ControlPanelDevice.h>
#include <alljoyn/controlpanel/ControlPanel.h>
#include <alljoyn/controlpanel/NotificationAction.h>
#include <alljoyn/controlpanel/LanguageSets.h>
#include <alljoyn/controlpanel/ControlPanelService.h>
#include "ControlPanelConstants.h"
#include <alljoyn/controlpanel/LogModule.h>

namespace ajn {
namespace services {
using namespace cpsConsts;

ControlPanelControlleeUnit::ControlPanelControlleeUnit(qcc::String const& unitName) :
    m_UnitName(unitName), m_HttpControl(0)
{
}

ControlPanelControlleeUnit::~ControlPanelControlleeUnit()
{

}

const qcc::String& ControlPanelControlleeUnit::getUnitName() const
{
    return m_UnitName;
}

QStatus ControlPanelControlleeUnit::addControlPanel(ControlPanel* controlPanel)
{
    if (!controlPanel) {
        QCC_DbgHLPrintf(("Could not add a NULL controlPanel"));
        return ER_BAD_ARG_1;
    }

    m_ControlPanels.push_back(controlPanel);
    return ER_OK;
}

const std::vector<ControlPanel*>& ControlPanelControlleeUnit::getControlPanels() const
{
    return m_ControlPanels;
}

QStatus ControlPanelControlleeUnit::addNotificationAction(NotificationAction* notificationAction)
{
    if (!notificationAction) {
        QCC_DbgHLPrintf(("Could not add a NULL notificationAction"));
        return ER_BAD_ARG_1;
    }

    m_NotificationActions.push_back(notificationAction);
    return ER_OK;
}

const std::vector<NotificationAction*>& ControlPanelControlleeUnit::getNotificationActions() const
{
    return m_NotificationActions;
}

QStatus ControlPanelControlleeUnit::setHttpControl(HttpControl* httpControl)
{
    if (!httpControl) {
        QCC_DbgHLPrintf(("Could not add a NULL httpControl"));
        return ER_BAD_ARG_1;
    }

    if (m_HttpControl) {
        QCC_DbgHLPrintf(("Could not set httpControl. HttpControl already set"));
        return ER_BUS_PROPERTY_ALREADY_EXISTS;
    }

    m_HttpControl = httpControl;
    return ER_OK;
}

const HttpControl* ControlPanelControlleeUnit::getHttpControl() const
{
    return m_HttpControl;
}

QStatus ControlPanelControlleeUnit::registerObjects(BusAttachment* bus)
{
    QStatus status = ER_OK;

    if (m_HttpControl) {
        status = m_HttpControl->registerObjects(bus, m_UnitName);
        if (status != ER_OK) {
            QCC_LogError(status, ("Could not register the HttpControl"));
            return status;
        }
    }

    for (size_t indx = 0; indx < m_ControlPanels.size(); indx++) {
        status = m_ControlPanels[indx]->registerObjects(bus, m_UnitName);
        if (status != ER_OK) {
            QCC_LogError(status, ("Could not register Objects for the ControlPanels"));
            return status;
        }
    }

    for (size_t indx = 0; indx < m_NotificationActions.size(); indx++) {
        status = m_NotificationActions[indx]->registerObjects(bus, m_UnitName);
        if (status != ER_OK) {
            QCC_LogError(status, ("Could not register Objects for the ControlPanels"));
            return status;
        }
    }
    return status;
}

QStatus ControlPanelControlleeUnit::unregisterObjects(BusAttachment* bus)
{
    QStatus returnStatus = ER_OK;

    if (m_HttpControl) {
        QStatus status = m_HttpControl->unregisterObjects(bus);
        if (status != ER_OK) {
            QCC_LogError(status, ("Could not unregister the HttpControl"));
            returnStatus = status;
        }
    }

    for (size_t indx = 0; indx < m_ControlPanels.size(); indx++) {
        QStatus status = m_ControlPanels[indx]->unregisterObjects(bus);
        if (status != ER_OK) {
            QCC_LogError(status, ("Could not register Objects for the ControlPanels"));
            returnStatus = status;
        }
    }

    for (size_t indx = 0; indx < m_NotificationActions.size(); indx++) {
        QStatus status = m_NotificationActions[indx]->unregisterObjects(bus);
        if (status != ER_OK) {
            QCC_LogError(status, ("Could not register Objects for the ControlPanels"));
            returnStatus = status;
        }
    }
    return returnStatus;
}

} /* namespace services */
} /* namespace ajn */

