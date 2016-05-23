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

#import "LSFSDKLightingDirector.h"
#import "LSFSDKLightingItemUtil.h"
#import "manager/LSFSDKLampCollectionManager.h"
#import "manager/LSFSDKPresetCollectionManager.h"
#import "manager/LSFSDKGroupCollectionManager.h"
#import "manager/LSFSDKTransitionEffectCollectionManager.h"
#import "manager/LSFSDKPulseEffectCollectionManager.h"
#import "manager/LSFSDKSceneElementCollectionManager.h"
#import "manager/LSFSDKSceneCollectionManagerV1.h"
#import "manager/LSFSDKSceneCollectionManagerV2.h"
#import "manager/LSFSDKMasterSceneCollectionManager.h"
#import "manager/LSFSDKAllJoynManager.h"
#import "model/LSFSDKLightingItemInitializedFilter.h"
#import "model/LSFConstants.h"
#import <alljoyn/Init.h>

static NSString *LANGUAGE_DEFAULT = @"en";

@interface LSFSDKLightingDirector()

-(LSFSDKLampCollectionManager *)getLampCollectionManager;
-(LSFSDKPresetCollectionManager *)getPresetCollectionManager;
-(LSFSDKGroupCollectionManager *)getGroupCollectionManager;
-(LSFSDKTransitionEffectCollectionManager *)getTransitionEffectCollectionManager;
-(LSFSDKPulseEffectCollectionManager *)getPulseEffectCollectionManager;
-(LSFSDKSceneElementCollectionManager *)getSceneElementCollectionManager;
-(LSFSDKSceneCollectionManagerV1 *)getSceneCollectionManager;
-(LSFSDKSceneCollectionManagerV2 *)getSceneCollectionManagerV2;
-(LSFSDKMasterSceneCollectionManager *)getMasterSceneCollectionManager;
-(LSFControllerManager *)getControllerManager;

@end

@implementation LSFSDKLightingDirector

@synthesize HUE_MIN = _HUE_MIN;
@synthesize HUE_MAX = _HUE_MAX;
@synthesize SATURATION_MIN = _SATURATION_MIN;
@synthesize SATURATION_MAX = _SATURATION_MAX;
@synthesize BRIGHTNESS_MIN = _BRIGHTNESS_MIN;
@synthesize BRIGHTNESS_MAX = _BRIGHTNESS_MAX;
@synthesize COLORTEMP_MIN = _COLORTEMP_MIN;
@synthesize COLORTEMP_MAX = _COLORTEMP_MAX;
@synthesize version = _version;
@synthesize busAttachment = _busAttachment;
@synthesize queue = _queue;
@synthesize lamps = _lamps;
@synthesize initializedLamps = _initializedLamps;
@synthesize groups = _groups;
@synthesize initializedGroups = _initializedGroups;
@synthesize presets = _presets;
@synthesize initializedPresets = _initializedPresets;
@synthesize transitionEffects = _transitionEffects;
@synthesize initializedTransitionEffects = _initializedTransitionEffects;
@synthesize pulseEffects = _pulseEffects;
@synthesize initializedPulseEffects = _initializedPulseEffects;
@synthesize sceneElements = _sceneElements;
@synthesize initializedSceneElements = _initializedSceneElements;
@synthesize scenes = _scenes;
@synthesize initializedScenes = _initializedScenes;
@synthesize masterScenes = _masterScenes;
@synthesize initializedMasterScenes = _initializedMasterScenes;
@synthesize defaultLanguage = _defaultLanguage;
@synthesize lightingManager = _lightingManager;

+(LSFSDKLightingDirector *)getLightingDirector
{
    static LSFSDKLightingDirector *lightingDirector = nil;
    static dispatch_once_t onceToken;

    dispatch_once(&onceToken, ^{
        AllJoynInit();
        AllJoynRouterInit();
        lightingDirector = [[self alloc] init];
    });

    return lightingDirector;
}

-(id)init
{
    self = [super init];

    if (self)
    {
        NSLog(@"LSFSDKLightingDirector - init(). Static Library Slice Used = %@", ARCH_STR);

        _lightingManager = [[LSFSDKLightingSystemManager alloc] init];
        _defaultLanguage = LANGUAGE_DEFAULT;
    }

    return self;
}

