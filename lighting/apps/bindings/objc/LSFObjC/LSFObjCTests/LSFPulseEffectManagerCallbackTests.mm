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

#import "LSFPulseEffectManagerCallbackTests.h"
#import "MockPulseEffectManagerCallbackDelegateHandler.h"
#import <internal/LSFPulseEffectManagerCallback.h>
#import <alljoyn/Init.h>

@interface LSFPulseEffectManagerCallbackTests()

@property (nonatomic) MockPulseEffectManagerCallbackDelegateHandler *pemcdh;
@property (nonatomic) LSFPulseEffectManagerCallback *pemc;
@property (nonatomic) NSMutableArray *dataArray;

@end

@implementation LSFPulseEffectManagerCallbackTests

@synthesize pemcdh = _pemcdh;
@synthesize pemc = _pemc;
@synthesize dataArray = _dataArray;

-(void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.

    AllJoynInit();
    self.pemcdh = [[MockPulseEffectManagerCallbackDelegateHandler alloc] init];
    self.pemc = new LSFPulseEffectManagerCallback(self.pemcdh);
    self.dataArray = [[NSMutableArray alloc] init];
}

-(void)tearDown
{
    delete self.pemc;
    self.pemcdh = nil;
    AllJoynShutdown();

    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

-(void)testGetPulseEffect
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *functionName = @"getPulseEffect";
    NSString *pulseEffectID = @"pulseEffectID1";
    NSString *fromPresetID = @"fromPresetEffectID1";
    NSString *toPresetID = @"toPresetEffectID1";
    unsigned int pulsePeriod = 500;
    unsigned int pulseDuration = 1000;
    unsigned int numberPulses = 10;
    NSNumber *period = [[NSNumber alloc] initWithUnsignedInt: pulsePeriod];
    NSNumber *duration = [[NSNumber alloc] initWithUnsignedInt: pulseDuration];
    NSNumber *numPulses = [[NSNumber alloc] initWithUnsignedInt: numberPulses];

    LSFPulseEffectV2 *pe = [[LSFPulseEffectV2 alloc] initWithToPreset: toPresetID period: pulsePeriod duration: pulseDuration numPulses: numberPulses fromPreset: fromPresetID];

    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: pulseEffectID];
    [self.dataArray addObject: fromPresetID];
    [self.dataArray addObject: toPresetID];
    [self.dataArray addObject: period];
    [self.dataArray addObject: duration];
    [self.dataArray addObject: numPulses];

    //Call callback method
    std::string peid([pulseEffectID UTF8String]);
    self.pemc->GetPulseEffectReplyCB(code, peid, *static_cast<lsf::PulseEffect*>(pe.handle));

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.pemcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testApplyPulseEffectOnLamps
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *functionName = @"applyPulseEffectOnLamps";
    NSString *pulseEffectID = @"pulseEffectID1";

    NSString *lampID1 = @"lampID1";
    NSString *lampID2 = @"lampID2";
    NSArray *lampIDs = [NSArray arrayWithObjects: lampID1, lampID2, nil];

    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: pulseEffectID];
    [self.dataArray addObject: lampIDs];

    //Call callback method
    std::string peid([pulseEffectID UTF8String]);
    LSFStringList lampIDList;
    lampIDList.push_back([lampID1 UTF8String]);
    lampIDList.push_back([lampID2 UTF8String]);
    self.pemc->ApplyPulseEffectOnLampsReplyCB(code, peid, lampIDList);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.pemcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testApplyPulseEffectOnLampGroups
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *functionName = @"applyPulseEffectOnLampGroups";
    NSString *pulseEffectID = @"pulseEffectID1";

    NSString *lampGroupID1 = @"lampGroupID1";
    NSString *lampGroupID2 = @"lampGroupID2";
    NSArray *lampGroupIDs = [NSArray arrayWithObjects: lampGroupID1, lampGroupID2, nil];

    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: pulseEffectID];
    [self.dataArray addObject: lampGroupIDs];

    //Call callback method
    std::string peid([pulseEffectID UTF8String]);
    LSFStringList lampGroupIDList;
    lampGroupIDList.push_back([lampGroupID1 UTF8String]);
    lampGroupIDList.push_back([lampGroupID2 UTF8String]);
    self.pemc->ApplyPulseEffectOnLampGroupsReplyCB(code, peid, lampGroupIDList);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.pemcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testGetAllPulseEffectIDs
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *functionName = @"getAllPulseEffectIDs";
    NSString *pulseEffectID1 = @"pulseEffectID1";
    NSString *pulseEffectID2 = @"pulseEffectID2";
    NSString *pulseEffectID3 = @"pulseEffectID3";
    NSString *pulseEffectID4 = @"pulseEffectID4";
    NSArray *pulseEffectIDsArray = [[NSArray alloc] initWithObjects: pulseEffectID1, pulseEffectID2, pulseEffectID3, pulseEffectID4, nil];

    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: pulseEffectIDsArray];

    //Call callback method
    LSFStringList pulseEffectIDList;
    std::string id1([pulseEffectID1 UTF8String]);
    pulseEffectIDList.push_back(id1);
    std::string id2([pulseEffectID2 UTF8String]);
    pulseEffectIDList.push_back(id2);
    std::string id3([pulseEffectID3 UTF8String]);
    pulseEffectIDList.push_back(id3);
    std::string id4([pulseEffectID4 UTF8String]);
    pulseEffectIDList.push_back(id4);
    self.pemc->GetAllPulseEffectIDsReplyCB(code, pulseEffectIDList);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.pemcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testGetPulseEffectName
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *functionName = @"getPulseEffectName";
    NSString *pulseEffectID = @"PulseEffectID1";
    NSString *language = @"en";
    NSString *pulseEffectName = @"testPulseEffectName";

    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: pulseEffectID];
    [self.dataArray addObject: language];
    [self.dataArray addObject: pulseEffectName];

    //Call callback method
    std::string peid([pulseEffectID UTF8String]);
    std::string name([pulseEffectName UTF8String]);
    std::string lang([language UTF8String]);
    self.pemc->GetPulseEffectNameReplyCB(code, peid, lang, name);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.pemcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testSetPulseEffectName
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *functionName = @"setPulseEffectName";
    NSString *pulseEffectID = @"pulseEffectID1";
    NSString *language = @"en";

    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: pulseEffectID];
    [self.dataArray addObject: language];

    //Call callback method
    std::string peid([pulseEffectID UTF8String]);
    std::string lang([language UTF8String]);
    self.pemc->SetPulseEffectNameReplyCB(code, peid, lang);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.pemcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testPulseEffectsNameChanged
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    NSString *functionName = @"pulseEffectsNameChanged";
    NSString *pulseEffectID1 = @"pulseEffectID1";
    NSString *pulseEffectID2 = @"pulseEffectID2";
    NSString *pulseEffectID3 = @"pulseEffectID3";
    NSString *pulseEffectID4 = @"pulseEffectID4";
    NSArray *pulseEffectIDsArray = [[NSArray alloc] initWithObjects: pulseEffectID1, pulseEffectID2, pulseEffectID3, pulseEffectID4, nil];

    [self.dataArray addObject: functionName];
    [self.dataArray addObject: pulseEffectIDsArray];

    //Call callback method
    LSFStringList pulseEffectIDList;
    std::string id1([pulseEffectID1 UTF8String]);
    pulseEffectIDList.push_back(id1);
    std::string id2([pulseEffectID2 UTF8String]);
    pulseEffectIDList.push_back(id2);
    std::string id3([pulseEffectID3 UTF8String]);
    pulseEffectIDList.push_back(id3);
    std::string id4([pulseEffectID4 UTF8String]);
    pulseEffectIDList.push_back(id4);
    self.pemc->PulseEffectsNameChangedCB(pulseEffectIDList);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.pemcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testCreatePulseEffect
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    unsigned int tid = 1234;
    NSNumber *trackingID = [[NSNumber alloc] initWithUnsignedInt: tid];
    NSString *functionName = @"createPulseEffect";
    NSString *pulseEffectID = @"pulseEffectID1";

    [self.dataArray addObject: functionName];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: trackingID];
    [self.dataArray addObject: pulseEffectID];

    //Call callback method
    std::string peid([pulseEffectID UTF8String]);
    self.pemc->CreatePulseEffectReplyCB(code, peid, tid);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.pemcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testPulseEffectsCreated
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    NSString *functionName = @"pulseEffectsCreated";
    NSString *pulseEffectID1 = @"pulseEffectID1";
    NSString *pulseEffectID2 = @"pulseEffectID2";
    NSString *pulseEffectID3 = @"pulseEffectID3";
    NSString *pulseEffectID4 = @"pulseEffectID4";
    NSArray *pulseEffectIDsArray = [[NSArray alloc] initWithObjects: pulseEffectID1, pulseEffectID2, pulseEffectID3, pulseEffectID4, nil];

    [self.dataArray addObject: functionName];
    [self.dataArray addObject: pulseEffectIDsArray];

    //Call callback method
    LSFStringList pulseEffectIDList;
    std::string id1([pulseEffectID1 UTF8String]);
    pulseEffectIDList.push_back(id1);
    std::string id2([pulseEffectID2 UTF8String]);
    pulseEffectIDList.push_back(id2);
    std::string id3([pulseEffectID3 UTF8String]);
    pulseEffectIDList.push_back(id3);
    std::string id4([pulseEffectID4 UTF8String]);
    pulseEffectIDList.push_back(id4);
    self.pemc->PulseEffectsCreatedCB(pulseEffectIDList);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.pemcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testUpdatePulseEffect
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *functionName = @"updatePulseEffect";
    NSString *pulseEffectID = @"pulseEffectID1";

    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: pulseEffectID];

    //Call callback method
    std::string peid([pulseEffectID UTF8String]);
    self.pemc->UpdatePulseEffectReplyCB(code, peid);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.pemcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testPulseEffectsUpdated
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    NSString *functionName = @"pulseEffectsUpdated";
    NSString *pulseEffectID1 = @"pulseEffectID1";
    NSString *pulseEffectID2 = @"pulseEffectID2";
    NSString *pulseEffectID3 = @"pulseEffectID3";
    NSString *pulseEffectID4 = @"pulseEffectID4";
    NSArray *pulseEffectIDsArray = [[NSArray alloc] initWithObjects: pulseEffectID1, pulseEffectID2, pulseEffectID3, pulseEffectID4, nil];

    [self.dataArray addObject: functionName];
    [self.dataArray addObject: pulseEffectIDsArray];

    //Call callback method
    LSFStringList pulseEffectIDList;
    std::string id1([pulseEffectID1 UTF8String]);
    pulseEffectIDList.push_back(id1);
    std::string id2([pulseEffectID2 UTF8String]);
    pulseEffectIDList.push_back(id2);
    std::string id3([pulseEffectID3 UTF8String]);
    pulseEffectIDList.push_back(id3);
    std::string id4([pulseEffectID4 UTF8String]);
    pulseEffectIDList.push_back(id4);
    self.pemc->PulseEffectsUpdatedCB(pulseEffectIDList);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.pemcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testDeletePulseEffect
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *functionName = @"deletePulseEffect";
    NSString *pulseEffectID = @"pulseEffectID1";

    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: pulseEffectID];

    //Call callback method
    std::string peid([pulseEffectID UTF8String]);
    self.pemc->DeletePulseEffectReplyCB(code, peid);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.pemcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testPulseEffectsDeleted
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    NSString *functionName = @"pulseEffectsDeleted";
    NSString *pulseEffectID1 = @"pulseEffectID1";
    NSString *pulseEffectID2 = @"pulseEffectID2";
    NSString *pulseEffectID3 = @"pulseEffectID3";
    NSString *pulseEffectID4 = @"pulseEffectID4";
    NSArray *pulseEffectIDsArray = [[NSArray alloc] initWithObjects: pulseEffectID1, pulseEffectID2, pulseEffectID3, pulseEffectID4, nil];

    [self.dataArray addObject: functionName];
    [self.dataArray addObject: pulseEffectIDsArray];

    //Call callback method
    LSFStringList pulseEffectIDList;
    std::string id1([pulseEffectID1 UTF8String]);
    pulseEffectIDList.push_back(id1);
    std::string id2([pulseEffectID2 UTF8String]);
    pulseEffectIDList.push_back(id2);
    std::string id3([pulseEffectID3 UTF8String]);
    pulseEffectIDList.push_back(id3);
    std::string id4([pulseEffectID4 UTF8String]);
    pulseEffectIDList.push_back(id4);
    self.pemc->PulseEffectsDeletedCB(pulseEffectIDList);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.pemcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

@end
