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

#import <Foundation/Foundation.h>
#import "AJNBusAttachment.h"
#import "AJNPropertyStore.h"

/**
 AJNAboutService is a wrapper for AboutService which uses AllJoyn BusObject and implements the org.alljoyn.About standard interface.
 Applications that provide AllJoyn IoE services use an instance of this class to announce
 their capabilities and other identifying details of the services being provided.
 */
__deprecated
@interface AJNAboutService : NSObject

/**
 A flag that indicate the service mode.
 */
@property bool isServiceStarted __deprecated;

/**
 Register the bus and the property store to be used by AJNAboutService and set the isServiceStarted to true.
 @param bus A reference to the AJNBusAttachment.
 @param store A reference to a property store.
 */
- (void)registerBus:(AJNBusAttachment *)bus andPropertystore:(id <AJNPropertyStore> )store __deprecated;

/**
 Register the AJNAboutService on the AllJoyn bus passing the port to be announced - only if isServiceStarted is true.
 @param port used to bind the session.
 @return ER_OK if successful.
 */
- (QStatus)registerPort:(AJNSessionPort)port __deprecated;

/**
 * Unregister the AJNAboutService  from the bus.
 */
- (void)unregister __deprecated;

/**
 Add object Descriptions to the AJNAboutService announcement.
 @param path The path of the interface.
 @param interfaceNames The name of the interface.
 @return ER_OK if successful.
 */
- (QStatus)addObjectDescriptionWithPath:(NSString *)path andInterfaceNames:(NSMutableArray *)interfaceNames __deprecated;

/**
 Remove object Descriptions from the AboutService announcement.
 @param path The path of the interface.
 @param interfaceNames The name of the interface.
 @return ER_OK if successful.
 */
- (QStatus)removeObjectDescriptionWithPath:(NSString *)path andInterfaceNames:(NSMutableArray *)interfaceNames __deprecated;

/**
 Send or replace the org.alljoyn.About.Announce sessionless signal.
 </br>Validate store and object announcements and emit the announce signal.
 @return ER_MANDATORY_FIELD_MISSING: Logs an error with specific field that has a problem.
 */
- (QStatus)announce __deprecated;

@end
