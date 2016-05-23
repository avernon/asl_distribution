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

#ifndef AJNAboutService_PropertyStore_h
#define AJNAboutService_PropertyStore_h

#import <Foundation/Foundation.h>
#import "alljoyn/Status.h"

/**
 AJNPropertyStore protocol overview
 */
__deprecated
@protocol AJNPropertyStore <NSObject>

#pragma mark – Protocol enum
///---------------------
/// @name Protocol enum
///---------------------
/**
 * Filter has three possible values ANNOUNCE, READ,WRITE
 * READ is for data that is marked as read
 * ANNOUNCE is for data that is marked as announce
 * WRITE is for data that is marked as write
 */
typedef enum {
	ANNOUNCE,     //!< ANNOUNCE Property that has  ANNOUNCE  enabled
	READ,        //!< READ     Property that has READ  enabled
	WRITE,       //!< WRITE    Property that has  WRITE  enabled
} PFilter;


#define QAS_ER_LANGUAGE_NOT_SUPPORTED       ((QStatus)0xb001)
#define QAS_ER_FEATURE_NOT_AVAILABLE        ((QStatus)0xb002)
#define QAS_ER_INVALID_VALUE                        ((QStatus)0xb003)
#define QAS_ER_MAX_SIZE_EXCEEDED            ((QStatus)0xb004)

#pragma mark – Protocol methods

/**
 Calls Reset() implemented only for  ConfigService
 @return status
 */
- (QStatus)reset __deprecated;

/**
 Update properties method
 @param name name of the property
 @param languageTag languageTag is the language to use for the action can be NULL meaning default.
 @param value value is a pointer to the data to change.
 @return status
 */
- (QStatus)updatePropertyName:(NSString *)name andLanguageTag:(NSString *)languageTag andValue:(NSMutableArray **)value __deprecated;

/**
 Delete property method
 @param name name of the property
 @param languageTag languageTag is the language to use for the action can't be NULL.
 @return status
 */
- (QStatus)deletePropertyName:(NSString *)name andLanguageTag:(NSString *)languageTag __deprecated;

@end

#endif //  AJNAboutService_PropertyStore_h
