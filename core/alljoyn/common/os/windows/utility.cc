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
 * Utility functions for Windows
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

#include <windows.h>

#include <qcc/windows/utility.h>

#define QCC_MODULE "UTILITY"


void strerror_r(uint32_t errCode, char* ansiBuf, uint16_t ansiBufSize)
{
    if (!ansiBuf || (ansiBufSize == 0)) {
        return;
    }

    if (!FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                        NULL,
                        errCode,
                        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                        (LPSTR)ansiBuf,
                        ansiBufSize,
                        NULL)) {
        ansiBuf[0] = '\0';
    }
}


void WinsockCheck()
{
}

wchar_t* MultibyteToWideString(const char* str)
{
    wchar_t* buffer = NULL;

    if (NULL == str) {
        return buffer;
    }
    size_t charLen = mbstowcs(NULL, str, 0);
    if (charLen == (size_t)-1) {
        return buffer;
    }
    ++charLen;
    buffer = new wchar_t[charLen];
    if (NULL == buffer) {
        return buffer;
    }
    if (mbstowcs(buffer, str, charLen) == (size_t)-1) {
        delete[] buffer;
        buffer = NULL;
        return buffer;
    }
    return buffer;
}
