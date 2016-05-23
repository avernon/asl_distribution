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

#import "LSFSDKLightingItem.h"
#import "LSFSDKScene.h"
#import "model/LSFMasterSceneDataModel.h"

/**
 * This class represents an LSFSDKMasterScene definition in the lighting controller. This class
 * provides an interface to perform LSFSDKMasterScene operations. Supported operations include
 * adding and removing scene members, renaming, applying and deleting the LSFSDKMasterScene.
 * Master scenes contain an array of scenes and allow them to be applied simultaneously.
 * Master scenes are considered fully initialized when the name and array of scenes have
 * been received. Master scenes are still operational and can still be applied even in the
 * uninitialized state.
 *
 * @warning This class is not meant to be instantiated directly. MasterScenes should be retrieved
 * from the LSFSDKLightingDirector using the [LSFSDKLightingDirector masterScenes] method.
 *
 * @warning This class does not support MasterScene creation. See [LSFSDKLightingDirector createMasterSceneWithScenes:name:].
 */
@interface LSFSDKMasterScene : LSFSDKLightingItem
{
    @protected LSFMasterSceneDataModel *masterSceneDataModel;
}

/** @name Initializing an LSFSDKMasterScene Object */

/**
 * @warning This method is not intended to be used by clients, and may change or be
 * removed in subsequent releases of the SDK.
 */
-(instancetype)init NS_UNAVAILABLE;

/** @name Master Scene Operations */

/**
 * Applies the current LSFSDKMasterScene in the Lighting system.
 */
-(void)apply;

/**
 * Modifies the current LSFSDKMasterScene with the provided array of Scenes.
 *
 * @param scenes  The array of new Scenes
 */
-(void)modify: (NSArray *)scenes;

/**
 * Adds a Scene to the current LSFSDKMasterScene.
 *
 * @param scene  The Scene to be added
 */
-(void)add: (LSFSDKScene *)scene;

/**
 * Removes a Scene from the current LSFSDKMasterScene
 *
 * @param scene  The Scene to be removed
 */
-(void)remove: (LSFSDKScene *)scene;

/**
 * Permanently deletes the current LSFSDKMasterScene from the lighting controller.
 */
-(void)deleteItem;

/** @name Querying a Master Scene */

/**
 * Returns all the Scenes associated with the LSFSDKMasterScene.
 *
 * @return Array of Scenes in the Master Scene
 */
-(NSArray *)getScenes;

/** Finding Objects in a Master Scene */

/**
 * Tests to see if the current LSFSDKMasterScene contains the provided LSFSDKScene.
 *
 * @param scene  LSFSDKScene to be confirmed present in the LSFSDKMasterScene
 *
 * @return Returns true if the LSFSDKMasterScene contains LSFSDKScene, false otherwise
 */
-(BOOL)hasScene: (LSFSDKScene *)scene;

/** @name Protected methods */

/**
 * @warning This method is not intended to be used by clients, and may change or be
 * removed in subsequent releases of the SDK.
 *
 * @param sceneID  The ID of the Scene
 */
-(BOOL)hasSceneWithID: (NSString *)sceneID;

/**
 * @warning This method is not intended to be used by clients, and may change or be
 * removed in subsequent releases of the SDK.
 */
-(LSFMasterSceneDataModel *)getMasterSceneDataModel;

@end
