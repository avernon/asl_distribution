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
#import "LSFSDKMasterSceneDelegate.h"

/**
 * Provides a base class for developers to extend and implement to receive all MasterScene related events in the
 * Lighting system. Any method of the LSFSDKMasterSceneDelegate interface that is not overridden in the subclass will
 * be treated as a no-op.
 *
 * **Note:** Once implemented, the delegate must be registered with the LSDFSDKLightingDirector in order
 * to receive MasterScene callbacks. See [LSFSDKLightingDirector addMasterSceneDelegate:] for more information.
 */
@interface LSFSDKMasterSceneDelegateBase : NSObject <LSFSDKMasterSceneDelegate>

@end
