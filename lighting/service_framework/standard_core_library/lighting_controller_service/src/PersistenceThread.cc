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

#include <qcc/Debug.h>

#ifdef LSF_BINDINGS
#include <lsf/controllerservice/PersistenceThread.h>
#include <lsf/controllerservice/ControllerService.h>
#else
#include <PersistenceThread.h>
#include <ControllerService.h>
#endif

using namespace lsf;

#ifdef LSF_BINDINGS
using namespace controllerservice;
#endif

#define QCC_MODULE "PERSISTED_THREAD"

PersistenceThread::PersistenceThread(ControllerService& service)
    : service(service),
    running(true)
{
    QCC_DbgTrace(("%s", __func__));
}

PersistenceThread::~PersistenceThread()
{
    QCC_DbgTrace(("%s", __func__));
}


void PersistenceThread::Run()
{
    QCC_DbgTrace(("%s", __func__));
    while (running) {
        // wait!
        semaphore.Wait();

        if (running) {
            service.GetLampGroupManager().ReadWriteFile();
            service.GetMasterSceneManager().ReadWriteFile();
            service.GetPresetManager().ReadWriteFile();
            service.GetSceneElementManager().ReadWriteFile();
            service.GetSceneManager().ReadWriteFile();
            service.GetTransitionEffectManager().ReadWriteFile();
            service.GetPulseEffectManager().ReadWriteFile();
            service.GetUnknownBlobGroupManager().ReadWriteFile();
        }
    }
    QCC_DbgPrintf(("%s: Exited", __func__));
}

void PersistenceThread::SignalReadWrite()
{
    QCC_DbgTrace(("%s", __func__));
    // signal
    semaphore.Post();
}

void PersistenceThread::Stop()
{
    QCC_DbgTrace(("%s", __func__));
    running = false;
    SignalReadWrite();
}

void PersistenceThread::Join()
{
    QCC_DbgTrace(("%s", __func__));
    Thread::Join();
}

