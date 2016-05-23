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
#import "LSFSDKResponseCodes.h"
#import "LSFSDKTrackingID.h"

/**
 * This class contains all pertinent information for errors that occur in the Lighting
 * system. This class provides an interface to retrieve the following data: the name of
 * the error, the response code returned by the Lighting operation, the ID of the Lighting
 * item for which the error occured, and the tracking ID only if the error occurred during
 * creation.
 */
@interface LSFSDKLightingItemErrorEvent : NSObject

/**
 * The name of the error.
 */
@property (nonatomic, strong) NSString *name;

/**
 * The response code of the error.
 */
@property (nonatomic) lsf::LSFResponseCode responseCode;

/**
 * The ID of the Lighting item.
 */
@property (nonatomic, strong) NSString *itemID;

/**
 * The tracking ID of the Lighting item.
 */
@property (nonatomic, strong) LSFSDKTrackingID *trackingID;

/** @name Initializing an LSFSDKLightingItemErrorEvent Object */

/**
 * Constructs a LSFSDKLightingItemErrorEvent object.
 *
 * @param name  The name of the error.
 * @param responseCode  The response code of the error.
 * @param itemID  The ID of the Lighting item.
 * @param trackingID  The tracking ID of the Lighting Object.
 */
-(id)initWithName: (NSString *)name responseCode: (lsf::LSFResponseCode)responseCode itemID: (NSString *)itemID andTrackingID: (LSFSDKTrackingID *)trackingID;

@end