-(int)HUE_MIN
{
    return [[LSFConstants getConstants] MIN_HUE];
}

-(int)HUE_MAX
{
    return [[LSFConstants getConstants] MAX_HUE];
}

-(int)SATURATION_MIN
{
    return [[LSFConstants getConstants] MIN_SATURATION];
}

-(int)SATURATION_MAX
{
    return [[LSFConstants getConstants] MAX_SATURATION];
}

-(int)BRIGHTNESS_MIN
{
    return [[LSFConstants getConstants] MIN_BRIGHTNESS];
}

-(int)BRIGHTNESS_MAX
{
    return [[LSFConstants getConstants] MAX_BRIGHTNESS];
}

-(int)COLORTEMP_MIN
{
    return [[LSFConstants getConstants] MIN_COLOR_TEMP];
}

-(int)COLORTEMP_MAX
{
    return [[LSFConstants getConstants] MAX_COLOR_TEMP];
}

-(unsigned int)version
{
    return 2;
}

-(void)start
{
    [self startWithApplicationName: @"LightingDirector"];
}

-(void)startWithApplicationName: (NSString *)applicationName
{
    [self startWithApplicationName: applicationName dispatchQueue: nil];
}

-(void)startWithBusAttachment: (ajn::BusAttachment *)busAttachment
{
    [self startWithBusAttachment: busAttachment dispatchQueue: nil];
}

-(void)startWithApplicationName: (NSString *)applicationName dispatchQueue: (dispatch_queue_t)queue
{
    [self.lightingManager initializeWithApplicationName: applicationName dispatchQueue: queue andAllJoynDelegate: nil];
    [self.lightingManager start];
}

-(void)startWithBusAttachment: (ajn::BusAttachment *)busAttachment dispatchQueue: (dispatch_queue_t)queue
{
    [self.lightingManager initializeWithBusAttachment: busAttachment dispatchQueue: queue andAllJoynDelegate: nil];
    [self.lightingManager start];
}

-(void)stop
{
    [self.lightingManager stop];
}

-(BOOL)isControllerServiceLeaderV1
{
    return [LSFSDKAllJoynManager isControllerServiceLeaderV1];
}

-(ajn::BusAttachment *)busAttachment
{
    return [LSFSDKAllJoynManager getBusAttachment];
}

-(dispatch_queue_t)queue
{
    return [self.lightingManager dispatchQueue];
}

-(NSArray *)lamps
{
    return [[self getLampCollectionManager] getLamps];
}

-(NSArray *)initializedLamps
{
    return [[self getLampCollectionManager] getLampsWithFilter: [[LSFSDKLightingItemInitializedFilter alloc] init]];
}

-(NSUInteger)lampCount
{
    return [[[self getLampCollectionManager] getLamps] count];
}

-(LSFSDKLamp *)getLampWithID: (NSString *)lampID
{
    return [[self getLampCollectionManager] getLampWithID: lampID];
}

-(NSArray *)groups
{
    return [[self getGroupCollectionManager] getGroups];
}

-(NSArray *)initializedGroups
{
    return [[self getGroupCollectionManager] getGroupsWithFilter: [[LSFSDKLightingItemInitializedFilter alloc] init]];
}

-(NSUInteger)groupCount
{
    return [[[self getGroupCollectionManager] getGroups] count];
}

-(LSFSDKGroup *)getGroupWithID: (NSString *)groupID
{
    return [[self getGroupCollectionManager] getGroupWithID: groupID];
}

-(NSArray *)presets
{
    return [[self getPresetCollectionManager] getPresets];
}

-(NSArray *)initializedPresets
{
    return [[self getPresetCollectionManager] getPresetsWithFilter: [[LSFSDKLightingItemInitializedFilter alloc] init]];
}

-(NSUInteger)presetCount
{
    return [[[self getPresetCollectionManager] getPresets] count];
}

-(LSFSDKPreset *)getPresetWithID: (NSString *)presetID
{
    return [[self getPresetCollectionManager] getPresetWithID: presetID];
}

