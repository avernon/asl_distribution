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

#import "LSFSDKMutableColorItem.h"
#import "model/LSFConstants.h"

@implementation LSFSDKMutableColorItem

-(void)turnOn
{
    [self setPowerOn: YES];
}

-(void)turnOff
{
    [self setPowerOn: NO];
}

-(void)setPower: (Power)power
{
    [self setPowerOn: (power == ON)];
}

-(void)togglePower
{
    [self setPowerOn: [self isOff]];
}

-(void)setColor: (LSFSDKColor *)color
{
    NSString *errorContext = @"LSFSDKMutableColorItem setColor: error";

    if ([self postInvalidArgIfNull: errorContext object: color])
    {
        [self setColorHsvtWithHue: color.hue saturation: color.saturation brightness: color.brightness colorTemp: color.colorTemp];
    }
}

-(void)setColorHsvt: (NSArray *)hsvt
{
    NSString *errorContext = @"LSFSDKMutableColorItem setColorHsvt: error";

    if ([self postInvalidArgIfNull: errorContext object: hsvt])
    {
        if ([hsvt count] != 4)
        {
            [self postInvalidArgIfNull: errorContext object: nil];
        }
        else
        {
            unsigned int hue = [(NSNumber *)[hsvt objectAtIndex: 0] unsignedIntValue];
            unsigned int saturation = [(NSNumber *)[hsvt objectAtIndex: 1] unsignedIntValue];
            unsigned int brightness = [(NSNumber *)[hsvt objectAtIndex: 2] unsignedIntValue];
            unsigned int colorTemp = [(NSNumber *)[hsvt objectAtIndex: 3] unsignedIntValue];

            [self setColorHsvtWithHue: hue saturation: saturation brightness: brightness colorTemp: colorTemp];
        }
    }
}

/*
 * LSFSDKLampState implementation
 */

-(void)setPowerOn: (BOOL)powerOn
{
    @throw [NSException exceptionWithName: NSInternalInconsistencyException reason: [NSString stringWithFormat:@"You must override %@ in a subclass", NSStringFromSelector(_cmd)] userInfo: nil];
}

-(void)setColorHsvtWithHue: (unsigned int)hueDegress saturation: (unsigned int)saturationPercent brightness: (unsigned int)brightnessPercent colorTemp: (unsigned int)colorTempDegrees
{
    @throw [NSException exceptionWithName: NSInternalInconsistencyException reason: [NSString stringWithFormat:@"You must override %@ in a subclass", NSStringFromSelector(_cmd)] userInfo: nil];
}

-(void)setHue:(unsigned int)hueDegrees
{
    @throw [NSException exceptionWithName: NSInternalInconsistencyException reason: [NSString stringWithFormat:@"You must override %@ in a subclass", NSStringFromSelector(_cmd)] userInfo: nil];
}

-(void)setSaturation:(unsigned int)saturationPercent
{
    @throw [NSException exceptionWithName: NSInternalInconsistencyException reason: [NSString stringWithFormat:@"You must override %@ in a subclass", NSStringFromSelector(_cmd)] userInfo: nil];
}

-(void)setBrightness:(unsigned int)brightnessPercent
{
    @throw [NSException exceptionWithName: NSInternalInconsistencyException reason: [NSString stringWithFormat:@"You must override %@ in a subclass", NSStringFromSelector(_cmd)] userInfo: nil];
}

-(void)setColorTemp:(unsigned int)colorTempDegrees
{
    @throw [NSException exceptionWithName: NSInternalInconsistencyException reason: [NSString stringWithFormat:@"You must override %@ in a subclass", NSStringFromSelector(_cmd)] userInfo: nil];
}

@end
