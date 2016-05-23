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

#import "LSFHelperControllerServiceManagerCallback.h"
#import "LSFAllJoynManager.h"
#import "LSFDispatchQueue.h"
#import "LSFControllerModel.h"

@interface LSFHelperControllerServiceManagerCallback()

@property (nonatomic, strong) dispatch_queue_t queue;

@end

@implementation LSFHelperControllerServiceManagerCallback

@synthesize queue = _queue;

-(id)init
{
    self = [super init];

    if (self)
    {
        self.queue = ([LSFDispatchQueue getDispatchQueue]).queue;
    }

    return self;
}

/*
 * Implementation of LSFControllerServiceManagerCallbackDelegate
 */

-(void)getControllerServiceVersionReply: (unsigned int)version
{
    LSFControllerModel *model = [LSFControllerModel getControllerModel];
    model.controllerVersion = version;
}

-(void)lightingResetControllerServiceReplyWithCode: (LSFResponseCode)rc
{
    NSLog(@"LSFSampleControllerServiceManagerCallback - Lighting Controller Service Reset reply with code %i", rc);
}

-(void)controllerServiceLightingReset
{
    NSLog(@"LSFSampleControllerServiceManagerCallback - Controller Service Lighting Reset");
}

-(void)controllerServiceNameChangedForControllerID: (NSString *)controllerID andName: (NSString *)controllerName
{
    LSFControllerModel *model = [LSFControllerModel getControllerModel];

    if ([model.theID isEqualToString: controllerID])
    {
        NSLog(@"Controller name changed and Controller IDs match");
        model.name = controllerName;

        dispatch_async(dispatch_get_main_queue(), ^{
            [[NSNotificationCenter defaultCenter] postNotificationName: @"ControllerNameChanged" object: self userInfo: nil];
        });
    }
}

@end
