/******************************************************************************
 * Copyright (c) 2015, AllSeen Alliance. All rights reserved.
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

#import <lsf/controllerservice/OEM_CS_Config.h>
#import "../LSFSDKAboutData.h"

using namespace lsf;

#ifdef LSF_BINDINGS
using namespace controllerservice;
#endif

@protocol LSFControllerServiceDelegate <NSObject>

-(NSString *)getControllerDefaultDeviceID: (NSString *)generatedDeviceID;
-(unsigned long long)getMacAddressAsDecimal: (NSString *)generatedMacAddress;
-(BOOL)isNetworkConnected;
-(OEM_CS_RankParam_Mobility)getControllerRankMobility;
-(OEM_CS_RankParam_Power)getControllerRankPower;
-(OEM_CS_RankParam_Availability)getControllerRankAvailability;
-(OEM_CS_RankParam_NodeType)getControllerRankNodeType;
-(void)populateDefaultProperties: (LSFSDKAboutData *)aboutData;

@end
