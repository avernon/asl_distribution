/******************************************************************************
 * Copyright (c) 2013, AllSeen Alliance. All rights reserved.
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

#ifndef CONTROLPANELDEVICE2_H_
#define CONTROLPANELDEVICE2_H_

#include <alljoyn/controlpanel/ControlPanelSessionHandler.h>
#include <alljoyn/controlpanel/ControlPanelControllerUnit.h>
#include <alljoyn/controlpanel/NotificationAction.h>
#include <map>

namespace ajn {
namespace services {

class ControlPanelListener;

/**
 * ControlPanelDevice
 */
class ControlPanelDevice {
  public:

    friend class ControlPanelSessionHandler;

    /**
     * Constructor for ControlPanelDevice
     * @param deviceBusName
     */
    ControlPanelDevice(qcc::String const& deviceBusName);

    /**
     * Destructor for ControlPanelDevice
     */
    virtual ~ControlPanelDevice();

    /**
     * startSessionAsync - start a session with Device Asynchronously
     * @return status - success/failure
     */
    QStatus startSessionAsync();

    /**
     * startSession - start session with device synchronously
     * @return status - success/failure
     */
    QStatus startSession();

    /**
     * endSession - endSession with device
     * @return status - success/failure
     */
    QStatus endSession();

    /**
     * ShutDown device - end Session and release units
     * @return status - success/failure
     */
    QStatus shutdownDevice();

    /**
     * getDeviceBusName - get the busName of the device
     * @return deviceBusName - busName of device
     */
    const qcc::String& getDeviceBusName() const;

    /**
     * getSessionId - get the SessionId of the remote Session with device
     * @return const ajn::SessionId
     */
    const ajn::SessionId getSessionId() const;

    /**
     * getDeviceUnits
     * @return the ControlPanelUnits of this Device
     */
    const std::map<qcc::String, ControlPanelControllerUnit*>& getDeviceUnits() const;

    /**
     * getAllControlPanels - fills the passed in vector with all controlPanels contained by this device
     * @param controlPanelsVec - a vector with all the controlPanel defined as children of this DeviceUnit
     */
    void getAllControlPanels(std::vector<ControlPanel*>& controlPanelsVec);

    /**
     * Get an existing unit using the objectPath
     * @param objectPath - objectPath of unit
     * @return ControlPanelUnit pointer
     */
    ControlPanelControllerUnit* getControlPanelUnit(qcc::String const& objectPath);

    /**
     * addControlPanelUnit - add a ControlPanel unit using the objectPath and interfaces passed in
     * @param objectPath - objectPath received in the announce
     * @param interfaces - interfaces received in the announce
     * @return ControlPanelUnit pointer
     */
    ControlPanelControllerUnit* addControlPanelUnit(qcc::String const& objectPath, std::vector<qcc::String> const& interfaces);

    /**
     * addNotificationAction - add a Notification using an objectPath received in a notification
     * @param objectPath - objectPath used to create the NotificationAction
     * @return NotificationAction pointer
     */
    NotificationAction* addNotificationAction(qcc::String const& objectPath);

    /**
     * Delete and shutdown the NotificationAction
     * @param notificationAction - notificationAction to remove
     * @return status - success/failure
     */
    QStatus removeNotificationAction(NotificationAction* notificationAction);

    /**
     * Get the Listener defined for this SessionHandler
     * @return
     */
    ControlPanelListener* getListener() const;

    /**
     * Set the Listener defined for this SessionHandler
     * @param listener
     * @return status - success/failure
     */
    QStatus setListener(ControlPanelListener* listener);

  private:

    /**
     * Private function to handle a Session being joined with this Device
     */
    void handleSessionJoined();

    /**
     * Parse ObjectPath and create a Control Panel unit using the unitName and panel
     * @param objectPath - objectPath to parse
     * @param unitName - unitname will be filled based on the objectPath
     * @param panel - panel will be filled based on the objectPath
     * @param createIfNotFound - create Unit if it is not found in map
     * @return a ControlPanelUnit
     */
    ControlPanelControllerUnit* getControlPanelUnit(qcc::String const& objectPath, qcc::String& unitName, qcc::String& panel, bool createIfNotFound = true);

    /**
     * The Device's BusName
     */
    qcc::String m_DeviceBusName;

    /**
     * SessionHandler for Device
     */
    ControlPanelSessionHandler m_SessionHandler;

    /**
     * Map containing the Devices Units
     */
    std::map<qcc::String, ControlPanelControllerUnit*> m_DeviceUnits;

    /**
     * Listener - can be used to override the default ControlPanelListener of the Device
     */
    ControlPanelListener* m_Listener;

};

} /* namespace services */
} /* namespace ajn */
#endif /* CONTROLPANELDEVICE2_H_ */
