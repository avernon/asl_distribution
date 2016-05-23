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
#import "alljoyn/gateway/RuleObjectDescription.h"

@interface AJGWCRuleObjectPath : NSObject

/**
 * Constructor
 * @param handle A handle to a cpp RuleObjectPath object
 */
- (id)initWithHandle:(ajn::gwc::RuleObjectPath *) handle;

/**
 * Constructor
 * @param objectPath AllJoyn object identification
 * @param friendlyName The friendly name of the object path. This name may be presented
 * @param isPrefix TRUE if the object path is a prefix for the full object path
 * @param isPrefixAllowed TRUE if the object path can be treated as a prefix
 * to the end user.
 */
- (id)initWithObjectPath:(NSString*) objectPath friendlyName:(NSString*) friendlyName isPrefix:(bool) isPrefix isPrefixAllowed:(bool)isPrefixAllowed;

/**
 * AllJoyn object identification
 * @return The value of the object path
 */
- (NSString*)path;

/**
 * Returns the friendly name  of the object path.
 * This name may be presented to the end user.
 * @return Object path friendly name
 */
- (NSString*)friendlyName;

/**
 * @return Returns whether this object path is a prefix
 */
- (bool)isPrefix;

/**
 * Set whether this object path is a prefix
 * @param isPrefix set the prefix flag to isPrefix
 */
- (void)setPrefix:(bool) isPrefix;

/**
 * @return Returns whether this object path prefix is allowed
 */
- (bool)isPrefixAllowed;

/**
 * Set whether this object path prefix is allowed to be set
 * @param isPrefixAllowed set the prefix flag permissions
 */
- (void)setPrefixAllowed:(bool) isPrefixAllowed;

/**
 * Returns the cpp handle of this class
 * @return AclRules
 */
- (ajn::gwc::RuleObjectPath*)handle;


@end