-(NSArray *)transitionEffects
{
    return [[self getTransitionEffectCollectionManager] getTransitionEffects];
}

-(NSArray *)initializedTransitionEffects
{
    return [[self getTransitionEffectCollectionManager] getTransitionEffectsWithFilter: [[LSFSDKLightingItemInitializedFilter alloc] init]];
}

-(NSUInteger)transitionEffectCount
{
    return [[[self getTransitionEffectCollectionManager] getTransitionEffects] count];
}

-(LSFSDKTransitionEffect *)getTransitionEffectWithID: (NSString *)transitionEffectID
{
    return [[self getTransitionEffectCollectionManager] getTransitionEffectWithID: transitionEffectID];
}

-(NSArray *)pulseEffects
{
    return [[self getPulseEffectCollectionManager] getPulseEffects];
}

-(NSArray *)initializedPulseEffects
{
    return [[self getPulseEffectCollectionManager] getPulseEffectsWithFilter: [[LSFSDKLightingItemInitializedFilter alloc] init]];
}

-(NSUInteger)pulseEffectCount
{
    return [[[self getPulseEffectCollectionManager] getPulseEffects] count];
}

-(LSFSDKPulseEffect *)getPulseEffectWithID: (NSString *)pulseEffectID
{
    return [[self getPulseEffectCollectionManager] getPulseEffectWithID: pulseEffectID];
}

-(NSArray *)effects
{
    NSMutableArray *allEffects = [[NSMutableArray alloc] init];
    [allEffects addObjectsFromArray: [self presets]];
    [allEffects addObjectsFromArray: [self transitionEffects]];
    [allEffects addObjectsFromArray: [self pulseEffects]];

    return allEffects;
}

-(NSArray *)initializedEffects
{
    NSMutableArray *allInitializedEffects = [[NSMutableArray alloc] init];
    [allInitializedEffects addObjectsFromArray: [self initializedPresets]];
    [allInitializedEffects addObjectsFromArray: [self initializedTransitionEffects]];
    [allInitializedEffects addObjectsFromArray: [self initializedPulseEffects]];

    return allInitializedEffects;
}

-(NSUInteger)effectCount
{
    return [self presetCount] + [self transitionEffectCount] + [self pulseEffectCount];
}

-(id<LSFSDKEffect>)getEffectWithID:(NSString *)effectID
{
    id<LSFSDKEffect> effect = [self getPresetWithID: effectID];

    if (effect == nil) {
        effect = [self getTransitionEffectWithID: effectID];
    }

    if (effect == nil) {
        effect = [self getPulseEffectWithID: effectID];
    }

    return effect;
}

-(NSArray *)sceneElements
{
    return [[self getSceneElementCollectionManager] getSceneElements];
}

-(NSArray *)initializedSceneElements
{
    return [[self getSceneElementCollectionManager] getSceneElementsWithFilter: [[LSFSDKLightingItemInitializedFilter alloc] init]];
}

-(NSUInteger)sceneElementCount
{
    return [[[self getSceneElementCollectionManager] getSceneElements] count];
}

-(LSFSDKSceneElement *)getSceneElementWithID: (NSString *)sceneElementID
{
    return [[self getSceneElementCollectionManager] getSceneElementWithID: sceneElementID];
}

-(NSArray *)scenes
{
    NSMutableArray *scenes = [[NSMutableArray alloc] init];
    [scenes addObjectsFromArray: [[self getSceneCollectionManagerV2] getScenes]];
    if (!scenes.count)
    {
        [scenes addObjectsFromArray: [[self getSceneCollectionManager] getScenes]];
    }

    return scenes;
}

-(NSArray *)initializedScenes
{
    NSMutableArray *initializedScenes = [[NSMutableArray alloc] init];
    [initializedScenes addObjectsFromArray: [[self getSceneCollectionManagerV2] getScenesWithFilter: [[LSFSDKLightingItemInitializedFilter alloc] init]]];
    if (!initializedScenes.count)
    {
        [initializedScenes addObjectsFromArray: [[self getSceneCollectionManager] getScenesWithFilter: [[LSFSDKLightingItemInitializedFilter alloc] init]]];
    }

    return initializedScenes;
}

