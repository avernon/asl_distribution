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

#include <Alarm.h>
#include <qcc/Debug.h>

using namespace lsf;

#define QCC_MODULE "LSF_ALARM"

Alarm::Alarm(AlarmListener* alarmListener) :
    isRunning(true),
    alarmListener(alarmListener),
    progressInTime(0),
    timeToTrack(0),
    alarmReset(false)
{
    QCC_DbgPrintf(("%s", __func__));
    Thread::Start();
}

Alarm::~Alarm()
{
    QCC_DbgPrintf(("%s", __func__));
}

void Alarm::Run()
{
    QCC_DbgPrintf(("%s", __func__));

    while (isRunning) {
        QCC_DbgPrintf(("%s", __func__));
        usleep(1000000);
        if (alarmReset) {
            QCC_DbgPrintf(("%s: Alarm Reloaded", __func__));
            progressInTime = 0;
            alarmReset = false;
        } else {
            if (timeToTrack) {
                progressInTime++;
                if (progressInTime == timeToTrack) {
                    QCC_DbgPrintf(("%s: Calling AlarmTriggered", __func__));
                    progressInTime = 0;
                    timeToTrack = 0;
                    alarmListener->AlarmTriggered();
                }
            }
        }
    }
}

void Alarm::Join()
{
    QCC_DbgPrintf(("%s", __func__));
    Thread::Join();
}

void Alarm::Stop()
{
    isRunning = false;
    progressInTime = 0;
    timeToTrack = 0;
    alarmReset = false;
}

void Alarm::SetAlarm(uint8_t timeInSecs)
{
    timeToTrack = timeInSecs;
    alarmReset = true;
}
