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

#import "LSFSceneElement.h"
#import "LSFUtils.h"
#import <LSFTypes.h>

@interface LSFSceneElement()

@property (nonatomic, readonly) lsf::SceneElement *sceneElement;

@end

@implementation LSFSceneElement

@synthesize sceneElement = _sceneElement;

-(id)init
{
    self = [super init];

    if (self)
    {
        self.handle = new lsf::SceneElement();
    }

    return self;
}

-(id)initWithLampIDs: (NSArray *)lampIDs lampGroupIDs: (NSArray *)lampGroupIDs andEffectID: (NSString *)effectID
{
    self = [super init];

    if (self)
    {
        lsf::LSFStringList lampIDList = [LSFUtils convertNSArrayToStringList: lampIDs];
        lsf::LSFStringList lampGroupIDList = [LSFUtils convertNSArrayToStringList: lampGroupIDs];
        std::string eid([effectID UTF8String]);
        self.handle = new lsf::SceneElement(lampIDList, lampGroupIDList, eid);
    }

    return self;
}

-(void)setLamps: (NSArray *)lampIDs
{
    lsf::LSFStringList lampIDList = [LSFUtils convertNSArrayToStringList: lampIDs];
    self.sceneElement->lamps = lampIDList;
}

-(NSArray *)lamps
{
    lsf::LSFStringList lampIDs = self.sceneElement->lamps;
    return [LSFUtils convertStringListToNSArray: lampIDs];
}

-(void)setLampGroups: (NSArray *)lampGroupIDs
{
    lsf::LSFStringList lampGroupIDList = [LSFUtils convertNSArrayToStringList: lampGroupIDs];
    self.sceneElement->lampGroups = lampGroupIDList;
}

-(NSArray *)lampGroups
{
    lsf::LSFStringList lampGroupIDs = self.sceneElement->lampGroups;
    return [LSFUtils convertStringListToNSArray: lampGroupIDs];
}

-(void)setEffectID:(NSString *)effectID
{
    std::string eid([effectID UTF8String]);
    self.sceneElement->effectID = eid;
}

-(NSString *)effectID
{
    return [NSString stringWithUTF8String: (self.sceneElement->effectID).c_str()];
}

/*
 * Accessor for the internal C++ API object this objective-c class encapsulates
 */
- (lsf::SceneElement *)sceneElement
{
    return static_cast<lsf::SceneElement*>(self.handle);
}

@end
