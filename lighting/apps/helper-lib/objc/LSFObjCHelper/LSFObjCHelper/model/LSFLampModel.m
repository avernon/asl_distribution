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

#import "LSFLampModel.h"

NSString *LAMP_DEFAULT_NAME = @"<Loading lamp info...>";

@interface LSFLampModel()

@property (nonatomic) BOOL detailsInitialized;

@end

@implementation LSFLampModel

@synthesize lampDetails = _lampDetails;
@synthesize lampParameters = _lampParameters;
@synthesize aboutData = _aboutData;
@synthesize detailsInitialized = _detailsInitialized;

-(id)initWithLampID: (NSString *)lampID
{
    return [self initWithLampID: lampID andLampName: @"<Loading lamp info...>"];
}

-(id)initWithLampID: (NSString *)lampID andLampName: (NSString *)name
{
    self = [super initWithID: lampID andName: name];

    if (self)
    {
        self.lampDetails = [[LSFSDKLampDetails alloc] init];
        self.lampParameters = [[LSFSDKLampParameters alloc] init];
        self.aboutData = [[LSFLampAbout alloc] init];
        self.detailsInitialized = NO;
    }

    return self;
}

-(void)setLampDetails: (LSFSDKLampDetails *)lampDetails
{
    _lampDetails = lampDetails;
    self.capability = [[LSFCapabilityData alloc] initWithDimmable: self.lampDetails.dimmable color: self.lampDetails.color andTemp: self.lampDetails.variableColorTemp];
    self.detailsInitialized = YES;
}

-(BOOL)isInitialized
{
    return ([super isInitialized] && self.detailsInitialized);
}

@end
