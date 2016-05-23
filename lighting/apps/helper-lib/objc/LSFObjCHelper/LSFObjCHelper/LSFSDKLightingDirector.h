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
#import "LSFSDKNextControllerConnectionDelegate.h"
#import "LSFSDKLamp.h"
#import "LSFSDKGroup.h"
#import "LSFSDKPreset.h"
#import "LSFSDKTransitionEffect.h"
#import "LSFSDKPulseEffect.h"
#import "LSFSDKScene.h"
#import "LSFSDKMasterScene.h"
#import "LSFSDKSceneElement.h"
#import "LSFSDKEffect.h"
#import "LSFSDKLampDelegate.h"
#import "LSFSDKGroupDelegate.h"
#import "LSFSDKPresetDelegate.h"
#import "LSFSDKTransitionEffectDelegate.h"
#import "LSFSDKPulseEffectDelegate.h"
#import "LSFSDKSceneElementDelegate.h"
#import "LSFSDKSceneDelegate.h"
#import "LSFSDKMasterSceneDelegate.h"
#import "LSFSDKControllerDelegate.h"
#import "LSFSDKTrackingID.h"
#import "LSFSDKController.h"
#import "manager/LSFSDKLightingSystemManager.h"
#import <alljoyn/BusAttachment.h>

#ifdef __aarch64__
#define ARCH_STR @"64-bit"
#else
#define ARCH_STR @"32-bit"
#endif

/**
 * LSFSDKLightingDirector is the main entry point to the Lighting SDK and provides access to the
 * components in the Lighting system. This includes the lamps connected to the lighting controller
 * and all group, preset, effect, and scene definitions stored in the lighting controller. The
 * LSFSDKLightingDirector also provides an interface to create groups, presets, effects, and scenes as
 * well as add/remove callbacks that will be notified when events occur in the Lighting system.
 *
 * Please see the LSFTutorial project for an example of how to use the LightingDirector class.
 *
 * @warning The LightingController requires a WiFi or Ethernet network connection.
 */
@interface LSFSDKLightingDirector : NSObject
{
    @protected LSFSDKLightingSystemManager *lightingManager;
}

/** @name Class Properties */

/**
 * Readonly peopert that specifies the minimum hue
 */
@property (nonatomic, readonly) int HUE_MIN;

/**
 * Readonly peopert that specifies the maximum hue
 */
@property (nonatomic, readonly) int HUE_MAX;

/**
 * Readonly peopert that specifies the minimum saturation
 */
@property (nonatomic, readonly) int SATURATION_MIN;

/**
 * Readonly peopert that specifies the maximum saturation
 */
@property (nonatomic, readonly) int SATURATION_MAX;

/**
 * Readonly peopert that specifies the minimum brightness
 */
@property (nonatomic, readonly) int BRIGHTNESS_MIN;

/**
 * Readonly peopert that specifies the maximum brightness
 */
@property (nonatomic, readonly) int BRIGHTNESS_MAX;

/**
 * Readonly peopert that specifies the minimum color temperature
 */
@property (nonatomic, readonly) int COLORTEMP_MIN;

/**
 * Readonly peopert that specifies the maximum color temperature
 */
@property (nonatomic, readonly) int COLORTEMP_MAX;

/**
 * Readonly property that returns the version number of the Lighting SDK.
 */
@property (nonatomic, readonly) unsigned int version;

/**
 * Readonly property that returns the AllJoyn BusAttachment object being used to connect to the Lighting System
 *
 * @warning The BusAttachment will be nil until some time after the call start.
 */
@property (nonatomic, readonly) ajn::BusAttachment *busAttachment;

/*
 * Readonly property that returns the dispatch queue being used by the lighting system.
 */
@property (nonatomic, readonly) dispatch_queue_t queue;

/**
 * Readonly property that returns a snapshot of all the Lamps connected to the Lighting controller including
 * lamps that may not have received all data.
 *
 * @warning The contents of this array may change in subsequent calls to this method as new lamps are discovered
 * or existing lamps are determined to be offline. This array may also be empty.
 */
@property (nonatomic, strong, readonly) NSArray *lamps;

/**
 * Readonly property that returns a snapshot of all the Lamps connected to the Lighting controller that have received all
 * their data.
 *
 * @warning The contents of this array may change in subsequent calls to this method as new lamps are discovered or existing
 * lamps are determined to be offline. This array may also be empty.
 */