-(NSUInteger)sceneCount
{
    NSUInteger count = [[[self getSceneCollectionManagerV2] getScenes] count];
    if (!count)
    {
        count = [[[self getSceneCollectionManager] getScenes] count];
    }

    return count;
}

-(LSFSDKScene *)getSceneWithID: (NSString *)sceneID
{
    LSFSDKScene *scene = [[self getSceneCollectionManagerV2] getSceneWithID: sceneID];

    if (scene == nil)
    {
        scene = [[self getSceneCollectionManager] getSceneWithID: sceneID];
    }

    return scene;
}

-(NSArray *)masterScenes
{
    return [[self getMasterSceneCollectionManager] getMasterScenes];
}

-(NSArray *)initializedMasterScenes
{
    return [[self getMasterSceneCollectionManager] getMasterScenesWithFilter: [[LSFSDKLightingItemInitializedFilter alloc] init]];
}

-(NSUInteger)masterSceneCount
{
    return [[[self getMasterSceneCollectionManager] getMasterScenes] count];
}

-(LSFSDKController *)leadController
{
    return [[self getControllerManager] getLeader];
}

-(LSFSDKMasterScene *)getMasterSceneWithID: (NSString *)masterSceneID
{
    return [[self getMasterSceneCollectionManager] getMasterSceneWithID: masterSceneID];
}

-(LSFSDKTrackingID *)createGroupWithMembers: (NSArray *)members groupName: (NSString *)groupName
{
    LSFSDKTrackingID *trackingID = [[LSFSDKTrackingID alloc] init];
    uint32_t tid = 0;

    [[LSFSDKAllJoynManager getGroupManager] createLampGroupWithTracking: &tid lampGroup: [LSFSDKLightingItemUtil createLampGroupFromGroupMembers: members] withName: groupName];
    trackingID.value = tid;

    return trackingID;
}

-(LSFSDKTrackingID *)createPresetWithPower: (Power)power color: (LSFSDKColor *)color presetName: (NSString *)presetName
{
    LSFSDKTrackingID *trackingID = [[LSFSDKTrackingID alloc] init];
    uint32_t tid = 0;

    [[LSFSDKAllJoynManager getPresetManager] createPresetWithTracking: &tid state: [LSFSDKLightingItemUtil createLampStateFromPower: (power ? ON : OFF) hue: color.hue saturation: color.saturation brightness: color.brightness colorTemp: color.colorTemp] andPresetName: presetName];
    trackingID.value = tid;

    return trackingID;
}

-(LSFSDKTrackingID *)createTransitionEffectWithLampState: (id<LSFSDKLampState>)state duration: (unsigned int)duration name: (NSString *)effectName
{
    LSFSDKTrackingID *trackingID = [[LSFSDKTrackingID alloc] init];
    uint32_t tid = 0;

    if ([state isKindOfClass: [LSFSDKPreset class]])
    {
        [[LSFSDKAllJoynManager getTransitionEffectManager] createTransitionEffectWithTracking: &tid transitionEffect: [LSFSDKLightingItemUtil createTransitionEffectFromPreset: (LSFSDKPreset *)state duration: duration] andTransitionEffectName: effectName];
    }
    else
    {
        [[LSFSDKAllJoynManager getTransitionEffectManager] createTransitionEffectWithTracking: &tid transitionEffect: [LSFSDKLightingItemUtil createTransitionEffectFromPower: [state getPowerOn] hsvt: [state getColorHsvt] duration: duration] andTransitionEffectName: effectName];
    }

    trackingID.value = tid;
    return trackingID;
}

