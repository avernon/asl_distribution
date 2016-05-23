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
#import "AJGWCEnums.h"
#import "alljoyn/gateway/ConnectorAppStatus.h"

@interface AJGWCConnectorAppStatus : NSObject

/**
 * Constructor
 * @param handle A handle to a cpp ConnectorAppStatus object
 */
- (id)initWithHandle:(ajn::gwc::ConnectorAppStatus*) handle;

/**
 * Constructor
 */
//- (id)initWithAppStatus:(AJNMessageArgument*) appStatus;

/**
 * Constructor
 * @param installStatus install status {@link AJGWCInstallStatus}
 * @param installDescription install description
 * @param connectionStatus connection status {@link AJGWCConnectionStatus}
 * @param operationalStatus operational status  {@link AJGWCOperationalStatus}
 */
- (id)initWithInstallStatus:(AJGWCInstallStatus) installStatus installDescription:(NSString*) installDescription connectionStatus:(AJGWCConnectionStatus) connectionStatus operationalStatus:(AJGWCOperationalStatus) operationalStatus;
/**
 * @return The installation status of the Connector App
 */
- (AJGWCInstallStatus)installStatus;

/**
 * @return The installation description of the Connector App
 */
- (NSString*)installDescriptions;

/**
 * @return Connection status of the Connector App to its cloud service
 */
- (AJGWCConnectionStatus)connectionStatus;

/**
 * @return The state whether the Connector App is running
 */
- (AJGWCOperationalStatus)operationalStatus;

@end
