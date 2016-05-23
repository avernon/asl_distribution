# Contributed by Qualcomm Connected Experiences, Inc.,
# with authorization from the AllSeen Alliance, Inc.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# 
# Pursuant to Section 1 of the License, the work of authorship constituting
# a Work and any Contribution incorporated in the Work shall mean only that
# Contributor's code submissions authored by that Contributor.  Any rights
# granted under the License are conditioned upon acceptance of these
# clarifications.
/**
 * @file
 *
 * This file implements utilities functions
 */

/******************************************************************************
 *
 *
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

#include <qcc/platform.h>

#include <ctype.h>

#include <qcc/String.h>
#include <qcc/StringUtil.h>
#include <qcc/Util.h>

#include "BusUtil.h"


#define QCC_MODULE "ALLJOYN"


#define MAX_NAME_LEN 256

using namespace qcc;
using namespace std;

namespace ajn {

bool IsLegalUniqueName(const char* str)
{
    if (!str) {
        return false;
    }
    const char* p = str;

    char c = *p++;
    if (c != ':' || !(IsAlphaNumeric(*p) || (*p == '-') || (*p == '_'))) {
        return false;
    }
    p++;

    size_t periods = 0;
    while ((c = *p++)) {
        if (!IsAlphaNumeric(c) && (c != '-') && (c != '_')) {
            if ((c != '.') || (*p == '.') || (*p == 0)) {
                return false;
            }
            periods++;
        }
    }
    return (periods > 0) && ((p - str) <= MAX_NAME_LEN);
}


bool IsLegalBusName(const char* str)
{
    if (!str) {
        return false;
    }
    if (*str == ':') {
        return IsLegalUniqueName(str);
    }
    const char* p = str;
    size_t periods = 0;
    char c = *p++;
    /* Must begin with an alpha character, underscore, or hyphen */
    if (!IsAlpha(c) && (c != '_') && (c != '-')) {
        return false;
    }
    while ((c = *p++) != 0) {
        if (!IsAlphaNumeric(c) && (c != '_') && (c != '-')) {
            if ((c != '.') || (*p == '.') || (*p == 0) || isdigit(*p)) {
                return false;
            }
            periods++;
        }
    }
    return (periods > 0) && ((p - str) <= MAX_NAME_LEN);
}


bool IsLegalObjectPath(const char* str)
{
    if (!str) {
        return false;
    }
    /* Must begin with slash */
    char c = *str++;
    if (c != '/') {
        return false;
    }
    while ((c = *str++) != 0) {
        if (!IsAlphaNumeric(c) && (c != '_')) {
            if ((c != '/') || (*str == '/') || (*str == 0)) {
                return false;
            }
        }
    }
    return true;
}


bool IsLegalInterfaceName(const char* str)
{
    if (!str) {
        return false;
    }
    const char* p = str;

    /* Must begin with an alpha character or underscore */
    char c = *p++;
    if (!IsAlpha(c) && (c != '_')) {
        return false;
    }
    size_t periods = 0;
    while ((c = *p++) != 0) {
        if (!IsAlphaNumeric(c) && (c != '_')) {
            if ((c != '.') || (*p == '.') || (*p == 0)) {
                return false;
            }
            periods++;
        }
    }
    return (periods > 0) && ((p - str) <= MAX_NAME_LEN);
}


bool IsLegalErrorName(const char* str)
{
    return IsLegalInterfaceName(str);
}


bool IsLegalMemberName(const char* str)
{
    if (!str) {
        return false;
    }
    const char* p = str;
    char c = *p++;

    if (!IsAlpha(c) && (c != '_')) {
        return false;
    }
    while ((c = *p++) != 0) {
        if (!IsAlphaNumeric(c) && (c != '_')) {
            return false;
        }
    }
    return (p - str) <= MAX_NAME_LEN;
}


qcc::String BusNameFromObjPath(const char* str)
{
    qcc::String path;

    if (IsLegalObjectPath(str) && (str[1] != 0)) {
        char c = *str++;
        do {
            if (c == '/') {
                c = '.';
            }
            path.push_back(c);
        } while ((c = *str++) != 0);
    }
    return path;
}

QStatus ParseMatchRule(const qcc::String& match,
                       MatchMap& matchMap)
{
    QStatus status = ER_OK;
    size_t pos = 0;
    while (pos < match.length()) {
        size_t endPos = match.find_first_of(',', pos);
        if (endPos == String::npos) {
            endPos = match.length();
        }
        size_t eqPos = match.find_first_of('=', pos);
        if ((eqPos == String::npos) || (eqPos >= endPos)) {
            status = ER_FAIL;
            break;
        }
        ++eqPos;
        size_t begQuotePos = match.find_first_of('\'', eqPos);
        size_t endQuotePos = String::npos;
        if ((begQuotePos != String::npos) && (++begQuotePos < match.length())) {
            endQuotePos = match.find_first_of('\'', begQuotePos);
        }
        if (endQuotePos == String::npos) {
            status = ER_FAIL;
            break;
        }
        String key = match.substr(pos, eqPos - 1 - pos);
        String value = match.substr(begQuotePos, endQuotePos - begQuotePos);
        matchMap.insert(pair<String, String>(key, value));
        pos = endPos + 1;
    }
    return status;
}

bool WildcardMatch(qcc::String str, qcc::String pat)
{
    size_t patsize = pat.size();
    size_t strsize = str.size();
    const char* p = pat.c_str();
    const char* s = str.c_str();
    uint32_t pi, si;

    //
    // Zero length strings are unmatchable.
    //
    if (patsize == 0 || strsize == 0) {
        return true;
    }

    for (pi = 0, si = 0; pi < patsize && si < strsize; ++pi, ++si) {
        switch (p[pi]) {
        case '*':
            //
            // Point to the character after the wildcard.
            //
            ++pi;

            //
            // If the wildcard is at the end of the pattern, we match
            //
            if (pi == patsize) {
                return false;
            }

            //
            // If the next character is another wildcard, we could go through
            // a bunch of special case work to figure it all out, but in the
            // spirit of simplicity we don't deal with it and return "different".
            //
            if (p[pi] == '*' || p[pi] == '?') {
                return true;
            }

            //
            // Scan forward in the string looking for the character after the
            // wildcard.
            //
            for (; si < strsize; ++si) {
                if (s[si] == p[pi]) {
                    break;
                }
            }
            break;

        case '?':
            //
            // A question mark matches any character in the string.
            //
            break;

        default:
            //
            // If no wildcard, we just compare character for character.
            //
            if (p[pi] != s[si]) {
                return true;
            }
            break;
        }
    }

    //
    // If we fall through to here, we have matched all the way through one or
    // both of the strings.  If pi == patsize and si == strsize then we matched
    // all the way to the end of both strings and we have a match.
    //
    if (pi == patsize && si == strsize) {
        return false;
    }

    //
    // If pi < patsize and si == strsize there are characters in the pattern
    // that haven't been matched.  The only way this can be a match is if
    // that last character is a '*' meaning zero or more characters match.
    //
    if (pi < patsize && si == strsize) {
        if (p[pi] == '*') {
            return false;
        } else {
            return true;
        }
    }

    //
    // The remaining chase is pi == patsize and si < strsize which means
    // that we've got characters in the string that haven't been matched
    // by the pattern.  There's no way this can be a match.
    //
    return true;
}

}