@property (nonatomic, strong, readonly) NSArray *initializedLamps;

/*
 * Readonly property that returns the number of lamps connected to the lighting controller.
 */
@property (nonatomic, readonly) NSUInteger lampCount;

/**
 * Readonly property that returns a snapshot of all the Groups stored in the Lighting controller including
 * groups that may not have received all data.
 *
 * @warning The contents of this array may change in subsequent calls to this method as new groups are created
 * or existing groups are deleted. This array may also be empty.
 */
@property (nonatomic, strong, readonly) NSArray *groups;

/**
 * Readonly property that returns a snapshot of all the Groups stored in the Lighting controller that have received all
 * their data.
 *
 * @warning The contents of this array may change in subsequent calls to this method as new groups are created or existing
 * groups are deleted. This array may also be empty.
 */
@property (nonatomic, strong, readonly) NSArray *initializedGroups;

/*
 * Readonly property that returns the number of groups stored in the lighting controller.
 */
@property (nonatomic, readonly) NSUInteger groupCount;

/**
 * Readonly property that returns a snapshot of all the Presets stored in the Lighting controller including
 * presets that may not have received all data.
 *
 * @warning The contents of this array may change in subsequent calls to this method as new presets are created
 * or existing presets are deleted. This array may also be empty.
 */
@property (nonatomic, strong, readonly) NSArray *presets;

/**
 * Readonly property that returns a snapshot of all the Presets stored in the Lighting controller that have received all
 * their data.
 *
 * @warning The contents of this array may change in subsequent calls to this method as new presets are created or existing
 * presets are deleted. This array may also be empty.
 */
@property (nonatomic, strong, readonly) NSArray *initializedPresets;

/*
 * Readonly property that returns the number of presets stored in the lighting controller.
 */
@property (nonatomic, readonly) NSUInteger presetCount;

/**
 * Readonly property that returns a snapshot of all the Transition Effects stored in the Lighting controller including
 * transition effects that may not have received all data.
 *
 * @warning The contents of this array may change in subsequent calls to this method as new transition effects are created
 * or existing transition effects are deleted. This array may also be empty.
 */
@property (nonatomic, strong, readonly) NSArray *transitionEffects;

/**
 * Readonly property that returns a snapshot of all the Transition Effects stored in the Lighting controller that have received all
 * their data.
 *
 * @warning The contents of this array may change in subsequent calls to this method as new transition effects are created or existing
 * transition effects are deleted. This array may also be empty.
 */
@property (nonatomic, strong, readonly) NSArray *initializedTransitionEffects;

/*
 * Readonly property that returns the number of transition effects stored in the lighting controller.
 */
@property (nonatomic, readonly) NSUInteger transitionEffectCount;

/**
 * Readonly property that returns a snapshot of all the Pulse Effects stored in the Lighting controller including
 * pulse effects that may not have received all data.
 *
 * @warning The contents of this array may change in subsequent calls to this method as new pulse effects are created
 * or existing pulse effects are deleted. This array may also be empty.
 */
@property (nonatomic, strong, readonly) NSArray *pulseEffects;

/**
 * Readonly property that returns a snapshot of all the Pulse Effects stored in the Lighting controller that have received all
 * their data.
 *
 * @warning The contents of this array may change in subsequent calls to this method as new pulse effects are created or existing
 * pulse effects are deleted. This array may also be empty.
 */
@property (nonatomic, strong, readonly) NSArray *initializedPulseEffects;

/*
 * Readonly property that returns the number of pulse effects stored in the lighting controller.
 */
@property (nonatomic, readonly) NSUInteger pulseEffectCount;

/**
 * Readonly property that returns a snapshot of all the Effects (presets, transition effects, and pulse effects) stored in the
 * Lighting controller including effects that may not have received all data.
 *
 * @warning The contents of this array may change in subsequent calls to this method as new effects are created or existing effects
 * are deleted. This array may also be empty.
 */
@property (nonatomic, strong, readonly) NSArray *effects;

/**
 * Readonly property that returns a snapshot of all the Effects (presets, transition effects, and pulse effects) stored in the
 * Lighting controller that have received all their data.
 *
 * @warning The contents of this array may change in subsequent calls to this method as new effects are created or existing effects
 * are deleted. This array may also be empty.
 */
@property (nonatomic, strong, readonly) NSArray *initializedEffects;

