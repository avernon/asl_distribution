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
#import "AJNBusAttachment.h"
#import "LSFLampGroupManager.h"
#import "LSFSceneManager.h"
#import "LSFMasterSceneManager.h"
#import "LSFSampleControllerClientCallback.h"
#import "LSFSampleControllerServiceManagerCallback.h"
#import "LSFSampleLampManagerCallback.h"
#import "LSFSampleLampGroupManagerCallback.h"
#import "LSFSamplePresetManagerCallback.h"
#import "LSFSampleSceneManagerCallback.h"
#import "LSFSampleMasterSceneManagerCallback.h"
#import "LSFLampAnnouncementData.h"
#import "LSFAboutManager.h"

@interface LSFAllJoynManager : NSObject

@property (nonatomic, strong) AJNBusAttachment *bus;
@property (nonatomic, strong) LSFControllerClient *lsfControllerClient;
@property (nonatomic, strong) LSFControllerServiceManager *lsfControllerServiceManager;
@property (nonatomic, strong) LSFLampManager *lsfLampManager;
@property (nonatomic, strong) LSFLampGroupManager *lsfLampGroupManager;
@property (nonatomic, strong) LSFPresetManager *lsfPresetManager;
@property (nonatomic, strong) LSFSceneManager *lsfSceneManager;
@property (nonatomic, strong) LSFMasterSceneManager *lsfMasterSceneManager;
@property (nonatomic, strong) LSFSampleControllerClientCallback *sccc;
@property (nonatomic, strong) LSFSampleControllerServiceManagerCallback *scsmc;
@property (nonatomic, strong) LSFSampleLampManagerCallback *slmc;
@property (nonatomic, strong) LSFSampleLampGroupManagerCallback *slgmc;
@property (nonatomic, strong) LSFSamplePresetManagerCallback *spmc;
@property (nonatomic, strong) LSFSampleSceneManagerCallback *ssmc;
@property (nonatomic, strong) LSFSampleMasterSceneManagerCallback *smsmc;
@property (nonatomic, strong) LSFAboutManager *aboutManager;
@property (nonatomic) BOOL isConnectedToController;

+(LSFAllJoynManager *)getAllJoynManager;
-(void)addNewLamp: (NSString*)lampID lampAnnouncementData:(LSFLampAnnouncementData*)lampAnnData;
-(void)getAboutDataForLampID: (NSString*)lampID;

@end
