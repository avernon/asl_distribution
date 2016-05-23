/******************************************************************************
 * Copyright (c) AllSeen Alliance. All rights reserved.
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
#import "LSFLampState.h"

@interface LSFPulseEffectV2 : LSFObject

@property (nonatomic, strong) LSFLampState *toState;
@property (nonatomic) unsigned int pulsePeriod;
@property (nonatomic) unsigned int pulseDuration;
@property (nonatomic) unsigned int numPulses;
@property (nonatomic, strong) LSFLampState *fromState;
@property (nonatomic, strong) NSString * toPreset;
@property (nonatomic, strong) NSString * fromPreset;
@property (nonatomic) BOOL invalidArgs;

-(id)init;
-(id)initWithToLampState: (LSFLampState *)toLampState period: (unsigned int)period duration: (unsigned int)duration numPulses: (unsigned int)numPulses;
-(id)initWithToLampState: (LSFLampState *)toLampState period: (unsigned int)period duration: (unsigned int)duration numPulses: (unsigned int)numPulses fromLampState: (LSFLampState *)fromLampState;
-(id)initWithToPreset: (NSString *)toLampPreset period: (unsigned int)period duration: (unsigned int)duration numPulses: (unsigned int)numPulses;
-(id)initWithToPreset: (NSString *)toLampPreset period: (unsigned int)period duration: (unsigned int)duration numPulses: (unsigned int)numPulses fromPreset: (NSString *)fromLampPreset;

@end
