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

#import "AJNConvertUtil.h"

@implementation AJNConvertUtil

+ (qcc::String)convertNSStringToQCCString:(NSString *)nsstring
{
	return ((qcc::String)[nsstring UTF8String]);
}

+ (NSString *)convertQCCStringtoNSString:(qcc::String)qccstring
{
	return (@(qccstring.c_str()));
}

+ (const char *)convertNSStringToConstChar:(NSString *)nsstring
{
	return([nsstring UTF8String]);
}

+ (NSString *)convertConstCharToNSString:(const char *)constchar
{
	if ((constchar == NULL) || (constchar[0] == 0)) {
		return @"";
	}
	else {
		return(@(constchar));
	}
}

@end
