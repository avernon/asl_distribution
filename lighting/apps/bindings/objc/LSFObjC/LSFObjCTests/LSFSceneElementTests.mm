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

#import "LSFSceneElementTests.h"
#import <internal/LSFSceneElement.h>
#import <alljoyn/Init.h>

@interface LSFSceneElementTests()

@property (nonatomic) LSFSceneElement *sceneElement;

@end

@implementation LSFSceneElementTests

@synthesize sceneElement = _sceneElement;

-(void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.

    AllJoynInit();
    self.sceneElement = [[LSFSceneElement alloc] init];
}

-(void)tearDown
{
    self.sceneElement = nil;
    AllJoynShutdown();

    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

-(void)testNoArgConstructor
{
    XCTAssertTrue((self.sceneElement.lamps.count == 0), @"Lamp IDs should be empty");
    XCTAssertTrue((self.sceneElement.lampGroups.count == 0), @"Lamp Group IDs should be empty");
    XCTAssertTrue([self.sceneElement.effectID isEqualToString: @""], @"Effect ID should be an empty string");
}

-(void)testConstructorWithArguments
{
    NSArray *lampIDs = [NSArray arrayWithObjects: @"lampID1", @"lampID2", @"lampID3", nil];
    NSArray *lampGroupIDs = [NSArray arrayWithObjects: @"lampGroupID1", @"lampGroupID2", nil];
    NSString *effectID = @"testEffectID";

    self.sceneElement = [[LSFSceneElement alloc] initWithLampIDs: lampIDs lampGroupIDs: lampGroupIDs andEffectID: effectID];

    XCTAssertTrue((self.sceneElement.lamps.count == 3), @"Lamp IDs should be 3");
    XCTAssertTrue([self.sceneElement.lamps isEqualToArray: lampIDs], @"Lamp IDs array should be equal");
    XCTAssertTrue((self.sceneElement.lampGroups.count == 2), @"Lamp Group IDs should be 2");
    XCTAssertTrue([self.sceneElement.lampGroups isEqualToArray: lampGroupIDs], @"Lamp Group IDs array should be equal");
    XCTAssertTrue([self.sceneElement.effectID isEqualToString: effectID], @"Effect ID should be an equal");
}

-(void)testSetGetLamps
{
    XCTAssertTrue((self.sceneElement.lamps.count == 0), @"Lamp IDs should be empty");

    NSArray *lampIDs = [NSArray arrayWithObjects: @"lampID1", @"lampID2", @"lampID3", nil];
    self.sceneElement.lamps = lampIDs;

    XCTAssertTrue((self.sceneElement.lamps.count == 3), @"Lamp IDs should be 3");
    XCTAssertTrue([self.sceneElement.lamps isEqualToArray: lampIDs], @"Lamp IDs array should be equal");
}

-(void)testSetGetLampGroups
{
    XCTAssertTrue((self.sceneElement.lampGroups.count == 0), @"Lamp Group IDs should be empty");

    NSArray *lampGroupIDs = [NSArray arrayWithObjects: @"lampGroupID1", @"lampGroupID2", nil];
    self.sceneElement.lampGroups = lampGroupIDs;

    XCTAssertTrue((self.sceneElement.lampGroups.count == 2), @"Lamp Group IDs should be 2");
    XCTAssertTrue([self.sceneElement.lampGroups isEqualToArray: lampGroupIDs], @"Lamp Group IDs array should be equal");
}

-(void)testSetGetEffectID
{
    XCTAssertTrue([self.sceneElement.effectID isEqualToString: @""], @"Effect ID should be an empty string");

    NSString *effectID = @"testEffectID";
    self.sceneElement.effectID = effectID;

    XCTAssertTrue([self.sceneElement.effectID isEqualToString: effectID], @"Effect ID should be an equal");
}

@end
