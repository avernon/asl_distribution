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

#import "LSFLampState.h"
#import "LSFTypes.h"

@interface LSFLampState()

@property (nonatomic, readonly) lsf::LampState *lampState;

@end

@implementation LSFLampState

@synthesize lampState = _lampState;

-(id)init
{
    self = [super init];
    
    if (self)
    {
        self.handle = new lsf::LampState();
    }
    
    return self;
}

-(id)initWithOnOff: (BOOL)onOff brightness: (unsigned int)brightness hue: (unsigned int)hue saturation: (unsigned int)saturation colorTemp: (unsigned int)colorTemp;
{
    self = [super init];
    
    if (self)
    {
        self.handle = new lsf::LampState(onOff, hue, saturation, colorTemp, brightness);
    }
    
    return self;
}

-(void)setOnOff: (BOOL)onOff
{
    self.lampState->onOff = onOff;
}

-(BOOL)onOff
{
    bool onOff = self.lampState->onOff;
    
    if (onOff)
    {
        return YES;
    }
    else
    {
        return NO;
    }
}

-(void)setBrightness: (unsigned int)brightness
{
    self.lampState->brightness = brightness;
}

-(unsigned int)brightness
{
    return self.lampState->brightness;
}

-(void)setHue: (unsigned int)hue
{
    self.lampState->hue = hue;
}

-(unsigned int)hue
{
    return self.lampState->hue;
}

-(void)setSaturation: (unsigned int)saturation
{
    self.lampState->saturation = saturation;
}

-(unsigned int)saturation
{
    return self.lampState->saturation;
}

-(void)setColorTemp: (unsigned int)colorTemp
{
    self.lampState->colorTemp = colorTemp;
}

-(unsigned int)colorTemp
{
    return self.lampState->colorTemp;
}

/*
 * Accessor for the internal C++ API object this objective-c class encapsulates
 */
- (lsf::LampState *)lampState
{
    return static_cast<lsf::LampState*>(self.handle);
}

@end
