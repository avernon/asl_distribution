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

#import "LSFSceneElementManagerCallbackTests.h"
#import "MockSceneElementManagerCallbackDelegateHandler.h"
#import <internal/LSFSceneElementManagerCallback.h>
#import <alljoyn/Init.h>

@interface LSFSceneElementManagerCallbackTests()

@property (nonatomic) MockSceneElementManagerCallbackDelegateHandler *semcdh;
@property (nonatomic) LSFSceneElementManagerCallback *semc;
@property (nonatomic) NSMutableArray *dataArray;

@end

@implementation LSFSceneElementManagerCallbackTests

@synthesize semcdh = _semcdh;
@synthesize semc = _semc;
@synthesize dataArray = _dataArray;

-(void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.

    AllJoynInit();
    self.semcdh = [[MockSceneElementManagerCallbackDelegateHandler alloc] init];
    self.semc = new LSFSceneElementManagerCallback(self.semcdh);
    self.dataArray = [[NSMutableArray alloc] init];
}

-(void)tearDown
{
    delete self.semc;
    self.semcdh = nil;
    AllJoynShutdown();

    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

-(void)testGetAllSceneElementIDs
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *functionName = @"getAllSceneElementIDs";
    NSString *sceneElementID1 = @"sceneElementID1";
    NSString *sceneElementID2 = @"sceneElementID2";
    NSString *sceneElementID3 = @"sceneElementID3";
    NSString *sceneElementID4 = @"sceneElementID4";
    NSArray *sceneElementIDsArray = [[NSArray alloc] initWithObjects: sceneElementID1, sceneElementID2, sceneElementID3, sceneElementID4, nil];

    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: sceneElementIDsArray];

    //Call callback method
    LSFStringList sceneElementIDList;
    std::string id1([sceneElementID1 UTF8String]);
    sceneElementIDList.push_back(id1);
    std::string id2([sceneElementID2 UTF8String]);
    sceneElementIDList.push_back(id2);
    std::string id3([sceneElementID3 UTF8String]);
    sceneElementIDList.push_back(id3);
    std::string id4([sceneElementID4 UTF8String]);
    sceneElementIDList.push_back(id4);
    self.semc->GetAllSceneElementIDsReplyCB(code, sceneElementIDList);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.semcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testGetSceneElementName
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *functionName = @"getSceneElementName";
    NSString *sceneElementID = @"sceneElementID1";
    NSString *language = @"en";
    NSString *sceneElementName = @"testSceneElementName";

    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: sceneElementID];
    [self.dataArray addObject: language];
    [self.dataArray addObject: sceneElementName];

    //Call callback method
    std::string seid([sceneElementID UTF8String]);
    std::string name([sceneElementName UTF8String]);
    std::string lang([language UTF8String]);
    self.semc->GetSceneElementNameReplyCB(code, seid, lang, name);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.semcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testSetSceneElementName
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *functionName = @"setSceneElementName";
    NSString *sceneElementID = @"sceneElementID1";
    NSString *language = @"en";

    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: sceneElementID];
    [self.dataArray addObject: language];

    //Call callback method
    std::string seid([sceneElementID UTF8String]);
    std::string lang([language UTF8String]);
    self.semc->SetSceneElementNameReplyCB(code, seid, lang);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.semcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testSceneElementsNameChanged
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    NSString *functionName = @"sceneElementsNameChanged";
    NSString *sceneElementID1 = @"sceneElementID1";
    NSString *sceneElementID2 = @"sceneElementID2";
    NSString *sceneElementID3 = @"sceneElementID3";
    NSString *sceneElementID4 = @"sceneElementID4";
    NSArray *sceneElementIDsArray = [[NSArray alloc] initWithObjects: sceneElementID1, sceneElementID2, sceneElementID3, sceneElementID4, nil];

    [self.dataArray addObject: functionName];
    [self.dataArray addObject: sceneElementIDsArray];

    //Call callback method
    LSFStringList sceneElementIDList;
    std::string id1([sceneElementID1 UTF8String]);
    sceneElementIDList.push_back(id1);
    std::string id2([sceneElementID2 UTF8String]);
    sceneElementIDList.push_back(id2);
    std::string id3([sceneElementID3 UTF8String]);
    sceneElementIDList.push_back(id3);
    std::string id4([sceneElementID4 UTF8String]);
    sceneElementIDList.push_back(id4);
    self.semc->SceneElementsNameChangedCB(sceneElementIDList);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.semcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testCreateSceneElement
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    unsigned int tid = 1234;
    NSNumber *trackingID = [[NSNumber alloc] initWithUnsignedInt: tid];
    NSString *functionName = @"createSceneElement";
    NSString *sceneElementID = @"sceneElementID1";

    [self.dataArray addObject: functionName];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: trackingID];
    [self.dataArray addObject: sceneElementID];

    //Call callback method
    std::string seid([sceneElementID UTF8String]);
    self.semc->CreateSceneElementReplyCB(code, seid, tid);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.semcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testSceneElementsCreated
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    NSString *functionName = @"sceneElementsCreated";
    NSString *sceneElementID1 = @"sceneElementID1";
    NSString *sceneElementID2 = @"sceneElementID2";
    NSString *sceneElementID3 = @"sceneElementID3";
    NSString *sceneElementID4 = @"sceneElementID4";
    NSArray *sceneElementIDsArray = [[NSArray alloc] initWithObjects: sceneElementID1, sceneElementID2, sceneElementID3, sceneElementID4, nil];

    [self.dataArray addObject: functionName];
    [self.dataArray addObject: sceneElementIDsArray];

    //Call callback method
    LSFStringList sceneElementIDList;
    std::string id1([sceneElementID1 UTF8String]);
    sceneElementIDList.push_back(id1);
    std::string id2([sceneElementID2 UTF8String]);
    sceneElementIDList.push_back(id2);
    std::string id3([sceneElementID3 UTF8String]);
    sceneElementIDList.push_back(id3);
    std::string id4([sceneElementID4 UTF8String]);
    sceneElementIDList.push_back(id4);
    self.semc->SceneElementsCreatedCB(sceneElementIDList);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.semcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testUpdateSceneElement
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *functionName = @"updateSceneElement";
    NSString *sceneElementID = @"sceneElementID1";

    [self.dataArray addObject: functionName];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: sceneElementID];

    //Call callback method
    std::string seid([sceneElementID UTF8String]);
    self.semc->UpdateSceneElementReplyCB(code, seid);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.semcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testSceneElementsUpdated
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    NSString *functionName = @"sceneElementsUpdated";
    NSString *sceneElementID1 = @"sceneElementID1";
    NSString *sceneElementID2 = @"sceneElementID2";
    NSString *sceneElementID3 = @"sceneElementID3";
    NSString *sceneElementID4 = @"sceneElementID4";
    NSArray *sceneElementIDsArray = [[NSArray alloc] initWithObjects: sceneElementID1, sceneElementID2, sceneElementID3, sceneElementID4, nil];

    [self.dataArray addObject: functionName];
    [self.dataArray addObject: sceneElementIDsArray];

    //Call callback method
    LSFStringList sceneElementIDList;
    std::string id1([sceneElementID1 UTF8String]);
    sceneElementIDList.push_back(id1);
    std::string id2([sceneElementID2 UTF8String]);
    sceneElementIDList.push_back(id2);
    std::string id3([sceneElementID3 UTF8String]);
    sceneElementIDList.push_back(id3);
    std::string id4([sceneElementID4 UTF8String]);
    sceneElementIDList.push_back(id4);
    self.semc->SceneElementsUpdatedCB(sceneElementIDList);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.semcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testDeleteSceneElement
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *functionName = @"deleteSceneElement";
    NSString *sceneElementID = @"sceneElementID1";

    [self.dataArray addObject: functionName];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: sceneElementID];

    //Call callback method
    std::string seid([sceneElementID UTF8String]);
    self.semc->DeleteSceneElementReplyCB(code, seid);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.semcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testSceneElementsDeleted
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    NSString *functionName = @"sceneElementsDeleted";
    NSString *sceneElementID1 = @"sceneElementID1";
    NSString *sceneElementID2 = @"sceneElementID2";
    NSString *sceneElementID3 = @"sceneElementID3";
    NSString *sceneElementID4 = @"sceneElementID4";
    NSArray *sceneElementIDsArray = [[NSArray alloc] initWithObjects: sceneElementID1, sceneElementID2, sceneElementID3, sceneElementID4, nil];

    [self.dataArray addObject: functionName];
    [self.dataArray addObject: sceneElementIDsArray];

    //Call callback method
    LSFStringList sceneElementIDList;
    std::string id1([sceneElementID1 UTF8String]);
    sceneElementIDList.push_back(id1);
    std::string id2([sceneElementID2 UTF8String]);
    sceneElementIDList.push_back(id2);
    std::string id3([sceneElementID3 UTF8String]);
    sceneElementIDList.push_back(id3);
    std::string id4([sceneElementID4 UTF8String]);
    sceneElementIDList.push_back(id4);
    self.semc->SceneElementsDeletedCB(sceneElementIDList);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.semcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testGetSceneElement
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *functionName = @"getSceneElement";
    NSString *sceneElementID = @"sceneElementID1";
    NSString *effectID = @"testEffectID";

    NSString *lampID1 = @"lampID1";
    NSString *lampID2 = @"lampID2";
    NSString *lampID3 = @"lampID3";
    NSArray *lampIDs = [NSArray arrayWithObjects: lampID1, lampID2, lampID3, nil];

    NSString *lampGroupID1 = @"lampGroupID1";
    NSString *lampGroupID2 = @"lampGroupID2";
    NSArray *lampGroupIDs = [NSArray arrayWithObjects: lampGroupID1, lampGroupID2, nil];

    LSFSceneElement *sceneElement = [[LSFSceneElement alloc] initWithLampIDs: lampIDs lampGroupIDs: lampGroupIDs andEffectID: effectID];

    [self.dataArray addObject: functionName];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: sceneElementID];
    [self.dataArray addObject: lampIDs];
    [self.dataArray addObject: lampGroupIDs];
    [self.dataArray addObject: effectID];

    //Call callback method
    std::string seid([sceneElementID UTF8String]);
    self.semc->GetSceneElementReplyCB(code, seid, *static_cast<lsf::SceneElement*>(sceneElement.handle));

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.semcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testApplySceneElement
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *functionName = @"applySceneElement";
    NSString *sceneElementID = @"sceneElementID1";

    [self.dataArray addObject: functionName];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: sceneElementID];

    //Call callback method
    std::string seid([sceneElementID UTF8String]);
    self.semc->ApplySceneElementReplyCB(code, seid);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.semcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testSceneElementsApplied
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    NSString *functionName = @"sceneElementsApplied";
    NSString *sceneElementID1 = @"sceneElementID1";
    NSString *sceneElementID2 = @"sceneElementID2";
    NSString *sceneElementID3 = @"sceneElementID3";
    NSString *sceneElementID4 = @"sceneElementID4";
    NSArray *sceneElementIDsArray = [[NSArray alloc] initWithObjects: sceneElementID1, sceneElementID2, sceneElementID3, sceneElementID4, nil];

    [self.dataArray addObject: functionName];
    [self.dataArray addObject: sceneElementIDsArray];

    //Call callback method
    LSFStringList sceneElementIDList;
    std::string id1([sceneElementID1 UTF8String]);
    sceneElementIDList.push_back(id1);
    std::string id2([sceneElementID2 UTF8String]);
    sceneElementIDList.push_back(id2);
    std::string id3([sceneElementID3 UTF8String]);
    sceneElementIDList.push_back(id3);
    std::string id4([sceneElementID4 UTF8String]);
    sceneElementIDList.push_back(id4);
    self.semc->SceneElementsAppliedCB(sceneElementIDList);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.semcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

@end
