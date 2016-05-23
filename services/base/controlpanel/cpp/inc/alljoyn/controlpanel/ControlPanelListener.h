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


#ifndef CONTROLPANELLISTENER_H_
#define CONTROLPANELLISTENER_H_

#include <alljoyn/controlpanel/ControlPanelDevice.h>
#include <alljoyn/controlpanel/Property.h>

namespace ajn {
namespace services {

/**
 * An Abstract class with function receive. The implementation of this class
 * can be passed in to the initReceive function and will be the callback for
 * when notifications are received
 */
class ControlPanelListener {
  public:

    /**
     * Constructor for ControlPanelListener
     */
    ControlPanelListener() { };

    /**
     * Destructor for ControlPanelListener
     */
    virtual ~ControlPanelListener() { };

    /**
     * sessionEstablished - callback when a session is established with a device
     * @param device - the device that the session was established with
     */
    virtual void sessionEstablished(ControlPanelDevice* device) = 0;

    /**
     * sessionLost - callback when a session is lost with a device
     * @param device - device that the session was lost with
     */
    virtual void sessionLost(ControlPanelDevice* device) = 0;

    /**
     * signalPropertiesChanged - callback when a property Changed signal is received
     * @param device - device signal was received from
     * @param widget - widget signal was received for
     */
    virtual void signalPropertiesChanged(ControlPanelDevice* device, Widget* widget) = 0;

    /**
     * signalPropertyValueChanged - callback when a property Value Changed signal is received
     * @param device - device signal was received from
     * @param property - Property signal was received for
     */
    virtual void signalPropertyValueChanged(ControlPanelDevice* device, Property* property) = 0;

    /**
     * signalDismiss - callback when a Dismiss signal is received
     * @param device - device signal was received from
     * @param notificationAction - notificationAction signal was received for
     */
    virtual void signalDismiss(ControlPanelDevice* device, NotificationAction* notificationAction) = 0;

    /**
     * ErrorOccured - callback to tell application when something goes wrong
     * @param device - device  that had the error
     * @param status - status associated with error if applicable
     * @param transaction - the type of transaction that resulted in the error
     * @param errorMessage - a log-able error Message
     */
    virtual void errorOccured(ControlPanelDevice* device, QStatus status, ControlPanelTransaction transaction, qcc::String const& errorMessage) = 0;
};
} //namespace services
} //namespace ajn

#endif /* CONTROLPANELLISTENER_H_ */


