#ifndef _AJ_TARGET_H
#define _AJ_TARGET_H
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

#include <stdio.h>
#include <stddef.h>
#include <windows.h>
#include <assert.h>

#if _MSC_VER >= 1600   /* MSVC 2010 or higher */
#include <stdint.h>
#else
typedef signed char int8_t;           /** 8-bit signed integer */
typedef unsigned char uint8_t;        /** 8-bit unsigned integer */
typedef signed short int16_t;         /** 16-bit signed integer */
typedef unsigned short uint16_t;      /** 16-bit unsigned integer */
typedef signed int int32_t;           /** 32-bit signed integer */
typedef unsigned int uint32_t;        /** 32-bit unsigned integer */
typedef signed long long int64_t;     /** 64-bit signed integer */
typedef unsigned long long uint64_t;  /** 64-bit unsigned integer */
#endif

#ifndef TRUE
#define TRUE (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

#ifndef max
#define max(x, y) ((x) > (y) ? (x) : (y))
#endif

#ifndef min
#define min(x, y) ((x) < (y) ? (x) : (y))
#endif


#define WORD_ALIGN(x) ((x & 0x3) ? ((x >> 2) + 1) << 2 : x)
#define HOST_IS_LITTLE_ENDIAN  TRUE
#define HOST_IS_BIG_ENDIAN     FALSE

#define AJ_Printf(fmat, ...) \
    do { printf(fmat, ## __VA_ARGS__); fflush(stdout); } while (0)

#ifndef NDEBUG

extern uint8_t dbgCONFIGUREME;
extern uint8_t dbgINIT;
extern uint8_t dbgNET;
extern uint8_t dbgTARGET_CRYPTO;
extern uint8_t dbgTARGET_NVRAM;
extern uint8_t dbgTARGET_UTIL;

#endif

#define AJ_ASSERT(x)  assert(x)

/*
 * AJ_Reboot() is a NOOP on this platform
 */
#define AJ_Reboot()

#define AJ_EXPORT  __declspec(dllexport)

#define AJ_CreateNewGUID AJ_RandBytes

#define AJ_GetDebugTime(x) AJ_ERR_RESOURCES

#define inline __inline

#define AJ_DEPRECATED(func) __declspec(deprecated) func

/*
 * Main method allows argc, argv
 */
#define MAIN_ALLOWS_ARGS

#endif
