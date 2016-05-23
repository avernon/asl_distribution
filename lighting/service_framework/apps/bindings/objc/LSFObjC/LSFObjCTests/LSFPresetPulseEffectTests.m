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

#import "LSFPresetPulseEffectTests.h"
#import "LSFObjC/LSFPresetPulseEffect.h"

@interface LSFPresetPulseEffectTests()

@property (nonatomic) LSFPresetPulseEffect *presetPulseEffect;

@end

@implementation LSFPresetPulseEffectTests

@synthesize presetPulseEffect = _presetPulseEffect;

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

-(void)testStatePulseEffectWithoutFromPreset
{
    //Create data objects for LSFStatePulseEffect
    NSString *lampID1 = @"lampID1";
    NSString *lampID2 = @"lampID2";
    NSString *lampID3 = @"lampID3";
    NSArray *initialLampIDs = [NSArray arrayWithObjects: lampID1, lampID2, lampID3, nil];
    
    NSString *lampGroupID1 = @"lampGroupID1";
    NSString *lampGroupID2 = @"lampGroupID2";
    NSArray *initialLampGroupIDs = [NSArray arrayWithObjects: lampGroupID1, lampGroupID2, nil];
    
    NSString *initialToPresetID = @"initialToPresetID";
    
    unsigned int initialPeriod = 15;
    unsigned int initialDuration = 60;
    unsigned int initialNumPulses = 10;
    
    //Create LSFStatePulseEffect
    self.presetPulseEffect = [[LSFPresetPulseEffect alloc] initWithLampIDs: initialLampIDs lampGroupIDs: initialLampGroupIDs toPresetID: initialToPresetID period:initialPeriod duration: initialDuration andNumPulses: initialNumPulses];
    
    //Test extracting the data
    unsigned int period = self.presetPulseEffect.period;
    unsigned int duration = self.presetPulseEffect.duration;
    unsigned int numPulses = self.presetPulseEffect.numPulses;
    XCTAssertTrue(initialPeriod == period, @"Period should be equal to 15");
    XCTAssertTrue(initialDuration == duration, @"Duration should be equal to 60");
    XCTAssertTrue(initialNumPulses == numPulses, @"NumPulses should be equal to 10");
    
    NSArray *lampIDs = self.presetPulseEffect.lamps;
    NSSet *initialLampsSet = [NSSet setWithArray: initialLampIDs];
    NSSet *lampsSet = [NSSet setWithArray: lampIDs];
    BOOL isSetsEqual = [initialLampsSet isEqualToSet: lampsSet];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
    
    NSArray *lampGroupIDs = self.presetPulseEffect.lampGroups;
    NSSet *initialLampGroupsSet = [NSSet setWithArray: initialLampGroupIDs];
    NSSet *lampGroupsSet = [NSSet setWithArray: lampGroupIDs];
    isSetsEqual = [initialLampGroupsSet isEqualToSet: lampGroupsSet];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
    
    NSString *fromPresetID = self.presetPulseEffect.fromPresetID;
    NSString *toPresetID = self.presetPulseEffect.toPresetID;
    XCTAssertTrue([fromPresetID isEqualToString: @"CURRENT_STATE"], @"From preset ID should be equal to CURRENT_STATE");
    XCTAssertTrue([toPresetID isEqualToString: initialToPresetID], @"To preset ID should be equal to initialPresetID");
}

