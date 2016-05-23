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
#ifndef _QCC_PLATFORM_H
#define _QCC_PLATFORM_H
/**
 * @file
 *
 * This file just wraps including actual OS and toolchain specific header
 * files depding on the OS group setting.
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

#if defined(QCC_OS_GROUP_POSIX)
#include <qcc/posix/platform_types.h>
#elif defined(QCC_OS_GROUP_WINDOWS)
#include <qcc/windows/platform_types.h>
#include <qcc/windows/mapping.h>
#else
#error No OS GROUP defined.
#endif

#if defined(__GNUC__)

#define GCC_VERSION ((__GNUC__ * 10000) + (__GNUC_MINOR__ * 100) + __GNUC_PATCHLEVEL__)
#if (GCC_VERSION < 40700L)
/*
 * Versions of GCC prior to 4.7.0 have an annoying but intentional bug where
 * __cplusplus is set to 1 rather than the appropriate date code so that it
 * would be compatible with Solaris 8.
 */

#if (GCC_VERSION >= 40600L) && defined(__GXX_EXPERIMENTAL_CXX0X__)
/*
 * GCC 4.6.x supports C++11, at least in terms of unordered_map, etc. when the
 * -std=gnu++0x option is passed in.  Thus, fix the value of __cplusplus.
 */
#undef __cplusplus
#define __cplusplus 201100L
#endif  // GCC version >= 4.6 and -std=gnu++0x
#endif  // GCC version < 4.7



#if (__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1))
#define QCC_DEPRECATED(func) func __attribute__((deprecated)) /**< mark a function as deprecated in gcc. */
#else
#define QCC_DEPRECATED(func) func /**< not all gcc versions support the deprecated attribute. */
#endif

#define QCC_DLLEXPORT


#elif defined(_MSC_VER)

#define QCC_DEPRECATED(func) __declspec(deprecated) func /**< mark a function as deprecated in msvc. */

#define QCC_DLLEXPORT __declspec(dllexport)


#else /* Some unknown compiler */

#define QCC_DEPRECATED(func); /**< mark a function as deprecated. */

#endif /* Compiler type */

/**
 * Macro used to avoid unused variable warning in release code.
 * This Macro is only used when a variable is only used in the debug build
 * variant. When building in release mode the compiler will give an unused
 * variable warning.
 *
 * Example usage:
   @code
     String errMsg
     const char* errName = reply->GetErrorName(&errMsg);
     QCC_LogError(status, ("TimedPing returned ERROR_MESSAGE (error=%s, \"%s\")", errName, errMsg.c_str()));
     QCC_UNUSED(errName); // avoid unused variable warning in release build
   @endcode
 *
 * The `QCC_LogError` is an empty macro for release build variants but in debug
 * build variants it is not empty so it uses the errName variable.
 */
#define QCC_UNUSED(x) (void)(x)

/** Boolean type for C */
typedef int32_t QCC_BOOL;
/** Boolean logic true for QCC_BOOL type*/
#define QCC_TRUE 1
/** Boolean logic false for QCC_BOOL type*/
#define QCC_FALSE 0

#endif // _QCC_PLATFORM_H
