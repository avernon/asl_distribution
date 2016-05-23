/******************************************************************************
 * Copyright (c) AllSeen Alliance. All rights reserved.
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

#import "LSFSDKLightingSystemManager.h"
#import "LSFSDKAllJoynManager.h"
#import "LSFSDKLampCollectionManager.h"
#import "LSFSDKAllLampsLampGroup.h"

/*
 * Private Class
 */
@interface MyControllerAdapter : NSObject  <LSFSDKControllerDelegate, LSFSDKLampDelegate>

@property (nonatomic, weak) id<LSFSDKNextControllerConnectionDelegate> delegate;
@property (nonatomic, strong) LSFSDKLightingSystemManager *manager;
@property (nonatomic) unsigned int delay;

-(id)initWithNextControlleConnectionDelegate: (id<LSFSDKNextControllerConnectionDelegate>)nccd lightingSystemManager: (LSFSDKLightingSystemManager *)lsm andDelay: (unsigned int)delay;

@end

@implementation MyControllerAdapter

@synthesize delegate = _delegate;
@synthesize manager = _manager;
@synthesize delay = _delay;

-(id)initWithNextControlleConnectionDelegate: (id<LSFSDKNextControllerConnectionDelegate>)nccd lightingSystemManager: (LSFSDKLightingSystemManager *)lsm andDelay: (unsigned int)delay
{
    self = [super init];

    if (self)
    {
        self.delegate = nccd;
        self.manager = lsm;
        self.delay = (delay / 1000);
    }

    return self;
}

-(void)onLeaderChange:(LSFSDKController *)leader
{
    NSLog(@"MyControllerAdapter - onLeaderModelChanged() callback executing");

    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(self.delay * NSEC_PER_SEC)), self.manager.dispatchQueue, ^{
        if ([leader connected])
        {
            NSLog(@"MyControllerAdapter - Controller is connected, firing next controller connection delegate");
            [self.manager.controllerManager removeDelegate: self];
            [self.delegate onNextControllerConnection];
        }
    });
}

-(void)onControllerError:(LSFSDKControllerErrorEvent *)errorEvent
{
    //Intentionally left blank
}

-(void)onLampChanged:(LSFSDKLamp *)lamp
{
    //Intentionally left blank
}

-(void)onLampInitialized: (LSFSDKLamp *)lamp
{
    //Intentionally left blank
}

-(void)onLampRemoved: (LSFSDKLamp *)lamp
{
    //Intentionally left blank
}

-(void)onLampError: (LSFSDKLightingItemErrorEvent *)error
{
    //Intentionally left blank
}

@end //End Private Class

@interface LSFSDKLightingSystemManager()

-(void)clearModels;

@end

@implementation LSFSDKLightingSystemManager

@synthesize defaultLanguage = _defaultLanguage;
@synthesize dispatchQueue = _dispatchQueue;
@synthesize controllerClientCB = _controllerClientCB;
@synthesize controllerServiceManagerCB = _controllerServiceManagerCB;
@synthesize groupManagerCB = _groupManagerCB;
@synthesize lampManagerCB = _lampManagerCB;
@synthesize presetManagerCB = _presetManagerCB;
@synthesize transitionEffectManagerCB = _transitionEffectManagerCB;
@synthesize pulseEffectManagerCB = _pulseEffectManagerCB;
@synthesize sceneElementManagerCB = _sceneElementManagerCB;
@synthesize sceneManagerCB = _sceneManagerCB;
@synthesize masterSceneManagerCB = _masterSceneManagerCB;
@synthesize lampCollectionManager = _lampCollectionManager;
@synthesize presetCollectionManager = _presetCollectionManager;
@synthesize groupCollectionManager = _groupCollectionManager;
@synthesize transitionEffectCollectionManager = _transitionEffectCollectionManager;
@synthesize pulseEffectCollectionManager = _pulseEffectCollectionManager;
@synthesize sceneElementCollectionManager = _sceneElementCollectionManager;
@synthesize sceneCollectionManagerV1 = _sceneCollectionManagerV1;
@synthesize sceneCollectionManager = _sceneCollectionManager;
@synthesize masterSceneCollectionManager = _masterSceneCollectionManager;
@synthesize controllerManager = _controllerManager;

