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

#import "alljoyn/controlpanel/ControlPanelListener.h"
#import "AJCPSControlPanelListener.h"
#import "alljoyn/about/AJNConvertUtil.h"

#ifndef ALLJOYN_CONTROLPANEL_OBJC_AJCPSCONTROLPANELLISTENERADAPTER_H
#define ALLJOYN_CONTROLPANEL_OBJC_AJCPSCONTROLPANELLISTENERADAPTER_H

using namespace ajn::services;

class AJCPSControlPanelListenerAdapter : public ajn::services::ControlPanelListener
{
public:
    id<AJCPSControlPanelListener> listener;

    
    AJCPSControlPanelListenerAdapter(id<AJCPSControlPanelListener> listener) { this->listener = listener;}
    
    id<AJCPSControlPanelListener> getListener() {return this->listener;}
    
    /**
     * sessionEstablished - callback when a session is established with a device
     * @param device - the device that the session was established with
     */
    virtual void sessionEstablished(ControlPanelDevice* device) { [listener sessionEstablished:[[AJCPSControlPanelDevice alloc]initWithHandle:device]];}
    
    /**
     * sessionLost - callback when a session is lost with a device
     * @param device - device that the session was lost with
     */
    virtual void sessionLost(ControlPanelDevice* device) { [listener sessionLost:[[AJCPSControlPanelDevice alloc]initWithHandle:device]];}
    
    /**
     * signalPropertiesChanged - callback when a property Changed signal is received
     * @param device - device signal was received from
     * @param widget - widget signal was received for
     */
    virtual void signalPropertiesChanged(ControlPanelDevice* device, Widget* widget) {

        AJCPSWidget *new_widget = [[AJCPSWidget alloc]initWithHandle:widget];
        
        [listener signalPropertiesChanged:[[AJCPSControlPanelDevice alloc]initWithHandle:device]
                        widget:new_widget];
    }
    
    /**
     * signalPropertyValueChanged - callback when a property Value Changed signal is received
     * @param device - device signal was received from
     * @param property - Property signal was received for
     */
    virtual void signalPropertyValueChanged(ControlPanelDevice* device, Property* property)
    {
        AJCPSControlPanelDevice *qcp_device = [[AJCPSControlPanelDevice alloc]initWithHandle:device];
        
        AJCPSProperty *qcp_property = [[AJCPSProperty alloc]initWithHandle:property];
        
        [listener signalPropertyValueChanged:qcp_device property:qcp_property];
    }
    
    /**
     * signalDismiss - callback when a Dismiss signal is received
     * @param device - device signal was received from
     * @param notificationAction - notificationAction signal was received for
     */
    virtual void signalDismiss(ControlPanelDevice* device, NotificationAction* notificationAction)
    {
        AJCPSControlPanelDevice *qcp_device = [[AJCPSControlPanelDevice alloc]initWithHandle:device];
        
        AJCPSNotificationAction *qcp_notification_action = [[AJCPSNotificationAction alloc]initWithHandle:notificationAction];
        
        [listener signalDismiss:qcp_device notificationAction:qcp_notification_action];
    }
    
    /**
     * ErrorOccured - callback to tell application when something goes wrong
     * @param device - device  that had the error
     * @param status - status associated with error if applicable
     * @param transaction - the type of transaction that resulted in the error
     * @param errorMessage - a log-able error Message
     */
    virtual void errorOccured(ControlPanelDevice* device, QStatus status, ControlPanelTransaction transaction, qcc::String const& errorMessage)
    {
        AJCPSControlPanelDevice *qcp_device = [[AJCPSControlPanelDevice alloc]initWithHandle:device];
        
        AJCPSControlPanelTransaction qcp_controlpanel_transaction = transaction;
        
        NSString *qcp_error_message = [AJNConvertUtil convertQCCStringtoNSString:errorMessage];
        
        [listener errorOccured:qcp_device status:status transaction:qcp_controlpanel_transaction errorMessage:qcp_error_message];
    }

    virtual ~AJCPSControlPanelListenerAdapter() { };
    
    private:
        
};


#endif //ALLJOYN_CONTROLPANEL_OBJC_AJCPSCONTROLPANELLISTENERADAPTER_H
