////////////////////////////////////////////////////////////////////////////////
// Copyright AllSeen Alliance. All rights reserved.
//
//    Contributed by Qualcomm Connected Experiences, Inc.,
//    with authorization from the AllSeen Alliance, Inc.
//    
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//    
//        http://www.apache.org/licenses/LICENSE-2.0
//    
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//    
//    Pursuant to Section 1 of the License, the work of authorship constituting
//    a Work and any Contribution incorporated in the Work shall mean only that
//    Contributor's code submissions authored by that Contributor.  Any rights
//    granted under the License are conditioned upon acceptance of these
//    clarifications.
////////////////////////////////////////////////////////////////////////////////

#import "AJNTranslatorImpl.h"


AJNTranslatorImpl::AJNTranslatorImpl(id<AJNTranslator> aDelegate) : m_delegate(aDelegate)
{

}

/**
 * Virtual destructor for derivable class.
 */
AJNTranslatorImpl::~AJNTranslatorImpl()
{
    m_delegate = nil;
}

size_t AJNTranslatorImpl::NumTargetLanguages()
{
    return [m_delegate numTargetLanguages];
}

void AJNTranslatorImpl::GetTargetLanguage(size_t index, qcc::String& ret) 
{
    ret.assign([[m_delegate getTargetLanguage:(index)] UTF8String]);
}

const char* AJNTranslatorImpl::Translate(const char* sourceLanguage, const char* targetLanguage, const char* source, qcc::String& buffer)
{
    NSString* fromLang = [[NSString alloc] initWithUTF8String:(sourceLanguage)];
    NSString* toLang = [[NSString alloc] initWithUTF8String:(targetLanguage)];
    NSString* text = [[NSString alloc] initWithUTF8String:(source)];

    NSString* translation = [m_delegate translateText:(text) from:(fromLang) to:(toLang)];
    if(translation == nil)
    {
        return 0;
    }
    
    buffer.assign([translation UTF8String]);
    return buffer.c_str();
}

