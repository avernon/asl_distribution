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

#import <Foundation/Foundation.h>
@class AJGWCGatewayMgmtApp;

/**
 *  This class is responsible for handling session related events from the AllJoyn system.
 *  Extend this class to receive the events of: <br>
 *      - sessionEstablished <br>
 *      - sessionLost    <br>
 *
 *  The events are called on the AllJoyn thread, so avoid blocking them with
 *  long running tasks.
 */
@protocol AJGWCSessionListener <NSObject>

/**
 * sessionEstablished - callback when a session is established with a gateway
 * @param gatewayMgmtApp The gateway that the session will established with
 */
- (void)sessionEstablished:(AJGWCGatewayMgmtApp*) gatewayMgmtApp;

/**
 * sessionLost - callback when a session is lost with a gateway
 * @param gatewayMgmtApp The gateway that the session was lost with
 */
- (void)sessionLost:(AJGWCGatewayMgmtApp*) gatewayMgmtApp;

@end
