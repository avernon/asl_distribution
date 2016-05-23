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

#include "DeferredCallback.h"
#include <qcc/Debug.h>

#define QCC_MODULE "ALLJOYN_C"

namespace ajn {
bool DeferredCallback::initilized = false;
std::list<DeferredCallback*> DeferredCallback::sPendingCallbacks;
qcc::Thread* DeferredCallback::sMainThread = NULL;
bool DeferredCallback::sMainThreadCallbacksOnly = false;
qcc::Mutex DeferredCallback::sCallbackListLock;

}

int alljoyn_unity_deferred_callbacks_process()
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return ajn::DeferredCallback::TriggerCallbacks();
}

void alljoyn_unity_set_deferred_callback_mainthread_only(QCC_BOOL mainthread_only)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    ajn::DeferredCallback::sMainThreadCallbacksOnly = (mainthread_only == QCC_TRUE ? true : false);
}
