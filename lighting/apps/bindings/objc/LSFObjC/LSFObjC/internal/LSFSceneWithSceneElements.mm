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

#import "LSFSceneWithSceneElements.h"
#import "LSFUtils.h"
#import <LSFTypes.h>

@interface LSFSceneWithSceneElements()

@property (nonatomic, readonly) lsf::SceneWithSceneElements *sceneWithSceneElements;

@end

@implementation LSFSceneWithSceneElements

@synthesize sceneWithSceneElements = _sceneWithSceneElements;

-(id)init
{
    self = [super init];

    if (self)
    {
        self.handle = new lsf::SceneWithSceneElements();
    }

    return self;
}

-(id)initWithSceneElementIDs: (NSArray *)sceneElementIDs
{
    self = [super init];

    if (self)
    {
        lsf::LSFStringList sceneElementIDList = [LSFUtils convertNSArrayToStringList: sceneElementIDs];
        self.handle = new lsf::SceneWithSceneElements(sceneElementIDList);
    }

    return self;
}

-(LSFResponseCode)isDependentOnSceneElementWithID: (NSString *)sceneElementID
{
    std::string seid([sceneElementID UTF8String]);
    return self.sceneWithSceneElements->IsDependentOnSceneElement(seid);
}

-(void)setSceneElements: (NSArray *)sceneElements
{
    lsf::LSFStringList sceneElementIDList = [LSFUtils convertNSArrayToStringList: sceneElements];
    self.sceneWithSceneElements->sceneElements = sceneElementIDList;
}

-(NSArray *)sceneElements
{
    lsf::LSFStringList sceneElementIDs = self.sceneWithSceneElements->sceneElements;
    return [LSFUtils convertStringListToNSArray: sceneElementIDs];
}

/*
 * Accessor for the internal C++ API object this objective-c class encapsulates
 */
-(lsf::SceneWithSceneElements *)sceneWithSceneElements
{
    return static_cast<lsf::SceneWithSceneElements*>(self.handle);
}

@end
