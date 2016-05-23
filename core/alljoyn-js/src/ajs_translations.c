/**
 * @file
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

#include "ajs.h"
#include "ajs_util.h"

static char** languagesList;

static const char* GetTranslatedString(duk_context* ctx, duk_idx_t idx, uint16_t langNum, const char* langName)
{
    const char* translation = NULL;
    const char* original = duk_get_string(ctx, idx);

    if (!original) {
        return "???";
    }

    AJ_InfoPrintf(("Looking up translation for %s\n", original));

    AJS_GetGlobalStashObject(ctx, "translations");
    if (duk_is_object(ctx, -1)) {
        /*
         * Find out which language and then look up a translation
         */
        if (langName) {
            duk_push_string(ctx, langName);
        } else {
            AJS_GetAllJoynProperty(ctx, "languages");
            if (duk_is_array(ctx, -1)) {
                duk_get_prop_index(ctx, -1, langNum);
                duk_remove(ctx, -2);
            }
        }
        /*
         * If we got a language see if there is a translation
         */
        if (duk_is_string(ctx, -1)) {
            duk_get_prop(ctx, -2);
            if (duk_is_object(ctx, -1)) {
                duk_get_prop_string(ctx, -1, original);
                translation = duk_get_string(ctx, -1);
                duk_pop(ctx);
            }
        }
        duk_pop(ctx);
    }
    duk_pop(ctx);

    if (translation && *translation) {
        return translation;
    } else {
        return original;
    }
}

const char* AJS_GetDefaultTranslatedString(duk_context* ctx, duk_idx_t idx)
{
    return GetTranslatedString(ctx, idx, 0, AJS_GetCurrentLanguageName());
}

const char* AJS_GetTranslatedString(duk_context* ctx, duk_idx_t idx, uint16_t langNum)
{
    return GetTranslatedString(ctx, idx, langNum, NULL);
}

static int NativeTranslate(duk_context* ctx)
{
    const char* trans = NULL;

    if (duk_is_number(ctx, 1)) {
        trans = GetTranslatedString(ctx, 0, duk_get_int(ctx, 1), NULL);
    } else if (duk_is_string(ctx, 1)) {
        trans = GetTranslatedString(ctx, 0, 0, duk_get_string(ctx, 1));
    } else {
        trans = GetTranslatedString(ctx, 0, 0, AJS_GetCurrentLanguageName());
    }
    duk_push_string(ctx, trans);
    return 1;
}

/*
 * Translations is an object where the properties are arrays of translation strings. The property
 * names are the respective languages.
 */
static int NativeTranslationsSetter(duk_context* ctx)
{
    duk_uarridx_t numLangs = 0;

    if (!duk_is_object(ctx, 0)) {
        duk_error(ctx, DUK_ERR_TYPE_ERROR, "Translations requires an object");
    }
    /*
     * Check that translations have not already ben set
     */
    duk_push_global_stash(ctx);
    if (duk_has_prop_string(ctx, -1, "translations")) {
        duk_error(ctx, DUK_ERR_TYPE_ERROR, "Translations cannot be changed");
    }
    duk_pop(ctx);
    /*
     * Global languages list to be registered with AJ_RegisterDescriptionLanguages()
     */
    languagesList = duk_alloc(ctx, sizeof(const char*) * 2);
    /*
     * Array for languages
     */
    duk_push_this(ctx);
    duk_push_array(ctx);
    /*
     * Count the languages and accumulate them in an array
     */
    duk_enum(ctx, 0, DUK_ENUM_OWN_PROPERTIES_ONLY);
    while (duk_next(ctx, -1, 0)) {
        languagesList = duk_realloc(ctx, languagesList, sizeof(const char*) * (numLangs + 2));
        if (languagesList) {
            languagesList[numLangs] = (char*)duk_get_string(ctx, -1);
            duk_put_prop_index(ctx, -3, numLangs);
            ++numLangs;
        } else {
            duk_pop(ctx);
            break;
        }
    }
    duk_pop(ctx); // enum
    if (languagesList) {
        languagesList[numLangs] = NULL;
        numLangs = 0;
    }
    /*
     * Add the languages array to the AllJoyn object
     */
    duk_put_prop_string(ctx, -2, "languages");
    /*
     * Register the translate function
     */
    duk_push_c_lightfunc(ctx, NativeTranslate, 2, 0, 0);
    duk_put_prop_string(ctx, -2, "translate");
    duk_pop(ctx);
    /*
     * The translation array is stored in the global stash
     */
    duk_push_global_stash(ctx);
    duk_dup(ctx, 0);
    duk_put_prop_string(ctx, -2, "translations");
    duk_pop(ctx);
    /*
     * Freeze the translations object
     */
    AJS_ObjectFreeze(ctx, 0);
    /*
     * AllJoyn needs to know about the languages list
     */
    AJ_RegisterDescriptionLanguages((const char* const*)languagesList);
    /*
     * Announce the change
     */
    AJ_AboutSetShouldAnnounce();
    return 0;
}

void AJS_RegisterTranslations(duk_context* ctx, duk_idx_t ajIdx)
{
    /*
     * The only thing we do here is register a setter to do the required initializations when a
     * translations table is provided.
     */
    AJS_SetPropertyAccessors(ctx, ajIdx, "translations", NativeTranslationsSetter, NULL);
}

const char* AJS_GetLanguageName(duk_context* ctx, uint8_t langIndex)
{
    const char* langName = NULL;

    AJS_GetAllJoynProperty(ctx, "languages");
    if (duk_is_array(ctx, -1)) {
        duk_get_prop_index(ctx, -1, langIndex);
        if (duk_is_string(ctx, -1)) {
            langName = duk_get_string(ctx, -1);
        }
        duk_pop(ctx);
    }
    duk_pop(ctx);
    if (!langName) {
        langName = AJS_GetCurrentLanguageName();
    }
    return langName;
}

uint8_t AJS_GetLanguageIndex(duk_context* ctx, const char* langName)
{
    uint8_t i;

    AJS_GetAllJoynProperty(ctx, "languages");
    if (!duk_is_array(ctx, -1)) {
        i = 0;
    } else {
        duk_uarridx_t num = duk_get_length(ctx, -1);
        for (i = 0; i < num; ++i) {
            const char* str;
            duk_get_prop_index(ctx, -1, i);
            str = duk_get_string(ctx, -1);
            duk_pop(ctx);
            if (strcmp(langName, str) == 0) {
                break;
            }
        }
        if (i == num) {
            i = 0;
        }
    }
    duk_pop(ctx);
    return i;
}

uint8_t AJS_GetNumberOfLanguages(duk_context* ctx)
{
    uint8_t num = 0;
    AJS_GetAllJoynProperty(ctx, "languages");
    if (duk_is_array(ctx, -1)) {
        num = duk_get_length(ctx, -1);
    }
    duk_pop(ctx);
    return num ? num : 1;
}
