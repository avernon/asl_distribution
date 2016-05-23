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

#import "LSFLightingSystemManager.h"
#import "LSFAllJoynManager.h"
#import "LSFSDKControllerAdapter.h"

@interface LSFLightingSystemManager()

//@property (nonatomic, strong) LSFLampCollectionManager *lampCollectionManager;
//@property (nonatomic, strong) LSFGroupCollectionManager *groupCollectionManager
//@property (nonatomic, strong) LSFPresetCollectionManager *presetCollectionManager;
//@property (nonatomic, strong) LSFSceneCollectionManager *sceneCollectionManager;
//@property (nonatomic, strong) LSFMasterSceneCollectionManager *masterSceneCollectionManager;
@property (nonatomic, strong) LSFControllerManager *controllerManager;

@end

@implementation LSFLightingSystemManager

@synthesize DEFAULT_LANGUAGE = _DEFAULT_LANGUAGE;
@synthesize controllerManager = _controllerManager;

+(LSFLightingSystemManager *)getLightingSystemManager
{
    static LSFLightingSystemManager *director = nil;
    static dispatch_once_t onceToken;

    dispatch_once(&onceToken, ^{
        director = [[self alloc] init];
    });

    return director;
}

-(id)init
{
    self = [super init];

    if (self)
    {
        self.DEFAULT_LANGUAGE = @"en";
        self.controllerManager = [[LSFControllerManager alloc] init];

        //TODO - initialize private properties
    }

    return self;
}

-(void)start
{
    LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];
    [ajManager start];
}

-(void)stop
{
    LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];
    [ajManager stop];
}

//-(LSFLampCollectionManager *)getLampCollectionManager;
//-(LSFGroupCollectionManager *)getGroupCollectionManager;
//-(LSFPresetCollectionManager *)getPresetCollectionManager;
//-(LSFSceneCollectionManager *)getSceneCollectionManager;
//-(LSFMasterSceneCollectionManager *)getMasterSceneCollectionManager;

-(LSFControllerManager *)getControllerManager
{
    return self.controllerManager;
}

-(LSFLampManager *)getLampManager
{
    LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];
    return ajManager.lsfLampManager;
}

-(LSFLampGroupManager *)getGroupManager
{
    LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];
    return ajManager.lsfLampGroupManager;
}

-(LSFPresetManager *)getPresetManager
{
    LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];
    return ajManager.lsfPresetManager;
}

-(LSFSceneManager *)getSceneManager
{
    LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];
    return ajManager.lsfSceneManager;
}

-(LSFMasterSceneManager *)getMasterSceneManager
{
    LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];
    return ajManager.lsfMasterSceneManager;
}

-(void)postOnNextControllerConnection: (id<LSFSDKNextControllerConnectionDelegate>)delegate
{
    LSFSDKControllerAdapter *controllerAdapter = [[LSFSDKControllerAdapter alloc] init];
    controllerAdapter.delegate = delegate;

    LSFControllerManager *controllerManager = [self getControllerManager];
    [controllerManager addDelegate: controllerAdapter];
}

@end
