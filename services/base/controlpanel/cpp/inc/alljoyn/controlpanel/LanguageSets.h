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

#ifndef LANGUAGESETS_H_
#define LANGUAGESETS_H_

#include <alljoyn/controlpanel/LanguageSet.h>
#include <map>

namespace ajn {
namespace services {

/**
 * Class to store the LanguageSets defined
 */
class LanguageSets {
  public:

    /**
     * Constructor for LanguageSets
     */
    LanguageSets();

    /**
     * Destructor for LanguageSets
     */
    virtual ~LanguageSets();

    /**
     * Add a LanguageSet
     * @param languageSetName - name of LanguageSet
     * @param languageSet - languageSet
     */
    static void add(qcc::String const& languageSetName, LanguageSet const& languageSet);

    /**
     * Get a LanguageSet
     * @param languageSetName - the name of the languageSet to get
     * @return the languageSet requested or NULL if it does not exist
     */
    static LanguageSet* get(qcc::String const& languageSetName);

  private:

    /**
     * The LanguageSets map storing the LanguageSets defined
     */
    static std::map<qcc::String, LanguageSet> languageSets;
};

} /* namespace services */
} /* namespace ajn */
#endif /* LANGUAGESETS_H_ */
