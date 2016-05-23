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

#import "LSFStateTransitionEffectTests.h"
#import <internal/LSFStateTransitionEffect.h>

@interface LSFStateTransitionEffectTests()

@property (nonatomic) LSFStateTransitionEffect *stateTransitionEffect;

@end

@implementation LSFStateTransitionEffectTests

@synthesize stateTransitionEffect = _stateTransitionEffect;

- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

-(void)testNoArgConstructor
{
    self.stateTransitionEffect = [[LSFStateTransitionEffect alloc] init];
    XCTAssertNotNil(self.stateTransitionEffect, @"State Transition Effect should not be nil");
}

-(void)testStateTransitionEffectWithoutTransitionPeriod
{
    //Create data objects for LSFStateTransitionEffect
    NSString *lampID1 = @"lampID1";
    NSString *lampID2 = @"lampID2";
    NSString *lampID3 = @"lampID3";
    NSArray *initialLampIDs = [NSArray arrayWithObjects: lampID1, lampID2, lampID3, nil];
    
    NSString *lampGroupID1 = @"lampGroupID1";
    NSString *lampGroupID2 = @"lampGroupID2";
    NSArray *initialLampGroupIDs = [NSArray arrayWithObjects: lampGroupID1, lampGroupID2, nil];
    
    LSFLampState *initialState = [[LSFLampState alloc] initWithOnOff: YES brightness: 100 hue: 360 saturation: 100 colorTemp: 2700];
    
    //Create LSFStateTransitionEffect
    self.stateTransitionEffect = [[LSFStateTransitionEffect alloc] initWithLampIDs: initialLampIDs lampGroupIDs: initialLampGroupIDs andLampState: initialState];
    
    //Test extracting the data
    unsigned int transtionPeriod = self.stateTransitionEffect.transitionPeriod;
    XCTAssertTrue(transtionPeriod == 0, @"Transition period should be zero");
    
    NSArray *lampIDs = self.stateTransitionEffect.lamps;
    NSSet *initialLampsSet = [NSSet setWithArray: initialLampIDs];
    NSSet *lampsSet = [NSSet setWithArray: lampIDs];
    BOOL isSetsEqual = [initialLampsSet isEqualToSet: lampsSet];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
    
    NSArray *lampGroupIDs = self.stateTransitionEffect.lampGroups;
    NSSet *initialLampGroupsSet = [NSSet setWithArray: initialLampGroupIDs];
    NSSet *lampGroupsSet = [NSSet setWithArray: lampGroupIDs];
    isSetsEqual = [initialLampGroupsSet isEqualToSet: lampGroupsSet];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
    
    LSFLampState *state = self.stateTransitionEffect.lampState;
    XCTAssertTrue(state.onOff, @"State should be on");
    XCTAssertTrue(state.brightness == 100, @"Brightness should be 100");
    XCTAssertTrue(state.hue == 360, @"Hue should be 360");
    XCTAssertTrue(state.saturation == 100, @"Saturation should be 100");
    XCTAssertTrue(state.colorTemp == 2700, @"Color Temp should be 2700");
}

