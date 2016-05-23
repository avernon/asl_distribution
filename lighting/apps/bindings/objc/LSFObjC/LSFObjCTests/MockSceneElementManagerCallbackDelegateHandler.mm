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

#import "MockSceneElementManagerCallbackDelegateHandler.h"

@interface MockSceneElementManagerCallbackDelegateHandler()

@property (nonatomic) NSMutableArray *dataArray;

@end

@implementation MockSceneElementManagerCallbackDelegateHandler

@synthesize dataArray = _dataArray;

-(id)init
{
    self = [super init];

    if (self)
    {
        self.dataArray = [[NSMutableArray alloc] init];
    }

    return self;
}

-(NSArray *)getCallbackData
{
    return self.dataArray;
}

//Delegate methods
-(void)getAllSceneElementIDsReplyWithCode: (LSFResponseCode)rc andSceneElementIDs: (NSArray *)sceneElementIDs
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"getAllSceneElementIDs"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: sceneElementIDs];
}

-(void)getSceneElementNameReplyWithCode: (LSFResponseCode)rc sceneElementID: (NSString *)sceneElementID language: (NSString *)language andSceneElementName: (NSString *)sceneElementName
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"getSceneElementName"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: sceneElementID];
    [self.dataArray addObject: language];
    [self.dataArray addObject: sceneElementName];
}

-(void)setSceneElementNameReplyWithCode: (LSFResponseCode)rc sceneElementID: (NSString *)sceneElementID andLanguage: (NSString *)language
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"setSceneElementName"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: sceneElementID];
    [self.dataArray addObject: language];
}

-(void)sceneElementsNameChanged: (NSArray *)sceneElementIDs
{
    [self.dataArray removeAllObjects];
    [self.dataArray addObject: @"sceneElementsNameChanged"];
    [self.dataArray addObject: sceneElementIDs];
}

-(void)createSceneElementReplyWithCode: (LSFResponseCode)rc sceneElementID: (NSString *)sceneElementID andTrackingID: (unsigned int)trackingID
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    NSNumber *tid = [[NSNumber alloc] initWithUnsignedInt: trackingID];
    [self.dataArray addObject: @"createSceneElement"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: sceneElementID];
    [self.dataArray addObject: tid];
}

-(void)sceneElementsCreated: (NSArray *)sceneElementIDs
{
    [self.dataArray removeAllObjects];
    [self.dataArray addObject: @"sceneElementsCreated"];
    [self.dataArray addObject: sceneElementIDs];
}

-(void)updateSceneElementReplyWithCode: (LSFResponseCode)rc andSceneElementID: (NSString *)sceneElementID
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"updateSceneElement"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: sceneElementID];
}

-(void)sceneElementsUpdated: (NSArray *)sceneElementIDs
{
    [self.dataArray removeAllObjects];
    [self.dataArray addObject: @"sceneElementsUpdated"];
    [self.dataArray addObject: sceneElementIDs];
}

-(void)deleteSceneElementReplyWithCode: (LSFResponseCode)rc andSceneElementID: (NSString *)sceneElementID
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"deleteSceneElement"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: sceneElementID];
}

-(void)sceneElementsDeleted: (NSArray *)sceneElementIDs
{
    [self.dataArray removeAllObjects];
    [self.dataArray addObject: @"sceneElementsDeleted"];
    [self.dataArray addObject: sceneElementIDs];
}

-(void)getSceneElementReplyWithCode: (LSFResponseCode)rc sceneElementID: (NSString *)sceneElementID andSceneElement: (LSFSceneElement *)sceneElement
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"getSceneElement"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: sceneElementID];
    [self.dataArray addObject: sceneElement.lamps];
    [self.dataArray addObject: sceneElement.lampGroups];
    [self.dataArray addObject: sceneElement.effectID];
}

-(void)applySceneElementReplyWithCode: (LSFResponseCode)rc andSceneElementID: (NSString *)sceneElementID
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"applySceneElement"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: sceneElementID];
}

-(void)sceneElementsApplied: (NSArray *)sceneElementIDs
{
    [self.dataArray removeAllObjects];
    [self.dataArray addObject: @"sceneElementsApplied"];
    [self.dataArray addObject: sceneElementIDs];
}

@end
