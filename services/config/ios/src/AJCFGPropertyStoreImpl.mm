/******************************************************************************
 * Copyright (c) 2013, AllSeen Alliance. All rights reserved.
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

#import "AJCFGPropertyStoreImpl.h"
#import "alljoyn/about/AJNAboutServiceApi.h"

#define DEFAULT_LANGUAGE_STR @"DefaultLanguage"
#define DEVICE_NAME_STR @"DeviceName"
#define DEVICE_ID_STR @"DeviceId"
#define PASS_CODE_STR @"passcode"

@interface AJNMessageArgument (Private)

@property (nonatomic, readonly) ajn::MsgArg *msgArg;

@end

@interface AJCFGPropertyStoreImpl ()

@property (strong, nonatomic) NSDictionary *factoryProperties;

@end

@implementation AJCFGPropertyStoreImpl

- (id)initPointerToFactorySettingFile:(NSString *)filePath
{
	self = [super initWithHandleAllocationBlock:
	        ^{ return (ajn::services::AboutPropertyStoreImpl *)new PropertyStoreImplAdapter(self); }];
	if (self) {
		self.factoryProperties = [NSDictionary dictionaryWithContentsOfFile:filePath];
	}
    
	return self;
}

- (void)factoryReset
{
	// Clean the NSUserDefaults
	[[NSUserDefaults standardUserDefaults] removeObjectForKey:DEFAULT_LANGUAGE_STR];
	[[NSUserDefaults standardUserDefaults] removeObjectForKey:DEVICE_NAME_STR];
	[[NSUserDefaults standardUserDefaults] removeObjectForKey:DEVICE_ID_STR];
	[[NSUserDefaults standardUserDefaults] removeObjectForKey:PASS_CODE_STR];
	[[NSUserDefaults standardUserDefaults] synchronize];
    
	// Set the values from the factory store
	[self setDefaultLang:nil];
	[self setDeviceName:nil];
	[self setDeviceId:nil];
	[self setPasscode:nil];
}

- (QStatus)populateWritableMsgArgs:(const char *)languageTag ajnMsgArg:(AJNMessageArgument **)all
{
	QStatus status;
	ajn::MsgArg *msgArg = new ajn::MsgArg;
    
	status = ((PropertyStoreImplAdapter *)[super getHandle])->populateWritableMsgArgs(languageTag, *msgArg);
    
	*all = [[AJNMessageArgument alloc] initWithHandle:msgArg];
    
	return status;
}

- (QStatus)readAll:(const char *)languageTag withFilter:(PFilter)filter ajnMsgArg:(AJNMessageArgument **)all;
{
	QStatus status;
    
	if (filter != WRITE)
		return ER_FAIL;
    
	if (languageTag != NULL && languageTag[0] != 0) { // Check that the language is in the supported languages
		if (![self isLanguageSupported:languageTag])
			return ER_LANGUAGE_NOT_SUPPORTED;
	}
	else {
		AJNPropertyStoreProperty *defaultLang = [self property:DEFAULT_LANG];
		if (defaultLang == nil)
			return ER_LANGUAGE_NOT_SUPPORTED;
	}
    
	status = [self populateWritableMsgArgs:languageTag ajnMsgArg:all];
    
	return status;
}

- (QStatus)Update:(const char *)name languageTag:(const char *)languageTag ajnMsgArg:(AJNMessageArgument *)value
{
	// Only the default lang work here
    if (languageTag && (languageTag[0] != 0 && languageTag[0] != ' ')) {
        [[[AJCFGConfigLogger sharedInstance] logger] debugTag:@"PropertyStoreImplAdapter" text:[NSString stringWithFormat:@"Language tag is not empty! [%s]. Using  an empty string instead.", languageTag]];
    }
    
    languageTag = ""; // For now, the empty language tag is the only format we support for write. do not try to send other languageTag.
    
	// Get the enum value for the property name
	AJNPropertyStoreKey key_code = [self getPropertyStoreKeyFromName:name];
    
	if (key_code == NUMBER_OF_KEYS) {
		return ER_BAD_ARG_1;
	}
    
	// Check if this property is writable
	AJNPropertyStoreProperty *property = [self property:key_code];
    
	if (![property isWritable])
		return ER_INVALID_VALUE;
    
	// Erase the property from the property store in memory
	((PropertyStoreImplAdapter *)[super getHandle])->updatePropertyAccordingToPropertyCode((ajn::services::PropertyStoreKey)key_code, languageTag, [value msgArg]);
    
	NSString *key = [NSString stringWithCString:name encoding:NSUTF8StringEncoding];
	char *msgarg_value;
    
	[value value:@"s", &msgarg_value]; // Update entries are assumed to be strings.
    
	NSString *msgArgValue = [NSString stringWithCString:msgarg_value encoding:NSUTF8StringEncoding];
    
	// Update the entry from the NSUserDefaults persistant storage
	NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    
	NSDictionary *newValue = @{ @"":msgArgValue };
    
	[userDefaults setObject:newValue forKey:key]; // Add the default language representation, this is what supported for now.
    
	[userDefaults synchronize]; // Persist
    
	return [[AJNAboutServiceApi sharedInstance] announce];
}

- (AJNPropertyStoreKey)getPropertyStoreKeyFromName:(const char *)propertyStoreName
{
	NSArray *QASPropertyStoreName = @[@"DeviceId", @"DeviceName", @"AppId", @"AppName", @"DefaultLanguage", @"SupportedLanguages", @"Description", @"Manufacturer", @"DateOfManufacture", @"ModelNumber", @"SoftwareVersion", @"AJSoftwareVersion", @"HardwareVersion", @"SupportUrl", @""];
    
	for (int indx = 0; indx < NUMBER_OF_KEYS; indx++) {
		if ([QASPropertyStoreName[indx] isEqualToString:[NSString stringWithCString:propertyStoreName encoding:NSUTF8StringEncoding]] == YES)
			return (AJNPropertyStoreKey)indx;
	}
	return NUMBER_OF_KEYS;
}

- (QStatus)reset:(const char *)name languageTag:(const char *)languageTag
{
	// Only the default lang work here
    if (languageTag && (languageTag[0] != 0 && languageTag[0] != ' ')) {
        [[[AJCFGConfigLogger sharedInstance] logger] debugTag:@"PropertyStoreImplAdapter" text:[NSString stringWithFormat:@"Language tag is not empty! [%s]. Using  an empty string instead.", languageTag]];
    }
    
    languageTag = ""; // For now, the empty language tag is the only format we support for write. do not try to send other languageTag.
    
    
	// Get the enum value for the property name
	AJNPropertyStoreKey key_code = [self getPropertyStoreKeyFromName:name];
    
	if (key_code == NUMBER_OF_KEYS) {
		return ER_BAD_ARG_1;
	}
    
	// Check if this property is writable
	AJNPropertyStoreProperty *property = [self property:key_code];
    
	if (![property isWritable])
		return ER_INVALID_VALUE;
    
	// Erase the property from the property store in memory
	((PropertyStoreImplAdapter *)[super getHandle])->erasePropertyAccordingToPropertyCode((ajn::services::PropertyStoreKey)key_code, languageTag);
    
	NSString *key = [NSString stringWithCString:name encoding:NSUTF8StringEncoding];
    
	// Remove the entry from the NSUserDefaults persistant storage
    [[NSUserDefaults standardUserDefaults] removeObjectForKey:key];
    
	[[NSUserDefaults standardUserDefaults] synchronize];
    
	// Reset to factory setting and set the property:
	switch (key_code) {
		case DEVICE_ID:
			[self setDeviceId:nil];
			break;
            
		case DEVICE_NAME:
			[self setDeviceName:nil];
			break;
            
		case DEFAULT_LANG:
			[self setDefaultLang:nil];
			break;
            
		default:
			return ER_FEATURE_NOT_AVAILABLE;
	}
    
	return [[AJNAboutServiceApi sharedInstance] announce];
}

- (NSString *)getPersistentValue:(NSString *)key
{
	NSDictionary *dict = [[NSUserDefaults standardUserDefaults] dictionaryForKey:key];
    
	return [dict objectForKey:@""]; // For now, all values use the default language, which is the empty key
}

- (void)updateUserDefaultsValue:(NSString *)value usingKey:(NSString *)key
{
	//  Set the user defaults with the new value
	NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
	NSDictionary *newValue = @{ @"":value };
    
	[userDefaults setObject:newValue forKey:key]; // Add the default language representation, this is what we support for now.
    
	[userDefaults synchronize]; // Persist
}

- (NSString *)lookForValue:(NSString *)value accordingToKey:(NSString *)key
{
	NSString *val = value;
    
	if (!val) {
		val = [self getPersistentValue:key];
		if (!val) {
			val = [[self.factoryProperties objectForKey:key] objectForKey:@""];
		}
	}
	else {
		[self updateUserDefaultsValue:val usingKey:key];
	}
    
	return val;
}

- (QStatus)setDefaultLang:(NSString *)defaultLang
{
	NSString *val = [self lookForValue:defaultLang accordingToKey:DEFAULT_LANGUAGE_STR];
    
	if (val) {
		QStatus status = [super setDefaultLang:val];
		if (status == ER_OK) {
			[self updateUserDefaultsValue:val usingKey:DEFAULT_LANGUAGE_STR];
		}
        
		return status;
	}
    
	return ER_BAD_ARG_1;
}

- (QStatus)setDeviceName:(NSString *)deviceName
{
	NSString *val = [self lookForValue:deviceName accordingToKey:DEVICE_NAME_STR];
    
	if (val) {
		QStatus status =  [super setDeviceName:val];
        
		if (status == ER_OK) {
			[self updateUserDefaultsValue:val usingKey:DEVICE_NAME_STR];
		}
        
		return status;
	}
    
	return ER_BAD_ARG_1;
}

- (QStatus)setDeviceId:(NSString *)deviceId
{
	NSString *val = [self lookForValue:deviceId accordingToKey:DEVICE_ID_STR];
    
	if (val) {
		QStatus status = [super setDeviceId:val];
        
		if (status == ER_OK) {
			[self updateUserDefaultsValue:val usingKey:DEVICE_ID_STR];
		}
        
		return status;
	}
    
	return ER_BAD_ARG_1;
}

// The passcode is not stored in the property store, just the NSUserDefaults.
- (QStatus)setPasscode:(NSString *)passCode
{
	if (!passCode) {
		passCode = [[self.factoryProperties objectForKey:PASS_CODE_STR] objectForKey:@""];
	}
    
	[self updateUserDefaultsValue:passCode usingKey:PASS_CODE_STR];
    
	return ER_OK;
}

- (NSString *)getPasscode
{
	NSString *val = [self lookForValue:nil accordingToKey:PASS_CODE_STR];
    
	return val;
}

- (QStatus)isLanguageSupported:(const char *)language
{
	return ((PropertyStoreImplAdapter *)[self getHandle])->isLanguageSupported_Public_Adapter(language);
}

- (long)getNumberOfProperties
{
	return ((PropertyStoreImplAdapter *)[self getHandle])->getNumberOfProperties();
}

@end
