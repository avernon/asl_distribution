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

#import "LSFDataModel.h"

@interface LSFDataModel()

@end

@implementation LSFDataModel

@synthesize state = _state;
@synthesize capability = _capability;
@synthesize uniformity = _uniformity;

-(id)initWithID: (NSString *)theID andName: (NSString *)name
{
    self = [super initWithID: theID andName: name];

    if (self)
    {
        self.state = [[LSFLampState alloc] init];
        self.capability = [[LSFCapabilityData alloc] init];
        self.uniformity = [[LSFLampStateUniformity alloc] init];
        stateInitialized = NO;
    }

    return self;
}

-(void)setState: (LSFLampState *)state
{
    _state = state;
    stateInitialized = YES;
}

-(BOOL)isInitialized
{
    return ([super isInitialized] && stateInitialized);
}

-(BOOL)isStateEqualToModelState: (LSFDataModel *)other
{
    return (other != nil) ? [self isStateEqualToLampState: other.state] : NO;
}

-(BOOL)isStateEqualToLampState: (LSFLampState *)otherState
{
    return otherState != nil ?
        [self isStateEqualToPowerOn: otherState.onOff hue: otherState.hue saturation: otherState.saturation brightness: otherState.brightness colorTemp: otherState.colorTemp] : NO;
}

-(BOOL)isStateEqualToPowerOn: (BOOL)onOff hue: (unsigned int)hue saturation:(unsigned int)saturation brightness:(unsigned int)brightness colorTemp:(unsigned int)colorTemp
{
    return
        [self.state hue]        == hue          &&
        [self.state saturation] == saturation   &&
        [self.state brightness] == brightness   &&
        [self.state colorTemp]  == colorTemp    &&
        [self.state onOff]      == onOff;
}

@end
