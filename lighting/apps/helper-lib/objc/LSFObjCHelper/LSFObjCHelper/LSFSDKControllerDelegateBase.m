/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
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

#import "LSFSDKControllerDelegateBase.h"
#import "LSFSDKLightingDirector.h"
#import "manager/LSFControllerManager.h"
#import "manager/LSFSDKLightingSystemManager.h"

@implementation LSFSDKControllerDelegateBase

@synthesize delegate = _delegate;

-(id)init
{
    self = [super init];

    if (self)
    {
        //Intentionally left blank
    }

    return self;
}

-(void)onLeaderChange: (LSFSDKController *)leader
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        if (self.delegate)
        {
            [self.delegate onNextControllerConnection];
        }
    });

    //Remove self as delegate
    LSFSDKLightingSystemManager *manager = [[LSFSDKLightingDirector getLightingDirector] lightingManager];
    [[manager controllerManager] removeDelegate: self];
}

-(void)onControllerError: (LSFSDKControllerErrorEvent *)errorEvent
{
    //Intentionally left blank
}

@end
