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

#import "../callback/LSFSDKHelperControllerClientCallback.h"
#import "../callback/LSFSDKHelperControllerServiceManagerCallback.h"
#import "../callback/LSFSDKHelperGroupManagerCallback.h"
#import "../callback/LSFSDKHelperLampManagerCallback.h"
#import "../callback/LSFSDKHelperPresetManagerCallback.h"
#import "../callback/LSFSDKHelperTransitionEffectManagerCallback.h"
#import "../callback/LSFSDKHelperPulseEffectManagerCallback.h"
#import "../callback/LSFSDKHelperSceneElementManagerCallback.h"
#import "../callback/LSFSDKHelperSceneManagerCallback.h"
#import "../callback/LSFSDKHelperMasterSceneManagerCallback.h"
#import "../model/LSFLampAnnouncementData.h"
#import <alljoyn/BusAttachment.h>
#import <internal/LSFControllerClient.h>
#import <internal/LSFControllerServiceManager.h>
#import <internal/LSFLampManager.h>
#import <internal/LSFPresetManager.h>
#import <internal/LSFLampGroupManager.h>
#import <internal/LSFSceneElementManager.h>
#import <internal/LSFSceneManager.h>
#import <internal/LSFMasterSceneManager.h>
#import <internal/LSFTransitionEffectManager.h>
#import <internal/LSFPulseEffectManager.h>

@interface LSFSDKAllJoynManager : NSObject

+(void)initializeWithApplicationName: (NSString *)applicationName controllerClientCallback: (LSFSDKHelperControllerClientCallback *)ccc controllerServiceManagerCallback: (LSFSDKHelperControllerServiceManagerCallback *)csmc lampManagerCallback: (LSFSDKHelperLampManagerCallback *)lmc groupManagerCallback: (LSFSDKHelperGroupManagerCallback *)gmc presetManagerCallback: (LSFSDKHelperPresetManagerCallback *)pmc transitionEffectManagerCallback: (LSFSDKHelperTransitionEffectManagerCallback *)temc pulseEffectManagerCallback: (LSFSDKHelperPulseEffectManagerCallback *)pemc sceneElementManagerCallback: (LSFSDKHelperSceneElementManagerCallback *)semc sceneManagerCallback: (LSFSDKHelperSceneManagerCallback *)smc masterSceneManagerCallback: (LSFSDKHelperMasterSceneManagerCallback *)msmc;
+(void)initializeWithBusAttachment: (ajn::BusAttachment *)busAttachment controllerClientCallback: (LSFSDKHelperControllerClientCallback *)ccc controllerServiceManagerCallback: (LSFSDKHelperControllerServiceManagerCallback *)csmc lampManagerCallback: (LSFSDKHelperLampManagerCallback *)lmc groupManagerCallback: (LSFSDKHelperGroupManagerCallback *)gmc presetManagerCallback: (LSFSDKHelperPresetManagerCallback *)pmc transitionEffectManagerCallback: (LSFSDKHelperTransitionEffectManagerCallback *)temc pulseEffectManagerCallback: (LSFSDKHelperPulseEffectManagerCallback *)pemc sceneElementManagerCallback: (LSFSDKHelperSceneElementManagerCallback *)semc sceneManagerCallback: (LSFSDKHelperSceneManagerCallback *)smc masterSceneManagerCallback: (LSFSDKHelperMasterSceneManagerCallback *)msmc;
+(void)startWithQueue: (dispatch_queue_t)queue;
+(void)stop;
+(void)addNewLamp: (NSString*)lampID lampAnnouncementData:(LSFLampAnnouncementData *)lampAnnData;
+(void)getAboutDataForLampID: (NSString*)lampID;
+(void)setControllerConnected: (BOOL)isConnected;
+(BOOL)getControllerConnected;
+(void)setControllerServiceLeaderVersion: (unsigned int)version;
+(unsigned int)getControllerServiceLeaderVersion;
+(BOOL)isControllerServiceLeaderV1;
+(LSFControllerClient *)getControllerClient;
+(LSFControllerServiceManager *)getControllerServiceManager;
+(LSFLampManager *)getLampManager;
+(LSFLampGroupManager *)getGroupManager;
+(LSFPresetManager *)getPresetManager;
+(LSFSceneElementManager *)getSceneElementManager;
+(LSFSceneManager *)getSceneManager;
+(LSFMasterSceneManager *)getMasterSceneManager;
+(LSFTransitionEffectManager *)getTransitionEffectManager;
+(LSFPulseEffectManager *)getPulseEffectManager;
+(LSFSDKHelperControllerClientCallback *)getControllerClientCallback;
+(LSFSDKHelperControllerServiceManagerCallback *)getControllerServiceManagerCallback;
+(LSFSDKHelperLampManagerCallback *)getLampManagerCallback;
+(LSFSDKHelperGroupManagerCallback *)getGroupManagerCallback;
+(LSFSDKHelperPresetManagerCallback *)getPresetManagerCallback;
+(LSFSDKHelperSceneElementManagerCallback *)getSceneElementManagerCallback;
+(LSFSDKHelperSceneManagerCallback *)getSceneManagerCallback;
+(LSFSDKHelperMasterSceneManagerCallback *)getMasterSceneManagerCallback;
+(LSFSDKHelperTransitionEffectManagerCallback *)getTransitionEffectManagerCallback;
+(LSFSDKHelperPulseEffectManagerCallback *)getPulseEffectManagerCallback;
+(ajn::BusAttachment *)getBusAttachment;

@end