-(LSFSDKTrackingID *)createPulseEffectWithFromState: (id<LSFSDKLampState>)fromState toState: (id<LSFSDKLampState>)toState period: (unsigned int)period duration: (unsigned int)duration count: (unsigned int)count name: (NSString *)effectName
{
    LSFSDKTrackingID *trackingID = [[LSFSDKTrackingID alloc] init];
    uint32_t tid = 0;

    if (([fromState isKindOfClass: [LSFSDKPreset class]]) && ([toState isKindOfClass: [LSFSDKPreset class]]))
    {
        [[LSFSDKAllJoynManager getPulseEffectManager] createPulseEffectWithTracking: &tid pulseEffect: [LSFSDKLightingItemUtil createPulseeffectFromPreset: (LSFSDKPreset *)fromState toPreset: (LSFSDKPreset *)toState period: period duration: duration count: count] andPulseEffectName: effectName];
    }
    else
    {
        [[LSFSDKAllJoynManager getPulseEffectManager] createPulseEffectWithTracking: &tid pulseEffect: [LSFSDKLightingItemUtil createPulseEffectWithFromPowerOn: [fromState getPowerOn] fromColorHsvt: [fromState getColorHsvt] toPowerOn: [toState getPowerOn] toColorHsvt: [toState getColorHsvt] period: period duration: duration count: count] andPulseEffectName:effectName];
    }

    trackingID.value = tid;
    return trackingID;
}

-(LSFSDKTrackingID *)createSceneElementWithEffect: (id<LSFSDKEffect>)effect groupMembers: (NSArray *)members name: (NSString *)sceneElementName
{
    LSFSDKTrackingID *trackingID = [[LSFSDKTrackingID alloc] init];
    uint32_t tid = 0;

    [[LSFSDKAllJoynManager getSceneElementManager] createSceneElementWithTracking: &tid sceneElement: [LSFSDKLightingItemUtil createSceneElementWithEffectID: [effect theID] groupMembers: members] andSceneElementName:sceneElementName];

    trackingID.value = tid;
    return trackingID;
}

-(LSFSDKTrackingID *)createSceneWithSceneElements: (NSArray *)sceneElements name: (NSString *)sceneName
{
    LSFSDKTrackingID *trackingID = [[LSFSDKTrackingID alloc] init];
    uint32_t tid = 0;

    NSMutableArray *sceneElementIDs = [[NSMutableArray alloc] initWithCapacity: [sceneElements count]];

    for (LSFSDKSceneElement *sceneElement in sceneElements)
    {
        [sceneElementIDs addObject: [sceneElement theID]];
    }

    [[LSFSDKAllJoynManager getSceneManager] createSceneWithSceneElementsWithTracking: &tid sceneWithSceneElements: [LSFSDKLightingItemUtil createSceneWithSceneElements: sceneElementIDs] andSceneName: sceneName];

    trackingID.value = tid;
    return trackingID;
}

-(LSFSDKTrackingID *)createMasterSceneWithScenes: (NSArray *)scenes name: (NSString *)masterSceneName
{
    LSFSDKTrackingID *trackingID = [[LSFSDKTrackingID alloc] init];
    uint32_t tid = 0;

    NSMutableArray *sceneIDs = [[NSMutableArray alloc] initWithCapacity: [scenes count]];

    for (LSFSDKScene *scene in scenes)
    {
        [sceneIDs addObject: [scene theID]];
    }

    [[LSFSDKAllJoynManager getMasterSceneManager] createMasterSceneWithTracking: &tid masterScene: [LSFSDKLightingItemUtil createMasterSceneFromSceneID: sceneIDs] withName: masterSceneName];

    trackingID.value = tid;
    return trackingID;
}

-(void)postOnNextControllerConnectionWithDelay: (unsigned int)delay delegate: (id<LSFSDKNextControllerConnectionDelegate>)delegate;
{
    [self.lightingManager postOnNextControllerConnection: delegate withDelay: delay];
}

-(void)postOnNextControllerConnectionWithDelay: (unsigned int)delay block: (void (^)(void))block;
{
    //TODO - Implement
}

