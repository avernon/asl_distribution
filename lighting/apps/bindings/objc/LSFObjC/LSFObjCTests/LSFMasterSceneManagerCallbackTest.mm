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

#import "LSFMasterSceneManagerCallbackTest.h"
#import "MockMasterSceneManagerCallbackDelegateHandler.h"
#import <internal/LSFMasterSceneManagerCallback.h>

@interface LSFMasterSceneManagerCallbackTest()

@property (nonatomic) MockMasterSceneManagerCallbackDelegateHandler *msmcdh;
@property (nonatomic) LSFMasterSceneManagerCallback *msmc;
@property (nonatomic) NSMutableArray *dataArray;

@end

@implementation LSFMasterSceneManagerCallbackTest

@synthesize msmcdh = _msmcdh;
@synthesize msmc = _msmc;
@synthesize dataArray = _dataArray;

-(void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
    
    self.msmcdh = [[MockMasterSceneManagerCallbackDelegateHandler alloc] init];
    self.msmc = new LSFMasterSceneManagerCallback(self.msmcdh);
    self.dataArray = [[NSMutableArray alloc] init];
}

-(void)tearDown
{
    delete self.msmc;
    self.msmcdh = nil;
    
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

-(void)testGetMasterSceneIDs
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];
    
    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *functionName = @"getAllMasterSceneIDs";
    NSString *masterSceneID1 = @"masterSceneID1";
    NSString *masterSceneID2 = @"masterSceneID2";
    NSString *masterSceneID3 = @"masterSceneID3";
    NSString *masterSceneID4 = @"masterSceneID4";
    NSArray *masterSceneIDsArray = [[NSArray alloc] initWithObjects: masterSceneID1, masterSceneID2, masterSceneID3, masterSceneID4, nil];
    
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: masterSceneIDsArray];
    
    //Call callback method
    LSFStringList masterSceneIDList;
    std::string id1([masterSceneID1 UTF8String]);
    masterSceneIDList.push_back(id1);
    std::string id2([masterSceneID2 UTF8String]);
    masterSceneIDList.push_back(id2);
    std::string id3([masterSceneID3 UTF8String]);
    masterSceneIDList.push_back(id3);
    std::string id4([masterSceneID4 UTF8String]);
    masterSceneIDList.push_back(id4);
    self.msmc->GetAllMasterSceneIDsReplyCB(code, masterSceneIDList);
    
    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.msmcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testGetMasterSceneName
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];
    
    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *masterSceneID = @"masterSceneID1";
    NSString *functionName = @"getMasterSceneName";
    NSString *language = @"en";
    NSString *name = @"testMasterSceneName";
    
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: language];
    [self.dataArray addObject: masterSceneID];
    [self.dataArray addObject: name];
    
    //Call callback method
    std::string msid([masterSceneID UTF8String]);
    std::string lang([language UTF8String]);
    std::string masterSceneName([name UTF8String]);
    self.msmc->GetMasterSceneNameReplyCB(code, msid, lang, masterSceneName);
    
    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.msmcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testSetMasterSceneName
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];
    
    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *masterSceneID = @"masterSceneID1";
    NSString *functionName = @"setMasterSceneName";
    NSString *language = @"en";
    
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: language];
    [self.dataArray addObject: masterSceneID];
    
    //Call callback method
    std::string msid([masterSceneID UTF8String]);
    std::string lang([language UTF8String]);
    self.msmc->SetMasterSceneNameReplyCB(code, msid, lang);
    
    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.msmcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testMasterScenesNameChanged
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];
    
    //Populate array with test data
    NSString *functionName = @"masterScenesNameChanged";
    NSString *masterSceneID1 = @"masterSceneID1";
    NSString *masterSceneID2 = @"masterSceneID2";
    NSString *masterSceneID3 = @"masterSceneID3";
    NSString *masterSceneID4 = @"masterSceneID4";
    NSArray *masterSceneIDsArray = [[NSArray alloc] initWithObjects: masterSceneID1, masterSceneID2, masterSceneID3, masterSceneID4, nil];
    
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: masterSceneIDsArray];
    
    //Call callback method
    LSFStringList masterSceneIDList;
    std::string id1([masterSceneID1 UTF8String]);
    masterSceneIDList.push_back(id1);
    std::string id2([masterSceneID2 UTF8String]);
    masterSceneIDList.push_back(id2);
    std::string id3([masterSceneID3 UTF8String]);
    masterSceneIDList.push_back(id3);
    std::string id4([masterSceneID4 UTF8String]);
    masterSceneIDList.push_back(id4);
    self.msmc->MasterScenesNameChangedCB(masterSceneIDList);
    
    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.msmcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testCreateMasterScene
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];
    
    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *masterSceneID = @"masterSceneID1";
    NSString *functionName = @"createMasterScene";
    
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: masterSceneID];
    
    //Call callback method
    std::string msid([masterSceneID UTF8String]);
    self.msmc->CreateMasterSceneReplyCB(code, msid);
    
    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.msmcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testCreateMasterSceneWithTracking
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    unsigned int tid = 1234;
    NSNumber *trackingID = [[NSNumber alloc] initWithUnsignedInt: tid];
    NSString *masterSceneID = @"masterSceneID1";
    NSString *functionName = @"createMasterSceneWithTracking";

    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: masterSceneID];
    [self.dataArray addObject: trackingID];

    //Call callback method
    std::string msid([masterSceneID UTF8String]);
    self.msmc->CreateMasterSceneWithTrackingReplyCB(code, msid, tid);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.msmcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testMasterScenesCreated
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];
    
    //Populate array with test data
    NSString *functionName = @"masterScenesCreated";
    NSString *masterSceneID1 = @"masterSceneID1";
    NSString *masterSceneID2 = @"masterSceneID2";
    NSString *masterSceneID3 = @"masterSceneID3";
    NSString *masterSceneID4 = @"masterSceneID4";
    NSArray *masterSceneIDsArray = [[NSArray alloc] initWithObjects: masterSceneID1, masterSceneID2, masterSceneID3, masterSceneID4, nil];
    
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: masterSceneIDsArray];
    
    //Call callback method
    LSFStringList masterSceneIDList;
    std::string id1([masterSceneID1 UTF8String]);
    masterSceneIDList.push_back(id1);
    std::string id2([masterSceneID2 UTF8String]);
    masterSceneIDList.push_back(id2);
    std::string id3([masterSceneID3 UTF8String]);
    masterSceneIDList.push_back(id3);
    std::string id4([masterSceneID4 UTF8String]);
    masterSceneIDList.push_back(id4);
    self.msmc->MasterScenesCreatedCB(masterSceneIDList);
    
    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.msmcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testGetMasterScene
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];
    
    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *masterSceneID = @"masterSceneID1";
    NSString *functionName = @"getMasterScene";
    NSString *sceneID1 = @"sceneID1";
    NSString *sceneID2 = @"sceneID2";
    NSString *sceneID3 = @"sceneID3";
    NSString *sceneID4 = @"sceneID4";
    NSArray *sceneIDsArray = [[NSArray alloc] initWithObjects: sceneID1, sceneID2, sceneID3, sceneID4, nil];
    
    LSFMasterScene *masterScene = [[LSFMasterScene alloc] initWithSceneIDs: sceneIDsArray];
    
    [self.dataArray addObject: sceneIDsArray];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: masterSceneID];
    
    //Call callback method
    std::string msid([masterSceneID UTF8String]);
    self.msmc->GetMasterSceneReplyCB(code, msid, *(static_cast<lsf::MasterScene*>(masterScene.handle)));
    
    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.msmcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testDeleteMasterScene
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];
    
    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *masterSceneID = @"masterSceneID1";
    NSString *functionName = @"deleteMasterScene";
    
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: masterSceneID];
    
    //Call callback method
    std::string msid([masterSceneID UTF8String]);
    self.msmc->DeleteMasterSceneReplyCB(code, msid);
    
    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.msmcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testMasterScenesDeleted
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];
    
    //Populate array with test data
    NSString *functionName = @"masterScenesDeleted";
    NSString *masterSceneID1 = @"masterSceneID1";
    NSString *masterSceneID2 = @"masterSceneID2";
    NSString *masterSceneID3 = @"masterSceneID3";
    NSString *masterSceneID4 = @"masterSceneID4";
    NSArray *masterSceneIDsArray = [[NSArray alloc] initWithObjects: masterSceneID1, masterSceneID2, masterSceneID3, masterSceneID4, nil];
    
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: masterSceneIDsArray];
    
    //Call callback method
    LSFStringList masterSceneIDList;
    std::string id1([masterSceneID1 UTF8String]);
    masterSceneIDList.push_back(id1);
    std::string id2([masterSceneID2 UTF8String]);
    masterSceneIDList.push_back(id2);
    std::string id3([masterSceneID3 UTF8String]);
    masterSceneIDList.push_back(id3);
    std::string id4([masterSceneID4 UTF8String]);
    masterSceneIDList.push_back(id4);
    self.msmc->MasterScenesDeletedCB(masterSceneIDList);
    
    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.msmcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testUpdateMasterScene
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];
    
    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *masterSceneID = @"masterSceneID1";
    NSString *functionName = @"updateMasterScene";
    
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: masterSceneID];
    
    //Call callback method
    std::string msid([masterSceneID UTF8String]);
    self.msmc->UpdateMasterSceneReplyCB(code, msid);
    
    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.msmcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testMasterScenesUpdated
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];
    
    //Populate array with test data
    NSString *functionName = @"masterScenesUpdated";
    NSString *masterSceneID1 = @"masterSceneID1";
    NSString *masterSceneID2 = @"masterSceneID2";
    NSString *masterSceneID3 = @"masterSceneID3";
    NSString *masterSceneID4 = @"masterSceneID4";
    NSArray *masterSceneIDsArray = [[NSArray alloc] initWithObjects: masterSceneID1, masterSceneID2, masterSceneID3, masterSceneID4, nil];
    
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: masterSceneIDsArray];
    
    //Call callback method
    LSFStringList masterSceneIDList;
    std::string id1([masterSceneID1 UTF8String]);
    masterSceneIDList.push_back(id1);
    std::string id2([masterSceneID2 UTF8String]);
    masterSceneIDList.push_back(id2);
    std::string id3([masterSceneID3 UTF8String]);
    masterSceneIDList.push_back(id3);
    std::string id4([masterSceneID4 UTF8String]);
    masterSceneIDList.push_back(id4);
    self.msmc->MasterScenesUpdatedCB(masterSceneIDList);
    
    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.msmcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testApplyMasterScene
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];
    
    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *masterSceneID = @"masterSceneID1";
    NSString *functionName = @"applyMasterScene";
    
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: masterSceneID];
    
    //Call callback method
    std::string msid([masterSceneID UTF8String]);
    self.msmc->ApplyMasterSceneReplyCB(code, msid);
    
    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.msmcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testMasterScenesApplied
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];
    
    //Populate array with test data
    NSString *functionName = @"masterScenesApplied";
    NSString *masterSceneID1 = @"masterSceneID1";
    NSString *masterSceneID2 = @"masterSceneID2";
    NSString *masterSceneID3 = @"masterSceneID3";
    NSString *masterSceneID4 = @"masterSceneID4";
    NSArray *masterSceneIDsArray = [[NSArray alloc] initWithObjects: masterSceneID1, masterSceneID2, masterSceneID3, masterSceneID4, nil];
    
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: masterSceneIDsArray];
    
    //Call callback method
    LSFStringList masterSceneIDList;
    std::string id1([masterSceneID1 UTF8String]);
    masterSceneIDList.push_back(id1);
    std::string id2([masterSceneID2 UTF8String]);
    masterSceneIDList.push_back(id2);
    std::string id3([masterSceneID3 UTF8String]);
    masterSceneIDList.push_back(id3);
    std::string id4([masterSceneID4 UTF8String]);
    masterSceneIDList.push_back(id4);
    self.msmc->MasterScenesAppliedCB(masterSceneIDList);
    
    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.msmcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

@end
