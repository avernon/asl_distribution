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

#import "LSFMasterSceneTests.h"
#import <internal/LSFMasterScene.h>
#import <alljoyn/Init.h>

@interface LSFMasterSceneTests()

@property (nonatomic, strong) LSFMasterScene *masterScene;

@end

@implementation LSFMasterSceneTests

@synthesize masterScene = _masterScene;

- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.

    AllJoynInit();
    self.masterScene = [[LSFMasterScene alloc] init];
}

- (void)tearDown
{
    self.masterScene = nil;
    AllJoynShutdown();
    
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

-(void)testNoArgConstructor
{
    //Create Scene IDs Array
    NSString *sceneID1 = @"sceneID1";
    NSString *sceneID2 = @"sceneID2";
    NSString *sceneID3 = @"sceneID3";
    NSArray *initialSceneIDs = [NSArray arrayWithObjects: sceneID1, sceneID2, sceneID3, nil];
    
    //Create Master Scene Object
    self.masterScene = [[LSFMasterScene alloc] initWithSceneIDs: initialSceneIDs];

    XCTAssertTrue([self.masterScene.sceneIDs isEqualToArray: initialSceneIDs], @"Arrays should be equal");
}

-(void)testSetGetSceneIDs
{
    //Create Scene IDs Array
    NSString *sceneID1 = @"sceneID1";
    NSString *sceneID2 = @"sceneID2";
    NSString *sceneID3 = @"sceneID3";
    NSArray *initialSceneIDs = [NSArray arrayWithObjects: sceneID1, sceneID2, sceneID3, nil];
    
    //Set Scene IDs
    self.masterScene.sceneIDs = initialSceneIDs;
    
    XCTAssertTrue([self.masterScene.sceneIDs isEqualToArray: initialSceneIDs], @"Arrays should be equal");
}

-(void)testIsDependentScene
{
    //Create Scene IDs Array
    NSString *sceneID1 = @"sceneID1";
    NSString *sceneID2 = @"sceneID2";
    NSString *sceneID3 = @"sceneID3";
    NSArray *initialSceneIDs = [NSArray arrayWithObjects: sceneID1, sceneID2, sceneID3, nil];
    
    //Set Scene IDs
    self.masterScene.sceneIDs = initialSceneIDs;
    
    //Test
    LSFResponseCode code = [self.masterScene isDependentOnScene: @"sceneID1"];
    XCTAssertTrue(code == LSF_ERR_DEPENDENCY, @"Scene should be dependent");
    
    code = [self.masterScene isDependentOnScene: @"sceneID2"];
    XCTAssertTrue(code == LSF_ERR_DEPENDENCY, @"Scene should be dependent");
    
    code = [self.masterScene isDependentOnScene: @"sceneID3"];
    XCTAssertTrue(code == LSF_ERR_DEPENDENCY, @"Scene should be dependent");
    
    code = [self.masterScene isDependentOnScene: @"BadSceneID"];
    XCTAssertTrue(code == LSF_OK, @"Scene should not be dependent");
}

@end
