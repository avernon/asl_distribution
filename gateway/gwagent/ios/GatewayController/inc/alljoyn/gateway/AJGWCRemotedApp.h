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
#import "alljoyn/gateway/RemotedApp.h"
#import "AJGWCAnnouncedApp.h"
#import "AJGWCConnectorCapabilities.h"

@interface AJGWCRemotedApp : AJGWCAnnouncedApp

/**
 * Constructor
 * @param handle A handle to a cpp RemotedApp object
 */
- (id)initWithHandle:(ajn::gwc::RemotedApp *) handle;

/**
 * Constructor
 * @param busUniqueName The name of the {@link AJNBusAttachment} of the remoted application
 * @param appName The name of the application
 * @param appId The application id
 * @param deviceName The name of the device
 * @param deviceId The device id
 * @param ruleObjDescriptions Configuration of the object paths and interfaces that are
 * used by the Connector App to reach this remoted application
 */
- (id)initWithBusUniqueName:(NSString*) busUniqueName appName:(NSString*) appName appId:(uint8_t*) appId deviceName:(NSString*) deviceName deviceId:(NSString*) deviceId ruleObjDescriptions:(NSArray**) ruleObjDescriptions;

/**
 * Constructor
 * @param aboutData The data sent with the Anno uncement
 * @param ruleObjDescriptions Configuration of the object paths and interfaces that are
 * used by the Connector App to reach this remoted application
 */
- (id)initWithAboutData:(NSDictionary*) aboutData ruleObjDescriptions:(NSArray*) ruleObjDescriptions;

/**
 * Constructor
 * @param announcedApp The {@link AJGWCAnnouncedApp} to be used to build this {@link AJGWCRemotedApp}
 * @param ruleObjDescriptions Configuration of the object paths and interfaces that are
 * used by the Connector App to reach this remoted application
 */
- (id)initWithAnnouncedApp:(AJGWCAnnouncedApp*) announcedApp ruleObjDescriptions:(NSArray**) ruleObjDescriptions;

/**
 * Configuration of the object paths and interfaces that are
 * used by the Connector App to reach this remoted application
 * @return List of {@link AJGWCRuleObjectDescription} objects
 */
- (NSArray*)ruleObjDescriptions;

/**
 * Returns the cpp handle of this class
 * @return RemotedApp
 */
- (ajn::gwc::RemotedApp*)handle;
@end
