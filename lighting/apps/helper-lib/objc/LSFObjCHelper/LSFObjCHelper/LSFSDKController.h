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

#import "LSFSDKLightingItem.h"
#import "model/LSFControllerModel.h"

/**
 * This class provides an interface to retrieve information about a given controller
 * in the Lighting system.
 *
 * @warning Client software should not instantiate the LSFSDKController directly, but should
 * instead get it from the LSFSDKLightingDirector using the [LSFSDKLightingDirector leadController]
 * method.
 */
@interface LSFSDKController : LSFSDKLightingItem
{
    @protected LSFControllerModel *controllerModel;
}

/** @name Class Properties */

/**
 * Returns a boolean that indicates if it is the lead controller in the Lighting system.
 *
 * @return Return true if this is the lead controller, false otherwise
 */
@property (nonatomic, readonly) BOOL connected;

/**
 * Returns the version of the controller.
 *
 * @return Version of the controller.
 */
@property (nonatomic, readonly) unsigned int version;

/** @name Protected methods */

/**
 * @warning This method is not intended to be used by clients, and may change or be
 * removed in subsequent releases of the SDK.
 */
-(LSFControllerModel *) getControllerDataModel;

@end
