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

#import "LSFObject.h"
#import "LampValues.h"

@interface LSFLampDetails : LSFObject

@property (nonatomic) LampMake lampMake;
@property (nonatomic) LampModel lampModel;
@property (nonatomic) DeviceType deviceType;
@property (nonatomic) LampType lampType;
@property (nonatomic) BaseType baseType;
@property (nonatomic) unsigned int lampBeamAngle;
@property (nonatomic) BOOL dimmable;
@property (nonatomic) BOOL color;
@property (nonatomic) BOOL variableColorTemp;
@property (nonatomic) BOOL hasEffects;
@property (nonatomic) unsigned int maxVoltage;
@property (nonatomic) unsigned int minVoltage;
@property (nonatomic) unsigned int wattage;
@property (nonatomic) unsigned int incandescentEquivalent;
@property (nonatomic) unsigned int maxLumens;
@property (nonatomic) unsigned int minTemperature;
@property (nonatomic) unsigned int maxTemperature;
@property (nonatomic) unsigned int colorRenderingIndex;
@property (nonatomic, strong) NSString *lampID;

-(id)init;

@end
