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
#ifndef _ALLJOYN_ABOUTDATAINTERNAL_H
#define _ALLJOYN_ABOUTDATAINTERNAL_H
#include <map>
#include <set>

#include <alljoyn/AboutData.h>
#include <qcc/Mutex.h>
#include <algorithm>
#include <cctype>

namespace ajn {

/**
 * Class that provides translations of text using a lookup table where
 * each translated string is stored as a MsgArg as currently required
 * by AboutData.
 */
class MsgArgTableTranslator : public LookupTableTranslator {
  public:
    /**
     * @see LookupTableTranslator::NumFields
     */
    virtual size_t NumFields()
    {
        return localizedStore.size();
    }

    /**
     * @see LookupTableTranslator::GetFieldId
     */
    virtual const char* GetFieldId(size_t index)
    {
        localizedStoreIterator it = localizedStore.begin();
        for (size_t count = 0; (count < index) && (it != localizedStore.end()); it++, count++)
            ; //empty for loop to advance the iterator to the element indicated by the index
        if (it == localizedStore.end()) {
            return nullptr;
        }
        return it->first.c_str();
    }

    /**
     * @see Translator::Translate
     */
    virtual const char* Translate(const char* sourceLanguage, const char* targetLanguage, const char* sourceText)
    {
        QCC_UNUSED(sourceLanguage);
        char* result;
        QStatus status = localizedStore[sourceText][targetLanguage].Get("s", &result);
        return (status == ER_OK) ? result : nullptr;
    }

    /**
     * @see Translator::TranslateToMsgArg
     */
    virtual QStatus TranslateToMsgArg(const char* sourceLanguage,
                                      const char* targetLanguage, const char* sourceText, MsgArg*& value)
    {
        QCC_UNUSED(sourceLanguage);
        value = &localizedStore[sourceText][targetLanguage];
        return (value->typeId == ALLJOYN_INVALID) ? ER_ABOUT_INVALID_ABOUTDATA_FIELD_VALUE : ER_OK;
    }

    /**
     * @see Translator::AddMsgArgTranslation
     */
    virtual QStatus AddMsgArgTranslation(const char* id, const MsgArg* value, const char* language)
    {
        if (supportedLanguages.find(language) == supportedLanguages.end()) {
            supportedLanguages.insert(language);
        }
        localizedStore[id][language] = *value;
        return ER_OK;
    }

  protected:
    /**
     * Local member variable mapping a field id to a set of translations
     * in various languages.
     */
    std::map<qcc::String, std::map<qcc::String, MsgArg, CaseInsensitiveCompare>
> localizedStore;

    /**
     * typedef localized store iterator
     */
    typedef std::map<qcc::String, std::map<qcc::String, MsgArg, CaseInsensitiveCompare> >::iterator localizedStoreIterator;
};

/**
 * Class used to hold internal values for the AboutData class
 */
class AboutData::Internal {
    friend class AboutData;
  public:
    AboutData::Internal& operator=(const AboutData::Internal& other) {
        aboutFields = other.aboutFields;
        propertyStore = other.propertyStore;
        defaultTranslator = other.defaultTranslator;
        translator = other.translator;
        keyLanguage = other.keyLanguage;
        return *this;
    }

  private:
    size_t GetSupportedLanguages(const char** languageTags, size_t num);

    /**
     * A std::map that maps the field name to its FieldDetails.
     */
    std::map<qcc::String, FieldDetails> aboutFields;

    /**
     * property store used to hold property store values that are not localized
     * key: Field Name
     * value: Data
     */
    std::map<qcc::String, MsgArg> propertyStore;

    struct CaseInsensitiveCompare {
        struct CaseInsensitiveCharCompare {
            bool operator()(const char& lhs, const char& rhs)
            {
                return std::tolower(lhs) < std::tolower(rhs);
            }
        };

        bool operator()(const qcc::String& lhs, const qcc::String& rhs) const
        {
            return std::lexicographical_compare(lhs.begin(), lhs.end(),
                                                rhs.begin(), rhs.end(),
                                                CaseInsensitiveCharCompare());
        }
    };

    /**
     * key: Field Name
     * value: map of language / Data
     */
    std::map<qcc::String, std::map<qcc::String, MsgArg, CaseInsensitiveCompare> > localizedPropertyStore;

    std::vector<qcc::String> supportedLanguages;

    /**
     * typedef const iterator
     */
    typedef std::map<qcc::String, std::map<qcc::String, MsgArg, CaseInsensitiveCompare> >::const_iterator localizedPropertyStoreConstIterator;

    /**
     * local member variable for supported languages
     */
    std::set<qcc::String, CaseInsensitiveCompare> supportedLanguages;

    /**
     * typedef supported languages iterator
     */
    typedef std::set<qcc::String, CaseInsensitiveCompare>::iterator supportedLanguagesIterator;

    /**
     * mutex lock to protect the property store.
     */
    qcc::Mutex propertyStoreLock;
};
}
#endif //_ALLJOYN_ABOUTDATAINTERNAL_H
