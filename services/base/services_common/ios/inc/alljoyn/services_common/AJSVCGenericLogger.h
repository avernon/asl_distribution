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

/**
 AJSVCGenericLogger protocol allows a custom logging using:
 </br> - QLogLevel enum which represents the available log levels.
 </br> - A set of methods one per logLevel.
 </br> The methods receive a 'tag' String to represent the current context and a log text String.
 </br> - Log level setter and getter.
 */
@protocol AJSVCGenericLogger <NSObject>

/**
 @enum QLogLevel
 */
typedef NS_ENUM (NSInteger, QLogLevel) {
	/** Fatal Error */
	QLEVEL_FATAL = 1,
	/** Error */
	QLEVEL_ERROR = 2,
	/** Warning */
	QLEVEL_WARN  = 3,
	/** Information */
	QLEVEL_INFO  = 4,
	/** Debug */
	QLEVEL_DEBUG = 5,
};

/**
 Log in Debug Level.
 @param tag identifies area of code.
 @param logText Text to be logged.
 */
- (void)debugTag:(NSString *)tag text:(NSString *)logText;

/**
 Log in Info Level.
 @param tag identifies area of code.
 @param logText Text to be logged.
 */
- (void)infoTag:(NSString *)tag text:(NSString *)logText;

/**
 Log in Warn Level.
 @param tag identifies area of code.
 @param logText Text to be logged.
 */
- (void)warnTag:(NSString *)tag text:(NSString *)logText;

/**
 Log in Error Level.
 @param tag identifies area of code.
 @param logText Text to be logged.
 */
- (void)errorTag:(NSString *)tag text:(NSString *)logText;

/**
 Log in Fatal Level.
 @param tag identifies area of code.
 @param logText Text to be logged.
 */
- (void)fatalTag:(NSString *)tag text:(NSString *)logText;

/**
 Set log level filter value currently in effect.
 @param logLevel log level (QLogLevel).
 */
- (void)setLogLevel:(QLogLevel)logLevel;

/**
 Get log level filter value currently in effect.
 */
- (QLogLevel)logLevel;

@end
