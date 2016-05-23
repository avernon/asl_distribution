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

#import "AJCPSLanguageSet.h"
#import "alljoyn/about/AJNConvertUtil.h"

@interface AJCPSLanguageSet ()
@property (nonatomic) ajn::services::LanguageSet *handle;
@end


@implementation AJCPSLanguageSet

- (id)initWithHandle:(ajn::services::LanguageSet *)handle
{
	self = [super init];
	if (self) {
		self.handle = handle;
	}
	return self;
}

- (NSString *)getLanguageSetName
{
	return [AJNConvertUtil convertQCCStringtoNSString:self.handle->getLanguageSetName()];
}

- (size_t)getNumLanguages
{
	return self.handle->getNumLanguages();
}

- (void)addLanguage:(NSString *)language
{
	return self.handle->addLanguage([AJNConvertUtil convertNSStringToQCCString:language]);
}

- (NSArray *)getLanguages
{
    if (!self.handle)
        return nil;
    
	const std::vector <qcc::String> cpp_languages = self.handle->getLanguages();
    
	NSMutableArray *languages = [[NSMutableArray alloc]init];
    
	for (int i = 0; i != cpp_languages.size(); i++) {
		[languages addObject:[AJNConvertUtil convertQCCStringtoNSString:cpp_languages.at(i)]];
	}
    
	return languages;
}

@end
