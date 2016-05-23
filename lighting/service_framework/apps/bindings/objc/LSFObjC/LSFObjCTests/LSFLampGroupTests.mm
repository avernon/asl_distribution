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

#import "LSFLampGroupTests.h"
#import "LSFObjC/LSFLampGroup.h"

@interface LSFLampGroupTests()

@property (nonatomic) LSFLampGroup *lampGroup;

@end

@implementation LSFLampGroupTests

@synthesize lampGroup = _lampGroup;

- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
    
    self.lampGroup = [[LSFLampGroup alloc] init];
}

- (void)tearDown
{
    self.lampGroup = nil;
    
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

-(void)testLamps
{
    //Test lamp ID set
    NSString *lampID1 = @"lampID1";
    NSString *lampID2 = @"lampID2";
    NSString *lampID3 = @"lampID3";
    
    NSArray *setLampIDs = [NSArray arrayWithObjects: lampID1, lampID2, lampID3, nil];
    [self.lampGroup setLamps: setLampIDs];
    
    NSArray *getlampIDs = [self.lampGroup lamps];
   
    NSSet *startData = [[NSSet alloc] initWithArray: setLampIDs];
    NSSet *endData = [[NSSet alloc] initWithArray: getlampIDs];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testGroups
{
    //Test lamp group ID set
    NSString *lampGroupID1 = @"lampGroupID1";
    NSString *lampGroupID2 = @"lampGroupID2";
    
    NSArray *setLampGroupIDs = [NSArray arrayWithObjects: lampGroupID1, lampGroupID2, nil];
    [self.lampGroup setLampGroups: setLampGroupIDs];
    
    NSArray *getlampGroupIDs = [self.lampGroup lampGroups];
    
    NSSet *startData = [[NSSet alloc] initWithArray: setLampGroupIDs];
    NSSet *endData = [[NSSet alloc] initWithArray: getlampGroupIDs];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testIsDependentGroup;
{
    //Test lamp group ID set
    NSString *lampGroupID1 = @"lampGroupID1";
    NSString *lampGroupID2 = @"lampGroupID2";
    NSString *nonDependentGroupID = @"nonDependentGroupID";
    
    NSArray *setLampGroupIDs = [NSArray arrayWithObjects: lampGroupID1, lampGroupID2, nil];
    [self.lampGroup setLampGroups: setLampGroupIDs];
    
    LSFResponseCode code;
    code = [self.lampGroup isDependentLampGroup: lampGroupID1];
    XCTAssertTrue(code == LSF_ERR_DEPENDENCY, @"Response code should be equal to LSF_ERR_DEPENDENCY");
    
    code = [self.lampGroup isDependentLampGroup: lampGroupID2];
    XCTAssertTrue(code == LSF_ERR_DEPENDENCY, @"Response code should be equal to LSF_ERR_DEPENDENCY");
    
    code = [self.lampGroup isDependentLampGroup: nonDependentGroupID];
    XCTAssertTrue(code == LSF_OK, @"Response code should be equal to LSF_OK");
}

@end