-(void)testStatePulseEffectWithFromPreset
{
    //Create data objects for LSFStatePulseEffect
    NSString *lampID1 = @"lampID1";
    NSString *lampID2 = @"lampID2";
    NSString *lampID3 = @"lampID3";
    NSArray *initialLampIDs = [NSArray arrayWithObjects: lampID1, lampID2, lampID3, nil];
    
    NSString *lampGroupID1 = @"lampGroupID1";
    NSString *lampGroupID2 = @"lampGroupID2";
    NSArray *initialLampGroupIDs = [NSArray arrayWithObjects: lampGroupID1, lampGroupID2, nil];
    
    NSString *initialFromPresetID = @"initialFromPresetID";
    NSString *initialToPresetID = @"initialToPresetID";
    
    unsigned int initialPeriod = 15;
    unsigned int initialDuration = 60;
    unsigned int initialNumPulses = 10;
    
    //Create LSFStatePulseEffect
    self.presetPulseEffect = [[LSFPresetPulseEffect alloc] initWithLampIDs: initialLampIDs lampGroupIDs: initialLampGroupIDs fromPresetID: initialFromPresetID toPresetID: initialToPresetID period:initialPeriod duration: initialDuration andNumPulses: initialNumPulses];
    
    //Test extracting the data
    unsigned int period = self.presetPulseEffect.period;
    unsigned int duration = self.presetPulseEffect.duration;
    unsigned int numPulses = self.presetPulseEffect.numPulses;
    XCTAssertTrue(initialPeriod == period, @"Period should be equal to 15");
    XCTAssertTrue(initialDuration == duration, @"Duration should be equal to 60");
    XCTAssertTrue(initialNumPulses == numPulses, @"NumPulses should be equal to 10");
    
    NSArray *lampIDs = self.presetPulseEffect.lamps;
    NSSet *initialLampsSet = [NSSet setWithArray: initialLampIDs];
    NSSet *lampsSet = [NSSet setWithArray: lampIDs];
    BOOL isSetsEqual = [initialLampsSet isEqualToSet: lampsSet];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
    
    NSArray *lampGroupIDs = self.presetPulseEffect.lampGroups;
    NSSet *initialLampGroupsSet = [NSSet setWithArray: initialLampGroupIDs];
    NSSet *lampGroupsSet = [NSSet setWithArray: lampGroupIDs];
    isSetsEqual = [initialLampGroupsSet isEqualToSet: lampGroupsSet];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
    
    NSString *fromPresetID = self.presetPulseEffect.fromPresetID;
    NSString *toPresetID = self.presetPulseEffect.toPresetID;
    XCTAssertTrue([fromPresetID isEqualToString: initialFromPresetID], @"From preset ID should be equal to initialFromPresetID");
    XCTAssertTrue([toPresetID isEqualToString: initialToPresetID], @"To preset ID should be equal to initialToPresetID");
}

