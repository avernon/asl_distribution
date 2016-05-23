/**
 * @file
 * alljoyn_sessionportlistener is a collection of functions implemented by users
 * of the AllJoyn API in order to receive session port related event information.
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
#ifndef _ALLJOYN_C_SESSIONPORTLISTENER_H
#define _ALLJOYN_C_SESSIONPORTLISTENER_H

#include <alljoyn_c/AjAPI.h>
#include <alljoyn_c/Session.h>
#include <alljoyn_c/SessionListener.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * alljoyn_sessionportlistener is an abstract interface implemented by users of the
 * AllJoyn API in order to receive session port related event information.
 */
typedef struct _alljoyn_sessionportlistener_handle*         alljoyn_sessionportlistener;

/**
 * Type for the AcceptSessionJoiner callback.

 * Accept or reject an incoming JoinSession request. The session does not exist until
 * after this function returns.
 *
 * This callback is only used by session creators. Therefore it is only called on listeners
 * passed to alljoyn_busattachment_bindsessionport.
 *
 * @param context        the context pointer that was passed to alljoyn_sessionportlistener_create
 * @param sessionPort    Session port that was joined.
 * @param joiner         Unique name of potential joiner.
 * @param opts           Session options requested by the joiner.
 * @return   Return true if JoinSession request is accepted. false if rejected.
 */
typedef QCC_BOOL (*alljoyn_sessionportlistener_acceptsessionjoiner_ptr)(const void* context, alljoyn_sessionport sessionPort,
                                                                        const char* joiner,  const alljoyn_sessionopts opts);

/**
 * Type for the SessionJoined callback.
 *
 * Called by the bus when a session has been successfully joined. The session is now fully up.
 *
 * This callback is only used by session creators. Therefore it is only called on the alljoyn_sessionportlistener_callbacks
 * passed in when calling alljoyn_busattachment_bindsessionport.
 *
 * @param context        the context pointer that was passed to alljoyn_sessionportlistener_create
 * @param sessionPort    Session port that was joined.
 * @param id             Id of session.
 * @param joiner         Unique name of the joiner.
 */
typedef void (*alljoyn_sessionportlistener_sessionjoined_ptr)(const void* context, alljoyn_sessionport sessionPort,
                                                              alljoyn_sessionid id, const char* joiner);

/**
 * Structure used during alljoyn_sessionportlistener_create to provide callbacks into C.
 */
typedef struct {
    /**
     * Accept or reject an incoming JoinSession request. The session does not
     * exist until this after this function returns.
     */
    alljoyn_sessionportlistener_acceptsessionjoiner_ptr accept_session_joiner;
    /**
     * Called by the bus when a session has been successfully joined. The session
     * is now fully up.
     */
    alljoyn_sessionportlistener_sessionjoined_ptr session_joined;
} alljoyn_sessionportlistener_callbacks;

/**
 * Create an alljoyn_sessionportlistener which will trigger the provided callbacks, passing along the provided context.
 *
 * @param callbacks Callbacks to trigger for associated events.
 * @param context   Context to pass to callback functions
 *
 * @return Handle to newly allocated alljoyn_sessionportlistener.
 */
extern AJ_API alljoyn_sessionportlistener alljoyn_sessionportlistener_create(const alljoyn_sessionportlistener_callbacks* callbacks,
                                                                             const void* context);

/**
 * Destroy an alljoyn_sessionportlistener.
 *
 * @param listener alljoyn_sessionportlistener to destroy.
 */
extern AJ_API void alljoyn_sessionportlistener_destroy(alljoyn_sessionportlistener listener);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