/*
 * Readonly property that returns the number of effects stored in the lighting controller.
 */
@property (nonatomic, readonly) NSUInteger effectCount;

/**
 * Readonly property that returns a snapshot of all the SceneElements stored in the Lighting controller including
 * scene elements that may not have received all data.
 *
 * @warning The contents of this array may change in subsequent calls to this method as new scene elements
 * are created or existing scene elements are deleted. This array may be empty.
 */
@property (nonatomic, strong, readonly) NSArray *sceneElements;

/**
 * Readonly property that returns a snapshot of all the Scene Elements stored in the Lighting controller that have received all
 * their data.
 *
 * @warning The contents of this array may change in subsequent calls to this method as new scene elements
 * are created or existing scene elements are deleted. This array may be empty.
 */
@property (nonatomic, strong, readonly) NSArray *initializedSceneElements;

/*
 * Readonly property that returns the number of scene elements stored in the lighting controller.
 */
@property (nonatomic, readonly) NSUInteger sceneElementCount;

/**
 * Readonly property that returns a snapshot of all the Scenes stored in the Lighting controller including
 * scene that may not have received all data.
 *
 * @warning The contents of this array may change in subsequent calls to this method as new scenes are created or
 * existing scenes are deleted. This array may be empty.
 */
@property (nonatomic, strong, readonly) NSArray *scenes;

/**
 * Readonly property that returns the number of scenes stored in the lighting controller.
 */
@property (nonatomic, readonly) NSUInteger sceneCount;

/**
 * Readonly property that returns a snapshot of all the Scenes stored in the Lighting controller that have received all their data.
 *
 * @warning The contents of this array may change in subsequent calls to this method as new scenes are created or
 * existing scenes are deleted. This array may be empty.
 */
@property (nonatomic, strong, readonly) NSArray *initializedScenes;

/**
 * Readonly property that returns a snapshot of all the Master Scenes stored in the Lighting controller includeing master scenes that may not
 * have received all data.
 *
 * @warning The contents of this array may change in subsequent calls to this method as new master scenes are created or existing master scenes
 * are deleted. This array may be empty.
 */
@property (nonatomic, strong, readonly) NSArray *masterScenes;

/**
 * Readonly property that returns a snapshot of all the Master Scenes stored in the Lighting controller that have received all
 * their data.
 *
 * @warning The contents of this array may change in subsequent calls to this method as new master scenes are created or existing
 * master scenes are deleted. This array may be empty.
 */
@property (nonatomic, strong, readonly) NSArray *initializedMasterScenes;

/**
 * Readonly property that returns the number of master scenes stored in the lighting controller.
 */
@property (nonatomic, readonly) NSUInteger masterSceneCount;

/**
 * Readonly property that returns the lead controller in the Lighting system.
 */
@property (nonatomic, strong, readonly) LSFSDKController *leadController;

/**
 * Specifies the default language used in the Lighting System.
 *
 * @warning If this property is never called, the default language is english ("en").
 */
@property (nonatomic, strong) NSString *defaultLanguage;

/*
 * Readonly property that returns an instance of the LSFSDKLightingSystemManager.
 *
 * @warning This property is not intended for public use.
 */
@property (nonatomic, strong, readonly) LSFSDKLightingSystemManager *lightingManager;

/** @name Getting the Shared LSFSDKLightingDirector Instance */

/**
 * Returns an LSFSDKLightingDirector instance.
 *
 * @warning The start method must be called at some point when you're ready
 * to begin working with the Lighting system.
 *
 * @return The LSFSDKLightingDirector instance.
 */
+(LSFSDKLightingDirector *)getLightingDirector;

/** @name Starting/Stopping LSFSDKLightingDirector */

/**
 * Causes the LSFSDKLightingDirector to start interacting with the Lighting system. The LSFSDKLightingDirector
 * will try to connect to a lighting controller. This method will create its own BusAttachment and dispatch queue.
 *
 * @warning This method should be called before interacting with the LSFSDKLightingDirector.
 * Subsequent calls to this method must each be preceded by a call to stop.
 *
 * @warning You should ensure WiFi or Ethernet connection is available before calling this method.
 */
-(void)start;