-(id)init
{
    self = [super init];

    if (self)
    {
        self.defaultLanguage = @"en";
        LSFSDKAllLampsLampGroup *allLampsLampGroup = [LSFSDKAllLampsLampGroup getInstance];
        [allLampsLampGroup setLightingSystemManager: self];

        _controllerClientCB = [[LSFSDKHelperControllerClientCallback alloc] initWithLightingSystemManager: self];
        _controllerServiceManagerCB = [[LSFSDKHelperControllerServiceManagerCallback alloc] initWithLightingSystemManager: self];
        _groupManagerCB = [[LSFSDKHelperGroupManagerCallback alloc] initWithLightingSystemManager: self];
        _lampManagerCB = [[LSFSDKHelperLampManagerCallback alloc] initWithLightingSystemManager: self];
        _presetManagerCB = [[LSFSDKHelperPresetManagerCallback alloc] initWithLightingSystemManager: self];
        _transitionEffectManagerCB = [[LSFSDKHelperTransitionEffectManagerCallback alloc] initWithLightingSystemManager:self];
        _pulseEffectManagerCB = [[LSFSDKHelperPulseEffectManagerCallback alloc] initWithLightingSystemManager: self];
        _sceneElementManagerCB = [[LSFSDKHelperSceneElementManagerCallback alloc] initWithLightingSystemManager: self];
        _sceneManagerCB = [[LSFSDKHelperSceneManagerCallback alloc] initWithLightingSystemManager: self];
        _masterSceneManagerCB = [[LSFSDKHelperMasterSceneManagerCallback alloc] initWithLightingSystemManager: self];

        _lampCollectionManager = [[LSFSDKLampCollectionManager alloc] initWithLightingSystemManager: self];
        _presetCollectionManager = [[LSFSDKPresetCollectionManager alloc] initWithLightingSystemManager: self];
        _groupCollectionManager = [[LSFSDKGroupCollectionManager alloc] initWithLightingSystemManager: self];
        _transitionEffectCollectionManager = [[LSFSDKTransitionEffectCollectionManager alloc] initWithLightingSystemManager: self];
        _pulseEffectCollectionManager = [[LSFSDKPulseEffectCollectionManager alloc] initWithLightingSystemManager: self];
        _sceneElementCollectionManager = [[LSFSDKSceneElementCollectionManager alloc] initWithLightingSystemManager: self];
        _sceneCollectionManagerV1 = [[LSFSDKSceneCollectionManagerV1 alloc] initWithLightingSystemManager: self];
        _sceneCollectionManager = [[LSFSDKSceneCollectionManagerV2 alloc] initWithLightingSystemManager: self];
        _masterSceneCollectionManager = [[LSFSDKMasterSceneCollectionManager alloc] initWithLightingSystemManager: self];

        _controllerManager = [[LSFControllerManager alloc] init];
        [_controllerManager addDelegate: self];

        [_lampCollectionManager addDelegate: self];

        // For AllLamps groups creation
        [_lampCollectionManager addLampDelegate: _groupManagerCB];
        //TODO - initialize properties
    }

    return self;
}

-(void)initializeWithApplicationName: (NSString *)applicationName dispatchQueue: (dispatch_queue_t)queue andAllJoynDelegate: (id<LSFSDKAllJoynDelegate>)alljoynDelegate
{
    self.dispatchQueue = queue;

    [LSFSDKAllJoynManager initializeWithApplicationName: applicationName controllerClientCallback: _controllerClientCB controllerServiceManagerCallback: _controllerServiceManagerCB lampManagerCallback: _lampManagerCB groupManagerCallback: _groupManagerCB presetManagerCallback: _presetManagerCB transitionEffectManagerCallback: _transitionEffectManagerCB pulseEffectManagerCallback: _pulseEffectManagerCB sceneElementManagerCallback: _sceneElementManagerCB sceneManagerCallback: _sceneManagerCB masterSceneManagerCallback: _masterSceneManagerCB];
}

-(void)initializeWithBusAttachment: (ajn::BusAttachment *)busAttachment dispatchQueue: (dispatch_queue_t)queue andAllJoynDelegate: (id<LSFSDKAllJoynDelegate>)alljoynDelegate
{
    self.dispatchQueue = queue;

    [LSFSDKAllJoynManager initializeWithBusAttachment: busAttachment controllerClientCallback: _controllerClientCB controllerServiceManagerCallback: _controllerServiceManagerCB lampManagerCallback: _lampManagerCB groupManagerCallback: _groupManagerCB presetManagerCallback: _presetManagerCB transitionEffectManagerCallback: _transitionEffectManagerCB pulseEffectManagerCallback: _pulseEffectManagerCB sceneElementManagerCallback: _sceneElementManagerCB sceneManagerCallback: _sceneManagerCB masterSceneManagerCallback: _masterSceneManagerCB];
}

-(void)start
{
    [LSFSDKAllJoynManager startWithQueue: self.dispatchQueue];
}

-(void)stop
{
    [LSFSDKAllJoynManager stop];
}

