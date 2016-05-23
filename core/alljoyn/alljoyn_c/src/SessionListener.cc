/**
 * @file
 * This implements the C accessable version of the SessionListener class using
 * function pointers, and a pass-through implementation of SessionListener.
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

#include <alljoyn/SessionListener.h>
#include <alljoyn_c/SessionListener.h>
#include <string.h>
#include <assert.h>
#include "DeferredCallback.h"
#include <qcc/Debug.h>

#define QCC_MODULE "ALLJOYN_C"

namespace ajn {

/**
 * Abstract base class implemented by AllJoyn users and called by AllJoyn to inform
 * users of session related events.
 */
class SessionListenerCallbackC : public SessionListener {
  public:
    SessionListenerCallbackC(const alljoyn_sessionlistener_callbacks* in_callbacks, const void* in_context)
    {
        QCC_DbgTrace(("%s", __FUNCTION__));
        memcpy(&callbacks, in_callbacks, sizeof(alljoyn_sessionlistener_callbacks));
        context = in_context;
    }

    virtual void SessionLost(SessionId sessionId, SessionLostReason reason)
    {
        QCC_DbgTrace(("%s", __FUNCTION__));
        if (callbacks.session_lost != NULL) {
            if (!DeferredCallback::sMainThreadCallbacksOnly) {
                callbacks.session_lost(context, sessionId, static_cast<alljoyn_sessionlostreason>(reason));
            } else {
                DeferredCallback_3<void, const void*, SessionId, alljoyn_sessionlostreason>* dcb =
                    new DeferredCallback_3<void, const void*, SessionId, alljoyn_sessionlostreason>(callbacks.session_lost, context, sessionId, static_cast<alljoyn_sessionlostreason>(reason));
                DEFERRED_CALLBACK_EXECUTE(dcb);
            }
        }
    }

    virtual void SessionMemberAdded(SessionId sessionId, const char* uniqueName)
    {
        QCC_DbgTrace(("%s", __FUNCTION__));
        if (callbacks.session_member_added != NULL) {
            if (!DeferredCallback::sMainThreadCallbacksOnly) {
                callbacks.session_member_added(context, sessionId, uniqueName);
            } else {
                DeferredCallback_3<void, const void*, SessionId, const char*>* dcb =
                    new DeferredCallback_3<void, const void*, SessionId, const char*>(callbacks.session_member_added, context, sessionId, uniqueName);
                DEFERRED_CALLBACK_EXECUTE(dcb);
            }
        }
    }

    virtual void SessionMemberRemoved(SessionId sessionId, const char* uniqueName)
    {
        QCC_DbgTrace(("%s", __FUNCTION__));
        if (callbacks.session_member_removed != NULL) {
            if (!DeferredCallback::sMainThreadCallbacksOnly) {
                callbacks.session_member_removed(context, sessionId, uniqueName);
            } else {
                DeferredCallback_3<void, const void*, SessionId, const char*>* dcb =
                    new DeferredCallback_3<void, const void*, SessionId, const char*>(callbacks.session_member_removed, context, sessionId, uniqueName);
                DEFERRED_CALLBACK_EXECUTE(dcb);
            }
        }
    }
  protected:
    alljoyn_sessionlistener_callbacks callbacks;
    const void* context;
};

}

struct _alljoyn_sessionlistener_handle {
    /* Empty by design, this is just to allow the type restrictions to save coders from themselves */
};

alljoyn_sessionlistener alljoyn_sessionlistener_create(const alljoyn_sessionlistener_callbacks* callbacks, const void* context)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return (alljoyn_sessionlistener) new ajn::SessionListenerCallbackC(callbacks, context);
}

void alljoyn_sessionlistener_destroy(alljoyn_sessionlistener listener)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    assert(listener != NULL && "listener parameter must not be NULL");
    delete (ajn::SessionListenerCallbackC*)listener;
}
