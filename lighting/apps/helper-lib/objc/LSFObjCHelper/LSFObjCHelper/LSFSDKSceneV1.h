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

#import "LSFSDKScene.h"
#import "LSFSDKPreset.h"
#import "LSFSDKGroup.h"
#import "model/LSFSceneDataModel.h"

/**
 * This class represents a SceneV1 definition in the lighting controller. SceneV1s are only
 * relevant in pre 15.04 controllers. This class provides an interface to perform SceneV1
 * operations. Supported operations include renaming, applying, and deleting the SceneV1.
 *
 * @warning This class is not meant to be instantiated directly. SceneV1s should be retrieved
 * from the LightingDirector using the [LSFSDKLightingDirector scenes] method.
 *
 * @warning This class does not support SceneV1 creation. SceneV1s must already exist on the
 * lighting controller.
 */
@interface LSFSDKSceneV1 : LSFSDKScene
{
    @protected LSFSceneDataModel *sceneModel;
}

/** @name Initializing an LSFSDKSceneV1 Object */

/**
 * @warning This method is not intended to be used by clients, and may change or be
 * removed in subsequent releases of the SDK.
 */
-(instancetype)init NS_UNAVAILABLE;

/** @name Finding Objects in a SceneV1 */

/**
 * Tests to see if the current LSFSDKSceneV1 contains the provided LSFSDKPreset.
 *
 * @param preset The LSFSDKPreset to be confirmed a component of the LSFSDKSceneV1
 *
 * @return Returns true if the LSFSDKSceneV1 contains the LSFSDKPreset, false otherwise
 */
-(BOOL)hasPreset: (LSFSDKPreset *)preset;

/**
 * Tests to see if the current LSFSDKSceneV1 contains the provided LSFSDKGroup.
 *
 * @param group The LSFSDKGroup to be confirmed a component of the LSFSDKSceneV1
 *
 * @return Returns true if the LSFSDKSceneV1 contains the LSFSDKGroup, false otherwise
 */
-(BOOL)hasGroup: (LSFSDKGroup *)group;

/** @name Protected methods */

/**
 * @warning This method is not intended to be used by clients, and may change or be
 * removed in subsequent releases of the SDK.
 *
 * @param presetID  The ID of the preset
 */
-(BOOL)hasPresetWithID: (NSString *)presetID;

/**
 * @warning This method is not intended to be used by clients, and may change or be
 * removed in subsequent releases of the SDK.
 *
 * @param groupID  The ID of the group
 */
-(BOOL)hasGroupWithID: (NSString *)groupID;

/**
 * @warning This method is not intended to be used by clients, and may change or be
 * removed in subsequent releases of the SDK.
 */
-(LSFSceneDataModel *)getSceneDataModel;

@end