-(void)testStateTransitionEffectWithTransitionPeriod
{
    //Create data objects for LSFStateTransitionEffect
    NSString *lampID1 = @"lampID1";
    NSString *lampID2 = @"lampID2";
    NSArray *initialLampIDs = [NSArray arrayWithObjects: lampID1, lampID2, nil];
    
    NSString *lampGroupID2 = @"lampGroupID2";
    NSArray *initialLampGroupIDs = [NSArray arrayWithObjects: lampGroupID2, nil];
    
    LSFLampState *initialState = [[LSFLampState alloc] initWithOnOff: NO brightness: 50 hue: 180 saturation: 25 colorTemp: 9000];
    
    unsigned int initialTransitionPeriod = 30;
    
    //Create LSFStateTransitionEffect
    self.stateTransitionEffect = [[LSFStateTransitionEffect alloc] initWithLampIDs: initialLampIDs lampGroupIDs: initialLampGroupIDs lampState: initialState andTransitionPeriod: initialTransitionPeriod];
    
    //Test extracting the data
    unsigned int transtionPeriod = self.stateTransitionEffect.transitionPeriod;
    XCTAssertTrue(transtionPeriod == 30, @"Transition period should be 30");
    
    NSArray *lampIDs = self.stateTransitionEffect.lamps;
    NSSet *initialLampsSet = [NSSet setWithArray: initialLampIDs];
    NSSet *lampsSet = [NSSet setWithArray: lampIDs];
    BOOL isSetsEqual = [initialLampsSet isEqualToSet: lampsSet];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
    
    NSArray *lampGroupIDs = self.stateTransitionEffect.lampGroups;
    NSSet *initialLampGroupsSet = [NSSet setWithArray: initialLampGroupIDs];
    NSSet *lampGroupsSet = [NSSet setWithArray: lampGroupIDs];
    isSetsEqual = [initialLampGroupsSet isEqualToSet: lampGroupsSet];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
    
    LSFLampState *state = self.stateTransitionEffect.lampState;
    XCTAssertFalse(state.onOff, @"State should be on");
    XCTAssertTrue(state.brightness == 50, @"Brightness should be 100");
    XCTAssertTrue(state.hue == 180, @"Hue should be 360");
    XCTAssertTrue(state.saturation == 25, @"Saturation should be 100");
    XCTAssertTrue(state.colorTemp == 9000, @"Color Temp should be 2700");
}

