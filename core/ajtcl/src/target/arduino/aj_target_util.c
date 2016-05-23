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

#include "Arduino.h"
#include <ajtcl/aj_target.h>
#include <ajtcl/aj_util.h>
#include <ajtcl/aj_debug.h>

typedef struct time_struct {

    /* The number of milliseconds in the time. */
    uint32_t milliseconds;

} TIME_STRUCT;

void AJ_Sleep(uint32_t time)
{
    delay(time);
}

uint32_t AJ_GetElapsedTime(AJ_Time* timer, uint8_t cumulative)
{
    uint32_t elapsed;
    TIME_STRUCT now;

    now.milliseconds =  millis();
    elapsed = (uint32_t)now.milliseconds - (timer->seconds * 1000 + timer->milliseconds);  // watch for wraparound
    if (!cumulative) {
        timer->seconds = (uint32_t)(now.milliseconds / 1000);
        timer->milliseconds = (uint16_t)(now.milliseconds % 1000);
    }
    return elapsed;
}
void AJ_InitTimer(AJ_Time* timer)
{
    TIME_STRUCT now;
    now.milliseconds =  millis();
    timer->seconds = (uint32_t)(now.milliseconds / 1000);
    timer->milliseconds = (uint16_t)(now.milliseconds % 1000);
}

uint64_t AJ_DecodeTime(char* der, const char* fmt)
{
    int32_t diff;

    diff = (1000 * (timerA->seconds - timerB->seconds)) + (timerA->milliseconds - timerB->milliseconds);
    return diff;
}

void AJ_TimeAddOffset(AJ_Time* timerA, uint32_t msec)
{
    uint32_t msecNew;
    if (msec == -1) {
        timerA->seconds = -1;
        timerA->milliseconds = -1;
    } else {
        msecNew = (timerA->milliseconds + msec);
        timerA->seconds = timerA->seconds + (msecNew / 1000);
        timerA->milliseconds = msecNew % 1000;
    }
}

int8_t AJ_CompareTime(AJ_Time timerA, AJ_Time timerB)
{
    if (timerA.seconds == timerB.seconds) {
        if (timerA.milliseconds == timerB.milliseconds) {
            return 0;
        } else if (timerA.milliseconds > timerB.milliseconds) {
            return 1;
        } else {
            return -1;
        }
    } else if (timerA.seconds > timerB.seconds) {
        return 1;
    } else {
        return -1;
    }
}

void* AJ_Malloc(size_t sz)
{
    return malloc(sz);
}

void* AJ_Realloc(void* ptr, size_t size)
{
    return realloc(ptr, size);
}

void AJ_Free(void* mem)
{
    if (mem) {
        free(mem);
    }
}

void ram_diag()
{
    AJ_AlwaysPrintf(("SRAM usage (stack, heap, static): %d, %d, %d\n",
                     stack_used(),
                     heap_used(),
                     static_used()));
}

uint8_t AJ_StartReadFromStdIn()
{
    return FALSE;
}

uint8_t AJ_StopReadFromStdIn()
{
    return FALSE;
}

char* AJ_GetCmdLine(char* buf, size_t num)
{
    if (Serial.available() > 0) {
        int countBytesRead;
        // read the incoming bytes until a newline character:
        countBytesRead = Serial.readBytesUntil('\n', buf, num);
        buf[countBytesRead] = '\0';
        return buf;
    } else {
        return NULL;
    }
}

uint16_t AJ_ByteSwap16(uint16_t x)
{
    return (((x) >> 8) | ((x) << 8));
}
uint32_t AJ_ByteSwap32(uint32_t x)
{
    return  (((x) >> 24) | (((x) & 0xFF0000) >> 8) | (((x) & 0x00FF00) << 8) | ((x) << 24));
}
uint64_t AJ_ByteSwap64(uint64_t x)
{
    return (((x)) >> 56) |
           (((x) & 0x00FF000000000000) >> 40) |
           (((x) & 0x0000FF0000000000) >> 24) |
           (((x) & 0x000000FF00000000) >>  8) |
           (((x) & 0x00000000FF000000) <<  8) |
           (((x) & 0x0000000000FF0000) << 24) |
           (((x) & 0x000000000000FF00) << 40) |
           (((x)) << 56);
}

/* This function conforms to the ANSII C function atoi */
int AJ_atoi(char const*inP)
{
    int out = 0;
    int sign = 1;

    /* Advance past ascii white space at beginning of string */
    while (*inP == ' ' || (*inP >= 0x09 && *inP <= 0x0d)) {
        inP++;
    }

    /* Allow a Sign indication */
    if (*inP == '-') {
        inP++;
        sign = -1;
    } else if (*inP == '+') {
        inP++;
    }

    /* Accept all contiguous digits between 0-9 */
    while (*inP >= '0' && *inP <= '9') {
        out = (out * 10) + (*inP - '0');
        inP++;
    }

    out *= sign;

    return out;
}

#ifndef NDEBUG

uint8_t dbgCONFIGUREME = 0;
uint8_t dbgNET = 0;
uint8_t dbgTARGET_CRYPTO = 0;
uint8_t dbgTARGET_NVRAM = 0;
uint8_t dbgTARGET_UTIL = 0;

int _AJ_DbgEnabled(const char* module)
{
    return FALSE;
}

#endif
