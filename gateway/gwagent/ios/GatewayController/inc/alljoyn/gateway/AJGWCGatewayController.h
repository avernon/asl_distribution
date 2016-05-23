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
#import "AJNBusAttachment.h"
#import "AJGWCGatewayMgmtApp.h"

/**
 * This class includes the main functionality for the Gateway Controller Application
 */
@interface AJGWCGatewayController : NSObject

/**
 * GetInstance
 * @return The {@link AJGWCGatewayController} object
 */
+ (id)sharedInstance;

/**
 * Initialize the gateway controller
 * @param bus {@link AJNBusAttachment} to use
 */
+ (void)startWithBus:(AJNBusAttachment *) bus;

/**
 * Shutdown the gateway controller
 */
- (void)shutdown;

/**
 * @return {@link AJNBusAttachment} that is used by the {@link AJGWCGatewayController}
 */
- (AJNBusAttachment*)busAttachment;

/**
 * create a Gateway by parsing announce descriptions.
 * @param gatewayBusName BusName of device received in announce
 * @param objectDescs ObjectDescriptions received in announce
 * @param aboutData The data sent with the Announcement
 * @return a {@link AJGWCGatewayMgmtApp} object or nil in case of error
 */
- (AJGWCGatewayMgmtApp*)createGatewayWithBusName:(NSString*) gatewayBusName objectDescs:(NSDictionary *) objectDescs  aboutData:(NSDictionary *) aboutData;

/**
 * getGateway - get a Gateway using the busName
 * @param gatewayBusName gatewayBusName to get
 * @return the {@link AJGWCGatewayMgmtApp} or NULL if not found
 */
- (AJGWCGatewayMgmtApp*)gateway:(NSString *) gatewayBusName;

/**
 * Get a dictionary of all Gateways
 * @return Gateways dictionary
 */
- (NSDictionary*)gateways;

@end
