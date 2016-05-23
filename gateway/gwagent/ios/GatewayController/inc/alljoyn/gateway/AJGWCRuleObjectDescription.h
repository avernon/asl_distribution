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
#import "AJGWCRuleObjectPath.h"
#import "AJGWCRuleInterface.h"
#import "alljoyn/gateway/RuleObjectDescription.h"

@interface AJGWCRuleObjectDescription : NSObject

/**
 * Constructor
 * @param handle A handle to a cpp RuleObjectDescription object
 */
- (id)initWithHandle:(ajn::gwc::RuleObjectDescription *) handle;

/**
 * Constructor
 * @param objectPath AllJoyn object identification
 * @param interfaces Set of the interfaces related to the given object path
 */
- (id)initWithObjectPath:(AJGWCRuleObjectPath*) objectPath interfaces:(NSSet*) interfaces;

/**
 * Constructor
 * @param objectPath AllJoyn object identification {@link AJGWCRuleObjectPath}
 * @param interfaces Set of the interfaces related to the given object path
 * @param isConfigured Set TRUE to permit this {@link AJGWCRuleObjectDescription} object path and interfaces
 * to be remoted by the Connector App
 */
- (id)initWithObjectPath:(AJGWCRuleObjectPath*) objectPath interfaces:(NSSet*) interfaces isConfigured:(bool) isConfigured;

/**
 * The object path supported by the Service Provider Application manifest
 * @return Object path
 */
- (AJGWCRuleObjectPath*)objectPath;

/**
 * The interfaces supported by the Service Provider Application manifest
 * @return Set of the {@link AJGWCRuleInterface} objects
 */
- (NSSet*)interfaces;

/**
 * The flag has TRUE if this {@link AJGWCRuleObjectDescription} is configured
 * to permit the object path and interfaces to be remoted by the Connector App
 * @return configured state
 */
- (bool)isConfigured;

/**
 * Set TRUE to permit this {@link AJGWCRuleObjectDescription} object path and interfaces
 * to be remoted by the Connector App
 * @param configured configured state
 */
- (void)setConfigured:(bool) configured;

/**
 * Returns the cpp handle of this class
 * @return {@link ajn::gwc::RuleObjectDescription*}
 */
- (ajn::gwc::RuleObjectDescription*)handle;
@end
