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

#import "internal/LSFObject.h"
#import <LampValues.h>

/**
 * This class encapsulates all of the details for lamps and illustrates the make/model of the lamp
 * as well as the capabilities of the lamp.
 */
@interface LSFSDKLampDetails : LSFObject

/** @name Class Properties */

/**
 * Specifies the make of the lamp.
 */
@property (nonatomic) LampMake lampMake;

/**
 * Specifies the model of the lamp.
 */
@property (nonatomic) LampModel lampModel;

/**
 * Specifies the device type of the lamp.
 */
@property (nonatomic) DeviceType deviceType;

/**
 * Specifies the base type of the lamp.
 */
@property (nonatomic) LampType lampType;

/**
 * Specifies the base type of the lamp.
 */
@property (nonatomic) BaseType baseType;

/**
 * Specifies the beam angle of the lamp.
 */
@property (nonatomic) unsigned int lampBeamAngle;

/**
 * Indicates whether or not the lamp is dimmable.
 */
@property (nonatomic) BOOL dimmable;

/**
 * Indicates whether or not the lamp supports color.
 */
@property (nonatomic) BOOL color;

/**
 * Indicates whether or not the lamp has a variable color temperature.
 */
@property (nonatomic) BOOL variableColorTemp;

/**
 * Indicates whether or not the lamp supports effects.
 */
@property (nonatomic) BOOL hasEffects;

/**
 * Specifies the maximum voltage of the lamp.
 */
@property (nonatomic) unsigned int maxVoltage;

/**
 * Specifies the minimum voltage of the lamp.
 */
@property (nonatomic) unsigned int minVoltage;

/**
 * Specifies the wattage of the lamp.
 */
@property (nonatomic) unsigned int wattage;

/**
 * Specifies the incandescent equivalent wattage of the lamp.
 */
@property (nonatomic) unsigned int incandescentEquivalent;

/**
 * Specifies the maximum lumens supported by the lamp.
 */
@property (nonatomic) unsigned int maxLumens;

/**
 * Specifies the minimum color temperature of the lamp.
 */
@property (nonatomic) unsigned int minTemperature;

/**
 * Specifies the maximum color temperature of the lamp.
 */
@property (nonatomic) unsigned int maxTemperature;

/**
 * Specifies the color rendering index of the lamp.
 */
@property (nonatomic) unsigned int colorRenderingIndex;

/**
 * Specifies the ID of the lamp.
 */
@property (nonatomic, strong) NSString *lampID;

/** @name Initializing an LSFSDKLampDetails Object */

/**
 * Constructs a LSFSDKLampDetails object.
 *
 * @warning This method is intended to be used internally. Client software should not instantiate
 * LSFSDKLampDetails directly, but should instead get them from the LSFSDKLamp using the [LSFSDKLamp details]
 * method.
 */
-(id)init;

@end
