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

#ifndef CONTROLPANELCONTROLLEEUNIT_H_
#define CONTROLPANELCONTROLLEEUNIT_H_

#include <alljoyn/controlpanel/ControlPanel.h>
#include <alljoyn/controlpanel/NotificationAction.h>
#include <alljoyn/controlpanel/HttpControl.h>

namespace ajn {
namespace services {

/**
 * Class that represents a ControlPanel Unit.
 */
class ControlPanelControlleeUnit {
  public:

    /**
     * Constructor of ControlPanelControlleeUnit
     * @param unitName - name of ControlPanelControllee Unit
     */
    ControlPanelControlleeUnit(qcc::String const& unitName);

    /**
     * Destructor of ControlPanelControlleeUnit
     */
    virtual ~ControlPanelControlleeUnit();

    /**
     * Get the UnitName of the ControlPanelControlleeUnit
     * @return unitName
     */
    const qcc::String& getUnitName() const;

    /**
     * Add a ControlPanel to the ControlPanelControlleeUnit
     * @param controlPanel
     * @return status - success/failure
     */
    QStatus addControlPanel(ControlPanel* controlPanel);

    /**
     * Get the ControlPanels of the ControlPanelControlleeUnit
     * @return ControlPanels
     */
    const std::vector<ControlPanel*>& getControlPanels() const;

    /**
     * Add a NotificationAction to the ControlPanelControlleeUnit
     * @param notificationAction
     * @return status - success/failure
     */
    QStatus addNotificationAction(NotificationAction* notificationAction);

    /**
     * Get the NotificationActions of the ControlPanelControlleeUnit
     * @return the NotificationActions
     */
    const std::vector<NotificationAction*>& getNotificationActions() const;

    /**
     * Set the HTTPControl of the ControlPanelControlleeUnit
     * @param httpControl
     * @return status - success/failure
     */
    QStatus setHttpControl(HttpControl* httpControl);

    /**
     * Get the HttpControl of the ControlPanelControlleeUnit
     * @return HttpControl
     */
    const HttpControl* getHttpControl() const;
    /**
     * Register the busObjects of the ControlPanelControlleeUnit
     * @param bus - the bus to register the Objects with
     * @return status - success/failure
     */
    QStatus registerObjects(BusAttachment* bus);

    /**
     * UnRegister the busObjects of the ControlPanelControlleeUnit
     * @param bus - the bus to unregister the Objects with
     * @return status - success/failure
     */
    QStatus unregisterObjects(BusAttachment* bus);

  private:

    /**
     * Name of Unit
     */
    qcc::String m_UnitName;

    /**
     * Vector of ControlPanels implemented by the Controllee
     */
    std::vector<ControlPanel*> m_ControlPanels;

    /**
     * Vector of NotificationActions implemented by the Controllee
     */
    std::vector<NotificationAction*> m_NotificationActions;

    /**
     * The HTTPControl of the Unit
     */
    HttpControl* m_HttpControl;
};

} /* namespace services */
} /* namespace ajn */
#endif /* CONTROLPANELCONTROLLEEUNIT_H_ */
