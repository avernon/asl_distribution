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

#import "LSFControllerServiceManager.h"
#import "LSFControllerServiceManagerCallback.h"

@interface LSFControllerServiceManager()

@property (nonatomic, readonly) lsf::ControllerServiceManager *controllerServiceManager;
@property (nonatomic, assign) LSFControllerServiceManagerCallback *controllerServiceManagerCallback;

@end

@implementation LSFControllerServiceManager

@synthesize controllerServiceManager = _controllerServiceManager;
@synthesize controllerServiceManagerCallback = _controllerServiceManagerCallback;

-(id)initWithControllerClient: (LSFControllerClient *)controllerClient andControllerServiceManagerCallbackDelegate: (id<LSFControllerServiceManagerCallbackDelegate>)csmDelegate
{
    self = [super init];
    
    if (self)
    {
        self.controllerServiceManagerCallback = new LSFControllerServiceManagerCallback(csmDelegate);
        self.handle = new lsf::ControllerServiceManager(*(static_cast<lsf::ControllerClient*>(controllerClient.handle)), *(self.controllerServiceManagerCallback));
    }
    
    return self;
}

-(ControllerClientStatus)getControllerServiceVersion
{
    return self.controllerServiceManager->GetControllerServiceVersion();
}

-(ControllerClientStatus)lightingResetControllerService
{
    return self.controllerServiceManager->LightingResetControllerService();
}

/*
 * Accessor for the internal C++ API object this objective-c class encapsulates
 */
- (lsf::ControllerServiceManager *)controllerServiceManager
{
    return static_cast<lsf::ControllerServiceManager*>(self.handle);
}

@end
