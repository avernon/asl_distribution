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

#import "LSFControllerClient.h"
#import "LSFControllerClientCallback.h"

@interface LSFControllerClient ()

@property (nonatomic, assign) AJNBusAttachment *bus;
@property (nonatomic, assign) LSFControllerClientCallback *controllerClientCallback;
@property (nonatomic, readonly) ControllerClient *controllerClient;

@end

@implementation LSFControllerClient

@synthesize bus = _bus;
@synthesize controllerClientCallback = _controllerClientCallback;
@synthesize controllerClient = _controllerClient;

-(id)initWithBusAttachment: (AJNBusAttachment *)bus
                            andControllerClientCallbackDelegate: (id<LSFControllerClientCallbackDelegate>)cccDelegate;
{
    self = [super init];
    
    if (self)
    {
        self.bus = bus;
        self.controllerClientCallback = new LSFControllerClientCallback(cccDelegate);
        self.handle = new ControllerClient(*static_cast<ajn::BusAttachment*>(bus.handle),
                                           *(self.controllerClientCallback));
    }
    
    return self;
}

-(void)dealloc
{
    lsf::ControllerClient *ptr = [self controllerClient];

    if (ptr)
    {
        delete ptr;
    }

    self.handle = NULL;
}

-(unsigned int)getVersion
{
    return self.controllerClient->GetVersion();
}

-(ControllerClientStatus)start
//-(void)start
{
    return self.controllerClient->Start();
    //self.controllerClient->Start();
}

-(ControllerClientStatus)stop
//-(void)stop
{
    return self.controllerClient->Stop();
    //self.controllerClient->Stop();
}

/*
 * Accessor for the internal C++ API object this objective-c class encapsulates
 */
- (lsf::ControllerClient *)controllerClient
{
    return static_cast<lsf::ControllerClient*>(self.handle);
}

@end

