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
#include "qcc/String.h"

/**
 AJNConvertUtil class includes a string convert methods.
 */
__deprecated
@interface AJNConvertUtil : NSObject

/**
 Convert NSString to qcc::String.
 @param nsstring String from type NSString.
 @return qcc::String.
 */
+ (qcc ::String)convertNSStringToQCCString:(NSString *)nsstring __deprecated;

/**
 Convert qcc::String to NSString.
 @param qccstring String from type qcc::String.
 @return NSString.
 */
+ (NSString *)convertQCCStringtoNSString:(qcc ::String)qccstring __deprecated;

/**
 Convert NSString to const char.
 @param nsstring String from type NSString.
 @return const char.
 */
+ (const char *)convertNSStringToConstChar:(NSString *)nsstring __deprecated;

/**
 Convert const char to NSString.
 @param constchar const char.
 @return NSString.
 */
+ (NSString *)convertConstCharToNSString:(const char *)constchar __deprecated;
@end
