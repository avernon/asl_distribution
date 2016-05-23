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

#import <Foundation/Foundation.h>
#import "LSFDataModel.h"

extern const NSString *PULSE_EFFECT_DEFAULT_NAME;
extern const unsigned int PULSE_EFFECT_DEFAULT_PERIOD;
extern const unsigned int PULSE_EFFECT_DEFAULT_DURATION;
extern const unsigned int PULSE_EFFECT_DEFAULT_COUNT;

@interface LSFPulseEffectDataModelV2 : LSFDataModel
{
    @protected BOOL endStateInitialized;
    @protected BOOL periodInitialized;
    @protected BOOL durationInitialized;
    @protected BOOL countInitialized;
}

@property (nonatomic, strong) LSFLampState *endState;
@property (nonatomic, strong) NSString *startPresetID;
@property (nonatomic, strong) NSString *endPresetID;
@property (nonatomic) unsigned int period;
@property (nonatomic) unsigned int duration;
@property (nonatomic) unsigned int count;
@property (nonatomic) BOOL startWithCurrent;

-(id)init;
-(id)initWithPulseEffectID: (NSString *)pulseEffectID;
-(id)initWithPulseEffectID: (NSString *)pulseEffectID andPulseEffectName: (NSString *)pulseEffectName;
-(BOOL)containsPreset: (NSString *) presetID;

@end
