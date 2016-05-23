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

#import "LSFMasterScene.h"
#import "LSFTypes.h"
#import "LSFUtils.h"

@interface LSFMasterScene()

@property (nonatomic, readonly) lsf::MasterScene *masterScene;

@end

@implementation LSFMasterScene

@synthesize masterScene = _masterScene;

-(id)init
{
    self = [super init];
    
    if (self)
    {
        self.handle = new lsf::MasterScene();
    }
    
    return self;
}

-(id)initWithSceneIDs: (NSArray *)sceneIDs
{
    self = [super init];
    
    if (self)
    {
        lsf::LSFStringList sceneIDList = [LSFUtils convertNSArrayToStringList: sceneIDs];
        self.handle = new lsf::MasterScene(sceneIDList);
    }
    
    return self;
}

-(void)setSceneIDs:(NSArray *)sceneIDs
{
    self.masterScene->scenes = [LSFUtils convertNSArrayToStringList: sceneIDs];
}

-(NSArray *)sceneIDs
{
    return [LSFUtils convertStringListToNSArray: self.masterScene->scenes];
}

-(LSFResponseCode)isDependentOnScene: (NSString *)sceneID
{
    std::string sid([sceneID UTF8String]);
    return self.masterScene->IsDependentOnScene(sid);
}

/*
 * Accessor for the internal C++ API object this objective-c class encapsulates
 */
- (lsf::MasterScene *)masterScene
{
    return static_cast<lsf::MasterScene*>(self.handle);
}

@end