/**
 * Causes the LSFSDKLightingDirector to start interacting with the Lighting system using the
 * specified application name. The LSFSDKLightingDirector will try to connect to a lighting
 * controller. This method uses the application name when creating the AllJoyn bus
 * attachment and creates its own dispatch queue.
 *
 * @warning This method should be called before interacting with the LSFSDKLightingDirector.
 * Subsequent calls to this method must each be preceded by a call to stop.
 *
 * @warning You should ensure WiFi or Ethernet connection is available before calling this method.
 *
 * @param applicationName  Name for the AllJoyn BusAttachment. See the AllJoyn core documentation for more information on bus attachments.
 */
-(void)startWithApplicationName: (NSString *)applicationName;

/**
 * Causes the LSFSDKLightingDirector to start interacting with the Lighting system using the
 * specified AllJoyn bus attachment. The LSFSDKLightingDirector will try to connect to a lighting
 * controller. This also method creates its own dispatch queue.
 *
 * @warning This method should be called before interacting with the LSFSDKLightingDirector.
 * Subsequent calls to this method must each be preceded by a call to stop.
 *
 * @warning You should ensure WiFi or Ethernet connection is available before calling this method.
 *
 * @param busAttachment  AllJoyn BusAttachment to be used for the Lighting system. See the AllJoyn core documentation for more information on bus attachments.
 */
-(void)startWithBusAttachment: (ajn::BusAttachment *)busAttachment;

/**
 * Causes the LightingDirector to start interacting with the Lighting system using the
 * specified application name and dispatch queue. The LightingDirector will try to connect
 * to a lighting controller. This method uses the application name when creating the AllJoyn
 * bus attachment.
 *
 * @warning This method should be called before interacting with the LSFSDKLightingDirector.
 * Subsequent calls to this method must each be preceded by a call to stop.
 *
 * @warning You should ensure WiFi or Ethernet connection is available before calling this method.
 *
 * @param applicationName  Name for the AllJoyn BusAttachment. See the AllJoyn core documentation for more information on bus attachments.
 * @param queue  Instance of dispatch queue that will handle all lighting events on the provided thread. The SDK will process internal tasks and invoke all client delegates from the thread associated with this queue.
 */
-(void)startWithApplicationName: (NSString *)applicationName dispatchQueue: (dispatch_queue_t)queue;

/**
 * Causes the LSFSDKLightingDirector to start interacting with the Lighting system using the
 * specified AllJoyn bus attachment and dispatch queue. The LSFSDKLightingDirector will try to
 * connect to a lighting controller.
 *
 * @warning This method should be called before interacting with the LSFSDKLightingDirector.
 * Subsequent calls to this method must each be preceded by a call to stop.
 *
 * @warning You should ensure WiFi or Ethernet connection is available before calling this method.
 *
 * @param busAttachment  AllJoyn BusAttachment to be used for the Lighting system. See the AllJoyn core documentation for more information on bus attachments.
 * @param queue  Instance of dispatch queue that will handle all lighting events on the provided thread. The SDK will process internal tasks and invoke all client delegates from the thread associated with this queue.
 */
-(void)startWithBusAttachment: (ajn::BusAttachment *)busAttachment dispatchQueue: (dispatch_queue_t)queue;

/**
 * Causes the LSFSDKLightingDirector to stop interacting with the Lighting system. The LSFSDKLightingDirector
 * will disconnect from the lighting controller, if a connection exists.
 *
 * @warning This method must be preceded by a call to start.
 */
-(void)stop;

/** @name Getters for Lighting System components */

/**
 * Returns true if the lead controller service only supports the lighting controller
 * interface version 1.
 *
 * @return true for a V1 controller service, false for V2 or later.
 */
-(BOOL)isControllerServiceLeaderV1;

/**
 * Returns a reference to a LSFSDKLamp with the corresponding ID. If a match is not found for the
 * ID, this method will return nil.
 *
 * @param lampID  The ID of the LSFSDKLamp
 *
 * @return Reference to a LSFSDKLamp or null.
 */
-(LSFSDKLamp *)getLampWithID: (NSString *)lampID;

/**
 * Returns a reference to a LSFSDKGroup with the corresponding ID. If a match is not found for the
 * ID, this method will return nil.
 *
 * @param groupID  The ID of the LSFSDKGroup
 *
 * @return Reference to a LSFSDKGroup or nil.
 */
-(LSFSDKGroup *)getGroupWithID: (NSString *)groupID;

