/**
 * @file
 *
 * This file implements the _Message class
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

#include <qcc/platform.h>

#include <assert.h>
#include <ctype.h>

#include <alljoyn/Message.h>
#include "BusAttachmentC.h"
#include "MsgArgC.h"
#include <alljoyn_c/Message.h>
#include <alljoyn_c/BusAttachment.h>
#include <qcc/Debug.h>

#define QCC_MODULE "ALLJOYN_C"

struct _alljoyn_message_handle {
    _alljoyn_message_handle(ajn::BusAttachmentC& bus) : msg(bus) { }
    ajn::Message msg;
};

alljoyn_message alljoyn_message_create(alljoyn_busattachment bus)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return new struct _alljoyn_message_handle (*((ajn::BusAttachmentC*)bus));
}

void alljoyn_message_destroy(alljoyn_message msg)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    delete msg;
}

QCC_BOOL alljoyn_message_isbroadcastsignal(alljoyn_message msg)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return msg->msg->IsBroadcastSignal();
}

QCC_BOOL alljoyn_message_isglobalbroadcast(alljoyn_message msg)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return msg->msg->IsGlobalBroadcast();
}

QCC_BOOL alljoyn_message_issessionless(alljoyn_message msg)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return msg->msg->IsSessionless();
}

uint8_t alljoyn_message_getflags(alljoyn_message msg)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return msg->msg->GetFlags();
}

QCC_BOOL alljoyn_message_isexpired(alljoyn_message msg, uint32_t* tillExpireMS)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return msg->msg->IsExpired(tillExpireMS);
}

QCC_BOOL alljoyn_message_isunreliable(alljoyn_message msg)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return msg->msg->IsUnreliable();
}

QCC_BOOL alljoyn_message_isencrypted(alljoyn_message msg)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return msg->msg->IsEncrypted();
}

const char* alljoyn_message_getauthmechanism(alljoyn_message msg)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return msg->msg->GetAuthMechanism().c_str();
}

alljoyn_messagetype alljoyn_message_gettype(alljoyn_message msg)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return (alljoyn_messagetype)msg->msg->GetType();
}

void alljoyn_message_getargs(alljoyn_message msg, size_t* numArgs, alljoyn_msgarg* args)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    const ajn::MsgArg* tmpArgs;
    msg->msg->GetArgs(*numArgs, tmpArgs);
    *args = (alljoyn_msgarg)tmpArgs;
}

const alljoyn_msgarg alljoyn_message_getarg(alljoyn_message msg, size_t argN)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return (alljoyn_msgarg)msg->msg->GetArg(argN);
}

QStatus alljoyn_message_parseargs(alljoyn_message msg, const char* signature, ...)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    size_t sigLen = (signature ? strlen(signature) : 0);
    if (sigLen == 0) {
        return ER_BAD_ARG_2;
    }
    const ajn::MsgArg* msgArgs;
    size_t numMsgArgs;

    msg->msg->GetArgs(numMsgArgs, msgArgs);

    va_list argp;
    va_start(argp, signature);
    QStatus status = ajn::MsgArgC::VParseArgsC(signature, sigLen, msgArgs, numMsgArgs, &argp);
    va_end(argp);
    return status;
}

uint32_t alljoyn_message_getcallserial(alljoyn_message msg)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return msg->msg->GetCallSerial();
}

const char* alljoyn_message_getsignature(alljoyn_message msg)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return msg->msg->GetSignature();
}

const char* alljoyn_message_getobjectpath(alljoyn_message msg)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return msg->msg->GetObjectPath();
}

const char* alljoyn_message_getinterface(alljoyn_message msg)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return msg->msg->GetInterface();
}

const char* alljoyn_message_getmembername(alljoyn_message msg)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return msg->msg->GetMemberName();
}

uint32_t alljoyn_message_getreplyserial(alljoyn_message msg)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return msg->msg->GetReplySerial();
}

const char* alljoyn_message_getsender(alljoyn_message msg)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return msg->msg->GetSender();
}

const char* alljoyn_message_getreceiveendpointname(alljoyn_message msg)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return msg->msg->GetRcvEndpointName();
}

const char* alljoyn_message_getdestination(alljoyn_message msg)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return msg->msg->GetDestination();
}

uint32_t alljoyn_message_getcompressiontoken(alljoyn_message msg)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return msg->msg->GetCompressionToken();
}

alljoyn_sessionid alljoyn_message_getsessionid(alljoyn_message msg)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return (alljoyn_sessionid)msg->msg->GetSessionId();
}

const char* alljoyn_message_geterrorname(alljoyn_message msg, char* errorMessage, size_t* errorMessage_size)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    qcc::String* str = new qcc::String("");
    const char* ret = msg->msg->GetErrorName(str);

    if (errorMessage != NULL && errorMessage_size > 0) {
        strncpy(errorMessage, str->c_str(), *errorMessage_size);
        //Make sure the string is always nul terminated.
        errorMessage[*errorMessage_size - 1] = '\0';
    }
    //string plus nul character
    *errorMessage_size = str->size() + 1;
    delete str;
    return ret;
}

size_t alljoyn_message_tostring(alljoyn_message msg, char* str, size_t buf)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    if (!msg) {
        return (size_t)0;
    }
    qcc::String s = msg->msg->ToString();
    /*
     * it is ok to send in NULL for str when the user is only interested in the
     * size of the resulting string.
     */
    if (str) {
        strncpy(str, s.c_str(), buf);
        str[buf - 1] = '\0'; //prevent sting not being null terminated.
    }
    //string plus nul character
    return s.size() + 1;
}

size_t alljoyn_message_description(alljoyn_message msg, char* str, size_t buf)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    if (!msg) {
        return (size_t)0;
    }
    qcc::String s = msg->msg->Description();
    /*
     * it is ok to send in NULL for str when the user is only interested in the
     * size of the resulting string.
     */
    if (str) {
        strncpy(str, s.c_str(), buf);
        str[buf - 1] = '\0'; //prevent sting not being null terminated.
    }
    //string plus nul character
    return s.size() + 1;
}

uint32_t alljoyn_message_gettimestamp(alljoyn_message msg)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return msg->msg->GetTimeStamp();
}

QCC_BOOL alljoyn_message_eql(const alljoyn_message one, const alljoyn_message other)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    return (one->msg == other->msg);
}

void alljoyn_message_setendianess(const char endian)
{
    QCC_DbgTrace(("%s", __FUNCTION__));
    ajn::_Message::SetEndianess(endian);
}
