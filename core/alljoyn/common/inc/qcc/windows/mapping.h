/**
 * @file
 *
 * Map API names for Win32
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
#ifndef _TOOLCHAIN_QCC_MAPPING_H
#define _TOOLCHAIN_QCC_MAPPING_H

#include <windows.h>
#include <float.h>
/// @cond ALLJOYN_DEV
/**
 * Map snprintf to _snprintf
 *
 * snprintf does not properly map in windows this is needed to insure calls to
 * snprintf(char *str, size_t size, const char *format, ...) will compile in
 * Windows.
 */
#define snprintf _snprintf

/**
 * Map stroll to _strtoi64
 *
 * stroll does not properly map in windows this is needed to insure calls to
 * strtoll(const char *nptr, char **endptr, int base) will compile in Windows.
 */
#define strtoll _strtoi64

/**
 * Map strtoull to _strtoui64
 *
 * strtoull does not properly map in windows this is needed to insure calls to
 * strtoull(const char *nptr, char **endptr, int base) will compile in Windows.
 */
#define strtoull _strtoui64

/**
 * Map strcasecmp to _stricmp
 *
 * strcasecmp does not properly map in windows this is needed to insure calls to
 * strcasecmp(const char *s1, const char *s2) will compile in windows.
 */
#define strcasecmp _stricmp
/**
 * Map fpclassify to _fpclass
 *
 * fpclassify does not properly map in windows this is needed to insure calls to
 * fpclassify(x) will compile in Windows.
 */
#define fpclassify _fpclass

/** macro representing floating point value that is not-a-number */
#define FP_NAN (_FPCLASS_SNAN | _FPCLASS_QNAN)
/** macro representing floating point value positive or negative zero */
#define FP_ZERO (_FPCLASS_NZ | _FPCLASS_PZ)
/** macro representing floating point value positive or negative infinity */
#define FP_INFINITE (_FPCLASS_NINF | _FPCLASS_PINF)
/// @endcond
#else
#ifdef __cplusplus
#include <algorithm>
#endif
#endif

/**
 * @defgroup windows_groupid_names The GroupID names
 * The GroupID names for Universal, Desktop, and Whitelisted Windows Applications. These GroupIDs
 * are used to enforce the Windows app isolation policies.
 */
///@{
/**
 * GroupID name for desktop Windows applications.
 */
#define DESKTOP_APPLICATION           "DesktopApplication"
/**
 * GroupID name for universal Windows applications.
 */
#define UNIVERSAL_WINDOWS_APPLICATION "UniversalWindowsApplication"
/**
 * GroupID name for white listed Windows applications.
 */
#define WHITELISTED_APPLICATION       "WhitelistedApplication"
///@}

/**
 * @name _WIN32_WINNT version constants
 * _WIN32_WINNT version constants, defined here just in case the Windows SDK version used to
 * compile AllJoyn doesn't include them already in Include\shared\sdkddkver.h. Compiler would complain
 * if the SDK public header values were different from the values below.
 */
///@{
#define _WIN32_WINNT_WIN7     0x0601
#define _WIN32_WINNT_WIN8     0x0602
#define _WIN32_WINNT_WINBLUE  0x0603
#define _WIN32_WINNT_WIN10    0x0A00
///@}

#endif