/**
 * Returns a reference to a LSFSDKPreset with the corresponding ID. If a match is not found for the
 * ID, this method will return nil.
 *
 * @param presetID  The ID of the LSFSDKPreset
 *
 * @return Reference to a LSFSDKPreset or nil.
 */
-(LSFSDKPreset *)getPresetWithID: (NSString *)presetID;

/**
 * Returns a reference to a LSFSDKTransitionEffect with the corresponding ID. If a match is not found for the
 * ID, this method will return nil.
 *
 * @param transitionEffectID  The ID of the LSFSDKTransitionEffect
 *
 * @return Reference to a LSFSDKTransitionEffect or nil.
 */
-(LSFSDKTransitionEffect *)getTransitionEffectWithID: (NSString *)transitionEffectID;

/**
 * Returns a reference to a LSFSDKPulseEffect with the corresponding ID. If a match is not found for the
 * ID, this method will return nil.
 *
 * @param pulseEffectID  The ID of the LSFSDKPulseEffect
 *
 * @return Reference to a LSFSDKPulseEffect or nil.
 */
-(LSFSDKPulseEffect *)getPulseEffectWithID: (NSString *)pulseEffectID;

/**
 * Returns a reference to the LSFSDKEffect (preset, transition effect, or pulse effect) with the corresponding
 * effect ID. If a match is not found for the ID, this method will return nil.
 *
 * @param effectID  The ID of the LSFSDKEffect
 *
 * @return Reference to an LSFSDKEffect or nil.
 */
-(id<LSFSDKEffect>)getEffectWithID: (NSString *)effectID;

/**
 * Returns a reference to the LSFSDKSceneElement with the corresponding ID. If a match is not found for
 * the ID, this method will return nil.
 *
 * @param sceneElementID  The ID of the LSFSDKSceneElement
 *
 * @return Reference to a LSFSDKSceneElement or nil.
 */
-(LSFSDKSceneElement *)getSceneElementWithID: (NSString *)sceneElementID;

/**
 * Returns a reference to the LSFSDKScene with the corresponding ID. If a match is not found for
 * the ID, this method will return nil.
 *
 * @param sceneID  The ID of the LSFSDKScene
 *
 * @return Reference to a LSFSDKScene or nil.
 */
-(LSFSDKScene *)getSceneWithID: (NSString *)sceneID;

/**
 * Returns a reference to the LSFSDKMasterScene with the corresponding ID. If a match is not found for
 * the ID, this method will return nil.
 *
 * @param masterSceneID The ID of the LSFSDKMasterScene
 *
 * @return Reference to a LSFSDKMasterScene or nil.
 */
-(LSFSDKMasterScene *)getMasterSceneWithID: (NSString *)masterSceneID;

/** @name Creating Lighting System components */

/**
 * Asynchronously creates a Group on the Lighting controller. Once the group is successfully
 * created, the [LSFSDKGroupDelegate onGroupInitializedWithTrackingID:andGroup:] method will be
 * invoked and the tracking IDs will match.
 *
 * @param members  Specifies the group's members
 * @param groupName  Name of the Group
 *
 * @return LSFSDKTrackingID associated with the creation of the Group
 */
-(LSFSDKTrackingID *)createGroupWithMembers: (NSArray *)members groupName: (NSString *)groupName;

/**
 * Asynchronously creates a Preset on the Lighting controller. Once the preset is successfully
 * created, the [LSFSDKPresetDelegate onPresetInitializedWithTrackingID:andPreset:] method will be
 * invoked and the tracking IDs will match.
 *
 * @param power  Specifies the Power of the Preset's lamp state
 * @param color  Specifies the Color of the Preset's lamp state
 * @param presetName  Name of the Preset
 *
 * @return LSFSDKTrackingID associated with the creation of the Preset
 */
-(LSFSDKTrackingID *)createPresetWithPower: (Power)power color: (LSFSDKColor *)color presetName: (NSString *)presetName;

/**
 * Asynchronously creates a Transition Effect on the Lighting controller. Once the transition
 * effect is successfully created, the [LSFSDKTransitionEffectDelegate onTransitionEffectInitializedWithTrackingID:andTransitionEffect:]
 * method will be invoked and the tracking IDs will match.
 *
 * @param state  Specifies the lamp state of the TransitionEffect
 * @param duration  Specifies how long the TransitionEffect will take
 * @param effectName  Name of the TransitionEffect
 *
 * @return LSFSDKTrackingID associated with the creation of the TransitionEffect
 */