-(void)testSetGetLamps
{
    //Create data objects for LSFStateTransitionEffect
    NSString *lampID1 = @"lampID1";
    NSString *lampID2 = @"lampID2";
    NSArray *initialLampIDs = [NSArray arrayWithObjects: lampID1, lampID2, nil];
    
    NSString *lampGroupID2 = @"lampGroupID2";
    NSArray *initialLampGroupIDs = [NSArray arrayWithObjects: lampGroupID2, nil];
    
    LSFLampState *initialState = [[LSFLampState alloc] initWithOnOff: NO brightness: 50 hue: 180 saturation: 25 colorTemp: 9000];
    
    unsigned int initialTransitionPeriod = 30;
    
    //Create LSFStateTransitionEffect
    self.stateTransitionEffect = [[LSFStateTransitionEffect alloc] initWithLampIDs: initialLampIDs lampGroupIDs: initialLampGroupIDs lampState: initialState andTransitionPeriod: initialTransitionPeriod];
    
    //Set lamps with new array
    NSString *lampID3 = @"lampID3";
    NSString *lampID4 = @"lampID4";
    NSArray *newLampIDs = [NSArray arrayWithObjects: lampID3, lampID4, nil];
    
    self.stateTransitionEffect.lamps = newLampIDs;
    
    //Get lamps
    NSArray *lampIDs = self.stateTransitionEffect.lamps;
    NSSet *initialLampsSet = [NSSet setWithArray: newLampIDs];
    NSSet *lampsSet = [NSSet setWithArray: lampIDs];
    BOOL isSetsEqual = [initialLampsSet isEqualToSet: lampsSet];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testSetGetLampGroups
{
    //Create data objects for LSFStateTransitionEffect
    NSString *lampID1 = @"lampID1";
    NSString *lampID2 = @"lampID2";
    NSArray *initialLampIDs = [NSArray arrayWithObjects: lampID1, lampID2, nil];
    
    NSString *lampGroupID1 = @"lampGroupID1";
    NSArray *initialLampGroupIDs = [NSArray arrayWithObjects: lampGroupID1, nil];
    
    LSFLampState *initialState = [[LSFLampState alloc] initWithOnOff: NO brightness: 50 hue: 180 saturation: 25 colorTemp: 9000];
    
    unsigned int initialTransitionPeriod = 30;
    
    //Create LSFStateTransitionEffect
    self.stateTransitionEffect = [[LSFStateTransitionEffect alloc] initWithLampIDs: initialLampIDs lampGroupIDs: initialLampGroupIDs lampState: initialState andTransitionPeriod: initialTransitionPeriod];
    
    //Set lamp groups with new array
    NSString *lampGroupID2 = @"lampGroupID2";
    NSString *lampGroupID3 = @"lampGroupID3";
    NSArray *newLampGroupIDs = [NSArray arrayWithObjects: lampGroupID2, lampGroupID3, nil];
    
    self.stateTransitionEffect.lampGroups = newLampGroupIDs;
    
    //Get lamp groups
    NSArray *lampIDs = self.stateTransitionEffect.lampGroups;
    NSSet *initialLampsSet = [NSSet setWithArray: newLampGroupIDs];
    NSSet *lampsSet = [NSSet setWithArray: lampIDs];
    BOOL isSetsEqual = [initialLampsSet isEqualToSet: lampsSet];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testSetGetTransitionPeriod
{
    //Create data objects for LSFStateTransitionEffect
    NSString *lampID1 = @"lampID1";
    NSString *lampID2 = @"lampID2";
    NSArray *initialLampIDs = [NSArray arrayWithObjects: lampID1, lampID2, nil];
    
    NSString *lampGroupID1 = @"lampGroupID1";
    NSArray *initialLampGroupIDs = [NSArray arrayWithObjects: lampGroupID1, nil];
    
    LSFLampState *initialState = [[LSFLampState alloc] initWithOnOff: NO brightness: 50 hue: 180 saturation: 25 colorTemp: 9000];
    
    unsigned int initialTransitionPeriod = 30;
    
    //Create LSFStateTransitionEffect
    self.stateTransitionEffect = [[LSFStateTransitionEffect alloc] initWithLampIDs: initialLampIDs lampGroupIDs: initialLampGroupIDs lampState: initialState andTransitionPeriod: initialTransitionPeriod];
    
    //Set transition period
    self.stateTransitionEffect.transitionPeriod = 15;
    
    //Get transition period
    unsigned int newTransitionPeriod = self.stateTransitionEffect.transitionPeriod;
    XCTAssertTrue(newTransitionPeriod == 15, @"Transition period should be 15");
}

-(void)testSetGetLampState
{
    //Create data objects for LSFStateTransitionEffect
    NSString *lampID1 = @"lampID1";
    NSString *lampID2 = @"lampID2";
    NSArray *initialLampIDs = [NSArray arrayWithObjects: lampID1, lampID2, nil];
    
    NSString *lampGroupID1 = @"lampGroupID1";
    NSArray *initialLampGroupIDs = [NSArray arrayWithObjects: lampGroupID1, nil];
    
    LSFLampState *initialState = [[LSFLampState alloc] initWithOnOff: NO brightness: 50 hue: 180 saturation: 25 colorTemp: 9000];

    unsigned int initialTransitionPeriod = 30;
    
    //Create LSFStateTransitionEffect
    self.stateTransitionEffect = [[LSFStateTransitionEffect alloc] initWithLampIDs: initialLampIDs lampGroupIDs: initialLampGroupIDs lampState: initialState andTransitionPeriod: initialTransitionPeriod];
    
    //Set lamp state with new data
    LSFLampState *newState = [[LSFLampState alloc] initWithOnOff: YES brightness: 100 hue: 360 saturation: 100 colorTemp: 2700];
    self.stateTransitionEffect.lampState = newState;
    
    //Get lamp state
    LSFLampState *state = self.stateTransitionEffect.lampState;
    XCTAssertTrue(state.onOff, @"State should be on");
    XCTAssertTrue(state.brightness == 100, @"Brightness should be 100");
    XCTAssertTrue(state.hue == 360, @"Hue should be 360");
    XCTAssertTrue(state.saturation == 100, @"Saturation should be 100");
    XCTAssertTrue(state.colorTemp == 2700, @"Color Temp should be 2700");
}

@end
