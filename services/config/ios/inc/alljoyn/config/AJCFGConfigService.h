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

#import <Foundation/Foundation.h>
#import "AJNBusAttachment.h"
#import "AJCFGConfigServiceListenerImpl.h"
#import "AJCFGPropertyStoreImpl.h"
#import "alljoyn/services_common/AJSVCGenericLogger.h"

/**
 AJCFGConfigService is an AllJoyn BusObject that implements the org.alljoyn.Config standard interface.
 Applications that provide AllJoyn IoE services with config capability.
 */
@interface AJCFGConfigService : NSObject

/**
 Designated initializer.
 Create a AJCFGConfigService Object.
 @param bus A reference to the AJNBusAttachment.
 @param propertyStore A reference to a property store.
 @param listener A reference to a Config service listener.
 @return AJCFGConfigService if successful.
 */
- (id)initWithBus:(AJNBusAttachment *)bus propertyStore:(AJCFGPropertyStoreImpl *)propertyStore listener:(AJCFGConfigServiceListenerImpl *)listener;

/**
 Register the ConfigService on the alljoyn bus.
 @return ER_OK if successful.
 */
- (QStatus)registerService;

/**
 * Unregister the AJCFGConfigService on the alljoyn bus.
 */
- (void)unregisterService;

#pragma mark - Logger methods
/**
 Receive AJSVCGenericLogger to use for logging.
 @param logger Implementation of AJSVCGenericLogger.
 @return previous logger.
 */
- (void)setLogger:(id <AJSVCGenericLogger> )logger;

/**
 Get the currently-configured logger implementation.
 @return logger Implementation of AJSVCGenericLogger.
 */
- (id <AJSVCGenericLogger> )logger;

/**
 Set log level filter for subsequent logging messages.
 @param newLogLevel New log level enum value.
 @return logLevel New log level enum value that was in effect prior to this change.
 */
- (void)setLogLevel:(QLogLevel)newLogLevel;

/**
 Get log level filter value currently in effect.
 @return logLevel Log level enum value currently in effect.
 */
- (QLogLevel)logLevel;

@end
