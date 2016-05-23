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

#define AJ_EXPORT
#include "aj_shield.h"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef signed char int8_t;           /** 8-bit signed integer */
typedef unsigned char uint8_t;        /** 8-bit unsigned integer */
typedef signed long long int64_t;     /** 64-bit signed integer */
typedef unsigned long long uint64_t;  /** 64-bit unsigned integer */

typedef uint16_t suint32_t;  /* amount of data sent into a socket */


#include <string.h>
#include <malloc.h>
#include <assert.h>

#ifndef TRUE
#define TRUE (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

// Begin Memory Diagnostics
static const char* ramstart = (char*)0x20070000;
static const char* ramend = (char*)0x20088000;
extern char _end;

inline int stack_used() {
    register char* stack_ptr asm ("sp");
    return (ramend - stack_ptr);
}

inline int static_used() {
    return (&_end - ramstart);
}

inline int heap_used() {
    struct mallinfo mi = mallinfo();
    return (mi.uordblks);
}

void ram_diag();

/* atoi not supplied on all Arduino platforms */
int AJ_atoi(char const*inP);
#define atoi(x) AJ_atoi(x)

// End Memory Diagnostics

#define WORD_ALIGN(x) ((x & 0x3) ? ((x >> 2) + 1) << 2 : x)

#define HOST_IS_LITTLE_ENDIAN  TRUE
#define HOST_IS_BIG_ENDIAN     FALSE


#if defined(AJ_ARDUINO_SHIELD_BTLE)
    #define AJ_SERIAL_CONNECTION
#elif defined(AJ_ARDUINO_SHIELD_WIFI)
    #define WIFI_UDP_WORKING
    #include <WiFi.h>
    #include <WiFiUdp.h>
#elif defined(AJ_ARDUINO_SHIELD_ETH)
    #include <Ethernet.h>
    #include <EthernetUdp.h>
#endif

#define AJ_Printf(fmat, ...) \
    do { printf(fmat, ## __VA_ARGS__); } while (0)


#ifndef NDEBUG

extern uint8_t dbgCONFIGUREME;
extern uint8_t dbgINIT;
extern uint8_t dbgNET;
extern uint8_t dbgTARGET_CRYPTO;
extern uint8_t dbgTARGET_NVRAM;
extern uint8_t dbgTARGET_UTIL;

#endif

#ifndef min
#define min(x, y) (((x) < (y)) ? (x) : (y))
#endif

#ifndef max
#define max(x, y) (((x) > (y)) ? (x) : (y))
#endif

#define AJ_ASSERT(x) assert(x)

/*
 * AJ_Reboot() is a NOOP on this platform
 */
#define AJ_Reboot()

#define AJ_CreateNewGUID AJ_RandBytes

#define AJ_GetDebugTime(x) AJ_ERR_RESOURCES

#if (__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1))
#define AJ_DEPRECATED(func) func __attribute__((deprecated)) /**< mark a function as deprecated in gcc. */
#else
#define AJ_DEPRECATED(func) func /**< not all gcc versions support the deprecated attribute. */
#endif

#endif
