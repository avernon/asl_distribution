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
#ifndef _PLATFORM_TYPES_H
#define _PLATFORM_TYPES_H
/**
 * @file
 *
 * This file defines basic platform-specific types for Windows
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

#include <stddef.h>
#include <windows.h>

#if _MSC_VER >= 1600   /* MSVC 2010 or higher */
#include <stdint.h>
#else
typedef signed char int8_t;           ///< 8-bit signed integer.
typedef unsigned char uint8_t;        ///< 8-bit unsigned integer.
typedef signed short int16_t;         ///< 16-bit signed integer.
typedef unsigned short uint16_t;      ///< 16-bit unsigned integer.
typedef signed int int32_t;           ///< 32-bit signed integer.
typedef unsigned int uint32_t;        ///< 32-bit unsigned integer.
typedef signed long long int64_t;     ///< 64-bit signed integer.
typedef unsigned long long uint64_t;  ///< 64-bit unsigned integer.
#endif

#ifdef __cplusplus
namespace qcc {
typedef UINT_PTR SocketFd;      /**< Socket file descriptor type. */
typedef UINT_PTR UARTFd;        /**< UART file descriptor type. */
}
#else
typedef UINT_PTR qcc_SocketFd; /**< Socket file descriptor type. */
typedef UINT_PTR qcc_UARTFd;   /**< UART file descriptor type. */
#endif

/* Some windows header files define min and max as macros */
#undef min
#undef max

#ifndef PRIi64 /* From C9x inttypes.h */
/**
 * 64-bit signed integer from C9x inttypes.h
 */
#define PRIi64 "I64i"
/**
 * 64-bit unsigned integer from C9x inttypes.h
 */
#define PRIu64 "I64u"
#endif

#endif
