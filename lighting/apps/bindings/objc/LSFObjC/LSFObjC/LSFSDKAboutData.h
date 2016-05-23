/******************************************************************************
 * Copyright (c) AllSeen Alliance. All rights reserved.
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

#import "internal/LSFObject.h"
#import <alljoyn/AboutData.h>

/**
 * This class encapsulates all of the AllJoyn about data for the device running the controller service.
 * A pointer to this object will be passed to the developer in [LSFSDKLightingControllerConfiguration populateDefaultProperties:]
 * and the developer is responsible to populate this object with all relevant about data.
 *
 * See LSFSDKLightingControllerConfigurationBase for an example.
 */
@interface LSFSDKAboutData : LSFObject

/** @name Initializing an LSFSDKAboutData Object */

/**
 * Constructs a LSFSDKAboutData object.
 *
 * @warning This method is intended to be used internally. Client software should not instantiate
 * LSFSDKAboutData directly.
 *
 * @param aboutData  Pointer to AllJoyn AboutData object
 */
-(id)initWithAboutData: (ajn::AboutData *)aboutData;

/** @name Add About Data */

/**
 * Stores the provided string value using the provided about key.
 *
 * @param key  Specifies the AllJoyn About key
 * @param value  Specifies the value for the AllJoyn About key
 */
-(void)putKey: (NSString *)key withStringValue: (NSString *)value;

/**
 * Stores the provided string value using the provided about key.
 *
 * @param key  Specifies the AllJoyn About key
 * @param value  Specifies the value for the AllJoyn About key
 * @param language  Specifies the language tag of the AllJoyn About field
 */
-(void)putKey: (NSString *)key withStringValue: (NSString *)value andLanguage: (NSString *)language;

/**
 * Stores the provided array of values using the provided about key.
 *
 * @param key  Specifies the AllJoyn About key
 * @param value  Specifies the array of values for the AllJoyn About key
 */
-(void)putKey: (NSString *)key withStringArrayValue: (NSArray *)value;

/**
 * Stores the provided array of values using the provided about key.
 *
 * @param key  Specifies the AllJoyn About key
 * @param value  Specifies the array of values for the AllJoyn About key
 * @param language  Specifies the language tag of the AllJoyn About field
 */
-(void)putKey: (NSString *)key withStringArrayValue: (NSArray *)value andLanguage: (NSString *)language;

/**
 * Stores the provided byte data using the provided about key.
 *
 * @param key  Specifies the AllJoyn About key
 * @param value  Specifies the byte data for the AllJoyn About key
 */
-(void)putKey: (NSString *)key witDataValue: (NSData *)value;

/**
 * Stores the provided byte data using the provided about key.
 *
 * @param key  Specifies the AllJoyn About key
 * @param value  Specifies the byte data for the AllJoyn About key
 * @param language  Specifies the language tag of the AllJoyn About field
 */
-(void)putKey: (NSString *)key witDataValue: (NSData *)value andLanguage: (NSString *)language;

@end
