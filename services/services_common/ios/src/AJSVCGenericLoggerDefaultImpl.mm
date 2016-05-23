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

#import "AJSVCGenericLoggerDefaultImpl.h"
#import "AJSVCGenericLoggerAdapter.h"
#import "AJSVCGenericLoggerUtil.h"

@interface AJSVCGenericLoggerDefaultImpl ()
@property QLogLevel currentlogLevel;
@end

@implementation AJSVCGenericLoggerDefaultImpl

- (id)init
{
	self = [super init];
	if (self) {
		self.currentlogLevel = QLEVEL_DEBUG;
		[self printTag:[NSString stringWithFormat:@"%@", [[self class] description]]
                  text:@"Logger Started" logLevel:self.currentlogLevel];
        
  		[self printTag:[NSString stringWithFormat:@"%@", [[self class] description]]
                  text:[NSString stringWithFormat:@"App Version:%@", [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleVersion"]]
                                        logLevel:self.currentlogLevel];
	}
	return self;
}

- (void)debugTag:(NSString *)tag text:(NSString *)text
{
	[self printTag:tag text:text logLevel:QLEVEL_DEBUG];
}

- (void)infoTag:(NSString *)tag text:(NSString *)text
{
	[self printTag:tag text:text logLevel:QLEVEL_INFO];
}

- (void)warnTag:(NSString *)tag text:(NSString *)text
{
	[self printTag:tag text:text logLevel:QLEVEL_WARN];
}

- (void)errorTag:(NSString *)tag text:(NSString *)text
{
	[self printTag:tag text:text logLevel:QLEVEL_ERROR];
}

- (void)fatalTag:(NSString *)tag text:(NSString *)text
{
	[self printTag:tag text:text logLevel:QLEVEL_FATAL];
}

- (void)printTag:(NSString *)tag text:(NSString *)logText logLevel:(QLogLevel)functionLogLevel
{
	// Get the logger level and print logs accordingly
	QLogLevel loggerLogLevel = [self logLevel];
    
	if (functionLogLevel <= loggerLogLevel) {
		NSLog(@"[%@][%@] %@", [AJSVCGenericLoggerUtil toStringQLogLevel:functionLogLevel], tag, logText);
	}
}

- (void)setLogLevel:(QLogLevel)logLevel
{
	[self printTag:[NSString stringWithFormat:@"%@", [[self class] description]] text:[NSString stringWithFormat:@"New Log level is %@.", [AJSVCGenericLoggerUtil toStringQLogLevel:logLevel]] logLevel:self.currentlogLevel];
    
	self.currentlogLevel = logLevel;
}

- (QLogLevel)logLevel
{
	return self.currentlogLevel;
}

@end
