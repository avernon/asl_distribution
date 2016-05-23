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
#import "AJNBusAttachment.h"
#import "alljoyn/controlpanel/ControlPanel.h"
#import "AJCPSLanguageSet.h"
#import "AJCPSControlPanelDevice.h"
#import "AJCPSContainer.h"

/**
 * AJCPSControlPanel Class used to create a ControlPanel.
 * ControlPanels are made up of a LanguageSet and a RootContainer
 */
@interface AJCPSControlPanel : NSObject

- (id)initWithHandle:(ajn ::services ::ControlPanel *)handle;

/**
 * Get the name of the Panel - the name of the rootWidget
 * @return name of the Panel
 */
- (NSString *)getPanelName;

/**
 * Register the BusObjects for this Widget
 * @param bus - bus used to register the busObjects
 * @return status - success/failure
 */
- (QStatus)registerObjects:(AJNBusAttachment *)bus;

/**
 * Unregister the BusObjects for this Widget
 * @param bus - bus used to unregister the busObjects
 * @return status - success/failure
 */
- (QStatus)unregisterObjects:(AJNBusAttachment *)bus;

/**
 * Get the LanguageSet of the ControlPanel
 * @return
 */
- (AJCPSLanguageSet *)getLanguageSet;

/**
 * Get the Device of the ControlPanel
 * @return controlPanelDevice
 */
- (AJCPSControlPanelDevice *)getDevice;

/**
 * Get the objectPath
 * @return
 */
- (NSString *)getObjectPath;

/**
 * Get the RootWidget of the ControlPanel
 * @param Language the language to use for the action can be NULL meaning default.
 * @return pointer to rootWidget
 */
- (AJCPSContainer *)getRootWidget:(NSString *)Language;

@end