-(LSFSDKTrackingID *)createTransitionEffectWithLampState: (id<LSFSDKLampState>)state duration: (unsigned int)duration name: (NSString *)effectName;

/**
 * Asynchronously creates a Pulse Effect on the Lighting controller. Once the pulse
 * effect is successfully created, the [LSFSDKPulseEffectDelegate onPulseEffectInitializedWithTrackingID:andPulseEffect:]
 * method will be invoked and the tracking IDs will match.
 *
 * @param fromState  Specifies the starting LampState of the PulseEffect
 * @param toState  Specifies the ending LampState of the PulseEffect
 * @param period  Specifies the period of the pulse effect (in ms). Period refers to the time duration between the start of two pulses
 * @param duration  Specifies the duration of a single pulse (in ms). This must be less than the period
 * @param count  Specifies the number of pulses
 * @param effectName  Name of the PulseEffect
 *
 * @return LSFSDKTrackingID associated with the creation of the PulseEffect
 */
-(LSFSDKTrackingID *)createPulseEffectWithFromState: (id<LSFSDKLampState>)fromState toState: (id<LSFSDKLampState>)toState period: (unsigned int)period duration: (unsigned int)duration count: (unsigned int)count name: (NSString *)effectName;

/**
 * Asynchronously creates a Scene Element on the Lighting controller. Once the scene
 * element is successfully created, the [LSFSDKSceneElementDelegate onSceneElementInitializedWithTrackingID:andSceneElement:]
 * method will be invoked and the tracking IDs will match.
 *
 * @param effect  Specifies the SceneElement's effect
 * @param members  Specifies the GroupMembers for which the effect will be applied
 * @param sceneElementName  Name of the SceneElement
 *
 * @return LSFSDKTrackingID associated with the creation of the SceneElement
 */
-(LSFSDKTrackingID *)createSceneElementWithEffect: (id<LSFSDKEffect>)effect groupMembers: (NSArray *)members name: (NSString *)sceneElementName;

/**
 * Asynchronously creates a Scene on the Lighting controller. Once the scene
 * is successfully created, the [LSFSDKSceneDelegate onSceneInitializedWithTrackingID:andScene:]
 * method will be invoked and the tracking IDs will match.
 *
 * @param sceneElements  Specifies the SceneElements that belong to the Scene
 * @param sceneName  Name of the Scene
 *
 * @return LSFSDKTrackingID associated with the creation of the Scene
 */
-(LSFSDKTrackingID *)createSceneWithSceneElements: (NSArray *)sceneElements name: (NSString *)sceneName;

/**
 * Asynchronously creates a Master Scene on the Lighting controller. Once the master
 * scene is successfully created, the [LSFSDKMasterSceneDelegate onMasterSceneInitializedWithTrackingID:andMasterScene:]
 * method will be invoked and the tracking IDs will match.
 *
 * @param scenes  Specifies the Scenes that belong to the MasterScene
 * @param masterSceneName  Name of the MasterScene
 *
 * @return LSFSDKTrackingID associated with the creation of the MasterScene
 */
-(LSFSDKTrackingID *)createMasterSceneWithScenes: (NSArray *)scenes name: (NSString *)masterSceneName;

/** @name Add and Remove Lighting System delegates */

/**
 * Specifies a delegate to invoke once a connection to a lighting controller has been established. After a connection is established,
 * this delegate will be invoked only one time.
 *
 * @param delay  Specifies a delay to wait before invoking the delegate
 * @param delegate  The delegate to invoke on connection.
 */
-(void)postOnNextControllerConnectionWithDelay: (unsigned int)delay delegate: (id<LSFSDKNextControllerConnectionDelegate>)delegate;

/**
 * Specifies a block to execute once a connection to a lighting controller has been established. After a connection is established,
 * this block will be executed only one time.
 *
 * @param delay  Specifies a delay to wait before executing the block
 * @param block  The block to execute on connection.
 */
-(void)postOnNextControllerConnectionWithDelay: (unsigned int)delay block: (void (^)(void))block;

/**
 * Adds a global delegate to receive all Lighting system events associated with the provided delegate's
 * type. Adding multiple delegates of various types is supported.
 *
 * @param delegate  The delegate that receives Lighting System events.
 */
-(void)addDelegate: (id<LSFSDKLightingDelegate>)delegate;

