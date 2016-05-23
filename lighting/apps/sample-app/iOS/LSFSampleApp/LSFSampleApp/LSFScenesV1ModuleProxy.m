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

#import "LSFScenesV1ModuleProxy.h"
#import "scenesV1/LSFScenesV1SupportDelegate.h"
#import "LSFScenesV1NoSupportDelegate.h"

@implementation LSFScenesV1ModuleProxy

@synthesize scenesV1Delegate = _scenesV1Delegate;

+(LSFScenesV1ModuleProxy *)getProxy
{
    static LSFScenesV1ModuleProxy *proxy = nil;
    static dispatch_once_t onceToken;

    dispatch_once(&onceToken, ^{
        proxy = [[self alloc] init];
    });

    return proxy;
}

-(id)init
{
    self = [super init];

    if (self)
    {
#ifdef LSF_SCENES_V1_MODULE
        _scenesV1Delegate = [[LSFScenesV1SupportDelegate alloc] init];
#else
        _scenesV1Delegate = [[LSFScenesV1NoSupportDelegate alloc] init];
#endif
    }

    return self;
}

@end
