////////////////////////////////////////////////////////////////////////////////
// Copyright AllSeen Alliance. All rights reserved.
//
//    Contributed by Qualcomm Connected Experiences, Inc.,
//    with authorization from the AllSeen Alliance, Inc.
//    
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//    
//        http://www.apache.org/licenses/LICENSE-2.0
//    
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//    
//    Pursuant to Section 1 of the License, the work of authorship constituting
//    a Work and any Contribution incorporated in the Work shall mean only that
//    Contributor's code submissions authored by that Contributor.  Any rights
//    granted under the License are conditioned upon acceptance of these
//    clarifications.
////////////////////////////////////////////////////////////////////////////////

#import "AJNBusController.h"

////////////////////////////////////////////////////////////////////////////////
//
// Service Delegate Protocol
//

@protocol AJNServiceDelegate <AJNBusControllerDelegate>

@property (nonatomic, readonly) AJNBusObject *object;

- (AJNBusObject *)objectOnBus:(AJNBusAttachment *)bus;
- (void)shouldUnloadObjectOnBus:(AJNBusAttachment *)bus;

@optional

- (BOOL)shouldAcceptSessionJoinerNamed:(NSString *)joiner onSessionPort:(AJNSessionPort)sessionPort withSessionOptions:(AJNSessionOptions *)options;
- (void)didJoin:(NSString *)joiner inSessionWithId:(AJNSessionId)sessionId onSessionPort:(AJNSessionPort)sessionPort;

@end
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Service Controller
//

@interface AJNServiceController : NSObject<AJNBusController, AJNSessionPortListener>

@property (nonatomic, weak) id<AJNServiceDelegate> delegate;

@end
////////////////////////////////////////////////////////////////////////////////