-(void)setDispatchQueue: (dispatch_queue_t)dispatchQueue
{
    if (dispatchQueue == nil)
    {
        dispatchQueue = dispatch_queue_create("LSFDispatchQueue", NULL);
    }

    _dispatchQueue = dispatchQueue;
}

-(LSFSDKLampCollectionManager *)lampCollectionManager
{
    return _lampCollectionManager;
}

-(LSFSDKPresetCollectionManager *)presetCollectionManager
{
    return _presetCollectionManager;
}

-(LSFSDKGroupCollectionManager *)groupCollectionManager
{
    return _groupCollectionManager;
}

-(LSFSDKTransitionEffectCollectionManager *)transitionEffectCollectionManager
{
    return _transitionEffectCollectionManager;
}

-(LSFSDKPulseEffectCollectionManager *)pulseEffectCollectionManager
{
    return _pulseEffectCollectionManager;
}

-(LSFSDKSceneElementCollectionManager *)sceneElementCollectionManager
{
    return _sceneElementCollectionManager;
}

-(LSFSDKSceneCollectionManagerV1 *)sceneCollectionManagerV1
{
    return _sceneCollectionManagerV1;
}

-(LSFSDKSceneCollectionManagerV2 *)sceneCollectionManager
{
    return _sceneCollectionManager;
}

-(LSFSDKMasterSceneCollectionManager *)masterSceneCollectionManager
{
    return _masterSceneCollectionManager;
}

-(LSFLampManager *)lampManager
{
    return [LSFSDKAllJoynManager getLampManager];
}

-(LSFLampGroupManager *)groupManager
{
    return [LSFSDKAllJoynManager getGroupManager];
}

-(LSFPresetManager *)presetManager
{
    return [LSFSDKAllJoynManager getPresetManager];
}

-(LSFTransitionEffectManager *)transitionEffectManager
{
    return [LSFSDKAllJoynManager getTransitionEffectManager];
}

-(LSFPulseEffectManager *)pulseEffectManager
{
    return [LSFSDKAllJoynManager getPulseEffectManager];
}

-(LSFSceneElementManager *)sceneElementManager
{
    return [LSFSDKAllJoynManager getSceneElementManager];
}

-(LSFSceneManager *)sceneManager
{
    return [LSFSDKAllJoynManager getSceneManager];
}

-(LSFMasterSceneManager *)masterSceneManager
{
    return [LSFSDKAllJoynManager getMasterSceneManager];
}

-(LSFControllerManager *)controllerManager
{
    return _controllerManager;
}

-(void)postOnNextControllerConnection: (id<LSFSDKNextControllerConnectionDelegate>)delegate withDelay: (unsigned int)delay
{
    MyControllerAdapter *controllerAdapter = [[MyControllerAdapter alloc] initWithNextControlleConnectionDelegate: delegate lightingSystemManager: self andDelay: delay];
    [_controllerManager addDelegate: controllerAdapter];
}

/*
 * LSFSDKControllerDelegate implementation
 */
-(void)onLeaderChange:(LSFSDKController *)leader
{
    NSLog(@"LSFSDKLightingSystemManager - onLeaderModelChange() callback executing");

    if (![leader connected])
    {
        NSLog(@"Clearing Models");
        [self clearModels];
    }
}

-(void)onControllerError: (LSFSDKControllerErrorEvent *)errorEvent
{
    //Intentionally left blank
}

/*
 * LSFSDKLampDelegate implementation
 */
-(void)onLampChanged:(LSFSDKLamp *)lamp
{
    [[self groupManagerCB] postUpdateDependentLampGroups: lamp.theID];
}

-(void)onLampInitialized: (LSFSDKLamp *)lamp
{
    //Intentionally left blank
}

-(void)onLampRemoved: (LSFSDKLamp *)lamp
{
    //Intentionally left blank
}

-(void)onLampError: (LSFSDKLightingItemErrorEvent *)error
{
    //Intentionally left blank
}

/*
 * Private Functions
 */
-(void)clearModels
{
    [_lampManagerCB clear];

    [_lampCollectionManager removeAllLamps];
    [_presetCollectionManager removeAllPresets];
    [_groupCollectionManager removeAllGroups];
    [_transitionEffectCollectionManager removeAllTransitionEffects];
    [_pulseEffectCollectionManager removeAllPulseEffects];
    [_sceneElementCollectionManager removeAllSceneElements];
    [_sceneCollectionManagerV1 removeAllScenes];
    [_sceneCollectionManager removeAllScenes];
    [_masterSceneCollectionManager removeAllMasterScenes];
}

@end
