/**
 * @file
 *
 * Platform specific header files that defines time related functions
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
#include <qcc/platform.h>

#include <windows.h>
#include <sys/timeb.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <qcc/time.h>

uint32_t qcc::GetTimestamp(void)
{
    static uint32_t base = 0;
    struct _timeb timebuffer;
    uint32_t ret_val;

    _ftime(&timebuffer);

    ret_val = ((uint32_t)timebuffer.time) * 1000;
    ret_val += timebuffer.millitm;

#ifdef RANDOM_TIMESTAMPS
    /*
     * Randomize time base
     */
    while (!base) {
        srand(ret_val);
        base = rand() | (rand() << 16);
    }
#endif

    return ret_val + base;
}

uint64_t qcc::GetTimestamp64(void)
{
    static uint32_t base = 0;
    struct _timeb timebuffer;
    uint64_t ret_val;

    _ftime(&timebuffer);

    ret_val = ((uint64_t)timebuffer.time) * 1000;
    ret_val += timebuffer.millitm;

#ifdef RANDOM_TIMESTAMPS
    /*
     * Randomize time base
     */
    while (!base) {
        srand(ret_val);
        base = rand() | (rand() << 16);
    }
#endif

    return ret_val + base;
}

uint64_t qcc::GetEpochTimestamp(void)
{
    return GetTimestamp64();
}

void qcc::GetTimeNow(Timespec<MonotonicTime>* ts)
{
    struct _timeb timebuffer;

    _ftime(&timebuffer);

    ts->seconds = timebuffer.time;
    ts->mseconds = timebuffer.millitm;
}

qcc::String qcc::UTCTime()
{
    static const char* Day[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
    static const char* Month[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
    char buf[32];
    SYSTEMTIME systime;
    GetSystemTime(&systime);
    snprintf(buf, 32, "%s, %02d %s %04d %02d:%02d:%02d GMT",
             Day[systime.wDayOfWeek],
             systime.wDay,
             Month[systime.wMonth - 1],
             systime.wYear,
             systime.wHour,
             systime.wMinute,
             systime.wSecond);

    return buf;
}

int64_t qcc::ConvertStructureToTime(struct tm* timeptr)
{
    return _mktime64(timeptr);
}

QStatus qcc::ConvertTimeToStructure(const int64_t* timer, struct tm* tm) {
    if (_gmtime64_s(tm, (__time64_t*)timer) == 0) {
        return ER_OK;
    }
    return ER_FAIL;
}

QStatus qcc::ConvertToLocalTime(const int64_t* timer, struct tm* tm) {
    if (_localtime64_s(tm, (__time64_t*)timer) == 0) {
        return ER_OK;
    }
    return ER_FAIL;
}

size_t qcc::FormatTime(char* strDest, size_t maxSize, const char* format, const struct tm* timeptr)
{
    return strftime(strDest, maxSize, format, timeptr);
}
