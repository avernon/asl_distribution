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

#import "LSFSDKMyLampState.h"
#import "model/LSFConstants.h"

@implementation LSFSDKMyLampState

static LSFSDKColor *DEFAULT_COLOR = [LSFSDKColor white];

@synthesize power = _power;
@synthesize color = _color;

-(id)initWithLSFLampState: (LSFLampState *)state
{
    LSFConstants *constants = [LSFConstants getConstants];
    unsigned int hue = [constants unscaleLampStateValue: state.hue withMax: 100];
    unsigned int saturation = [constants unscaleLampStateValue: state.saturation withMax: 100];
    unsigned int brightness = [constants unscaleLampStateValue: state.brightness withMax: 100];
    unsigned int colorTemp = [constants unscaleColorTemp: state.colorTemp];

    return [self initWithPower: (state.onOff ? ON : OFF) hue: hue saturation: saturation brightness: brightness colorTemp: colorTemp];

}

-(id)initWithPower: (Power)power hue: (unsigned int)hue saturation: (unsigned int)sat brightness: (unsigned int)brightness colorTemp: (unsigned int)colorTemp;
{
    return [self initWithPower: power color: [[LSFSDKColor alloc] initWithHue: hue saturation: sat brightness: brightness colorTemp: colorTemp]];
}

-(id)initWithPower: (Power)power color: (LSFSDKColor *)colorState
{
    self = [super init];

    if (self)
    {
        _power = power;
        _color = (colorState != nil) ? colorState : DEFAULT_COLOR;
    }

    return self;
}

/*
 * LSFLightingLampState implementation
 */
-(BOOL)getPowerOn
{
    return (self.power == ON);
}

-(void)setPowerOn: (BOOL)powerOn
{
    _power = (powerOn) ? ON : OFF;
}

-(NSArray *)getColorHsvt
{
    NSNumber *hue = [[NSNumber alloc] initWithUnsignedInt: self.color.hue];
    NSNumber *saturation = [[NSNumber alloc] initWithUnsignedInt: self.color.saturation];
    NSNumber *brightness = [[NSNumber alloc] initWithUnsignedInt: self.color.brightness];
    NSNumber *colorTemp = [[NSNumber alloc] initWithUnsignedInt: self.color.colorTemp];

    return [NSArray arrayWithObjects: hue, saturation, brightness, colorTemp, nil];
}

-(void)setColorHsvtWithHue: (unsigned int)hueDegrees saturation: (unsigned int)saturationPercent brightness: (unsigned int)brightnessPercent colorTemp: (unsigned int)colorTempDegrees
{
    _color.hue = hueDegrees;
    _color.saturation = saturationPercent;
    _color.brightness = brightnessPercent;
    _color.colorTemp = colorTempDegrees;
}

@end
