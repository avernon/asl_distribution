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

#import "LSFLampStateUniformity.h"

@implementation LSFLampStateUniformity

@synthesize power = _power;
@synthesize brightness = _brightness;
@synthesize hue = _hue;
@synthesize saturation = _saturation;
@synthesize colorTemp = _colorTemp;

-(id)init
{
    return [self initWithPower: YES brightness: YES hue: YES saturation: YES andColorTemp: YES];
}

-(id)initWithLampStateUniformity: (LSFLampStateUniformity *)other
{
    return [self initWithPower: other.power brightness:other.brightness hue:other.hue saturation:other.saturation andColorTemp:other.colorTemp];
}

-(id)initWithPower: (BOOL)power brightness: (BOOL)brightness hue: (BOOL)hue saturation: (BOOL)saturation andColorTemp: (BOOL)colorTemp
{
    self = [super init];

    if (self)
    {
        self.power = power;
        self.brightness = brightness;
        self.hue = hue;
        self.saturation = saturation;
        self.colorTemp = colorTemp;
    }

    return self;
}

@end
