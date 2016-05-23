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
#import "LSFSDKLightingItem.h"
#import "LSFSDKEffect.h"
#import "LSFSDKGroupMember.h"
#import "LSFSDKDeletableItem.h"
#import "LSFSDKLamp.h"
#import "LSFSDKGroup.h"
#import "model/LSFSceneElementDataModelV2.h"

/**
 * This class represents a SceneElement definition in the lighting controller. This class
 * provides an interface to perform SceneElement operations. Supported operations include
 * modifying the scene element members and effect, applying the scene element, renaming, and
 * deleting the scene element. Scene elements encapsulate an effect and a set of lamps and/or
 * groups. Scene elements apply their effect to their lamps and groups. Scene elements are
 * considered fully initialized when the name, lamp and group members, and the effect have been
 * received. Scene elements are still operational and can still be applied even in the
 * uninitialized state.
 *
 * @warning This class is not meant to be instantiated directly. SceneElements should be retrieved
 * from the LSFSDKLightingDirector using the [LSFSDKLightingDirector sceneElements] method.
 *
 * @warning This class does not support SceneElement creation. See [LSFSDKLightingDirector createSceneElementWithEffect:groupMembers:name:].
 */
@interface LSFSDKSceneElement : LSFSDKLightingItem<LSFSDKDeletableItem>
{
    @protected LSFSceneElementDataModelV2 *sceneElementModel;
}

/** @name Initializing an LSFSDKSceneElement Object */

/**
 * @warning This method is not intended to be used by clients, and may change or be
 * removed in subsequent releases of the SDK.
 */
-(instancetype)init NS_UNAVAILABLE;

/** @name Scene Element Operations */

/**
 * Applies the current LSFSDKSceneElement in the Lighting system.
 */
-(void)apply;

/**
 * Modifies the Effect and GroupMembers of the current LSFSDKSceneElement using the provided parameters
 *
 * @param effect The new Effect.
 * @param members The new GroupMembers.
 */
-(void)modifyWithEffect: (id<LSFSDKEffect>)effect groupMembers: (NSArray *)members;

/**
 * Adds a member to the current LSFSDKSceneElement.
 *
 * @param member The GroupMember object to be added to the LSFSDKSceneElement
 */
-(void)addMember: (LSFSDKGroupMember *)member;

/**
 * Removes a member from the current LSFSDKSceneElement.
 *
 * @param member The GroupMember object to be removed from the LSFSDKSceneElement
 */
-(void)removeMember: (LSFSDKGroupMember *)member;

/** @name Finding Objects in a Scene Element */

/**
 * Tests to see if the current LSFSDKSceneElement contains the specified Lamp.
 *
 * @param lamp The Lamp to be confirmed a component of the LSFSDKSceneElement.
 *
 * @return Return true if the LSFSDKSceneElement contains Lamp, false otherwise.
 */
-(BOOL)hasLamp: (LSFSDKLamp *)lamp;

/**
 * Tests to see if the current LSFSDKSceneElement contains the specified Group.
 *
 * @param group The Group to be confirmed a component of the LSFSDKSceneElement.
 *
 * @return Return true if the LSFSDKSceneElement contains Group, false otherwise.
 */
-(BOOL)hasGroup: (LSFSDKGroup *)group;

/**
 * Tests to see if the current LSFSDKSceneElement contains the specified Effect.
 *
 * @param effect The Effect to be confirmed a component of the LSFSDKSceneElement.
 *
 * @return Return true if the LSFSDKSceneElement contains Effect, false otherwise.
 */
-(BOOL)hasEffect: (id<LSFSDKEffect>)effect;

/** @name Querying a Scene Element */

/**
 * Returns the Lamps associated with the current LSFSDKSceneElement.
 *
 * @return Arrays of Lamps associated with the LSFSDKSceneElement
 */
-(NSArray *)getLamps;

/**
 * Returns the Groups associated with the current LSFSDKSceneElement.
 *
 * @return Arrays of Groups associated with the LSFSDKSceneElement
 */
-(NSArray *)getGroups;

/**
 * Returns the effect associated with the current LSFSDKSceneElement.
 *
 * @return Reference to Effect
 */
-(id<LSFSDKEffect>)getEffect;

/** @name Protected methods */

/**
 * @warning This method is not intended to be used by clients, and may change or be
 * removed in subsequent releases of the SDK.
 *
 * @param lampID  The ID of the lamp
 */
-(BOOL)hasLampWithID: (NSString *)lampID;

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
 *
 * @param effectID  The ID of the effect
 */
-(BOOL)hasEffectWithID: (NSString *)effectID;

/**
 * @warning This method is not intended to be used by clients, and may change or be
 * removed in subsequent releases of the SDK.
 */
-(LSFSceneElementDataModelV2 *)getSceneElementDataModel;

@end
