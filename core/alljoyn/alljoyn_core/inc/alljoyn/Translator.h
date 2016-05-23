/**
 * @file
 * Translator is an abstract base class (interface) implemented by users of the
 * AllJoyn API in order to provide org.allseen.Introspectable descriptions in more than just one language
 */

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
#ifndef _ALLJOYN_DESCRIPTIONTRANSLATOR_H
#define _ALLJOYN_DESCRIPTIONTRANSLATOR_H

#ifndef __cplusplus
#error Only include Translator.h in C++ code.
#endif

#include <qcc/String.h>

namespace ajn {

/**
 * Abstract base class that provides translations of descriptions returned from
 * org.allseen.Introspectable.IntrospectWithDescription.
 */
class Translator {
  public:

    virtual ~Translator() { }

    /**
     * Retrieve the number of target language tags this Translator
     * can translate into.
     * @return size_t The number of target language tags
     */
    virtual size_t NumTargetLanguages() = 0;

    /**
     * Retrieve the n'th target language tag
     * @param index The index of the language tag to retrieve
     * @param ret The returned value
     */
    virtual void GetTargetLanguage(size_t index, qcc::String& ret) = 0;

    /**
     * Translate source from sourceLanguage into targetLanguage.
     * If this Translator does not have a translation for the given
     * parameters it should return NULL.
     *
     * @param sourceLanguage The language tag of the text in source
     * @param targetLanguage The language tag to translate into
     * @param source The source text to translate
     * @return The translated text or NULL
     */
    virtual const char* Translate(const char* sourceLanguage, const char* targetLanguage, const char* source) {
        return NULL;
    }

    /**
     * Translate source from sourceLanguage into targetLanguage.
     * If this Translator does not have a translation for the given
     * parameters it should return NULL. This version of the
     * function is designed for imeplementations that return dynamically allocated strings.
     * The string should be copied into buffer and buffer.c_str() must be returned. When alljoyn
     * finishes using the string buffer will be free'ed
     *
     * @param sourceLanguage The language tag of the text in source
     * @param targetLanguage The language tag to translate into
     * @param source The source text to translate
     * @param buffer A buffer to hold the dynamically allocated string returned by this function
     * @return The translated text or NULL
     */
    virtual const char* Translate(const char* sourceLanguage,
                                  const char* targetLanguage, const char* sourceText, qcc::String& buffer) {
        QCC_UNUSED(buffer);
        return Translate(sourceLanguage, targetLanguage, sourceText);
    }

    /**
     * Translate an id or source text from sourceLanguage into text in the
     * given targetLanguage. If this Translator does not support MsgArgs it
     * should return NULL.
     * This version of the function is designed for implementations that
     * return a pointer to a MsgArg that will not go away. This is required
     * by the AboutData::GetField() API.
     *
     * @param[in] sourceLanguage The language tag of the text in sourcetext. If
     *  sourceLanguage is NULL or empty, then sourceText is simply an id used
     *  for lookup.
     * @param[in] targetLanguage The language tag to translate into
     * @param[in] sourceText The source text to translate
     * @param[out] msgarg Returns the MsgArg containing the translation
     * @return
     *  - #ER_OK on success
     *  - #ER_NOT_IMPLEMENTED if translator does not support MsgArgs
     */
    virtual QStatus TranslateToMsgArg(const char* sourceLanguage,
                                      const char* targetLanguage, const char* sourceText, MsgArg*& msgarg) {
        QCC_UNUSED(sourceLanguage);
        QCC_UNUSED(targetLanguage);
        QCC_UNUSED(sourceText);
        QCC_UNUSED(msgarg);
        return ER_NOT_IMPLEMENTED;
    }

    /**
     * Add new localized text.
     *
     * @param[in] id The id of the localized text to add.
     * @param[in] value The localized text to be associated with the id.
     * @param[in] language The IETF language tag specified by RFC 5646.
     *
     * @return
     *  - #ER_OK on success
     *  - #ER_NOT_IMPLEMENTED if translator does not support adding target languages.
     */
    virtual QStatus AddStringTranslation(const char* id, const char* value, const char* language) {
        QCC_UNUSED(id);
        QCC_UNUSED(value);
        QCC_UNUSED(language);
        return ER_NOT_IMPLEMENTED;
    }

    /**
     * Add new localized text.
     *
     * @param[in] id The id of the localized text to add.
     * @param[in] value The localized text to be associated with the id.
     * @param[in] language The IETF language tag specified by RFC 5646.
     *
     * @return
     *  - #ER_OK on success
     *  - #ER_NOT_IMPLEMENTED if translator does not support adding target languages or the MsgArg type.
     */
    virtual QStatus AddMsgArgTranslation(const char* id, const MsgArg* value, const char* language) {
        if (value->typeId != ALLJOYN_STRING) {
            return ER_NOT_IMPLEMENTED;
        }
        return AddStringTranslation(id, value->v_string.str, language);
    }

