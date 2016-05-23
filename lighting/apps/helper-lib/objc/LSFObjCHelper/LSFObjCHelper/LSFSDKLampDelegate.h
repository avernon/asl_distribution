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
#import "listener/LSFSDKLightingDelegate.h"
#import "LSFSDKTrackingID.h"

@class LSFSDKLamp;
@class LSFSDKLightingItemErrorEvent;

/**
 * Provides an interface for developers to implement and receive all lamp related events in the
 * Lighting system. Developers will be notified when lamps are found, modified, initialized, and
 * lost from the lighting controller. Lamps are considered initialized when all lamp data has
 * been received from the lighting controller.
 *
 * **Note:** Once implemented, the delegate must be registered with the LSFSDKLightingDirector in order
 * to receive Lamp callbacks. See [LSFSDKLightingDirector addLampDelegate:] for more information.
 */
@protocol LSFSDKLampDelegate <LSFSDKLightingDelegate>

/**
 * Triggered when all data has been received from the lighting controller for a
 * particular LSFSDKLamp.
 *
 * @warning This callback will fire only once for each LSFSDKLamp when all data has been received from
 * the lighting controller.
 *
 * @param lamp Reference to LSFSDKLamp
 */
-(void)onLampInitialized: (LSFSDKLamp *)lamp;

/**
 * Triggered every time new data is received from the lighting controller for a
 * particular LSFSDKLamp.
 *
 * @param lamp Reference to LSFSDKLamp
 */
-(void)onLampChanged: (LSFSDKLamp *)lamp;

/**
 * Triggered when a particular LSFSDKLamp has been lost from the lighting controller.
 *
 * @warning This callback will fire only once for each LSFSDKLamp when it is lost from
 * the lighting controller.
 *
 * @param lamp Reference to LSFSDKLamp
 */
-(void)onLampRemoved: (LSFSDKLamp *)lamp;

/**
 * Triggered when an error occurs on a LSFSDKLamp operation.
 *
 * @param error Reference to LSFSDKLightingItemErrorEvent
 */
-(void)onLampError: (LSFSDKLightingItemErrorEvent *)error;

@end
