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
#ifndef _LSF_SEMAPHORE_H_
#define _LSF_SEMAPHORE_H_
/**
 * \ingroup Common
 */
/**
 * \file  common/inc/LSFSemaphore.h
 * This file provides definitions for LSF semaphore
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
#include <semaphore.h>
#include <stdint.h>
#include <Mutex.h>

namespace lsf {

/**
 * Class that implements a Semaphore \n
 * Use a semaphore when some thread wants to sleep until some other thread tells it to wake up
 */
class LSFSemaphore {
  public:

    /**
     * Constructor
     */
    LSFSemaphore();

    /**
     * Destrctor
     */
    ~LSFSemaphore();

    /**
     * Wait on a Semaphore
     */
    void Wait(void);

    /**
     * Post to a Semaphore
     */
    void Post(void);

  private:

    /**
     * Mutex associated with the Semaphore
     */
    sem_t mutex;
};


}

#endif
