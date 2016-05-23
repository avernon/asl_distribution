/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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
#import "LSFControllerClient.h"
#import "LSFControllerServiceManager.h"
#import "LSFLampManager.h"
#import "LSFPresetManager.h"
#import "BusAttachment.h"
#import "LSFLampGroupManager.h"
#import "LSFSceneManager.h"
#import "LSFMasterSceneManager.h"
#import "LSFTransitionEffectManager.h"
#import "LSFPulseEffectManager.h"
#import "LSFHelperControllerClientCallback.h"
#import "LSFHelperControllerServiceManagerCallback.h"
#import "LSFHelperLampManagerCallback.h"
#import "LSFHelperLampGroupManagerCallback.h"
#import "LSFHelperPresetManagerCallback.h"
#import "LSFHelperSceneManagerCallback.h"
#import "LSFHelperMasterSceneManagerCallback.h"
#import "LSFHelperTransitionEffectManagerCallback.h"
#import "LSFHelperPulseEffectManagerCallback.h"
#import "LSFLampAnnouncementData.h"
#import "LSFAboutManager.h"
#import "LSFSDKLightingSystemManager.h"

#ifdef __aarch64__
#define AJ_ARCH_STR @"64-bit"
#else
#define AJ_ARCH_STR @"32-bit"
#endif

/**
 * @warning *Note:* This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK.
 */
@interface LSFAllJoynManager : NSObject

@property (nonatomic, strong) LSFSDKLightingSystemManager *director;
@property (nonatomic, readonly) ajn::BusAttachment *bus;
@property (nonatomic, strong) LSFControllerClient *lsfControllerClient;
@property (nonatomic, strong) LSFControllerServiceManager *lsfControllerServiceManager;
@property (nonatomic, strong) LSFLampManager *lsfLampManager;
@property (nonatomic, strong) LSFLampGroupManager *lsfLampGroupManager;
@property (nonatomic, strong) LSFPresetManager *lsfPresetManager;
@property (nonatomic, strong) LSFSceneManager *lsfSceneManager;
@property (nonatomic, strong) LSFMasterSceneManager *lsfMasterSceneManager;
@property (nonatomic, strong) LSFTransitionEffectManager *lsfTransitionEffectManager;
@property (nonatomic, strong) LSFPulseEffectManager *lsfPulseEffectManager;
@property (nonatomic, strong) LSFHelperControllerClientCallback *sccc;
@property (nonatomic, strong) LSFHelperControllerServiceManagerCallback *scsmc;
@property (nonatomic, strong) LSFHelperLampManagerCallback *slmc;
@property (nonatomic, strong) LSFHelperLampGroupManagerCallback *slgmc;
@property (nonatomic, strong) LSFHelperPresetManagerCallback *spmc;
@property (nonatomic, strong) LSFHelperSceneManagerCallback *ssmc;
@property (nonatomic, strong) LSFHelperMasterSceneManagerCallback *smsmc;
@property (nonatomic, strong) LSFHelperTransitionEffectManagerCallback *temc;
@property (nonatomic, strong) LSFHelperPulseEffectManagerCallback *pemc;
@property (nonatomic, strong) LSFAboutManager *aboutManager;
@property (nonatomic) BOOL isConnectedToController;

+(LSFAllJoynManager *)getAllJoynManager;
-(void)start;
-(void)stop;
-(void)addNewLamp: (NSString*)lampID lampAnnouncementData:(LSFLampAnnouncementData*)lampAnnData;
-(void)getAboutDataForLampID: (NSString*)lampID;

@end
