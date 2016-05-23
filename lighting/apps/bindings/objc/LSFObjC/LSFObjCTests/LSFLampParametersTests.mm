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

#import "LSFLampParametersTests.h"
#import <LSFSDKLampParameters.h>

@interface LSFLampParametersTests()

@property (nonatomic) LSFSDKLampParameters *lampParams;

@end

@implementation LSFLampParametersTests

@synthesize lampParams = _lampParams;

-(void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
    
    self.lampParams = [[LSFSDKLampParameters alloc] init];
}

-(void)tearDown
{
    self.lampParams = nil;
    
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

-(void)testEnergyUsageMilliwatts
{
    XCTAssertTrue((self.lampParams.energyUsageMilliwatts == 0), @"Energy Usage Milliwatts should be zero");

    unsigned int eumData = 9;
    self.lampParams.energyUsageMilliwatts = eumData;
    XCTAssertTrue((self.lampParams.energyUsageMilliwatts == eumData), @"Energy Usage Milliwatts should be 9");
}

-(void)testLumens
{
    XCTAssertTrue((self.lampParams.lumens == 0), @"Lumens should be zero");

    unsigned int lumensData = 300;
    self.lampParams.lumens = lumensData;
    XCTAssertTrue((self.lampParams.lumens == lumensData), @"Lumens should be 300");
}

@end
