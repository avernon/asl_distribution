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
#ifndef _THREAD_H_
#define _THREAD_H_
/**
 * \ingroup Common
 */
/**
 * \file  common/inc/Thread.h
 * This file provides definitions for thread infrastructure
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

#include <alljoyn/Status.h>

namespace lsf {
/**
 * abstraction class to thread
 */
class Thread {
  public:
    /**
     * class constructor
     */
    Thread();
    /**
     * class destructor
     */
    virtual ~Thread();
    /**
     * This method is been called by the created thread after start()
     */
    virtual void Run() = 0;
    /**
     * Stop running thread.  \n
     * Can be implemented by changing a variable value that is shared with the run() method.  \n
     * This will release the thread.  \n
     */
    virtual void Stop() = 0;
    /**
     * Create and run new thread
     */
    QStatus Start();
    /**
     * Join running thread until it exits
     */
    void Join();

  private:

    static void* RunThread(void* data);

    pthread_t thread;
};

}


#endif
