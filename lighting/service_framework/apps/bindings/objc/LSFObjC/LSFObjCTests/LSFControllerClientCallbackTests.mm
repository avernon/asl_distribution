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

#import "LSFControllerClientCallbackTests.h"
#import "MockControllerClientCallbackDelegateHandler.h"
#import "LSFObjC/LSFControllerClientCallback.h"

@interface LSFControllerClientCallbackTests()

@property (nonatomic) MockControllerClientCallbackDelegateHandler *cccdh;
@property (nonatomic) LSFControllerClientCallback *ccc;
@property (nonatomic) NSMutableArray *dataArray;

@end

@implementation LSFControllerClientCallbackTests

@synthesize cccdh = _cccdh;
@synthesize ccc = _ccc;
@synthesize dataArray = _dataArray;

-(void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
    
    self.cccdh = [[MockControllerClientCallbackDelegateHandler alloc] init];
    self.ccc = new LSFControllerClientCallback(self.cccdh);
    self.dataArray = [[NSMutableArray alloc] init];
}

-(void)tearDown
{
    delete self.ccc;
    self.cccdh = nil;
    
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

-(void)testConnectedToControllerService
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];
    
    //Populate array with test data
    NSString *functionName = @"connectedToControllerService";
    NSString *controllerServiceID = @"TestContollerServiceID";
    NSString *controllerServiceName = @"TestControllerServiceName";
    
    [self.dataArray addObject: functionName];
    [self.dataArray addObject: controllerServiceID];
    [self.dataArray addObject: controllerServiceName];
    
    //Call callback method
    std::string csID([controllerServiceID UTF8String]);
    std::string csName([controllerServiceName UTF8String]);
    self.ccc->ConnectedToControllerServiceCB(csID, csName);
    
    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.cccdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testConnectToControllerServiceFailed
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];
    
    //Populate array with test data
    NSString *functionName = @"connectToControllerServiceFailed";
    NSString *controllerServiceID = @"TestContollerServiceID";
    NSString *controllerServiceName = @"TestControllerServiceName";
    
    [self.dataArray addObject: controllerServiceName];
    [self.dataArray addObject: controllerServiceID];
    [self.dataArray addObject: functionName];
    
    //Call callback method
    std::string csID([controllerServiceID UTF8String]);
    std::string csName([controllerServiceName UTF8String]);
    self.ccc->ConnectToControllerServiceFailedCB(csID, csName);
    
    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.cccdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testDisconnectedFromControllerService
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];
    
    //Populate array with test data
    NSString *functionName = @"disconnectedFromControllerService";
    NSString *controllerServiceID = @"TestContollerServiceID";
    NSString *controllerServiceName = @"TestControllerServiceName";
    
    [self.dataArray addObject: controllerServiceName];
    [self.dataArray addObject: controllerServiceID];
    [self.dataArray addObject: functionName];
    
    //Call callback method
    std::string csID([controllerServiceID UTF8String]);
    std::string csName([controllerServiceName UTF8String]);
    self.ccc->DisconnectedFromControllerServiceCB(csID, csName);
    
    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.cccdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

-(void)testControllerClientError
{
    //Ensure array is empty
    [self.dataArray removeAllObjects];
    
    //Populate array with test data
    NSString *functionName = @"controllerClientError";
    NSNumber *num1 = [[NSNumber alloc] initWithInt: ERROR_NONE];
    NSNumber *num2 = [[NSNumber alloc] initWithInt: ERROR_NO_ACTIVE_CONTROLLER_SERVICE_FOUND];
    NSNumber *num3 = [[NSNumber alloc] initWithInt: ERROR_REGISTERING_SIGNAL_HANDLERS];
    NSNumber *num4 = [[NSNumber alloc] initWithInt: ERROR_ALLJOYN_METHOD_CALL_TIMEOUT];
    NSArray *errorCodeArray = [[NSArray alloc] initWithObjects: num1, num2, num3, num4, nil];
    
    [self.dataArray addObject: errorCodeArray];
    [self.dataArray addObject: functionName];
    
    //Call callback method
    ErrorCodeList errorCodeList;
    errorCodeList.push_back(ERROR_NONE);
    errorCodeList.push_back(ERROR_NO_ACTIVE_CONTROLLER_SERVICE_FOUND);
    errorCodeList.push_back(ERROR_REGISTERING_SIGNAL_HANDLERS);
    errorCodeList.push_back(ERROR_ALLJOYN_METHOD_CALL_TIMEOUT);
    self.ccc->ControllerClientErrorCB(errorCodeList);
    
    //Test the data using NSSet
    NSSet *startData = [[NSSet alloc] initWithArray: self.dataArray];
    NSSet *endData = [[NSSet alloc] initWithArray: [self.cccdh getCallbackData]];
    BOOL isSetsEqual = [startData isEqualToSet: endData];
    XCTAssertTrue(isSetsEqual, @"Start and end data should be equal");
}

@end
