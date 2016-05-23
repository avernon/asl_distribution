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
#ifndef _ALARM_H_
#define _ALARM_H_
/**
 * \defgroup Common
 * Common code to client and server controller
 */
/**
 * \ingroup Common
 */
/**
 * \file  common/inc/Alarm.h
 * This file provides definitions for alarm infrastructure
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


#include <Thread.h>
#include <LSFSemaphore.h>
#include <signal.h>

#include <alljoyn/Status.h>

namespace lsf {

/**
 * An alarm listener is capable of receiving alarm callbacks
 */
class AlarmListener {

  public:
    /**
     * Virtual destructor for derivable class
     */
    virtual ~AlarmListener() { }

    /**
     * Invoked when an alarm is triggered
     */
    virtual void AlarmTriggered(void) = 0;
};

/**
 * Class used to implement an Alarm that is
 * capable of handling time in seconds.
 */
class Alarm : public Thread {
  public:

    /**
     * Contructor that accepts an alarmListener
     */
    Alarm(AlarmListener* alarmListener);

    /**
     * Destructor
     */
    ~Alarm();

    /**
     * Set an Alarm
     *
     * @param timeInSecs Alarm time in seconds
     */
    void SetAlarm(uint8_t timeInSecs);

    /**
     * Start the Alarm thread
     */
    void Run(void);

    /**
     * Stop the Alarm thread
     */
    void Stop(void);

    /**
     * Join the Alarm thread
     */
    void Join(void);

  private:

    /*
     * Indicates if the Alarm thread is running
     */
    volatile sig_atomic_t isRunning;

    /*
     * Alarm Listener
     */
    AlarmListener* alarmListener;

    /*
     * Internal variable used to track progress in time
     */
    volatile sig_atomic_t progressInTime;

    /*
     * Internal holder of the Alarm time
     */
    volatile sig_atomic_t timeToTrack;

    /*
     * Indicates if the Alarm time is reset
     */
    volatile sig_atomic_t alarmReset;
};

}


#endif
