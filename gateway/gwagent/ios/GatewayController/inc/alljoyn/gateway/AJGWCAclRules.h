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
#import "alljoyn/gateway/AclRules.h"
#import "AJGWCConnectorCapabilities.h"

@interface AJGWCAclRules : NSObject

/**
 * Constructor
 * @param handle A handle to a cpp AclRules object
 */
- (id)initWithHandle:(ajn::gwc::AclRules*) handle;

/**
 * Constructor
 * @param exposedServices The interfaces that Connector App exposes to its clients
 * @param remotedApps The applications that may be reached by the Connector App
 * via the configured interfaces and object paths
 */
- (id)initWithExposedServices:(NSArray*) exposedServices  remotedApps:(NSArray*) remotedApps;

/**
 * The applications that may be reached by the Connector App
 * via the configured interfaces and object paths
 * @return List of the remoted applications
 */
- (NSArray*)remotedApps;

/**
 * The interfaces that Connector App exposes to its clients
 * @return List of exposed services
 */
- (NSArray*)exposedServices;

/**
 * Set the given metadata to the existing one
 * @param metadata
 */

/**
 * Update the metadata with the given data
 * @param metadata The metadata to update the Access Rules
 */
- (void)updateMetadata:(NSDictionary*) metadata;

/**
 * Returns metadata value for the given key
 * @param key The metadata key
 * @return metadata The Access Rules metadata for the given key
 */
- (NSString*)metadata:(NSString*) key;

/**
 * Returns current metadata object
 * @return metadata The Access Rules metadata
 */
- (NSDictionary*)metadata;

/**
 * Returns the cpp handle of this class
 * @return AclRules
 */
- (ajn::gwc::AclRules*)handle;

@end
