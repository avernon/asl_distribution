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

#import "MockMasterSceneManagerCallbackDelegateHandler.h"

@interface MockMasterSceneManagerCallbackDelegateHandler()

@property (nonatomic) NSMutableArray *dataArray;

@end

@implementation MockMasterSceneManagerCallbackDelegateHandler

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
-(void)getAllMasterSceneIDsReplyWithCode: (LSFResponseCode)rc andMasterSceneIDs: (NSArray *)masterSceneIDs
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"getAllMasterSceneIDs"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: masterSceneIDs];
}

-(void)getMasterSceneNameReplyWithCode: (LSFResponseCode)rc masterSceneID: (NSString *)masterSceneID language: (NSString *)language andName: (NSString *)masterSceneName
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"getMasterSceneName"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: masterSceneID];
    [self.dataArray addObject: language];
    [self.dataArray addObject: masterSceneName];
}

-(void)setMasterSceneNameReplyWithCode: (LSFResponseCode)rc masterSceneID: (NSString *)masterSceneID andLanguage: (NSString *)language
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"setMasterSceneName"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: masterSceneID];
    [self.dataArray addObject: language];
}

-(void)masterScenesNameChanged: (NSArray *)masterSceneIDs
{
    [self.dataArray removeAllObjects];
    [self.dataArray addObject: @"masterScenesNameChanged"];
    [self.dataArray addObject: masterSceneIDs];
}

-(void)createMasterSceneReplyWithCode: (LSFResponseCode)rc andMasterSceneID: (NSString *)masterSceneID
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"createMasterScene"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: masterSceneID];
}

-(void)masterScenesCreated: (NSArray *)masterSceneIDs
{
    [self.dataArray removeAllObjects];
    [self.dataArray addObject: @"masterScenesCreated"];
    [self.dataArray addObject: masterSceneIDs];
}

-(void)getMasterSceneReplyWithCode: (LSFResponseCode)rc masterSceneID: (NSString *)masterSceneID andMasterScene: (LSFMasterScene *)masterScene
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"getMasterScene"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: masterSceneID];
    [self.dataArray addObject: masterScene.sceneIDs];
}

-(void)deleteMasterSceneReplyWithCode: (LSFResponseCode)rc andMasterSceneID: (NSString *)masterSceneID
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"deleteMasterScene"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: masterSceneID];
}

-(void)masterScenesDeleted: (NSArray *)masterSceneIDs
{
    [self.dataArray removeAllObjects];
    [self.dataArray addObject: @"masterScenesDeleted"];
    [self.dataArray addObject: masterSceneIDs];
}

-(void)updateMasterSceneReplyWithCode: (LSFResponseCode)rc andMasterSceneID: (NSString *)masterSceneID
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"updateMasterScene"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: masterSceneID];
}

-(void)masterScenesUpdated: (NSArray *)masterSceneIDs
{
    [self.dataArray removeAllObjects];
    [self.dataArray addObject: @"masterScenesUpdated"];
    [self.dataArray addObject: masterSceneIDs];
}

-(void)applyMasterSceneReplyWithCode: (LSFResponseCode)rc andMasterSceneID: (NSString *)masterSceneID
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"applyMasterScene"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: masterSceneID];
}

-(void)masterScenesApplied: (NSArray *)masterSceneIDs
{
    [self.dataArray removeAllObjects];
    [self.dataArray addObject: @"masterScenesApplied"];
    [self.dataArray addObject: masterSceneIDs];
}

@end
