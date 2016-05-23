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

#import "CommonBusListener.h"
#import "AJNSessionOptions.h"

@interface CommonBusListener ()
@property AJNSessionPort servicePort;
@end

@implementation CommonBusListener

/**
 * Accept or reject an incoming JoinSession request. The session does not exist until this
 * after this function returns.
 *
 * This callback is only used by session creators. Therefore it is only called on listeners
 * passed to BusAttachment::BindSessionPort.
 *
 * @param joiner            Unique name of potential joiner.
 * @param sessionPort       Session port that was joined.
 * @param options           Session options requested by the joiner.
 * @return   Return true if JoinSession request is accepted. false if rejected.
 */

- (id)initWithServicePort:(AJNSessionPort)servicePort
{
	self = [super init];
	if (self) {
		self.servicePort = servicePort;
	}
	return self;
}

/**
 * Set the Value of the SessionPort associated with this SessionPortListener
 * @param sessionPort
 */
- (void)setSessionPort:(AJNSessionPort)sessionPort
{
	self.servicePort = sessionPort;
}

/**
 * Get the SessionPort of the listener
 * @return
 */
- (AJNSessionPort)sessionPort
{
	return self.servicePort;
}

//  protocol method
- (BOOL)shouldAcceptSessionJoinerNamed:(NSString *)joiner onSessionPort:(AJNSessionPort)sessionPort withSessionOptions:(AJNSessionOptions *)options
{
	if (sessionPort != self.servicePort) {
		NSLog(@"Rejecting join attempt on unexpected session port %hu.", sessionPort);
		return false;
	}
	else {
		NSLog(@"Accepting join session request from %@ (proximity=%c, traffic=%u, transports=%hu).\n", joiner, options.proximity, options.trafficType, options.transports);
		return true;
	}
}

@end
