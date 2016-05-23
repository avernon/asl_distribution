/******************************************************************************
 * Copyright (c) 2013 - 2014, AllSeen Alliance. All rights reserved.
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

#ifndef CONTROLPANELCONTROLLEE_H_
#define CONTROLPANELCONTROLLEE_H_

#include <alljoyn/controlpanel/ControlPanelControlleeUnit.h>

namespace ajn {
namespace services {

/**
 * ControlPanelControllee Class.
 * Allows creation of a controllee to be controller by a controller
 * Made up of ControlPanels and/or NotificationWithActions and possibly
 * a HTTPControl
 */
class ControlPanelControllee {
  public:

    /**
     * Constructor of ControlPanelControllee
     */
    ControlPanelControllee();

    /**
     * Destructor of ControlPanelControllee
     */
    virtual ~ControlPanelControllee();

    /**
     * Add a ControlPanelUnit to the ControlPanelControllee
     * @param unit - unit to add
     * @return status - success/failure
     */
    QStatus addControlPanelUnit(ControlPanelControlleeUnit* unit);

    /**
     * Register the busObjects of the ControlPanelControllee
     * @param bus - the bus to register the Objects with
     * @return status - success/failure
     */
    QStatus registerObjects(BusAttachment* bus);

    /**
     * Unregister the busObjects of the ControlPanelControllee
     * @param bus - the bus to unregister the Objects with
     * @return status - success/failure
     */
    QStatus unregisterObjects(BusAttachment* bus);

    /**
     * Get the Units of the Controllee
     * @return the Controllee Units
     */
    const std::vector<ControlPanelControlleeUnit*>& getControlleeUnits() const;

  private:

    /**
     * Vector containing the Devices Units
     */
    std::vector<ControlPanelControlleeUnit*> m_Units;
};

} /* namespace services */
} /* namespace ajn */
#endif /* CONTROLPANELCONTROLLEE_H_ */
