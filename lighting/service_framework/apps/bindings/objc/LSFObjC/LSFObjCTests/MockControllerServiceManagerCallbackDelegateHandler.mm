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

#import "MockControllerServiceManagerCallbackDelegateHandler.h"

@interface MockControllerServiceManagerCallbackDelegateHandler()

@property (nonatomic) NSMutableArray *dataArray;

@end

@implementation MockControllerServiceManagerCallbackDelegateHandler

@synthesize dataArray = _dataArray;

-(id)init
{
    self = [super init];
    
    if (self)
    {
        self.dataArray = [[NSMutableArray alloc] init];
    }
    
    return self;
}

-(NSArray *)getCallbackData
{
    return self.dataArray;
}

//Delegate Methods
-(void)getControllerServiceVersionReply: (unsigned int)version
{
    [self.dataArray removeAllObjects];
    NSNumber *csVersion = [[NSNumber alloc] initWithUnsignedInteger: version];
    [self.dataArray addObject: @"getControllerServiceVersion"];
    [self.dataArray addObject: csVersion];
}

-(void)lightingResetControllerServiceReplyWithCode: (LSFResponseCode)rc
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"lightingResetControllerService"];
    [self.dataArray addObject: responseCode];
}

-(void)controllerServiceLightingReset
{
    [self.dataArray removeAllObjects];
    [self.dataArray addObject: @"controllerServiceLightingReset"];
}

-(void)controllerServiceNameChangedForControllerID: (NSString *)controllerID andName: (NSString *)controllerName
{
    [self.dataArray removeAllObjects];
    [self.dataArray addObject: @"controllerServiceNameChanged"];
    [self.dataArray addObject: controllerID];
    [self.dataArray addObject: controllerName];
}

@end