/**
 * Adds a global delegate to receive all Lamp events.
 *
 * @param delegate  The delegate that receives all lamp events.
 */
-(void)addLampDelegate: (id<LSFSDKLampDelegate>)delegate;

/**
 * Adds a global delegate to receive all Group events.
 *
 * @param delegate  The delegate that receives all group events.
 */
-(void)addGroupDelegate: (id<LSFSDKGroupDelegate>)delegate;

/**
 * Adds a global delegate to receive all Preset events.
 *
 * @param delegate  The delegate that receives all preset events.
 */
-(void)addPresetDelegate: (id<LSFSDKPresetDelegate>)delegate;

/**
 * Adds a global delegate to receive all Transition Effect events.
 *
 * @param delegate  The delegate that receives all transition effect events.
 */
-(void)addTransitionEffectDelegate: (id<LSFSDKTransitionEffectDelegate>)delegate;

/**
 * Adds a global delegate to receive all Pulse Effect events.
 *
 * @param delegate  The delegate that receives all pulse effect events.
 */
-(void)addPulseEffectDelegate: (id<LSFSDKPulseEffectDelegate>)delegate;

/**
 * Adds a global delegate to receive all Scene Element events.
 *
 * @param delegate  The delegate that receives all scene element events.
 */
-(void)addSceneElementDelegate: (id<LSFSDKSceneElementDelegate>)delegate;

/**
 * Adds a global delegate to receive all Scene events.
 *
 * @param delegate  The delegate that receives all scene events.
 */
-(void)addSceneDelegate: (id<LSFSDKSceneDelegate>)delegate;

/**
 * Adds a global delegate to receive all Master Scene events.
 *
 * @param delegate  The delegate that receives all master scene events.
 */
-(void)addMasterSceneDelegate: (id<LSFSDKMasterSceneDelegate>)delegate;

/**
 * Adds a global delegate to receive all Controller events.
 *
 * @param delegate  The delegate that receives all controller events.
 */
-(void)addControllerDelegate: (id<LSFSDKControllerDelegate>)delegate;

/**
 * Removes a global delegate to receive all Lighting System events associated with the provided
 * delegate's type.
 *
 * @param delegate  The delegate that receives Lighting System events.
 */
-(void)removeDelegate: (id<LSFSDKLightingDelegate>)delegate;

/**
 * Removes a global delegate to receive all Lamp events.
 *
 * @param delegate  The delegate that receives all lamp events.
 */
-(void)removeLampDelegate: (id<LSFSDKLampDelegate>)delegate;

/**
 * Removes a global delegate to receive all Group events.
 *
 * @param delegate  The delegate that receives all group events.
 */
-(void)removeGroupDelegate: (id<LSFSDKGroupDelegate>)delegate;

/**
 * Removes a global delegate to receive all Preset events.
 *
 * @param delegate  The delegate that receives all preset events.
 */
-(void)removePresetDelegate: (id<LSFSDKPresetDelegate>)delegate;

/**
 * Removes a global delegate to receive all Transition Effect events.
 *
 * @param delegate  The delegate that receives all transition effect events.
 */
-(void)removeTransitionEffectDelegate: (id<LSFSDKTransitionEffectDelegate>)delegate;

/**
 * Removes a global delegate to receive all Pulse Effect events.
 *
 * @param delegate  The delegate that receives all pulse effect events.
 */
-(void)removePulseEffectDelegate: (id<LSFSDKPulseEffectDelegate>)delegate;

/**
 * Removes a global delegate to receive all Scene Element events.
 *
 * @param delegate  The delegate that receives all scene element events.
 */
-(void)removeSceneElementDelegate: (id<LSFSDKSceneElementDelegate>)delegate;

/**
 * Removes a global delegate to receive all Scene events.
 *
 * @param delegate  The delegate that receives all scene events.
 */
-(void)removeSceneDelegate: (id<LSFSDKSceneDelegate>)delegate;

/**
 * Removes a global delegate to receive all Master Scene events.
 *
 * @param delegate  The delegate that receives all master scene events.
 */
-(void)removeMasterSceneDelegate: (id<LSFSDKMasterSceneDelegate>)delegate;

/**
 * Removes a global delegate to receive all Controller events.
 *
 * @param delegate  The delegate that receives all controller events.
 */
-(void)removeControllerDelegate: (id<LSFSDKControllerDelegate>)delegate;

@end
