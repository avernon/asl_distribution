/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
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

#import "LSFSDKBasicControllerService.h"

@implementation LSFSDKBasicControllerService

@synthesize controllerConfiguration = _controllerConfiguration;

-(id)initWithControllerConfiguration: (id<LSFSDKLightingControllerConfiguration>)configuration
{
    self = [super init];

    if (self)
    {
        _controllerConfiguration = configuration;

        //initialize self as callback in LSFController
        [self initializeWithControllerServiceDelegate: self];
    }

    return self;
}

-(NSString *)getControllerDefaultDeviceID: (NSString *) generatedDeviceID
{
    return generatedDeviceID;
}

-(unsigned long long)getMacAddressAsDecimal: (NSString *)generatedMacAddress
{
    NSString *macAddr = [_controllerConfiguration getMacAddress: generatedMacAddress];
    NSScanner *scanner = [NSScanner scannerWithString: macAddr];

    unsigned long long macAddressLongLong;
    [scanner scanHexLongLong: &macAddressLongLong];

    return macAddressLongLong;
}

-(BOOL)isNetworkConnected
{
    return [_controllerConfiguration isNetworkConnected];
}

-(OEM_CS_RankParam_Mobility)getControllerRankMobility
{
    return [_controllerConfiguration getRankMobility];
}

-(OEM_CS_RankParam_Power)getControllerRankPower
{
    return [_controllerConfiguration getRankPower];
}

-(OEM_CS_RankParam_Availability)getControllerRankAvailability
{
    return [_controllerConfiguration getRankAvailability];
}

-(OEM_CS_RankParam_NodeType)getControllerRankNodeType
{
    return [_controllerConfiguration getRankNodeType];
}

-(void)populateDefaultProperties:(LSFSDKAboutData *)aboutData
{
    return [_controllerConfiguration populateDefaultProperties: aboutData];
}

@end
