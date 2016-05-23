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
#import "LSFSDKNextControllerConnectionDelegate.h"
//#import "LSFLampCollectionManager.h"
//#import "LSFGroupCollectionManager.h"
//#import "LSFPresetCollectionManager.h"
//#import "LSFSceneCollectionManager.h"
//#import "LSFMasterSceneCollectionManager.h"
#import "LSFControllerManager.h"
#import "LSFLampManager.h"
#import "LSFLampGroupManager.h"
#import "LSFPresetManager.h"
#import "LSFSceneManager.h"
#import "LSFMasterSceneManager.h"

/**
 * @warning *Note:* This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK.
 */
@interface LSFLightingSystemManager : NSObject

@property (nonatomic, strong) NSString *DEFAULT_LANGUAGE;

+(LSFLightingSystemManager *)getLightingSystemManager;
-(void)start;
-(void)stop;
//-(LSFLampCollectionManager *)getLampCollectionManager;
//-(LSFGroupCollectionManager *)getGroupCollectionManager;
//-(LSFPresetCollectionManager *)getPresetCollectionManager;
//-(LSFSceneCollectionManager *)getSceneCollectionManager;
//-(LSFMasterSceneCollectionManager *)getMasterSceneCollectionManager;
-(LSFControllerManager *)getControllerManager;
-(LSFLampManager *)getLampManager;
-(LSFLampGroupManager *)getGroupManager;
-(LSFPresetManager *)getPresetManager;
-(LSFSceneManager *)getSceneManager;
-(LSFMasterSceneManager *)getMasterSceneManager;
-(void)postOnNextControllerConnection: (id<LSFSDKNextControllerConnectionDelegate>)delegate;

@end
