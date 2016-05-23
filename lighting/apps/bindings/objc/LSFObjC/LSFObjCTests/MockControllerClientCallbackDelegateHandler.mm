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

#import "MockControllerClientCallbackDelegateHandler.h"

@interface MockControllerClientCallbackDelegateHandler()

@property (nonatomic) NSMutableArray *dataArray;

@end

@implementation MockControllerClientCallbackDelegateHandler

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

//Delegate methods
-(void)connectedToControllerServiceWithID: (NSString *)controllerServiceID andName: (NSString *)controllerServiceName
{
    [self.dataArray removeAllObjects];
    [self.dataArray addObject: @"connectedToControllerService"];
    [self.dataArray addObject: controllerServiceID];
    [self.dataArray addObject: controllerServiceName];
}

-(void)connectToControllerServiceFailedForID: (NSString *)controllerServiceID andName: (NSString *)controllerServiceName
{
    [self.dataArray removeAllObjects];
    [self.dataArray addObject: @"connectToControllerServiceFailed"];
    [self.dataArray addObject: controllerServiceID];
    [self.dataArray addObject: controllerServiceName];
}

-(void)disconnectedFromControllerServiceWithID: (NSString *)controllerServiceID andName: (NSString *)controllerServiceName
{
    [self.dataArray removeAllObjects];
    [self.dataArray addObject: @"disconnectedFromControllerService"];
    [self.dataArray addObject: controllerServiceID];
    [self.dataArray addObject: controllerServiceName];
}

-(void)controllerClientError: (NSArray *)ec
{
    [self.dataArray removeAllObjects];
    [self.dataArray addObject: @"controllerClientError"];
    [self.dataArray addObject: ec];
}

@end
