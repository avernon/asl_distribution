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
#import "alljoyn/Status.h"
#import "AJNSessionOptions.h"
#import "alljoyn/gateway/GatewayMgmtApp.h"
#import "AJGWCAnnouncedApp.h"
#import "AJGWCGatewayMgmtApp.h"
#import "AJGWCSessionResult.h"
#import "AJGWCSessionListener.h"

@interface AJGWCGatewayMgmtApp : AJGWCAnnouncedApp

/**
 * Constructor
 * @param handle A handle to a cpp GatewayMgmtApp object
 */
- (id)initWithHandle:(ajn::gwc::GatewayMgmtApp*) handle;

/**
 * Constructor
 * @param busUniqueName The name of the {@link AJNBusAttachment} of the gateway that sent
 * the Announcement
 * @param aboutData The data sent with the Announcement
 */
- (id)initWithbusUniqueName:(NSString*) busUniqueName aboutData:(NSDictionary *) aboutData;

/**
 * Retrieve the list of applications installed on the gateway identified by the given gwBusName
 * @param sessionId The id of the session established with the gateway
 * @param connectorApps A reference to an array of The {@link AJGWCConnectorApp} installed applications
 * @return status of operation
 */
- (QStatus)retrieveConnectorApps:(AJNSessionId) sessionId connectorApps:(NSMutableArray*) connectorApps;

/**
 * Join session synchronously with the given gateway identified by the gwBusName.
 * This method doesn't require {@link AJGWCSessionListener}. Use this method
 * when there is no need to receive any session related event.
 * @return {@link AJGWCSessionResult}
 */
- (AJGWCSessionResult*)joinSession;

/**
 * Join session synchronously with the given gateway identified by the gwBusName.
 * The session related events will be sent to the given listener.
 * @param listener The listener is used to be notified about the session related events
 * @return {@link AJGWCSessionResult}
 */
- (AJGWCSessionResult*)joinSession:(id<AJGWCSessionListener>) listener;

/**
 * Join session asynchronously with the given gwBusName.
 * @param listener The listener is used to be notified about the session related events
 * @return Returns the joinSessionAsync status {@link QStatus}
 */
- (QStatus)joinSessionAsync:(id<AJGWCSessionListener>) listener;

/**
 * Disconnect the given session
 * @return Returns the leave session {@link QStatus}
 */
- (QStatus)leaveSession;

/**
 * Get the Listener defined for this SessionHandler
 * @return listener
 */
- (id<AJGWCSessionListener>)listener;

@end
