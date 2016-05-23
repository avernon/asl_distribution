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

#include <alljoyn/controlpanel/LanguageSet.h>
#include <algorithm>

namespace ajn {
namespace services {

LanguageSet::LanguageSet(qcc::String const& languageSetName) :
    m_LanguageSetName(languageSetName)
{
}

LanguageSet::~LanguageSet()
{
}

const qcc::String& LanguageSet::getLanguageSetName() const
{
    return m_LanguageSetName;
}

const size_t LanguageSet::getNumLanguages() const
{
    return m_Languages.size();
}

void LanguageSet::addLanguage(qcc::String const& language)
{
    if (std::find(m_Languages.begin(), m_Languages.end(), language) == m_Languages.end()) {
        m_Languages.push_back(language);
    }
}

const std::vector<qcc::String>& LanguageSet::getLanguages() const
{
    return m_Languages;
}
} /* namespace services */
} /* namespace ajn */
