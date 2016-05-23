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

#import <Foundation/Foundation.h>
#import "alljoyn/Status.h"
#import "AJNSessionOptions.h"
#import "alljoyn/controlpanel/ControlPanelDevice.h"
#import "AJCPSControlPanelControllerUnit.h"
#import "AJCPSNotificationAction.h"
#import "AJCPSControlPanelListener.h"

/**
 * AJCPSControlPanelDevice
 */
@interface AJCPSControlPanelDevice : NSObject
/**
 * Constructor for ControlPanelDevice
 * @param handle handle to the instance
 */
- (id)initWithHandle:(ajn ::services ::ControlPanelDevice *)handle;

/**
 * startSessionAsync - start a session with Device Asynchronously
 * @return status - success/failure
 */
- (QStatus)startSessionAsync;

/**
 * startSession - start session with device synchronously
 * @return status - success/failure
 */
- (QStatus)startSession;

/**
 * endSession - endSession with device
 * @return status - success/failure
 */
- (QStatus)endSession;

/**
 * ShutDown device - end Session and release units
 * @return status - success/failure
 */
- (QStatus)shutdownDevice;

/**
 * getDeviceBusName - get the busName of the device
 * @return deviceBusName - busName of device
 */
- (NSString *)getDeviceBusName;

/**
 * getSessionId - get the SessionId of the remote Session with device
 * @return const ajn::SessionId
 */
- (AJNSessionId)getSessionId;

/**
 * getDeviceUnits
 * @return the ControlPanelUnits of this Device
 */
// const std::map<qcc::String, ControlPanelControllerUnit*>& getDeviceUnits const;

- (NSDictionary *)getDeviceUnits;

/**
 * getAllControlPanels - returns an array with all controlPanels contained by this device
 * @return an array with all the controlPanel defined as children of this device
 */
- (NSArray *)getAllControlPanels;

/**
 * Get an existing unit using the objectPath
 * @param objectPath - objectPath of unit
 * @return ControlPanelUnit pointer
 */
- (AJCPSControlPanelControllerUnit *)getControlPanelUnit:(NSString *)objectPath;

/**
 * addControlPanelUnit - add a ControlPanel unit using the objectPath and interfaces passed in
 * @param objectPath - objectPath received in the announce
 * @param interfaces - interfaces received in the announce
 * @return ControlPanelUnit pointer
 */

- (AJCPSControlPanelControllerUnit *)addControlPanelUnit:(NSString *)objectPath interfaces:(NSArray *)interfaces;

/**
 * addNotificationAction - add a Notification using an objectPath received in a notification
 * @param objectPath - objectPath used to create the NotificationAction
 * @return NotificationAction pointer
 */
- (AJCPSNotificationAction *)addNotificationAction:(NSString *)objectPath;

/**
 * Delete and shutdown the NotificationAction
 * @param notificationAction - notificationAction to remove
 * @return status - success/failure
 */
- (QStatus)removeNotificationAction:(AJCPSNotificationAction *)notificationAction;

/**
 * Get the Listener defined for this SessionHandler
 * @return
 */
- (id <AJCPSControlPanelListener> )getListener;

/**
 * Set the Listener defined for this SessionHandler
 * @param listener AJCPSControlPanelListener that will receive session/signal events notifications.
 * @return status - success/failure
 */
- (QStatus)setListener:(id <AJCPSControlPanelListener> )listener;

@property (nonatomic, readonly)ajn::services::ControlPanelDevice * handle;

@end