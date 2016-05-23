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

#import "LSFSDKColor.h"
#import "LSFConstants.h"

@implementation LSFSDKColor

@synthesize hue = _hue;
@synthesize saturation = _saturation;
@synthesize brightness = _brightness;
@synthesize colorTemp = _colorTemp;

-(id)initWithHsvt: (NSArray *)hsvt
{
    unsigned int hue = [(NSNumber *)[hsvt objectAtIndex: 0] unsignedIntValue];
    unsigned int saturation = [(NSNumber *)[hsvt objectAtIndex: 1] unsignedIntValue];
    unsigned int brightness = [(NSNumber *)[hsvt objectAtIndex: 2] unsignedIntValue];
    unsigned int colorTemp = [(NSNumber *)[hsvt objectAtIndex: 3] unsignedIntValue];

    return [self initWithHue: hue saturation: saturation brightness: brightness colorTemp: colorTemp];
}

-(id)initWithHue: (unsigned int)hueValue saturation: (unsigned int)satValue brightness: (unsigned int)brightnessValue colorTemp: (unsigned int)colorTempValue
{
    self = [super init];

    if (self)
    {
        self.hue = hueValue;
        self.saturation = satValue;
        self.brightness = brightnessValue;
        self.colorTemp = colorTempValue;
    }

    return self;
}

-(id)initWithColor: (LSFSDKColor *)color
{
    return [self initWithHue: color.hue saturation: color.saturation brightness: color.brightness colorTemp: color.colorTemp];
}

-(void)setHue: (unsigned int)hue
{
    LSFConstants *constants = [LSFConstants getConstants];
    _hue = MAX(MIN(hue, constants.MAX_HUE), constants.MIN_HUE);
}

-(void)setSaturation: (unsigned int)saturation
{
    LSFConstants *constants = [LSFConstants getConstants];
    _saturation = MAX(MIN(saturation, constants.MAX_SATURATION), constants.MIN_SATURATION);
}

-(void)setBrightness: (unsigned int)brightness
{
    LSFConstants *constants = [LSFConstants getConstants];
    _brightness = MAX(MIN(brightness, constants.MAX_BRIGHTNESS), constants.MIN_BRIGHTNESS);
}

-(void)setColorTemp: (unsigned int)colorTemp
{
    LSFConstants *constants = [LSFConstants getConstants];
    _colorTemp = MAX(MIN(colorTemp, constants.MAX_COLOR_TEMP), constants.MIN_COLOR_TEMP);
}

+(LSFSDKColor *)red
{
    return [[LSFSDKColor alloc] initWithHue: 0 saturation: 100 brightness: 100 colorTemp: 3500];
}

+(LSFSDKColor *)green
{
    return [[LSFSDKColor alloc] initWithHue: 120 saturation: 100 brightness: 50 colorTemp: 3500];
}

+(LSFSDKColor *)blue
{
    return [[LSFSDKColor alloc] initWithHue: 240 saturation: 100 brightness: 100 colorTemp: 3500];
}

+(LSFSDKColor *)white
{
    return [[LSFSDKColor alloc] initWithHue: 0 saturation: 0 brightness: 100 colorTemp: 3500];
}

@end