-(void)addDelegate: (id<LSFSDKLightingDelegate>)delegate
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKLampDelegate)])
    {
        [self addLampDelegate: (id<LSFSDKLampDelegate>)delegate];
    }

    if ([delegate conformsToProtocol: @protocol(LSFSDKGroupDelegate)])
    {
        [self addGroupDelegate: (id<LSFSDKGroupDelegate>)delegate];
    }

    if ([delegate conformsToProtocol: @protocol(LSFSDKPresetDelegate)])
    {
        [self addPresetDelegate: (id<LSFSDKPresetDelegate>)delegate];
    }

    if ([delegate conformsToProtocol: @protocol(LSFSDKTransitionEffectDelegate)])
    {
        [self addTransitionEffectDelegate: (id<LSFSDKTransitionEffectDelegate>)delegate];
    }

    if ([delegate conformsToProtocol: @protocol(LSFSDKPulseEffectDelegate)])
    {
        [self addPulseEffectDelegate: (id<LSFSDKPulseEffectDelegate>)delegate];
    }

    if ([delegate conformsToProtocol: @protocol(LSFSDKSceneElementDelegate)])
    {
        [self addSceneElementDelegate: (id<LSFSDKSceneElementDelegate>)delegate];
    }

    if ([delegate conformsToProtocol: @protocol(LSFSDKSceneDelegate)])
    {
        [self addSceneDelegate: (id<LSFSDKSceneDelegate>)delegate];
    }

    if ([delegate conformsToProtocol: @protocol(LSFSDKMasterSceneDelegate)])
    {
        [self addMasterSceneDelegate: (id<LSFSDKMasterSceneDelegate>)delegate];
    }

    if ([delegate conformsToProtocol: @protocol(LSFSDKControllerDelegate)])
    {
        [self addControllerDelegate: (id<LSFSDKControllerDelegate>)delegate];
    }
}

-(void)addLampDelegate: (id<LSFSDKLampDelegate>)delegate
{
    [[self getLampCollectionManager] addLampDelegate: delegate];
}

-(void)addGroupDelegate: (id<LSFSDKGroupDelegate>)delegate
{
    [[self getGroupCollectionManager] addGroupDelegate: delegate];
}

-(void)addPresetDelegate: (id<LSFSDKPresetDelegate>)delegate
{
    [[self getPresetCollectionManager] addPresetDelegate: delegate];
}

-(void)addTransitionEffectDelegate: (id<LSFSDKTransitionEffectDelegate>)delegate
{
    [[self getTransitionEffectCollectionManager] addTransitionEffectDelegate: delegate];
}

-(void)addPulseEffectDelegate: (id<LSFSDKPulseEffectDelegate>)delegate
{
    [[self getPulseEffectCollectionManager] addPulseEffectDelegate: delegate];
}

-(void)addSceneElementDelegate: (id<LSFSDKSceneElementDelegate>)delegate
{
    [[self getSceneElementCollectionManager] addSceneElementDelegate: delegate];
}

-(void)addSceneDelegate: (id<LSFSDKSceneDelegate>)delegate
{
    [[self getSceneCollectionManager] addSceneDelegate: delegate];
    [[self getSceneCollectionManagerV2] addSceneDelegate: delegate];
}

-(void)addMasterSceneDelegate: (id<LSFSDKMasterSceneDelegate>)delegate
{
    [[self getMasterSceneCollectionManager] addMasterSceneDelegate: delegate];
}

-(void)addControllerDelegate: (id<LSFSDKControllerDelegate>)delegate
{
    [[self getControllerManager] addDelegate: delegate];
}

-(void)removeDelegate: (id<LSFSDKLightingDelegate>)delegate
{
    if ([delegate conformsToProtocol: @protocol(LSFSDKLampDelegate)])
    {
        [self removeLampDelegate: (id<LSFSDKLampDelegate>)delegate];
    }

    if ([delegate conformsToProtocol: @protocol(LSFSDKGroupDelegate)])
    {
        [self removeGroupDelegate: (id<LSFSDKGroupDelegate>)delegate];
    }

    if ([delegate conformsToProtocol: @protocol(LSFSDKPresetDelegate)])
    {
        [self removePresetDelegate: (id<LSFSDKPresetDelegate>)delegate];
    }

    if ([delegate conformsToProtocol: @protocol(LSFSDKTransitionEffectDelegate)])
    {
        [self removeTransitionEffectDelegate: (id<LSFSDKTransitionEffectDelegate>)delegate];
    }

    if ([delegate conformsToProtocol: @protocol(LSFSDKPulseEffectDelegate)])
    {
        [self removePulseEffectDelegate: (id<LSFSDKPulseEffectDelegate>)delegate];
    }

    if ([delegate conformsToProtocol: @protocol(LSFSDKSceneElementDelegate)])
    {
        [self removeSceneElementDelegate: (id<LSFSDKSceneElementDelegate>)delegate];
    }

    if ([delegate conformsToProtocol: @protocol(LSFSDKSceneDelegate)])
    {
        [self removeSceneDelegate: (id<LSFSDKSceneDelegate>)delegate];
    }

    if ([delegate conformsToProtocol: @protocol(LSFSDKMasterSceneDelegate)])
    {
        [self removeMasterSceneDelegate: (id<LSFSDKMasterSceneDelegate>)delegate];
    }

    if ([delegate conformsToProtocol: @protocol(LSFSDKControllerDelegate)])
    {
        [self removeControllerDelegate: (id<LSFSDKControllerDelegate>)delegate];
    }
}

