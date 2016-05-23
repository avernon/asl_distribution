/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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


#ifndef ASYNC_TASK_QUEUE_H_
#define ASYNC_TASK_QUEUE_H_

#include <pthread.h>
#include <queue>

namespace ajn {
namespace services {

/**
 * class TaskData
 * Base class to represent message
 */

class TaskData {
  public:
    virtual ~TaskData();
};

/**
 * class AsyncTask
 * User must derived from this class and implement its virtual functions
 */

class AsyncTask {
  public:
    AsyncTask() { }
    virtual ~AsyncTask() { };
    /**
     * OnEmptyQueue - handling 'queue become empty' events.
     */
    virtual void OnEmptyQueue() = 0;
    /**
     * OnEmptyQueue - handling 'queue got new message' events.
     *  @param taskdata - pointer to the data that currently processed.
     */
    virtual void OnTask(TaskData const* taskdata) = 0;
};

/**
 * class FeedbackAsyncTask provides option to process asynchronous tasks
 */
class AsyncTaskQueue {
  public:
    /**
     * AsyncTaskQueue constructor
     *  @param asyncTask - pointer to the class which callbacks will be called.
     *  @param ownersheap - if true, the queue will delete the data after calling to callbacks.
     */
    AsyncTaskQueue(AsyncTask* asyncTask, bool ownersheap = true);
    /**
     * AsyncTaskQueue destructor
     */
    ~AsyncTaskQueue();
    /**
     * Start
     */
    void Start();
    /**
     * Stop
     */
    void Stop();
    /**
     * Enqueue data
     */
    void Enqueue(TaskData const* taskdata);
  private:
    /**
     * The thread responsible for receiving messages
     */
    pthread_t m_Thread;

    /**
     * A Queue that holds the messages
     */
    std::queue<TaskData const*> m_MessageQueue;

    /**
     * The mutex Lock
     */
    pthread_mutex_t m_Lock;

    /**
     * The Queue Changed thread condition
     */
    pthread_cond_t m_QueueChanged;

    /**
     * is the thread in the process of shutting down
     */
    bool m_IsStopping;

    /**
     * A wrapper for the receiver Thread
     * @param context
     */
    static void* ReceiverThreadWrapper(void* context);

    /**
     * The function run in the Receiver
     */
    void Receiver();

    /**
     * class to report about events to the client
     */
    AsyncTask* m_AsyncTask;

    /**
     * is the thread is the owner of the objects in the queue and those will delete them.
     */
    bool m_ownersheap;
};

} //namespace services
} //namespace ajn




#endif /* ASYNC_TASK_QUEUE_H_ */