    /**
     * Get the best matching language according to RFC 4647 section 3.4.
     *
     * @param[in] requested The requested IETF language range.
     * @param[in] defaultLanguage The default language to use.
     * @param[out] ret The returned value
     */
    virtual void GetBestLanguage(const char* requested, const qcc::String& defaultLanguage, qcc::String& ret);
};

/**
 * Abstract base class that provides translations of text using a lookup
 * table that maps a "field id" and a target language to a description
 * in the target language corresponding to the indicated field.  Each
 * unique string to translate should have its own id.  For example,
 * AboutData has ids for manufacturer, description, etc.
 */
class LookupTableTranslator : public Translator {
  public:
    /**
     * @copydoc Translator::NumTargetLanguages
     * @see Translator::NumTargetLanguages
     */
    virtual size_t NumTargetLanguages();

    /**
     * @copydoc Translator::GetTargetLanguage
     * @see Translator::GetTargetLanguage
     */
    virtual void GetTargetLanguage(size_t index, qcc::String& ret);

    /**
     * @copydoc Translator::AddTargetLanguage
     * @see Translator::AddTargetLanguage
     */
    virtual QStatus AddTargetLanguage(const char* language, bool* added);

    /**
     * Retrieve the number of field ids this Translator has translations for.
     * @return size_t The number of field ids
     */
    virtual size_t NumFields() = 0;

    /**
     * Retrieve the n'th field id
     * @param index The index of the field id to retrieve
     * @return The n'th field id
     */
    virtual const char* GetFieldId(size_t index) = 0;

  protected:
    /**
     * Struct to handle case insensitive comparison operator used to make sure
     * the case of language tags are ignored when adding, sorting and reading them.
     */
    struct CaseInsensitiveCompare {
        /**
         * inner case insensitive comparison struct used by the
         * std::lexicographical_compare function.
         */
        struct CaseInsensitiveCharCompare {
            /**
             * CaseInsensitive comparison parentheses operator for individual chars
             * @param lhs char value to compare
             * @param rhs char value to compare
             * @return true if the case insensitive comparison of lhs < rhs
             */
            bool operator()(const char& lhs, const char& rhs)
            {
                return std::tolower(lhs) < std::tolower(rhs);
            }
        };

        /**
         * CaseInsensitive comparison parentheses operator for Strings
         * @param lhs String to compare
         * @param rhs String to to compare
         * @return true if the case insensitive comparison of lhs < rhs
         */
        bool operator()(const qcc::String& lhs, const qcc::String& rhs) const
        {
            return std::lexicographical_compare(lhs.begin(), lhs.end(),
                                                rhs.begin(), rhs.end(),
                                                CaseInsensitiveCharCompare());
        }
    };

    /**
     * Local member variable for supported target languages.
     */
    std::set<qcc::String, CaseInsensitiveCompare> supportedLanguages;

    /**
     * typedef supported languages iterator
     */
    typedef std::set<qcc::String, CaseInsensitiveCompare>::iterator supportedLanguagesIterator;
};

/**
 * Class that provides translations of text using a lookup table where
 * each translated string is stored as a simple string.  This can be used
 * for introspection descriptions, and potentially other APIs.
 */
class StringTableTranslator : public LookupTableTranslator {
  public:
    /**
     * @copydoc LookupTableTranslator::NumFields
     * @see LookupTableTranslator::NumFields
     */
    virtual size_t NumFields()
    {
        return localizedStore.size();
    }

    /**
     * @copydoc LookupTableTranslator::GetFieldId
     * @see LookupTableTranslator::GetFieldId
     */
    virtual const char* GetFieldId(size_t index);

    /**
     * @copydoc Translator::Translate
     * @see Translator::Translate
     */
    virtual const char* Translate(const char* sourceLanguage, const char* targetLanguage, const char* sourceText);

    /**
     * @copydoc Translator::AddStringTranslation
     * @see Translator::AddStringTranslation
     */
    virtual QStatus AddStringTranslation(const char* id, const char* value, const char* language);

    /**
     * Determine if the table is empty.
     *
     * @return  Returns true if the table is empty.
     */
    bool IsEmpty() const { return localizedStore.empty(); }

  protected:
    /**
     * Local member variable mapping a field id to a set of translations
     * in various languages.
     */
    std::map<qcc::String, std::map<qcc::String, qcc::String, CaseInsensitiveCompare> > localizedStore;

    /**
     * typedef localized store iterator
     */
    typedef std::map<qcc::String, std::map<qcc::String, qcc::String, CaseInsensitiveCompare> >::iterator localizedStoreIterator;
};

}

#endif
