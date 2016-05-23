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

#import "LSFPresetManagerCallbackTests.h"
#import "MockPresetManagerCallbackDelegateHandler.h"
#import <internal/LSFPresetManagerCallback.h>

@interface LSFPresetManagerCallbackTests()

@property (nonatomic) MockPresetManagerCallbackDelegateHandler *pmcdh;
@property (nonatomic) LSFPresetManagerCallback *pmc;
@property (nonatomic) NSMutableArray *dataArray;

@end

@implementation LSFPresetManagerCallbackTests

@synthesize pmcdh = _pmcdh;
@synthesize pmc = _pmc;
@synthesize dataArray = _dataArray;

-(void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
    
    self.pmcdh = [[MockPresetManagerCallbackDelegateHandler alloc] init];
    self.pmc = new LSFPresetManagerCallback(self.pmcdh);
    self.dataArray = [[NSMutableArray alloc] init];
}

-(void)tearDown
{
    delete self.pmc;
    self.pmcdh = nil;
    
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

-(void)testGetPreset
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];
    
    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *presetID = @"presetID1";
    NSString *functionName = @"getPreset";
    NSNumber *onOff = [[NSNumber alloc] initWithBool: YES];
    NSNumber *brightness = [[NSNumber alloc] initWithUnsignedInt: 100];
    NSNumber *hue = [[NSNumber alloc] initWithUnsignedInt: 200];
    NSNumber *saturation = [[NSNumber alloc] initWithUnsignedInt: 300];
    NSNumber *colorTemp = [[NSNumber alloc] initWithUnsignedInt: 400];
    
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: onOff];
    [self.dataArray addObject: brightness];
    [self.dataArray addObject: hue];
    [self.dataArray addObject: saturation];
    [self.dataArray addObject: colorTemp];
    [self.dataArray addObject: presetID];
    
    //Call callback method
    lsf::LampState *state = new lsf::LampState(true, 100, 200, 300, 400);
    std::string pid([presetID UTF8String]);
    self.pmc->GetPresetReplyCB(code, pid, *state);
    
    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.pmcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testGetAllPresetIDs
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];
    
    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *functionName = @"getAllPresetIDs";
    NSString *presetID1 = @"presetID1";
    NSString *presetID2 = @"presetID2";
    NSString *presetID3 = @"presetID3";
    NSString *presetID4 = @"presetID4";
    NSArray *presetIDsArray = [[NSArray alloc] initWithObjects: presetID1, presetID2, presetID3, presetID4, nil];
    
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: presetIDsArray];
    
    //Call callback method
    LSFStringList presetIDList;
    std::string id1([presetID1 UTF8String]);
    presetIDList.push_back(id1);
    std::string id2([presetID2 UTF8String]);
    presetIDList.push_back(id2);
    std::string id3([presetID3 UTF8String]);
    presetIDList.push_back(id3);
    std::string id4([presetID4 UTF8String]);
    presetIDList.push_back(id4);
    self.pmc->GetAllPresetIDsReplyCB(code, presetIDList);
    
    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.pmcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testGetPresetName
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];
    
    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *presetID = @"presetID1";
    NSString *functionName = @"getPresetName";
    NSString *language = @"en";
    NSString *name = @"testPresetName";
    
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: language];
    [self.dataArray addObject: presetID];
    [self.dataArray addObject: name];
    
    //Call callback method
    std::string pid([presetID UTF8String]);
    std::string lang([language UTF8String]);
    std::string presetName([name UTF8String]);
    self.pmc->GetPresetNameReplyCB(code, pid, lang, presetName);
    
    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.pmcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testSetPresetName
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];
    
    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *presetID = @"presetID1";
    NSString *functionName = @"setPresetName";
    NSString *language = @"en";
    
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: language];
    [self.dataArray addObject: presetID];
    
    //Call callback method
    std::string pid([presetID UTF8String]);
    std::string lang([language UTF8String]);
    self.pmc->SetPresetNameReplyCB(code, pid, lang);
    
    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.pmcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testPresetsNameChanged
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];
    
    //Populate array with test data
    NSString *functionName = @"presetsNameChanged";
    NSString *presetID1 = @"presetID1";
    NSString *presetID2 = @"presetID2";
    NSString *presetID3 = @"presetID3";
    NSString *presetID4 = @"presetID4";
    NSArray *lampIDsArray = [[NSArray alloc] initWithObjects: presetID1, presetID2, presetID3, presetID4, nil];
    
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: lampIDsArray];
    
    //Call callback method
    LSFStringList presetIDList;
    std::string id1([presetID1 UTF8String]);
    presetIDList.push_back(id1);
    std::string id2([presetID2 UTF8String]);
    presetIDList.push_back(id2);
    std::string id3([presetID3 UTF8String]);
    presetIDList.push_back(id3);
    std::string id4([presetID4 UTF8String]);
    presetIDList.push_back(id4);
    self.pmc->PresetsNameChangedCB(presetIDList);
    
    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.pmcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testCreatePreset
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];
    
    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *presetID = @"presetID1";
    NSString *functionName = @"createPreset";
    
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: presetID];
    
    //Call callback method
    std::string pid([presetID UTF8String]);
    self.pmc->CreatePresetReplyCB(code, pid);
    
    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.pmcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testCreatePresetWithTracking
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];

    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    unsigned int tid = 1234;
    NSNumber *trackingID = [[NSNumber alloc] initWithUnsignedInt: tid];
    NSString *presetID = @"presetID1";
    NSString *functionName = @"createPresetWithTracking";

    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: presetID];
    [self.dataArray addObject: trackingID];

    //Call callback method
    std::string pid([presetID UTF8String]);
    self.pmc->CreatePresetWithTrackingReplyCB(code, pid, tid);

    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.pmcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testPresetsCreated
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];
    
    //Populate array with test data
    NSString *functionName = @"presetsCreated";
    NSString *presetID1 = @"presetID1";
    NSString *presetID2 = @"presetID2";
    NSString *presetID3 = @"presetID3";
    NSString *presetID4 = @"presetID4";
    NSArray *lampIDsArray = [[NSArray alloc] initWithObjects: presetID1, presetID2, presetID3, presetID4, nil];
    
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: lampIDsArray];
    
    //Call callback method
    LSFStringList presetIDList;
    std::string id1([presetID1 UTF8String]);
    presetIDList.push_back(id1);
    std::string id2([presetID2 UTF8String]);
    presetIDList.push_back(id2);
    std::string id3([presetID3 UTF8String]);
    presetIDList.push_back(id3);
    std::string id4([presetID4 UTF8String]);
    presetIDList.push_back(id4);
    self.pmc->PresetsCreatedCB(presetIDList);
    
    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.pmcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testUpdatePreset
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];
    
    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *presetID = @"presetID1";
    NSString *functionName = @"updatePreset";
    
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: presetID];
    
    //Call callback method
    std::string pid([presetID UTF8String]);
    self.pmc->UpdatePresetReplyCB(code, pid);
    
    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.pmcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testPresetsUpdated
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];
    
    //Populate array with test data
    NSString *functionName = @"presetsUpdated";
    NSString *presetID1 = @"presetID1";
    NSString *presetID2 = @"presetID2";
    NSString *presetID3 = @"presetID3";
    NSString *presetID4 = @"presetID4";
    NSArray *lampIDsArray = [[NSArray alloc] initWithObjects: presetID1, presetID2, presetID3, presetID4, nil];
    
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: lampIDsArray];
    
    //Call callback method
    LSFStringList presetIDList;
    std::string id1([presetID1 UTF8String]);
    presetIDList.push_back(id1);
    std::string id2([presetID2 UTF8String]);
    presetIDList.push_back(id2);
    std::string id3([presetID3 UTF8String]);
    presetIDList.push_back(id3);
    std::string id4([presetID4 UTF8String]);
    presetIDList.push_back(id4);
    self.pmc->PresetsUpdatedCB(presetIDList);
    
    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.pmcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testDeletePreset
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];
    
    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *presetID = @"presetID1";
    NSString *functionName = @"deletePreset";
    
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: presetID];
    
    //Call callback method
    std::string pid([presetID UTF8String]);
    self.pmc->DeletePresetReplyCB(code, pid);
    
    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.pmcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testPresetsDeleted
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];
    
    //Populate array with test data
    NSString *functionName = @"presetsDeleted";
    NSString *presetID1 = @"presetID1";
    NSString *presetID2 = @"presetID2";
    NSString *presetID3 = @"presetID3";
    NSString *presetID4 = @"presetID4";
    NSArray *lampIDsArray = [[NSArray alloc] initWithObjects: presetID1, presetID2, presetID3, presetID4, nil];
    
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: lampIDsArray];
    
    //Call callback method
    LSFStringList presetIDList;
    std::string id1([presetID1 UTF8String]);
    presetIDList.push_back(id1);
    std::string id2([presetID2 UTF8String]);
    presetIDList.push_back(id2);
    std::string id3([presetID3 UTF8String]);
    presetIDList.push_back(id3);
    std::string id4([presetID4 UTF8String]);
    presetIDList.push_back(id4);
    self.pmc->PresetsDeletedCB(presetIDList);
    
    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.pmcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testGetDefaultLampState
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];
    
    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *functionName = @"getDefaultLampState";
    NSNumber *onOff = [[NSNumber alloc] initWithBool: YES];
    NSNumber *brightness = [[NSNumber alloc] initWithUnsignedInt: 100];
    NSNumber *hue = [[NSNumber alloc] initWithUnsignedInt: 200];
    NSNumber *saturation = [[NSNumber alloc] initWithUnsignedInt: 300];
    NSNumber *colorTemp = [[NSNumber alloc] initWithUnsignedInt: 400];
    
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: onOff];
    [self.dataArray addObject: brightness];
    [self.dataArray addObject: hue];
    [self.dataArray addObject: saturation];
    [self.dataArray addObject: colorTemp];
    
    //Call callback method
    lsf::LampState *state = new lsf::LampState(true, 100, 200, 300, 400);
    self.pmc->GetDefaultLampStateReplyCB(code, *state);
    
    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.pmcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testSetDefaultLampState
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];
    
    //Populate array with test data
    LSFResponseCode code = LSF_ERR_INVALID;
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: code];
    NSString *functionName = @"setDefaultLampState";
    
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: functionName];
    
    //Call callback method
    self.pmc->SetDefaultLampStateReplyCB(code);
    
    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.pmcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testDefaultLampStateChanged
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];
    
    //Populate array with test data
    NSString *functionName = @"defaultLampStateChanged";
    [self.dataArray addObject: functionName];
    
    //Call callback method
    self.pmc->DefaultLampStateChangedCB();
    
    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.pmcdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

@end