-(void)removeLampDelegate: (id<LSFSDKLampDelegate>)delegate
{
    [[self getLampCollectionManager] removeLampDelegate: delegate];
}

-(void)removeGroupDelegate: (id<LSFSDKGroupDelegate>)delegate
{
    [[self getGroupCollectionManager] removeGroupDelegate: delegate];
}

-(void)removePresetDelegate: (id<LSFSDKPresetDelegate>)delegate
{
    [[self getPresetCollectionManager] removePresetDelegate: delegate];
}

-(void)removeTransitionEffectDelegate: (id<LSFSDKTransitionEffectDelegate>)delegate
{
    [[self getTransitionEffectCollectionManager] removeDelegate: delegate];
}

-(void)removePulseEffectDelegate: (id<LSFSDKPulseEffectDelegate>)delegate
{
    [[self getPulseEffectCollectionManager] removePulseEffectDelegate: delegate];
}

-(void)removeSceneElementDelegate: (id<LSFSDKSceneElementDelegate>)delegate
{
    [[self getSceneElementCollectionManager] removeSceneElementDelegate: delegate];
}

-(void)removeSceneDelegate: (id<LSFSDKSceneDelegate>)delegate
{
    [[self getSceneCollectionManagerV2] removeSceneDelegate: delegate];
}

-(void)removeMasterSceneDelegate: (id<LSFSDKMasterSceneDelegate>)delegate
{
    [[self getMasterSceneCollectionManager] removeMasterSceneDelegate: delegate];
}

-(void)removeControllerDelegate: (id<LSFSDKControllerDelegate>)delegate
{
    [[self getControllerManager] removeDelegate: delegate];
}

-(void)setDefaultLanguage: (NSString *)defaultLanguage
{
    if (defaultLanguage != nil)
    {
        _defaultLanguage = defaultLanguage;
    }
}

-(NSString *)defaultLanguage
{
    return _defaultLanguage;
}

/*
 * Private Functions
 */
-(LSFSDKLampCollectionManager *)getLampCollectionManager
{
    return [self.lightingManager lampCollectionManager];
}

-(LSFSDKPresetCollectionManager *)getPresetCollectionManager
{
    return [self.lightingManager presetCollectionManager];
}

-(LSFSDKGroupCollectionManager *)getGroupCollectionManager
{
    return [self.lightingManager groupCollectionManager];
}

-(LSFSDKTransitionEffectCollectionManager *)getTransitionEffectCollectionManager
{
    return [self.lightingManager transitionEffectCollectionManager];
}

-(LSFSDKPulseEffectCollectionManager *)getPulseEffectCollectionManager
{
    return [self.lightingManager pulseEffectCollectionManager];
}

-(LSFSDKSceneElementCollectionManager *)getSceneElementCollectionManager
{
    return [self.lightingManager sceneElementCollectionManager];
}

-(LSFSDKSceneCollectionManagerV1 *)getSceneCollectionManager
{
    return [self.lightingManager sceneCollectionManagerV1];
}

-(LSFSDKSceneCollectionManagerV2 *)getSceneCollectionManagerV2
{
    return [self.lightingManager sceneCollectionManager];
}

-(LSFSDKMasterSceneCollectionManager *)getMasterSceneCollectionManager
{
    return [self.lightingManager masterSceneCollectionManager];
}

-(LSFControllerManager *)getControllerManager
{
    return [self.lightingManager controllerManager];
}

-(LSFSDKLightingSystemManager *)lightingManager
{
    return _lightingManager;
}

@end
