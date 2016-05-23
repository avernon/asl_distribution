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
#import "LSFSDKController.h"
#import "model/LSFControllerModel.h"

@class LSFSDKControllerErrorEvent;

/**
 * Provides an interface for developers to implement and receive all controller related events in the
 * Lighting system. Developers will be notified when a new controller becomes the leader on the network
 * and when there are any controller related errors.
 *
 * **Note:** Once implemented, the delegate must be registered with the LSFSDKLightingDirector in order
 * to receive Controller callbacks. See [LSFSDKLightingDirector addControllerDelegate:] for more information.
 */
@protocol LSFSDKControllerDelegate <LSFSDKLightingDelegate>

/**
 * Triggered when a new controller becomes the leader in the Lighting system.
 *
 * @param leader Reference to new lead controller
 */
-(void)onLeaderChange: (LSFSDKController *)leader;

/**
 * Triggered when an error occurs on a controller operation.
 *
 * @param errorEvent Reference to LSFSDKControllerErrorEvent
 */
-(void)onControllerError: (LSFSDKControllerErrorEvent *)errorEvent;

@end
