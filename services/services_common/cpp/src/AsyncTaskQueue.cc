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

#include "alljoyn/services_common/AsyncTaskQueue.h"
#include <pthread.h>
#include <queue>

using namespace ajn;
using namespace services;

TaskData::~TaskData() {

}

AsyncTaskQueue::AsyncTaskQueue(AsyncTask* asyncTask, bool ownersheap) :
    m_IsStopping(true), m_AsyncTask(asyncTask), m_ownersheap(ownersheap)
{

}

AsyncTaskQueue::~AsyncTaskQueue()
{

}

void AsyncTaskQueue::Enqueue(TaskData const* taskdata)
{
    pthread_mutex_lock(&m_Lock);
    m_MessageQueue.push(taskdata);
    pthread_cond_signal(&m_QueueChanged);
    pthread_mutex_unlock(&m_Lock);
}

void AsyncTaskQueue::Start()
{
    if (!m_IsStopping) {
        return;
    }

    m_IsStopping = false;

    pthread_mutex_init(&m_Lock, NULL);
    pthread_cond_init(&m_QueueChanged, NULL);
    pthread_create(&m_Thread, NULL, ReceiverThreadWrapper, this);
}

void AsyncTaskQueue::Stop()
{
    if (m_IsStopping) {
        return;
    }

    pthread_mutex_lock(&m_Lock);
    while (!m_MessageQueue.empty()) {
        m_MessageQueue.pop();
    }
    m_IsStopping = true;
    pthread_cond_signal(&m_QueueChanged);
    pthread_mutex_unlock(&m_Lock);
    pthread_join(m_Thread, NULL);

    pthread_cond_destroy(&m_QueueChanged);
    pthread_mutex_destroy(&m_Lock);
}

void* AsyncTaskQueue::ReceiverThreadWrapper(void* context)
{
    AsyncTaskQueue* asyncTask = reinterpret_cast<AsyncTaskQueue*>(context);
    if (asyncTask == NULL) { // should not happen
        return NULL;
    }
    asyncTask->Receiver();
    return NULL;
}

void AsyncTaskQueue::Receiver()
{
    pthread_mutex_lock(&m_Lock);
    while (!m_IsStopping) {
        while (!m_MessageQueue.empty()) {
            TaskData const* taskData = m_MessageQueue.front();
            m_MessageQueue.pop();
            pthread_mutex_unlock(&m_Lock);
            m_AsyncTask->OnTask(taskData);
            if (m_ownersheap) {
                delete taskData;
            }
            pthread_mutex_lock(&m_Lock);
        }
        m_AsyncTask->OnEmptyQueue();
        pthread_cond_wait(&m_QueueChanged, &m_Lock);
    }
    pthread_mutex_unlock(&m_Lock);
}

