/******************************************************************************
 * Copyright (c) 2015, AllSeen Alliance. All rights reserved.
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

#import "LSFController.h"
#import "Controller.h"

@interface LSFController()

@property (nonatomic, readonly) Controller *controller;

@end

@implementation LSFController

@synthesize controller = _controller;
@synthesize isLeader = _isLeader;
@synthesize name = _name;

-(id)init
{
    self = [super init];

    if (self)
    {
        self.handle = new Controller();
    }

    return self;
}

-(void)initializeWithControllerServiceDelegate: (id<LSFControllerServiceDelegate>)csd;
{
    self.controller->SetControllerCallback(csd);
}

-(void)dealloc
{
    Controller *ptr = [self controller];

    if (ptr)
    {
        delete ptr;
    }

    self.handle = NULL;
}

-(void)startControllerWithKeyStoreFilePath: (NSString *)keyStoreFilePath
{
    NSLog(@"LSFController.mm - start method exectuing. KeyStoreFilePath = %@", keyStoreFilePath);

    self.controller->StartController([keyStoreFilePath UTF8String]);
}

-(void)stopController
{
    NSLog(@"LSFController.mm - stop method exectuing");

    self.controller->StopController();
}

-(void)factoryResetController
{
    self.controller->FactoryResetController();
}

-(void)lightingResetController
{
    self.controller->LightingResetController();
}

-(void)sendNetworkConnected
{
    self.controller->SendNetworkConnected();
}

-(void)sendNetworkDisconnected
{
    self.controller->SendNetworkDisconnected();
}

-(BOOL)isLeader
{
    return self.controller->IsControllerLeader();
}

-(NSString *)name
{
    qcc::String controllerName = self.controller->GetControllerName();
    NSString *name = [NSString stringWithUTF8String: controllerName.c_str()];
    return name;
}

/*
 * Accessor for the internal C++ API object this objective-c class encapsulates
 */
- (Controller *)controller
{
    return static_cast<Controller*>(self.handle);
}

@end
