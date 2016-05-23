/**
 * @file
 * SessionListener is an abstract base class (interface) implemented by users of the
 * AllJoyn API in order to receive sessions related event information.
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
#ifndef _ALLJOYN_SESSIONLISTENER_H
#define _ALLJOYN_SESSIONLISTENER_H

#ifndef __cplusplus
#error Only include SessionListener.h in C++ code.
#endif

#include <alljoyn/Session.h>

namespace ajn {

/**
 * Abstract base class implemented by AllJoyn users and called by AllJoyn to inform
 * users of session related events.
 */
class SessionListener {
  public:

    /** Reason for the session being lost */
    typedef enum {
        ALLJOYN_SESSIONLOST_INVALID                      = 0x00, /**< Invalid */
        ALLJOYN_SESSIONLOST_REMOTE_END_LEFT_SESSION      = 0x01, /**< Remote end called LeaveSession */
        ALLJOYN_SESSIONLOST_REMOTE_END_CLOSED_ABRUPTLY   = 0x02, /**< Remote end closed abruptly */
        ALLJOYN_SESSIONLOST_REMOVED_BY_BINDER            = 0x03, /**< Session binder removed this endpoint by calling RemoveSessionMember */
        ALLJOYN_SESSIONLOST_LINK_TIMEOUT                 = 0x04, /**< Link was timed-out */
        ALLJOYN_SESSIONLOST_REASON_OTHER                 = 0x05 /**< Unspecified reason for session loss */
    } SessionLostReason;

    /**
     * Virtual destructor for derivable class.
     */
    virtual ~SessionListener() { }

    /**
     * Called by the bus when an existing session becomes disconnected. (Deprecated)
     * @deprecated
     *
     * @see SessionLost(SessionId sessionId, SessionLostReason reason)
     *
     * @param sessionId     Id of session that was lost.
     */
    virtual void SessionLost(SessionId sessionId) { };

    /**
     * Called by the bus when an existing session becomes disconnected.
     *
     * @param sessionId     Id of session that was lost.
     * @param reason        The reason for the session being lost
     */
    virtual void SessionLost(SessionId sessionId, SessionLostReason reason) { }

    /**
     * Called by the bus when a member of a multipoint session is added.
     *
     * @param sessionId     Id of session whose member(s) changed.
     * @param uniqueName    Unique name of member who was added.
     */
    virtual void SessionMemberAdded(SessionId sessionId, const char* uniqueName) { }

    /**
     * Called by the bus when a member of a multipoint session is removed.
     *
     * @param sessionId     Id of session whose member(s) changed.
     * @param uniqueName    Unique name of member who was removed.
     */
    virtual void SessionMemberRemoved(SessionId sessionId, const char* uniqueName) { }
};

}

#endif
