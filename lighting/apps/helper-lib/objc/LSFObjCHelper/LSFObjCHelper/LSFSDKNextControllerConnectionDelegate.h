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

/**
 * Provides an interface for developers to implement and receive a callback when a connection is
 * established with a LSFSDKLightingController.
 *
 * **Note:** Once implemented, the delegate must be registered with the LSFSDKLightingDirector in order
 * to receive a connection callback. See [LSFSDKLightingDirector postOnNextControllerConnectionWithDelay:delegate:]
 * for more information.
 */
@protocol LSFSDKNextControllerConnectionDelegate <NSObject>

/**
 * Triggered when a connection to a LSFSDKLightingController has been established.
 *
 * @warning This delegate will fire only once when a controller connection is established. This
 * delegate must be reregistered if the controller connection is lost.
 */
-(void)onNextControllerConnection;

@end
