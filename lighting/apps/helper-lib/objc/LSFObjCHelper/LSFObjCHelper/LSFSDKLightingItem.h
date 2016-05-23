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
#import "LSFSDKLightingItemProtocol.h"
#import "LSFSDKControllerClientDefs.h"
#import "model/LSFModel.h"

using namespace lsf;

/**
 * Base class for items in a Lighting system that implements the LSFSDKLightingItemProtocol.
 *
 * @warning Client software should not instantiate the LSFSDKLightingItem directly.
 */
@interface LSFSDKLightingItem : NSObject <LSFSDKLightingItemProtocol>

/**
 * Renames the current Lighting item using the provided name.
 *
 * @param name The new name for the Lighting item
 */
-(void)rename: (NSString *)name;

/**
 * Returns a boolean indicating whether or not the Lighting item has received all
 * its data from the lighting controller.
 *
 * @return Returns true if the Lighting item is initialized, false otherwise
 */
-(BOOL)isInitialized;

/**
 * Returns a boolean that indicates whether this Lighting item is comprised of the
 * provided object.
 *
 * @param item  Potential child Lighting item
 *
 * @return Returns true if this Lighting item is comprised of the provided object, false otherwise
 */
-(BOOL)hasComponent: (LSFSDKLightingItem *) item;

/** @name Protected Methods */

/**
 * @warning This method is not intended to be used by clients, and may change or be
 * removed in subsequent releases of the SDK.
 */
-(NSArray *)getDependentCollection;

/**
 * @warning This method is not intended to be used by clients, and may change or be
 * removed in subsequent releases of the SDK.
 */
-(NSArray *)getComponentCollection;

/**
 * @warning This method is not intended to be used by clients, and may change or be
 * removed in subsequent releases of the SDK.
 *
 * @param name  The name of the Lighting item
 * @param object  The Lighting item
 */
-(BOOL)postInvalidArgIfNull: (NSString *)name object: (id)object;

/**
 * @warning This method is not intended to be used by clients, and may change or be
 * removed in subsequent releases of the SDK.
 *
 * @param name  The name of the Lighting item
 * @param status  The status code retured
 */
-(BOOL)postErrorIfFailure: (NSString *)name status: (ControllerClientStatus)status;

/**
 * @warning This method is not intended to be used by clients, and may change or be
 * removed in subsequent releases of the SDK.
 *
 * @param name  The name of the Lighting item
 * @param status  The status code retured
 */
-(void)postError: (NSString *)name status: (LSFResponseCode)status;

/**
 * @warning This method is not intended to be used by clients, and may change or be
 * removed in subsequent releases of the SDK.
 */
-(LSFModel *)getItemDataModel;

@end
