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

#import "../LSFSDKGroup.h"

@interface LSFSDKGroup (Init)

/** @name Creating LSFSDKGroup */

/**
 * Constructs an instance of the LSFSDKGroup class.
 *
 * @param groupID The ID of the Group.
 *
 * @return Instance of LSFSDKGroup.
 *
 * @warning *Note:* This method is intended to be used internally. Client software should not instantiate
 * Groups directly, but should instead get them from the LSFSDKLightingDirector using the [[LSFSDKLightingDirector getLightingDirector] groups]
 * property.
 */
-(id)initWithGroupID: (NSString *)groupID;

/**
 * Constructs an instance of the LSFSDKGroup class.
 *
 * @param groupID The ID of the Group.
 * @param groupName The name of the Group
 *
 * @return Instance of LSFSDKGroup.
 *
 * @warning *Note:* This method is intended to be used internally. Client software should not instantiate
 * Groups directly, but should instead get them from the LSFSDKLightingDirector using the [[LSFSDKLightingDirector getLightingDirector] groups]
 * property.
 */
-(id)initWithGroupID: (NSString *)groupID andName: (NSString *)groupName;

@end
