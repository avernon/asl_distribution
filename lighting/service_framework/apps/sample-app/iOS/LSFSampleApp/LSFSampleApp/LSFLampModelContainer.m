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

#import "LSFLampModelContainer.h"
#import "LSFLampModel.h"

@interface LSFLampModelContainer()

//-(void)populateDictionary;

@end

@implementation LSFLampModelContainer

@synthesize lampContainer = _lampContainer;

+(id)getLampModelContainer
{
    static LSFLampModelContainer *lampModelContainer = nil;
    static dispatch_once_t onceToken;
    
    dispatch_once(&onceToken, ^{
        lampModelContainer = [[self alloc] init];
    });
    
    return lampModelContainer;
}

-(id)init
{
    self = [super init];
    
    if (self)
    {
        self.lampContainer = [[NSMutableDictionary alloc] init];
        
        //TODO - remove this call, only used for testing
        //[self populateDictionary];
    }
    
    return self;
}

//TODO - delete function when testing is over
//-(void)populateDictionary
//{
//    LSFLampModel *model1 = [[LSFLampModel alloc] initWithLampID: @"LampID1"];
//    [model1 setName: @"Basic White Lamp"];
//    [model1 setState: [[LSFLampState alloc] initWithOnOff: YES brightness: 0 hue: 0 saturation: 0 colorTemp: 0]];
//    
//    //Set Lamp Details
//    LSFLampDetails *lampDetails = [[LSFLampDetails alloc] init];
//    lampDetails.dimmable = NO;
//    lampDetails.color = NO;
//    lampDetails.variableColorTemp = NO;
//    [model1 setLampDetails: lampDetails];
//    
//    [self.lampContainer setValue: model1 forKey: @"LampID1"];
//    
//    LSFLampModel *model2 = [[LSFLampModel alloc] init];
//    [model2 setTheID: @"LampID2"];
//    [model2 setName: @"Dimmable White Lamp"];
//    [model2 setState: [[LSFLampState alloc] initWithOnOff: NO brightness: 25 hue: 0 saturation: 0 colorTemp: 0]];
//    
//    //Set Lamp Details
//    lampDetails = [[LSFLampDetails alloc] init];
//    lampDetails.dimmable = YES;
//    lampDetails.color = NO;
//    lampDetails.variableColorTemp = NO;
//    [model2 setLampDetails: lampDetails];
//    
//    [self.lampContainer setValue: model2 forKey: @"LampID2"];
//    
//    LSFLampModel *model3 = [[LSFLampModel alloc] init];
//    [model3 setTheID: @"LampID3"];
//    [model3 setName: @"Tunable White Lamp"];
//    [model3 setState: [[LSFLampState alloc] initWithOnOff: NO brightness: 50 hue: 0 saturation: 0 colorTemp: 6000]];
//    
//    //Set Lamp Details
//    lampDetails = [[LSFLampDetails alloc] init];
//    lampDetails.dimmable = YES;
//    lampDetails.color = NO;
//    lampDetails.variableColorTemp = YES;
//    [model3 setLampDetails: lampDetails];
//    
//    [self.lampContainer setValue: model3 forKey: @"LampID3"];
//}

@end
