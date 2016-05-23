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
#import "MsgArg.h"
#import "AJNMessageArgument.h"
#import "alljoyn/about/AnnounceHandler.h"
#import "alljoyn/about/AJNAboutClient.h"

/**
 AJNAboutDataConverter is a utility class to convert About Service data structurs into an Objective-c objects.
 Note that incase of illegal content - an emty string will be in use:  ERRORSTRING = @"";
 */
__deprecated
@interface AJNAboutDataConverter : NSObject

/**
 Convert AJNMessageArgument to NSString.
 @param ajnMsgArg An AJNMessageArgument object.
 @return NSString representation of the AJNMessageArgument content.
 */
+ (NSString *)messageArgumentToString:(AJNMessageArgument *)ajnMsgArg __deprecated;

/**
 Convert NSMutableDictionary of about data in the format of NSString/AJNMessageArgument to NSString.
 @param aboutDataDict NSMutableDictionary of about data in the format of NSString/AJNMessageArgument.
 @return NSString representation of the NSMutableDictionary content.
 */
+ (NSString *)aboutDataDictionaryToString:(NSMutableDictionary *)aboutDataDict __deprecated;

/**
 Convert c++ map of about data in the format of qcc::String/ajn::MsgArg to NSMutableDictionary of NSString/AJNMessageArgument.
 @param aboutData C++ map of about data in the format of qcc::String/ajn::MsgArg.
 @return NSMutableDictionary of NSString/AJNMessageArgument.
 */
+ (NSMutableDictionary *)convertToAboutDataDictionary:(const ajn ::services ::AnnounceHandler ::AboutData&)aboutData __deprecated;

/** Convert c++ map of object descriptions in the format of qcc::String/std::vector<qcc::String> to NSMutableDictionary of NSString/NSMutableArray.
 @param objectDescs C++ map of object descriptions in the format of qcc::String/std::vector<qcc::String>.
 @return NSMutableDictionary of NSString/NSMutableArray.
 */
+ (NSMutableDictionary *)convertToObjectDescriptionsDictionary:(const ajn ::services ::AnnounceHandler ::ObjectDescriptions&)objectDescs __deprecated;

/**
 Convert NSMutableDictionary of object descriptions in the format of NSString/NSMutableArray to NSString.
 @param objectDescDict NSMutableDictionary of object descriptions in the format of NSString/NSMutableArray.
 @return NSString representation of the object descriptions NSMutableDictionary content.
 */
+ (NSString *)objectDescriptionsDictionaryToString:(NSMutableDictionary *)objectDescDict __deprecated;
@end
