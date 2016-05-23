/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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
#import "AJSVCGenericLogger.h"

/**
 AJSVCGenericLoggerUtil is a util class that enable a log level covert/revert from the c++ layer to the objective-c one and vice versa.
 It also offers a log level toString capability.
 */
@interface AJSVCGenericLoggerUtil : NSObject

/**
 Convert QLogLevel(objective-c layer) to NSString.
 @param logLevel QLogLevel (objective-c layer).
 @return NSString representation of the QLogLevel content.
 */
+ (NSString *)toStringQLogLevel:(QLogLevel)logLevel;
@end
