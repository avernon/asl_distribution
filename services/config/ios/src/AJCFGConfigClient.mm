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

#import "AJCFGConfigClient.h"
#import "alljoyn/config/ConfigClient.h"
#import "alljoyn/services_common/AJSVCGenericLoggerAdapter.h"
#import "alljoyn/services_common/AJSVCGenericLoggerDefaultImpl.h"
#import "alljoyn/about/AJNConvertUtil.h"
#import "alljoyn/about/AJNAboutDataConverter.h"

#define DEFAULT_SESSION_ID 0

@interface AJCFGConfigClient ()

@property ajn::services::ConfigClient *handle;
@property id <AJSVCGenericLogger> currentLogger;
@property AJSVCGenericLoggerAdapter *AJSVCGenericLoggerAdapter;

@end

@implementation AJCFGConfigClient

- (void)dealloc
{
	delete self.handle;
}

- (id)initWithBus:(AJNBusAttachment *)bus
{
	self = [super init];
	if (self) {
		self.handle = new ajn::services::ConfigClient((ajn::BusAttachment&)(*bus.handle));
		// Set a default logger
		self.currentLogger = [[AJSVCGenericLoggerDefaultImpl alloc] init];
		// Call setLoger with the adapter and save the prev Logger
		self.AJSVCGenericLoggerAdapter = new AJSVCGenericLoggerAdapter(self.currentLogger);
	}
	return self;
}

- (QStatus)factoryResetWithBus:(NSString *)busName
{
	return [self factoryResetWithBus:busName sessionId:DEFAULT_SESSION_ID];
}

- (QStatus)factoryResetWithBus:(NSString *)busName sessionId:(AJNSessionId)sessionId
{
	return self.handle->FactoryReset([AJNConvertUtil convertNSStringToConstChar:busName], sessionId);
}

- (QStatus)restartWithBus:(NSString *)busName
{
	return [self restartWithBus:busName sessionId:DEFAULT_SESSION_ID];
}

- (QStatus)restartWithBus:(NSString *)busName sessionId:(AJNSessionId)sessionId
{
	return self.handle->Restart([AJNConvertUtil convertNSStringToConstChar:busName], sessionId);
}

- (QStatus)setPasscodeWithBus:(NSString *)busName daemonRealm:(NSString *)daemonRealm newPasscodeSize:(size_t)newPasscodeSize newPasscode:(const uint8_t *)newPasscode
{
	return [self setPasscodeWithBus:busName daemonRealm:daemonRealm newPasscodeSize:newPasscodeSize newPasscode:newPasscode sessionId:DEFAULT_SESSION_ID];
}

- (QStatus)setPasscodeWithBus:(NSString *)busName daemonRealm:(NSString *)daemonRealm newPasscodeSize:(size_t)newPasscodeSize newPasscode:(const uint8_t *)newPasscode sessionId:(AJNSessionId)sessionId
{
	return self.handle->SetPasscode([AJNConvertUtil convertNSStringToConstChar:busName], [AJNConvertUtil convertNSStringToConstChar:daemonRealm], newPasscodeSize, newPasscode, sessionId);
}

- (QStatus)configurationsWithBus:(NSString *)busName languageTag:(NSString *)languageTag configs:(NSMutableDictionary **)configs
{
	return [self configurationsWithBus:busName languageTag:languageTag configs:configs sessionId:DEFAULT_SESSION_ID];
}

- (QStatus)configurationsWithBus:(NSString *)busName languageTag:(NSString *)languageTag configs:(NSMutableDictionary **)configs sessionId:(AJNSessionId)sessionId
{
	std::map <qcc::String, ajn::MsgArg> tConfigurations;
    
	QStatus status = self.handle->GetConfigurations([AJNConvertUtil convertNSStringToConstChar:busName], [AJNConvertUtil convertNSStringToConstChar:languageTag], tConfigurations, sessionId);
    
	*configs = [AJNAboutDataConverter convertToAboutDataDictionary:tConfigurations];
    
	return status;
}

- (QStatus)updateConfigurationsWithBus:(NSString *)busName languageTag:(NSString *)languageTag configs:(NSMutableDictionary **)configs
{
	return [self updateConfigurationsWithBus:busName languageTag:languageTag configs:configs sessionId:DEFAULT_SESSION_ID];
}

- (QStatus)updateConfigurationsWithBus:(NSString *)busName languageTag:(NSString *)languageTag configs:(NSMutableDictionary **)configs sessionId:(AJNSessionId)sessionId
{
	std::map <qcc::String, ajn::MsgArg> tConfigurations;
    
	NSEnumerator *enumerator = [*configs keyEnumerator];
	id key;
    
	// Iterate over the NSMutableDictionary and get the key/value
	while ((key = [enumerator nextObject])) {
		// Put key/ value in the std::map<qcc::String, ajn::MsgArg>
		AJNMessageArgument *ajnMsgArg = [*configs objectForKey : (key)];
		ajn::MsgArg *cppValue = new ajn::MsgArg;
		cppValue = (ajn::MsgArg *)ajnMsgArg.handle;
		tConfigurations.insert(std::make_pair([AJNConvertUtil convertNSStringToQCCString:key], *cppValue));
	}
	QStatus status = self.handle->UpdateConfigurations([AJNConvertUtil convertNSStringToConstChar:busName], [AJNConvertUtil convertNSStringToConstChar:languageTag], tConfigurations, sessionId);
    
	return status;
}

- (QStatus)resetConfigurationsWithBus:(NSString *)busName languageTag:(NSString *)languageTag configNames:(NSMutableArray *)configNames
{
	return [self resetConfigurationsWithBus:busName languageTag:languageTag configNames:configNames sessionId:DEFAULT_SESSION_ID];
}

- (QStatus)resetConfigurationsWithBus:(NSString *)busName languageTag:(NSString *)languageTag configNames:(NSMutableArray *)configNames sessionId:(AJNSessionId)sessionId
{
	std::vector <qcc::String> tConfigNames;
    
	//  Convert NSMutableArray to std::vector<qcc::String>
	for (NSString *tStr in configNames) {
		tConfigNames.push_back([AJNConvertUtil convertNSStringToQCCString:tStr]);
	}
    
	return self.handle->ResetConfigurations([AJNConvertUtil convertNSStringToConstChar:busName], [AJNConvertUtil convertNSStringToConstChar:languageTag], tConfigNames, sessionId);
}

- (QStatus)versionWithBus:(NSString *)busName version:(int&)version
{
	return [self versionWithBus:busName version:version sessionId:DEFAULT_SESSION_ID];
}

- (QStatus)versionWithBus:(NSString *)busName version:(int&)version sessionId:(AJNSessionId)sessionId
{
	return self.handle->GetVersion([AJNConvertUtil convertNSStringToConstChar:busName], version, sessionId);
}

#pragma mark - Logger methods
- (void)setLogger:(id <AJSVCGenericLogger> )logger
{
	if (logger) {
		// Save current logger
		self.currentLogger = logger;
		// Call setLoger with the adapter and save the prev Logger
	}
	else {
		[self.currentLogger warnTag:([NSString stringWithFormat:@"%@", [[self class] description]]) text:@"Failed set a logger"];
	}
}

- (id <AJSVCGenericLogger> )logger
{
	return self.currentLogger;
}

- (void)setLogLevel:(QLogLevel)newLogLevel
{
	[self.currentLogger setLogLevel:newLogLevel];
}

- (QLogLevel)logLevel
{
	return [self.currentLogger logLevel];
}

@end
