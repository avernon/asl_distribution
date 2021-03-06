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

#import "AJNAboutDataConverter.h"
#import "AJNConvertUtil.h"

static NSString *ERRORSTRING = @"";

@implementation AJNAboutDataConverter

+ (NSString *)aboutDataDictionaryToString:(NSMutableDictionary *)aboutDataDict
{
	AJNMessageArgument *ajnMsgArgContent;
	NSMutableString *qnsAboutDataContent = [[NSMutableString alloc] init];
    
	// Iterate over dictionary in the format of NSString/AJNMessageArgument
	for (NSString *key in aboutDataDict) {
		// Add the dictionary key
		[qnsAboutDataContent appendString:([NSString stringWithFormat:@"%@: ", key])];
		// Get the dictionary value
		ajnMsgArgContent = aboutDataDict[key];
        
		if (ajnMsgArgContent != nil) {
			[qnsAboutDataContent appendString:([NSString stringWithFormat:@"%@ ", [self messageArgumentToString:(ajnMsgArgContent)]])];
		}
		else {
			//  AJNMessageArgument is invalid
			[qnsAboutDataContent appendString:([NSString stringWithString:ERRORSTRING])];
		}
		[qnsAboutDataContent appendString:([NSString stringWithFormat:@"\n"])];
	}
	return qnsAboutDataContent;
}

+ (NSString *)messageArgumentToString:(AJNMessageArgument *)ajnMsgArg
{
	NSString *ajnMsgArgSignature = [ajnMsgArg signature];
	NSMutableString *ajnMsgArgArrContent = [[NSMutableString alloc] init];
	NSMutableData *ajnMsgArgData;
	QStatus status;
	const char *ajnMsgArgContent_id;
    uint16_t short_number;
    
	// AJNMessageArgument is a string
	if ([ajnMsgArgSignature isEqualToString:(@"s")]) {
		status = [ajnMsgArg value:ajnMsgArgSignature, &ajnMsgArgContent_id];
		return (status == ER_OK) ? ([AJNConvertUtil convertConstCharToNSString:ajnMsgArgContent_id]) : ERRORSTRING;
	} else if ([ajnMsgArgSignature isEqualToString:(@"q")]) {
		status = [ajnMsgArg value:ajnMsgArgSignature, &short_number];
		return (status == ER_OK) ? ([NSString stringWithFormat:@"%d",short_number]): ERRORSTRING;
	}
	// AJNMessageArgument is an array of bytes (AppId)
	else if ([ajnMsgArgSignature isEqualToString:(@"ay")]) {
		uint8_t *AppIdBuffer;
		size_t numElements;
		status = [ajnMsgArg value:@"ay", &numElements, &AppIdBuffer];
		ajnMsgArgData = [NSMutableData dataWithBytes:AppIdBuffer length:(NSInteger)numElements];
		NSString *trimmedArray = [[ajnMsgArgData description] stringByTrimmingCharactersInSet:[NSCharacterSet characterSetWithCharactersInString:@"<>"]];
		return (status == ER_OK) ? trimmedArray : ERRORSTRING;
	}
	// AJNMessageArgument is an array of strings (SupportedLang)
	else if ([ajnMsgArgSignature isEqualToString:(@"as")]) {
		const ajn::MsgArg *stringArray;
		size_t fieldListNumElements;
		QStatus status = [ajnMsgArg value:@"as", &fieldListNumElements, &stringArray];
		if (status == ER_OK) {
			for (size_t i = 0; i < fieldListNumElements; i++) {
				char *tempString;
				stringArray[i].Get("s", &tempString);
				[ajnMsgArgArrContent appendString:([NSString stringWithFormat:@"%s ", tempString])];
			}
			return ajnMsgArgArrContent;
		}
		else {
			return ERRORSTRING;
		}
	}
     NSLog(@"[%@] [%@] signature is not implemented", @"DEBUG", [[self class] description]);

	return ERRORSTRING;
}

+ (NSMutableDictionary *)convertToAboutDataDictionary:(const ajn::services::AnnounceHandler::AboutData&)aboutData
{
	NSString *ajnAboutDataKey;
	AJNMessageArgument *ajnAboutDataValue;
	NSMutableDictionary *ajnAboutData = [[NSMutableDictionary alloc] init];
    
	//  iterate over std::map<qcc::String, ajn::MsgArg>
	for (ajn::services::AnnounceHandler::AboutData::const_iterator mapIt = aboutData.begin(); mapIt != aboutData.end(); mapIt++) {
		ajnAboutDataKey = [AJNConvertUtil convertQCCStringtoNSString:(mapIt->first)];
		ajn::MsgArg *tMsgArg = new ajn::MsgArg(mapIt->second);
		// Convert ajn::MsgArg to AJNMessageArgument
		ajnAboutDataValue = [[AJNMessageArgument alloc] initWithHandle:tMsgArg];
		[ajnAboutDataValue setOwnershipFlags:2 shouldApplyRecursively:true];
		[ajnAboutDataValue stabilize];
		[ajnAboutData setValue:ajnAboutDataValue forKey:ajnAboutDataKey];
		ajnAboutDataValue = nil;
	}
	return ajnAboutData;
}

+ (NSMutableDictionary *)convertToObjectDescriptionsDictionary:(const ajn::services::AnnounceHandler::ObjectDescriptions &)objectDescs
{
	NSString *path;
	NSMutableArray *intrfArray;
	std::vector <qcc::String> intrfVector;
	NSMutableDictionary *ajnObjectDescsDict = [[NSMutableDictionary alloc] init];
    
	// Iterate over the c++ object descriptions map
	for (ajn::services::AnnounceHandler::ObjectDescriptions::const_iterator mapIt = objectDescs.begin(); mapIt != objectDescs.end(); mapIt++) {
		// Convert key to NSString
		path = [AJNConvertUtil convertQCCStringtoNSString:(mapIt->first)];
		// Get the c++ vector address
		intrfVector = mapIt->second;
		intrfArray = [[NSMutableArray alloc] init];
		//  Iterate over c++ vector
		for (std::vector <qcc::String>::iterator vectorIt = intrfVector.begin(); vectorIt != intrfVector.end(); ++vectorIt) {
			// Convert the each element in the c++ vector to  NSString and insert into NSMutableArray
			[intrfArray addObject:([AJNConvertUtil convertQCCStringtoNSString:(*vectorIt)])];
		}
		// Add key/value into the dictionary
		[ajnObjectDescsDict setValue:intrfArray forKey:path];
		//  Clear container
		intrfVector.clear();
	}
	return ajnObjectDescsDict;
}

+ (NSString *)objectDescriptionsDictionaryToString:(NSMutableDictionary *)objectDescDict
{
	NSMutableString *qnsObjectDescContent = [[NSMutableString alloc] init];
    
	for (NSString *key in objectDescDict.allKeys) {
		//  Iterate over the NSMutableDictionary
		[qnsObjectDescContent appendString:([NSString stringWithFormat:@"path: %@ \n", key])];
		[qnsObjectDescContent appendString:([NSString stringWithFormat:@"interfaces: "])];
		for (NSString *intrf in objectDescDict[(key)]) {
			//  Add NSString followed by ' '
			[qnsObjectDescContent appendString:([NSString stringWithFormat:@"%@ ", intrf])];
		}
		[qnsObjectDescContent appendString:([NSString stringWithFormat:@"\n\n"])];
	}
	return (qnsObjectDescContent);
}

@end
