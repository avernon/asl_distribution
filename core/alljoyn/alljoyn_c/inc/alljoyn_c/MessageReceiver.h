/**
 * @file
 * MessageReceiver is a base class implemented by any class
 * which wishes to receive AllJoyn messages
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
#ifndef _ALLJOYN_C_MESSAGERECEIVER_H
#define _ALLJOYN_C_MESSAGERECEIVER_H

#include <qcc/platform.h>
#include <alljoyn_c/AjAPI.h>
#include <alljoyn_c/Message.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ALLJOYN_OPAQUE_BUSOBJECT_
#define _ALLJOYN_OPAQUE_BUSOBJECT_
/**
 * Message bus object
 */
typedef struct _alljoyn_busobject_handle*                   alljoyn_busobject;
#endif

/**
 * MethodHandlers are %MessageReceiver functions which are called by AllJoyn library
 * to forward AllJoyn method_calls to AllJoyn library users.
 *
 * @param bus       The bus object triggering this callback.
 * @param member    Method interface member entry.
 * @param message   The received method call message.
 */
typedef void (*alljoyn_messagereceiver_methodhandler_ptr)(alljoyn_busobject bus,
                                                          const alljoyn_interfacedescription_member* member,
                                                          alljoyn_message message);

/**
 * ReplyHandlers are %MessageReceiver functions which are called by AllJoyn library
 * to forward AllJoyn method_reply and error responses to AllJoyn library users.
 *
 * @param message   The received message.
 * @param context   User-defined context passed to MethodCall and returned upon reply.
 */
typedef void (*alljoyn_messagereceiver_replyhandler_ptr)(alljoyn_message message, void* context);

/**
 * SignalHandlers are %MessageReceiver functions which are called by AllJoyn library
 * to forward AllJoyn received signals to AllJoyn library users.
 *
 * @param member    Method or signal interface member entry.
 * @param srcPath   Object path of signal emitter.
 * @param message   The received message.
 */
typedef void (*alljoyn_messagereceiver_signalhandler_ptr)(const alljoyn_interfacedescription_member* member,
                                                          const char* srcPath, alljoyn_message message);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
