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

#import "LSFSceneWithSceneElementsTests.h"
#import <internal/LSFSceneWithSceneElements.h>
#import <alljoyn/Init.h>

@interface LSFSceneWithSceneElementsTests()

@property (nonatomic) LSFSceneWithSceneElements *sceneWithSceneElements;

@end

@implementation LSFSceneWithSceneElementsTests

@synthesize sceneWithSceneElements = _sceneWithSceneElements;

-(void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.

    AllJoynInit();
    self.sceneWithSceneElements = [[LSFSceneWithSceneElements alloc] init];
}

-(void)tearDown
{
    self.sceneWithSceneElements = nil;
    AllJoynShutdown();

    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

-(void)testNoArgConstructor
{
    XCTAssertTrue((self.sceneWithSceneElements.sceneElements.count == 0), @"Scene Element IDs should be empty");
}

-(void)testConstructorWithArguments
{
    NSArray *sceneElementIDs = [NSArray arrayWithObjects: @"sceneElementID1", @"sceneElementID2", @"sceneElementID3", nil];

    self.sceneWithSceneElements = [[LSFSceneWithSceneElements alloc] initWithSceneElementIDs: sceneElementIDs];

    XCTAssertTrue((self.sceneWithSceneElements.sceneElements.count == 3), @"Scene Element IDs should be 3");
    XCTAssertTrue([self.sceneWithSceneElements.sceneElements isEqualToArray: sceneElementIDs], @"Scene Element IDs should be equal");
}

-(void)testSetGetSceneElementIDs
{
    XCTAssertTrue((self.sceneWithSceneElements.sceneElements.count == 0), @"Scene Element IDs should be empty");

    NSArray *sceneElementIDs = [NSArray arrayWithObjects: @"sceneElementID1", @"sceneElementID2", @"sceneElementID3", nil];
    self.sceneWithSceneElements.sceneElements = sceneElementIDs;

    XCTAssertTrue((self.sceneWithSceneElements.sceneElements.count == 3), @"Scene Element IDs should be 3");
    XCTAssertTrue([self.sceneWithSceneElements.sceneElements isEqualToArray: sceneElementIDs], @"Scene Element IDs should be equal");
}

-(void)testIsDependentOnSceneElementID
{
    NSString *sceneElementID1 = @"sceneElementID1";
    NSString *sceneElementID2 = @"sceneElementID2";
    NSString *sceneElementID3 = @"sceneElementID3";
    NSString *nondependentSceneElementID = @"nondependentSceneElementID";
    NSArray *sceneElementIDs = [NSArray arrayWithObjects: sceneElementID1, sceneElementID2, sceneElementID3, nil];

    self.sceneWithSceneElements = [[LSFSceneWithSceneElements alloc] initWithSceneElementIDs: sceneElementIDs];

    LSFResponseCode status = [self.sceneWithSceneElements isDependentOnSceneElementWithID: sceneElementID1];
    XCTAssertTrue(status == LSF_ERR_DEPENDENCY, @"Status should be LSF_ERR_DEPENDENCY");

    status = [self.sceneWithSceneElements isDependentOnSceneElementWithID: sceneElementID2];
    XCTAssertTrue(status == LSF_ERR_DEPENDENCY, @"Status should be LSF_ERR_DEPENDENCY");

    status = [self.sceneWithSceneElements isDependentOnSceneElementWithID: sceneElementID3];
    XCTAssertTrue(status == LSF_ERR_DEPENDENCY, @"Status should be LSF_ERR_DEPENDENCY");

    status = [self.sceneWithSceneElements isDependentOnSceneElementWithID: nondependentSceneElementID];
    XCTAssertTrue(status == LSF_OK, @"Status should be LSF_OK");
}

@end
