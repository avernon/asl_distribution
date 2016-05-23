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

#import "LSFPresetModelContainer.h"
#import "LSFPresetModel.h"

@interface LSFPresetModelContainer()

//-(void)populateDictionary;

@end

@implementation LSFPresetModelContainer

@synthesize presetContainer = _presetContainer;

+(id)getPresetModelContainer
{
    static LSFPresetModelContainer *presetModelContainer = nil;
    static dispatch_once_t onceToken;
    
    dispatch_once(&onceToken, ^{
        presetModelContainer = [[self alloc] init];
    });
    
    return presetModelContainer;
}

-(id)init
{
    self = [super init];
    
    if (self)
    {
        self.presetContainer = [[NSMutableDictionary alloc] init];
        
        //TODO - remove this call, only used for testing
        //[self populateDictionary];
    }
    
    return self;
}

/*
 * Private Functions
 */
//TODO - delete function when testing is over
//-(void)populateDictionary
//{
//    LSFPresetModel *model1 = [[LSFPresetModel alloc] initWithPresetID: @"presetID1"];
//    model1.presetName = @"Max";
//    model1.preset = [[LSFLampState alloc] initWithOnOff: YES brightness: 100 hue: 360 saturation: 100 colorTemp: 9000];
//    [self.presetContainer setValue: model1 forKey: @"presetID1"];
//    
//    LSFPresetModel *model2 = [[LSFPresetModel alloc] initWithPresetID: @"presetID2"];
//    model2.presetName = @"Half";
//    model2.preset = [[LSFLampState alloc] initWithOnOff: YES brightness: 50 hue: 180 saturation: 50 colorTemp: 5000];
//    [self.presetContainer setValue: model2 forKey: @"presetID2"];
//}
@end
