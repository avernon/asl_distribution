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

@class LSFSDKMasterScene;
@class LSFSDKLightingItemErrorEvent;

/**
 * Provides an interface for developers to implement and receive all master scene related events in the
 * Lighting system. Developers will be notified when master scenes are added, modified, initialized, and
 * deleted from the lighting controller. Master scenes are considered initialized when all master scene
 * data has been received from the lighting controller.
 *
 * **Note:** Once implemented, the delegate must be registered with the LSFSDKLightingDirector in order
 * to receive MasterScene callbacks. See [LSFSDKLightingDirector addMasterSceneDelegate:] for more information.
 */
@protocol LSFSDKMasterSceneDelegate <LSFSDKLightingDelegate>

/**
 * Triggered when all data has been received from the lighting controller for a particular LSFSDKMasterScene.
 *
 * @warning This callback will fire only once for each LSFSDKMasterScene when all data has been received from
 * the lighting controller.
 *
 * @warning The tracking ID is only valid for master scenes created within your application.
 *
 * @param trackingID  Reference to LSFSDKTrackingID
 * @param masterScene  Reference to LSFSDKMasterScene
 */
-(void)onMasterSceneInitializedWithTrackingID: (LSFSDKTrackingID *)trackingID andMasterScene: (LSFSDKMasterScene *)masterScene;

/**
 * Triggered every time new data is received from the lighting controller for a particular LSFSDKMasterScene.
 *
 * @param masterScene  Reference to LSFSDKMasterScene
 */
-(void)onMasterSceneChanged: (LSFSDKMasterScene *)masterScene;

/**
 * Triggered when a particular LSFSDKMasterScene has been deleted from the lighting controller.
 *
 * @warning This callback will fire only once for each LSFSDKMasterScene when it is deleted from
 * the lighting controller.
 *
 * @param masterScene  Reference to LSFSDKMasterScene
 */
-(void)onMasterSceneRemoved: (LSFSDKMasterScene *)masterScene;

/**
 * Triggered when an error occurs on a LSFSDKMasterScene operation.
 *
 * @param error  Reference to LSFSDKLightingItemErrorEvent
 */
-(void)onMasterSceneError: (LSFSDKLightingItemErrorEvent *)error;

@end