-(void)testSetGetLamps
{
    //Create data objects for LSFStatePulseEffect
    NSString *lampID1 = @"lampID1";
    NSString *lampID2 = @"lampID2";
    NSString *lampID3 = @"lampID3";
    NSArray *initialLampIDs = [NSArray arrayWithObjects: lampID1, lampID2, lampID3, nil];
    
    NSString *lampGroupID1 = @"lampGroupID1";
    NSString *lampGroupID2 = @"lampGroupID2";
    NSArray *initialLampGroupIDs = [NSArray arrayWithObjects: lampGroupID1, lampGroupID2, nil];
    
    NSString *initialFromPresetID = @"initialFromPresetID";
    NSString *initialToPresetID = @"initialToPresetID";
    
    unsigned int initialPeriod = 15;
    unsigned int initialDuration = 60;
    unsigned int initialNumPulses = 10;
    
    //Create LSFStatePulseEffect
    self.presetPulseEffect = [[LSFPresetPulseEffect alloc] initWithLampIDs: initialLampIDs lampGroupIDs: initialLampGroupIDs fromPresetID: initialFromPresetID toPresetID: initialToPresetID period:initialPeriod duration: initialDuration andNumPulses: initialNumPulses];
    
    //Set lamps with new array
    NSString *lampID4 = @"lampID4";
    NSString *lampID5 = @"lampID5";
    NSArray *newLampIDs = [NSArray arrayWithObjects: lampID4, lampID5, nil];
    
    self.presetPulseEffect.lamps = newLampIDs;
    
    //Get lamps
    NSArray *lampIDs = self.presetPulseEffect.lamps;
    NSSet *initialLampsSet = [NSSet setWithArray: newLampIDs];
    NSSet *lampsSet = [NSSet setWithArray: lampIDs];
    BOOL isSetsEqual = [initialLampsSet isEqualToSet: lampsSet];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testSetGetLampGroups
{
    //Create data objects for LSFStatePulseEffect
    NSString *lampID1 = @"lampID1";
    NSString *lampID2 = @"lampID2";
    NSString *lampID3 = @"lampID3";
    NSArray *initialLampIDs = [NSArray arrayWithObjects: lampID1, lampID2, lampID3, nil];
    
    NSString *lampGroupID1 = @"lampGroupID1";
    NSString *lampGroupID2 = @"lampGroupID2";
    NSArray *initialLampGroupIDs = [NSArray arrayWithObjects: lampGroupID1, lampGroupID2, nil];
    
    NSString *initialFromPresetID = @"initialFromPresetID";
    NSString *initialToPresetID = @"initialToPresetID";
    
    unsigned int initialPeriod = 15;
    unsigned int initialDuration = 60;
    unsigned int initialNumPulses = 10;
    
    //Create LSFStatePulseEffect
    self.presetPulseEffect = [[LSFPresetPulseEffect alloc] initWithLampIDs: initialLampIDs lampGroupIDs: initialLampGroupIDs fromPresetID: initialFromPresetID toPresetID: initialToPresetID period:initialPeriod duration: initialDuration andNumPulses: initialNumPulses];
    
    //Set lamp groups with new array
    NSString *lampGroupID3 = @"lampGroupID3";
    NSArray *newLampGroupIDs = [NSArray arrayWithObjects: lampGroupID3, nil];
    
    self.presetPulseEffect.lampGroups = newLampGroupIDs;
    
    //Get lamp groups
    NSArray *lampGroupIDs = self.presetPulseEffect.lampGroups;
    NSSet *initialLampGroupsSet = [NSSet setWithArray: newLampGroupIDs];
    NSSet *lampGroupsSet = [NSSet setWithArray: lampGroupIDs];
    BOOL isSetsEqual = [initialLampGroupsSet isEqualToSet: lampGroupsSet];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testSetGetPeriod
{
    //Create data objects for LSFStatePulseEffect
    NSString *lampID1 = @"lampID1";
    NSString *lampID2 = @"lampID2";
    NSString *lampID3 = @"lampID3";
    NSArray *initialLampIDs = [NSArray arrayWithObjects: lampID1, lampID2, lampID3, nil];
    
    NSString *lampGroupID1 = @"lampGroupID1";
    NSString *lampGroupID2 = @"lampGroupID2";
    NSArray *initialLampGroupIDs = [NSArray arrayWithObjects: lampGroupID1, lampGroupID2, nil];
    
    NSString *initialFromPresetID = @"initialFromPresetID";
    NSString *initialToPresetID = @"initialToPresetID";
    
    unsigned int initialPeriod = 15;
    unsigned int initialDuration = 60;
    unsigned int initialNumPulses = 10;
    
    //Create LSFStatePulseEffect
    self.presetPulseEffect = [[LSFPresetPulseEffect alloc] initWithLampIDs: initialLampIDs lampGroupIDs: initialLampGroupIDs fromPresetID: initialFromPresetID toPresetID: initialToPresetID period:initialPeriod duration: initialDuration andNumPulses: initialNumPulses];
    
    //Set period
    self.presetPulseEffect.period = 30;
    
    //Get period
    unsigned int newPeriod = self.presetPulseEffect.period;
    XCTAssertTrue(newPeriod == 30, @"Period should be equal to 30");
}

-(void)testSetGetDuration
{
    //Create data objects for LSFStatePulseEffect
    NSString *lampID1 = @"lampID1";
    NSString *lampID2 = @"lampID2";
    NSString *lampID3 = @"lampID3";
    NSArray *initialLampIDs = [NSArray arrayWithObjects: lampID1, lampID2, lampID3, nil];
    
    NSString *lampGroupID1 = @"lampGroupID1";
    NSString *lampGroupID2 = @"lampGroupID2";
    NSArray *initialLampGroupIDs = [NSArray arrayWithObjects: lampGroupID1, lampGroupID2, nil];
    
    NSString *initialFromPresetID = @"initialFromPresetID";
    NSString *initialToPresetID = @"initialToPresetID";
    
    unsigned int initialPeriod = 15;
    unsigned int initialDuration = 60;
    unsigned int initialNumPulses = 10;
    
    //Create LSFStatePulseEffect
    self.presetPulseEffect = [[LSFPresetPulseEffect alloc] initWithLampIDs: initialLampIDs lampGroupIDs: initialLampGroupIDs fromPresetID: initialFromPresetID toPresetID: initialToPresetID period:initialPeriod duration: initialDuration andNumPulses: initialNumPulses];
    
    //Set duration
    self.presetPulseEffect.duration = 120;
    
    //Get duration
    unsigned int newDuration = self.presetPulseEffect.duration;
    XCTAssertTrue(newDuration == 120, @"Duration should be equal to 120");
}

-(void)testSetGetNumPulses
{
    //Create data objects for LSFStatePulseEffect
    NSString *lampID1 = @"lampID1";
    NSString *lampID2 = @"lampID2";
    NSString *lampID3 = @"lampID3";
    NSArray *initialLampIDs = [NSArray arrayWithObjects: lampID1, lampID2, lampID3, nil];
    
    NSString *lampGroupID1 = @"lampGroupID1";
    NSString *lampGroupID2 = @"lampGroupID2";
    NSArray *initialLampGroupIDs = [NSArray arrayWithObjects: lampGroupID1, lampGroupID2, nil];
    
    NSString *initialFromPresetID = @"initialFromPresetID";
    NSString *initialToPresetID = @"initialToPresetID";
    
    unsigned int initialPeriod = 15;
    unsigned int initialDuration = 60;
    unsigned int initialNumPulses = 10;
    
    //Create LSFStatePulseEffect
    self.presetPulseEffect = [[LSFPresetPulseEffect alloc] initWithLampIDs: initialLampIDs lampGroupIDs: initialLampGroupIDs fromPresetID: initialFromPresetID toPresetID: initialToPresetID period:initialPeriod duration: initialDuration andNumPulses: initialNumPulses];
    
    //Set num pulses
    self.presetPulseEffect.numPulses = 20;
    
    //Get num pulses
    unsigned int newNumPulses = self.presetPulseEffect.numPulses;
    XCTAssertTrue(newNumPulses == 20, @"Num Pulses should be equal to 20");
}

-(void)testSetGetFromPresetID
{
    //Create data objects for LSFStatePulseEffect
    NSString *lampID1 = @"lampID1";
    NSString *lampID2 = @"lampID2";
    NSString *lampID3 = @"lampID3";
    NSArray *initialLampIDs = [NSArray arrayWithObjects: lampID1, lampID2, lampID3, nil];
    
    NSString *lampGroupID1 = @"lampGroupID1";
    NSString *lampGroupID2 = @"lampGroupID2";
    NSArray *initialLampGroupIDs = [NSArray arrayWithObjects: lampGroupID1, lampGroupID2, nil];
    
    NSString *initialFromPresetID = @"initialFromPresetID";
    NSString *initialToPresetID = @"initialToPresetID";
    
    unsigned int initialPeriod = 15;
    unsigned int initialDuration = 60;
    unsigned int initialNumPulses = 10;
    
    //Create LSFStatePulseEffect
    self.presetPulseEffect = [[LSFPresetPulseEffect alloc] initWithLampIDs: initialLampIDs lampGroupIDs: initialLampGroupIDs fromPresetID: initialFromPresetID toPresetID: initialToPresetID period:initialPeriod duration: initialDuration andNumPulses: initialNumPulses];
    
    //Set from preset ID
    NSString *newFromPresetID = @"newFromPresetID";
    self.presetPulseEffect.fromPresetID = newFromPresetID;
    
    //Get from preset ID
    NSString *fromPresetID = self.presetPulseEffect.fromPresetID;
    XCTAssertTrue([fromPresetID isEqualToString: newFromPresetID], @"From preset ID should be newFromPresetID");
}

-(void)testSetGetToPresetID
{
    //Create data objects for LSFStatePulseEffect
    NSString *lampID1 = @"lampID1";
    NSString *lampID2 = @"lampID2";
    NSString *lampID3 = @"lampID3";
    NSArray *initialLampIDs = [NSArray arrayWithObjects: lampID1, lampID2, lampID3, nil];
    
    NSString *lampGroupID1 = @"lampGroupID1";
    NSString *lampGroupID2 = @"lampGroupID2";
    NSArray *initialLampGroupIDs = [NSArray arrayWithObjects: lampGroupID1, lampGroupID2, nil];
    
    NSString *initialFromPresetID = @"initialFromPresetID";
    NSString *initialToPresetID = @"initialToPresetID";
    
    unsigned int initialPeriod = 15;
    unsigned int initialDuration = 60;
    unsigned int initialNumPulses = 10;
    
    //Create LSFStatePulseEffect
    self.presetPulseEffect = [[LSFPresetPulseEffect alloc] initWithLampIDs: initialLampIDs lampGroupIDs: initialLampGroupIDs fromPresetID: initialFromPresetID toPresetID: initialToPresetID period:initialPeriod duration: initialDuration andNumPulses: initialNumPulses];
    
    //Set to preset ID
    NSString *newToPresetID = @"newToPresetID";
    self.presetPulseEffect.toPresetID = newToPresetID;
    
    //Get to preset ID
    NSString *toPresetID = self.presetPulseEffect.toPresetID;
    XCTAssertTrue([toPresetID isEqualToString: newToPresetID], @"To preset ID should be newToPresetID");
}

@end
