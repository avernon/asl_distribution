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
#ifndef _MUTEX_H_
#define _MUTEX_H_
/**
 * \ingroup Common
 */
/**
 * \file  common/inc/Mutex.h
 * This file provides definitions for mutex
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
/**
 * \ingroup Common
 */
#include <pthread.h>
#include <errno.h>
#include <alljoyn/Status.h>

namespace lsf {
/**
 * a wrapper class to mutex. \n
 * Use a mutex when thread wants to execute code that should not be executed by any other thread at the same time. \n
 * Mutex 'down' happens in one thread and mutex 'up' must happen in the same thread later on. \n
 */
class Mutex {
  public:
    /**
     * Mutex constructor
     */
    Mutex();
    /**
     * Mutex destructor
     */
    ~Mutex();
    /**
     * Lock mutex
     */
    QStatus Lock();
    /**
     * Unlock mutex
     */
    QStatus Unlock();
    /**
     * Get mutex object
     */
    pthread_mutex_t* GetMutex() { return &mutex; }

  private:

    pthread_mutex_t mutex;

};

}

#endif
