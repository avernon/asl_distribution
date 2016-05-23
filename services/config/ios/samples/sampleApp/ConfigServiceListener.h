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
#import "alljoyn/Status.h"
#import "AJNBusAttachment.h"
#import "alljoyn/config/AJCFGConfigServiceListener.h"
#import "alljoyn/config/AJCFGPropertyStoreImpl.h"

/**
 ConfigServiceListener is the sample implementation. it creates and initialize a Config service Listener to handle Config service callbacks.
 */
@interface ConfigServiceListener : NSObject <AJCFGConfigServiceListener>

/**
 Designated initializer.
 Create a ConfigServiceListener Object using the passed propertyStore and AJNBusAttachment.
 @param propertyStore A reference to a property store.
 @param bus A reference to the AJNBusAttachment.
 @return ConfigServiceListener if successful.
 */
- (id)initWithPropertyStore:(AJCFGPropertyStoreImpl *)propertyStore andBus:(AJNBusAttachment *)bus;

/**
 Restart of the device - method not implemented.
 @return ER_OK if successful.
 */
- (QStatus)restart;

/**
 Factory reset of the device - return to default values including password!
 @return ER_OK if successful.
 */
- (QStatus)factoryReset;

/**
 Receive Passphrase info and persist it.
 @param daemonRealm Daemon realm to persist.
 @param passcode passcode content.
 @return ER_OK if successful.
 */
- (QStatus)setPassphrase:(NSString *)daemonRealm withPasscode:(NSString *)passcode;


@end
