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

#import "LSFAnyCollectionOneShotWrapper.h"
#import <LSFSDKLightingDirector.h>

@implementation LSFAnyCollectionOneShotWrapper

@synthesize trackingID = _trackingID;
@synthesize trackingDelegate = _trackingDelegate;
@synthesize action = _action;
@synthesize errorAction = _errorAction;

-(id)initWithTrackingID: (LSFSDKTrackingID *)tid trackingIDDelegate: (id<LSFTrackingIDDelegate>)delegate
{
    return [self initWithTrackingID: tid trackingIDDelegate: delegate action: nil onError: nil];
}

-(id)initWithTrackingID: (LSFSDKTrackingID *)tid action: (void (^)(id item))actionOnFound
{
    return [self initWithTrackingID: tid action: actionOnFound onError: nil];
}

-(id)initWithTrackingID:(LSFSDKTrackingID *)tid action:(void (^)(id item))actionOnFound onError:(void (^)(id item))actionOnError
{
    return [self initWithTrackingID: tid trackingIDDelegate: nil action: actionOnFound onError: actionOnError];
}

-(id)initWithTrackingID: (LSFSDKTrackingID *)tid trackingIDDelegate: (id<LSFTrackingIDDelegate>)delegate action: (void (^)(id item))actionOnFound onError: (void (^)(id item))actionOnError
{
    self = [super init];

    if (self)
    {
        self.trackingID = tid;
        self.trackingDelegate = delegate;
        self.action = actionOnFound;
        self.errorAction = actionOnError;
    }

    return self;
}

-(void)dealloc
{
    self.trackingID = nil;
    self.trackingDelegate = nil;
}

-(void)onAnyInitializedWithTrackingID: (LSFSDKTrackingID *)tid andLightingItem: (id)item
{
    if (tid && (tid.value == self.trackingID.value))
    {
        [[LSFSDKLightingDirector getLightingDirector] removeDelegate: self];

        if (self.trackingDelegate)
        {
            [self.trackingDelegate onTrackingIDReceived: tid lightingItem: item];
        }

        if (self.action)
        {
            self.action(item);
        }
    }
}

-(void)onAnyError: (LSFSDKLightingItemErrorEvent *)error
{
    if (error.trackingID && (error.trackingID.value == self.trackingID.value))
    {
        [[LSFSDKLightingDirector getLightingDirector] removeDelegate: self];

        if (self.trackingDelegate)
        {
            [self.trackingDelegate onTrackingIDError: error];
        }

        if (self.errorAction)
        {
            self.errorAction(error);
        }
    }
}

@end
