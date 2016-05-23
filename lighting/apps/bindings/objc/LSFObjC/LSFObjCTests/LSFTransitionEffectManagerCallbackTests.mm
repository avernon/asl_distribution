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

#import "LSFTransitionEffectManagerCallbackTests.h"
#import "MockTransitionEffectManagerCallbackDelegateHandler.h"
#import <internal/LSFTransitionEffectManagerCallback.h>
#import <alljoyn/Init.h>

@interface LSFTransitionEffectManagerCallbackTests()

@property (nonatomic) MockTransitionEffectManagerCallbackDelegateHandler *temcdh;
@property (nonatomic) LSFTransitionEffectManagerCallback *temc;
@property (nonatomic) NSMutableArray *dataArray;

@end

@implementation LSFTransitionEffectManagerCallbackTests

@synthesize temcdh = _temcdh;
@synthesize temc = _temc;
@synthesize dataArray = _dataArray;

-(void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.

    AllJoynInit();
    self.temcdh = [[MockTransitionEffectManagerCallbackDelegateHandler alloc] init];
    self.temc = new LSFTransitionEffectManagerCallback(self.temcdh);
    self.dataArray = [[NSMutableArray alloc] init];
}

-(void)tearDown
{
    delete self.temc;
    self.temcdh = nil;
    AllJoynShutdown();

    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

-(void)testGetTransitionEffect
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *functionName = @"getTransitionEffect";
    NSString *transitionEffectID = @"transitionEffectID1";
    NSString *presetEffectID = @"presetEffectID1";
    unsigned int transitionPeriod = 5000;
    NSNumber *period = [[NSNumber alloc] initWithUnsignedInt: transitionPeriod];

    LSFTransitionEffectV2 *te = [[LSFTransitionEffectV2 alloc] initWithPresetID: presetEffectID transitionPeriod: transitionPeriod];

    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: transitionEffectID];
    [self.dataArray addObject: presetEffectID];
    [self.dataArray addObject: period];

    //Call callback method
    std::string teid([transitionEffectID UTF8String]);
    self.temc->GetTransitionEffectReplyCB(code, teid, *static_cast<lsf::TransitionEffect*>(te.handle));

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.temcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testApplyTransitionEffectOnLamps
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *functionName = @"applyTransitionEffectOnLamps";
    NSString *transitionEffectID = @"transitionEffectID1";

    NSString *lampID1 = @"lampID1";
    NSString *lampID2 = @"lampID2";
    NSArray *lampIDs = [NSArray arrayWithObjects: lampID1, lampID2, nil];

    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: transitionEffectID];
    [self.dataArray addObject: lampIDs];

    //Call callback method
    std::string teid([transitionEffectID UTF8String]);
    LSFStringList lampIDList;
    lampIDList.push_back([lampID1 UTF8String]);
    lampIDList.push_back([lampID2 UTF8String]);
    self.temc->ApplyTransitionEffectOnLampsReplyCB(code, teid, lampIDList);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.temcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testApplyTransitionEffectOnLampGroups
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *functionName = @"applyTransitionEffectOnLampGroups";
    NSString *transitionEffectID = @"transitionEffectID1";

    NSString *lampGroupID1 = @"lampGroupID1";
    NSString *lampGroupID2 = @"lampGroupID2";
    NSArray *lampGroupIDs = [NSArray arrayWithObjects: lampGroupID1, lampGroupID2, nil];

    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: transitionEffectID];
    [self.dataArray addObject: lampGroupIDs];

    //Call callback method
    std::string teid([transitionEffectID UTF8String]);
    LSFStringList lampGroupIDList;
    lampGroupIDList.push_back([lampGroupID1 UTF8String]);
    lampGroupIDList.push_back([lampGroupID2 UTF8String]);
    self.temc->ApplyTransitionEffectOnLampGroupsReplyCB(code, teid, lampGroupIDList);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.temcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testGetAllTransitionEffectIDs
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *functionName = @"getAllTransitionEffectIDs";
    NSString *transitionEffectID1 = @"transitionEffectID1";
    NSString *transitionEffectID2 = @"transitionEffectID2";
    NSString *transitionEffectID3 = @"transitionEffectID3";
    NSString *transitionEffectID4 = @"transitionEffectID4";
    NSArray *transitionEffectIDsArray = [[NSArray alloc] initWithObjects: transitionEffectID1, transitionEffectID2, transitionEffectID3, transitionEffectID4, nil];

    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: transitionEffectIDsArray];

    //Call callback method
    LSFStringList transitionEffectIDList;
    std::string id1([transitionEffectID1 UTF8String]);
    transitionEffectIDList.push_back(id1);
    std::string id2([transitionEffectID2 UTF8String]);
    transitionEffectIDList.push_back(id2);
    std::string id3([transitionEffectID3 UTF8String]);
    transitionEffectIDList.push_back(id3);
    std::string id4([transitionEffectID4 UTF8String]);
    transitionEffectIDList.push_back(id4);
    self.temc->GetAllTransitionEffectIDsReplyCB(code, transitionEffectIDList);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.temcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testGetTransitionEffectName
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *functionName = @"getTransitionEffectName";
    NSString *transitionEffectID = @"transitionEffectID1";
    NSString *language = @"en";
    NSString *transitionEffectName = @"testTransitionEffectName";

    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: transitionEffectID];
    [self.dataArray addObject: language];
    [self.dataArray addObject: transitionEffectName];

    //Call callback method
    std::string teid([transitionEffectID UTF8String]);
    std::string name([transitionEffectName UTF8String]);
    std::string lang([language UTF8String]);
    self.temc->GetTransitionEffectNameReplyCB(code, teid, lang, name);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.temcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testSetTransitionEffectName
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *functionName = @"setTransitionEffectName";
    NSString *transitionEffectID = @"transitionEffectID1";
    NSString *language = @"en";

    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: transitionEffectID];
    [self.dataArray addObject: language];

    //Call callback method
    std::string teid([transitionEffectID UTF8String]);
    std::string lang([language UTF8String]);
    self.temc->SetTransitionEffectNameReplyCB(code, teid, lang);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.temcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testTransitionEffectsNameChanged
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    NSString *functionName = @"transitionEffectsNameChanged";
    NSString *transitionEffectID1 = @"transitionEffectID1";
    NSString *transitionEffectID2 = @"transitionEffectID2";
    NSString *transitionEffectID3 = @"transitionEffectID3";
    NSString *transitionEffectID4 = @"transitionEffectID4";
    NSArray *transitionEffectIDsArray = [[NSArray alloc] initWithObjects: transitionEffectID1, transitionEffectID2, transitionEffectID3, transitionEffectID4, nil];

    [self.dataArray addObject: functionName];
    [self.dataArray addObject: transitionEffectIDsArray];

    //Call callback method
    LSFStringList transitionEffectIDList;
    std::string id1([transitionEffectID1 UTF8String]);
    transitionEffectIDList.push_back(id1);
    std::string id2([transitionEffectID2 UTF8String]);
    transitionEffectIDList.push_back(id2);
    std::string id3([transitionEffectID3 UTF8String]);
    transitionEffectIDList.push_back(id3);
    std::string id4([transitionEffectID4 UTF8String]);
    transitionEffectIDList.push_back(id4);
    self.temc->TransitionEffectsNameChangedCB(transitionEffectIDList);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.temcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testCreateTransitionEffect
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    unsigned int tid = 1234;
    NSNumber *trackingID = [[NSNumber alloc] initWithUnsignedInt: tid];
    NSString *functionName = @"createTransitionEffect";
    NSString *transitionEffectID = @"transitionEffectID1";

    [self.dataArray addObject: functionName];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: trackingID];
    [self.dataArray addObject: transitionEffectID];

    //Call callback method
    std::string teid([transitionEffectID UTF8String]);
    self.temc->CreateTransitionEffectReplyCB(code, teid, tid);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.temcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testTransitionEffectsCreated
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    NSString *functionName = @"transitionEffectsCreated";
    NSString *transitionEffectID1 = @"transitionEffectID1";
    NSString *transitionEffectID2 = @"transitionEffectID2";
    NSString *transitionEffectID3 = @"transitionEffectID3";
    NSString *transitionEffectID4 = @"transitionEffectID4";
    NSArray *transitionEffectIDsArray = [[NSArray alloc] initWithObjects: transitionEffectID1, transitionEffectID2, transitionEffectID3, transitionEffectID4, nil];

    [self.dataArray addObject: functionName];
    [self.dataArray addObject: transitionEffectIDsArray];

    //Call callback method
    LSFStringList transitionEffectIDList;
    std::string id1([transitionEffectID1 UTF8String]);
    transitionEffectIDList.push_back(id1);
    std::string id2([transitionEffectID2 UTF8String]);
    transitionEffectIDList.push_back(id2);
    std::string id3([transitionEffectID3 UTF8String]);
    transitionEffectIDList.push_back(id3);
    std::string id4([transitionEffectID4 UTF8String]);
    transitionEffectIDList.push_back(id4);
    self.temc->TransitionEffectsCreatedCB(transitionEffectIDList);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.temcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testUpdateTransitionEffect
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *functionName = @"updateTransitionEffect";
    NSString *transitionEffectID = @"transitionEffectID1";

    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: transitionEffectID];

    //Call callback method
    std::string teid([transitionEffectID UTF8String]);
    self.temc->UpdateTransitionEffectReplyCB(code, teid);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.temcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testTransitionEffectsUpdated
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    NSString *functionName = @"transitionEffectsUpdated";
    NSString *transitionEffectID1 = @"transitionEffectID1";
    NSString *transitionEffectID2 = @"transitionEffectID2";
    NSString *transitionEffectID3 = @"transitionEffectID3";
    NSString *transitionEffectID4 = @"transitionEffectID4";
    NSArray *transitionEffectIDsArray = [[NSArray alloc] initWithObjects: transitionEffectID1, transitionEffectID2, transitionEffectID3, transitionEffectID4, nil];

    [self.dataArray addObject: functionName];
    [self.dataArray addObject: transitionEffectIDsArray];

    //Call callback method
    LSFStringList transitionEffectIDList;
    std::string id1([transitionEffectID1 UTF8String]);
    transitionEffectIDList.push_back(id1);
    std::string id2([transitionEffectID2 UTF8String]);
    transitionEffectIDList.push_back(id2);
    std::string id3([transitionEffectID3 UTF8String]);
    transitionEffectIDList.push_back(id3);
    std::string id4([transitionEffectID4 UTF8String]);
    transitionEffectIDList.push_back(id4);
    self.temc->TransitionEffectsUpdatedCB(transitionEffectIDList);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.temcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testDeleteTransitionEffect
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *functionName = @"deleteTransitionEffect";
    NSString *transitionEffectID = @"transitionEffectID1";

    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: transitionEffectID];

    //Call callback method
    std::string teid([transitionEffectID UTF8String]);
    self.temc->DeleteTransitionEffectReplyCB(code, teid);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.temcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testTransitionEffectsDeleted
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    NSString *functionName = @"transitionEffectsDeleted";
    NSString *transitionEffectID1 = @"transitionEffectID1";
    NSString *transitionEffectID2 = @"transitionEffectID2";
    NSString *transitionEffectID3 = @"transitionEffectID3";
    NSString *transitionEffectID4 = @"transitionEffectID4";
    NSArray *transitionEffectIDsArray = [[NSArray alloc] initWithObjects: transitionEffectID1, transitionEffectID2, transitionEffectID3, transitionEffectID4, nil];

    [self.dataArray addObject: functionName];
    [self.dataArray addObject: transitionEffectIDsArray];

    //Call callback method
    LSFStringList transitionEffectIDList;
    std::string id1([transitionEffectID1 UTF8String]);
    transitionEffectIDList.push_back(id1);
    std::string id2([transitionEffectID2 UTF8String]);
    transitionEffectIDList.push_back(id2);
    std::string id3([transitionEffectID3 UTF8String]);
    transitionEffectIDList.push_back(id3);
    std::string id4([transitionEffectID4 UTF8String]);
    transitionEffectIDList.push_back(id4);
    self.temc->TransitionEffectsDeletedCB(transitionEffectIDList);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.temcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

@end
