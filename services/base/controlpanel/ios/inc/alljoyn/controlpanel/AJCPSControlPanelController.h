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

#import <Foundation/Foundation.h>
#import "alljoyn/controlpanel/ControlPanelController.h"
#import "AJCPSControlPanelDevice.h"

/**
 * AJCPSControlPanelController facilitated controlling of remote ControlPanels
 */
@interface AJCPSControlPanelController : NSObject

- (id)init;

- (id)initWithHandle:(ajn::services::ControlPanelController *)handle;

/**
 * create a controllable device by parsing announce descriptions.
 * @param deviceBusName - BusName of device received in announce
 * @param objectDescs - ObjectDescriptions received in announce
 * @return a ControlPanelDevice
 */
- (AJCPSControlPanelDevice *)createControllableDevice:(NSString *)deviceBusName ObjectDescs:(NSDictionary *)objectDescs;

/**
 * GetControllableDevice - get a device using the busName - creates it if it doesn't exist
 * @param deviceBusName - deviceName to get
 * @return ControlPanelDevice* - returns the Device
 */
- (AJCPSControlPanelDevice *)getControllableDevice:(NSString *)deviceBusName;

/**
 * deleteControllableDevice - shutdown a controllable device and delete it from the Controller
 * @param deviceBusName - deviceName to delete
 * @return status - success-failure
 */
- (QStatus)deleteControllableDevice:(NSString *)deviceBusName;

/**
 * deleteAllControllableDevices - shutdown and delete all controllable devices from the controller
 * @return status - success-failure
 */
- (QStatus)deleteAllControllableDevices;

/**
 * Get map of All Controllable Devices
 * @return controllable Devices map const std::map<qcc::String, ControlPanelDevice*>&
 */
- (NSDictionary *)getControllableDevices;

@property (nonatomic, readonly)ajn::services::ControlPanelController * handle;

@end