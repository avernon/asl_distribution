#ifndef _AJS_TRANSLATIONS_H
#define _AJS_TRANSLATIONS_H
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

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Lookup a string and find a translation if one exists
 *
 * @param ctx  An opaque pointer to a duktape context structure
 * @param idx  The index on the stack for the string to be translated
 * @param lang The chosen language
 */
const char* AJS_GetTranslatedString(duk_context* ctx, duk_idx_t idx, uint16_t lang);

/**
 * Lookup a string and find a translation to the current default language if one exists
 *
 * @param ctx  An opaque pointer to a duktape context structure
 * @param idx  The index on the stack for the string to be translated
 */
const char* AJS_GetDefaultTranslatedString(duk_context* ctx, duk_idx_t idx);

/**
 * Get the language name for a give language index
 *
 * @param ctx        An opaque pointer to a duktape context structure
 * @param langIndex  The index to lookup.
 *
 * @return  The language name or the default language
 */
const char* AJS_GetLanguageName(duk_context* ctx, uint8_t langIndex);

/**
 * Get the language index for a give language name
 *
 * @param ctx       An opaque pointer to a duktape context structure
 * @param langName  The name to lookup.
 *
 * @return The language index or 0 if the language is unknown.
 */
uint8_t AJS_GetLanguageIndex(duk_context* ctx, const char* langName);

/**
 * Get the number of languages supported
 *
 * @param  ctx  An opaque pointer to a duktape context structure
 * @return The number of supported languages - never less than 1
 */
uint8_t AJS_GetNumberOfLanguages(duk_context* ctx);

#ifdef __cplusplus
}
#endif

#endif
