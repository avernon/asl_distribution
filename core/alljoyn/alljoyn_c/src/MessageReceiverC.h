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
/**
 * @file
 * MessageReceiverC is an implementation of the MessagReceiver base class responsible
 * for mapping a C++ style MessageReceiver to a C style alljoyn_messagereceiver
 * function pointer
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
#ifndef _ALLJOYN_C_MESSAGERECEIVERC_H
#define _ALLJOYN_C_MESSAGERECEIVERC_H

#include <alljoyn/MessageReceiver.h>

namespace ajn {
/*
 * When setting up a asynchronous method call a  callback handler for C
 * alljoyn_messagereceiver_replyhandler_ptr function pointer will be passed in as
 * the callback handler.  AllJoyn expects a MessageReceiver::ReplyHandler method
 * handler.  The function handler will be passed as the part of the void*
 * context that is passed to the internal callback handler and will then be used
 * to map the internal callback handler to the user defined
 * messagereceived_replyhandler callback function pointer.
 */
class MessageReceiverReplyHandlerCallbackContext {
  public:
    MessageReceiverReplyHandlerCallbackContext(alljoyn_messagereceiver_replyhandler_ptr replyhandler_ptr, void* context) :
        replyhandler_ptr(replyhandler_ptr), context(context) { }

    alljoyn_messagereceiver_replyhandler_ptr replyhandler_ptr;
    void* context;
};

class MessageReceiverC : public MessageReceiver {
  public:
    void ReplyHandler(ajn::Message& message, void* context)
    {
        /*
         * The replyhandler_ptr in the context pointer is allocated as part
         * of the alljoyn_proxybusobject_methodcallasync function call or the
         * alljoyn_proxybusobject_methodcallasync_member function call.
         * Once the function alljoyn_messagereceiver_replyhandler_ptr has been
         * called the MessageReceiverReplyHandlerCallbackContext instance must
         * be deleted or it will result in a memory leak.
         */
        MessageReceiverReplyHandlerCallbackContext* in = (MessageReceiverReplyHandlerCallbackContext*)context;
        (in->replyhandler_ptr)((alljoyn_message) & message, in->context);
        in->replyhandler_ptr = NULL;
        delete in;
    }
};
}

#endif
