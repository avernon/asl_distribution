/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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

#import "AJSCCommonBusListener.h"
#import "AJNSessionOptions.h"

@interface AJSCCommonBusListener ()
@property AJNSessionPort servicePort;
@end

@implementation AJSCCommonBusListener


- (id)initWithServicePort:(AJNSessionPort) servicePort
{
    self = [super init];
    if (self) {
        self.servicePort = servicePort;
    }
    return self;
}

- (void)setSessionPort:(AJNSessionPort) sessionPort
{
    self.servicePort = sessionPort;
}

- (AJNSessionPort)sessionPort
{
    return self.servicePort;
}

/* protocol method */
- (BOOL)shouldAcceptSessionJoinerNamed:(NSString *)joiner onSessionPort:(AJNSessionPort)sessionPort withSessionOptions:(AJNSessionOptions *)options
{
    if (sessionPort != self.servicePort)
    {
        NSLog(@"Rejecting join attempt on unexpected session port %hu.", sessionPort);
        return false;
    } else {
    NSLog(@"Accepting join session request from %@ (proximity=%c, traffic=%u, transports=%hu).\n", joiner, options.proximity, options.trafficType, options.transports);
    return true;
    }
}

@end
