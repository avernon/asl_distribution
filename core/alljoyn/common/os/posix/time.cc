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

#include <time.h>
#include <stdio.h>

#include <qcc/time.h>

#if defined(QCC_OS_DARWIN)

#include <sys/time.h>
#include <mach/mach_time.h>
#include <mach/clock.h>
#include <mach/mach.h>

#endif

using namespace qcc;

static void platform_gettime(struct timespec* ts, bool useMonotonic)
{
#if defined(QCC_OS_DARWIN)
    clock_serv_t cclock;
    mach_timespec_t mts;
    host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
    clock_get_time(cclock, &mts);
    mach_port_deallocate(mach_task_self(), cclock);
    ts->tv_sec = mts.tv_sec;
    ts->tv_nsec = mts.tv_nsec;
#else
    clock_gettime(useMonotonic ? CLOCK_MONOTONIC : CLOCK_REALTIME, ts);
#endif
}

static time_t s_clockOffset = 0;

uint32_t qcc::GetTimestamp(void)
{
    struct timespec ts;
    uint32_t ret_val;

    platform_gettime(&ts, true);

    if (0 == s_clockOffset) {
        s_clockOffset = ts.tv_sec;
    }

    ret_val = ((uint32_t)(ts.tv_sec - s_clockOffset)) * 1000;
    ret_val += (uint32_t)ts.tv_nsec / 1000000;

    return ret_val;
}

uint64_t qcc::GetTimestamp64(void)
{
    struct timespec ts;
    uint64_t ret_val;

    platform_gettime(&ts, true);

    if (0 == s_clockOffset) {
        s_clockOffset = ts.tv_sec;
    }

    ret_val = ((uint64_t)(ts.tv_sec - s_clockOffset)) * 1000;
    ret_val += (uint64_t)ts.tv_nsec / 1000000;

    return ret_val;
}

uint64_t qcc::GetEpochTimestamp(void)
{
    struct timespec ts;
    uint64_t ret_val;

    platform_gettime(&ts, false);

    ret_val = ((uint64_t)(ts.tv_sec)) * 1000;
    ret_val += (uint64_t)ts.tv_nsec / 1000000;

    return ret_val;
}

void qcc::GetTimeNow(Timespec<MonotonicTime>* ts)
{
    struct timespec _ts;
    platform_gettime(&_ts, true);
    ts->seconds = _ts.tv_sec;
    ts->mseconds = _ts.tv_nsec / 1000000;
}

qcc::String qcc::UTCTime()
{
    static const char* Day[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
    static const char* Month[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
    char buf[32];
    time_t t;
    time(&t);
    struct tm utc;
    gmtime_r(&t, &utc);
    snprintf(buf, 32, "%s, %02d %s %04d %02d:%02d:%02d GMT",
             Day[utc.tm_wday],
             utc.tm_mday,
             Month[utc.tm_mon],
             1900 + utc.tm_year,
             utc.tm_hour,
             utc.tm_min,
             utc.tm_sec);

    return buf;
}

int64_t qcc::ConvertStructureToTime(struct tm* timeptr)
{
    return mktime(timeptr);
}

QStatus qcc::ConvertTimeToStructure(const int64_t* timer, struct tm* tm) {
    if (gmtime_r((time_t*)timer, tm)) {
        return ER_OK;
    }
    return ER_FAIL;
}

QStatus qcc::ConvertToLocalTime(const int64_t* timer, struct tm* tm) {
    if (localtime_r((time_t*)timer, tm)) {
        return ER_OK;
    }
    return ER_FAIL;
}

size_t qcc::FormatTime(char* strDest, size_t maxSize, const char* format, const struct tm* timeptr)
{
    return strftime(strDest, maxSize, format, timeptr);
}
