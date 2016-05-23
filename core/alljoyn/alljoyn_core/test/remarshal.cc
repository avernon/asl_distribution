/**
 * @file
 *
 * This file tests AllJoyn use of the DBus wire protocol
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

#include <ctype.h>
#include <qcc/platform.h>

#include <qcc/Util.h>
#include <qcc/Debug.h>
#include <qcc/Pipe.h>
#include <qcc/String.h>
#include <qcc/StringUtil.h>

#include <alljoyn/BusAttachment.h>
#include <alljoyn/Init.h>
#include <alljoyn/Message.h>
#include <alljoyn/version.h>

#include <alljoyn/Status.h>

/* Private files included for unit testing */
#include <PeerState.h>
#include <SignatureUtils.h>
#include <RemoteEndpoint.h>

using namespace qcc;
using namespace std;
using namespace ajn;

static BusAttachment* gBus;

class MyMessage : public _Message {
  public:


    MyMessage() : _Message(*gBus) { };

    QStatus MethodCall(const char* destination,
                       const char* objPath,
                       const char* interface,
                       const char* methodName,
                       const MsgArg* argList,
                       size_t numArgs,
                       uint8_t flags = 0)
    {
        qcc::String sig = MsgArg::Signature(argList, numArgs);
        printf("Signature = \"%s\"\n", sig.c_str());
        return CallMsg(sig, destination, 0, objPath, interface, methodName, argList, numArgs, flags);
    }

    QStatus Signal(const char* destination,
                   const char* objPath,
                   const char* interface,
                   const char* signalName,
                   const MsgArg* argList,
                   size_t numArgs)
    {
        qcc::String sig = MsgArg::Signature(argList, numArgs);
        printf("Signature = \"%s\"\n", sig.c_str());
        return SignalMsg(sig, destination, 0, objPath, interface, signalName, argList, numArgs, 0, 0);
    }

    QStatus UnmarshalBody() { return UnmarshalArgs("*"); }

    QStatus Read(RemoteEndpoint& ep, bool pedantic = true)
    {
        return _Message::Read(ep, pedantic);
    }

    QStatus Unmarshal(RemoteEndpoint& ep, bool pedantic = true)
    {
        return _Message::Unmarshal(ep, pedantic);
    }

    QStatus ReMarshal(const char* senderName)
    {
        /*
         * Remarshal with a different serial number or we will get an invalid serial error
         * (duplicate) when we try to unmarshal it.
         */
        _Message::SetSerialNumber();
        return _Message::ReMarshal(senderName);
    }

    QStatus Deliver(RemoteEndpoint& ep)
    {
        return _Message::Deliver(ep);
    }
};


/*
 * Marshal and unmarshal an arg list
 */
static QStatus TestRemarshal(const MsgArg* argList, size_t numArgs, const char* exception = NULL)
{
    QStatus status;
    Pipe stream;
    Pipe* pStream = &stream;
    static const bool falsiness = false;
    RemoteEndpoint ep(*gBus, falsiness, String::Empty, pStream);
    MyMessage msg;

    if (numArgs == 0) {
        printf("Empty arg.v_struct.Elements, arg.v_struct.numElements\n");
        return ER_FAIL;
    }

    printf("++++++++++++++++++++++++++++++++++++++++++++\n");
    qcc::String inargList = MsgArg::ToString(argList, numArgs);
    qcc::String inSig = MsgArg::Signature(argList, numArgs);
    printf("ArgList:\n%s", inargList.c_str());

    status = msg.MethodCall("desti.nation", "/foo/bar", "foo.bar", "test", argList, numArgs);
    printf("MethodCall status:%s\n", QCC_StatusText(status));
    if (status != ER_OK) {
        return status;
    }
    status = msg.Deliver(ep);
    if (status != ER_OK) {
        return status;
    }
    status = msg.Read(ep);
    if (status != ER_OK) {
        printf("Message::Read status:%s\n", QCC_StatusText(status));
        return status;
    }
    status = msg.Unmarshal(ep);
    if (status != ER_OK) {
        printf("Message::Unmarshal status:%s\n", QCC_StatusText(status));
        return status;
    }
    status = msg.UnmarshalBody();
    if (status != ER_OK) {
        printf("Message::UnmarshalArgs status:%s\n", QCC_StatusText(status));
        return status;
    }

    msg.ReMarshal("from.sender");
    status = msg.Deliver(ep);
    if (status != ER_OK) {
        printf("Message::ReMarshal status:%s\n", QCC_StatusText(status));
        return status;
    }
    status = msg.Unmarshal(ep);
    if (status != ER_OK) {
        printf("Message::Unmarshal status:%s\n", QCC_StatusText(status));
        return status;
    }
    status = msg.UnmarshalBody();
    if (status != ER_OK) {
        printf("Message::UnmarshalArgs status:%s\n", QCC_StatusText(status));
        return status;
    }

    return status;
}

int main(int argc, char** argv)
{
    if (AllJoynInit() != ER_OK) {
        return 1;
    }
#ifdef ROUTER
    if (AllJoynRouterInit() != ER_OK) {
        AllJoynShutdown();
        return 1;
    }
#endif

    QStatus status = ER_OK;

    printf("AllJoyn Library version: %s\n", ajn::GetVersion());
    printf("AllJoyn Library build info: %s\n", ajn::GetBuildInfo());

    gBus = new BusAttachment("remarshal");
    gBus->Start();

    struct {
        uint32_t num;
        const char* ord;
        bool even;
    } table[] = { { 1, "first", true }, { 2, "second", false }, { 3, "third", true } };
    MsgArg dict[ArraySize(table)];
    for (size_t i = 0; i < ArraySize(table); i++) {
        dict[i].Set("{s(ib)}", table[i].ord, table[i].num, table[i].even);
    }
    MsgArg arg;
    status = arg.Set("a{s(ib)}", 3, dict);
    if (status == ER_OK) {
        status = TestRemarshal(&arg, 1);
    }

    if (status == ER_OK) {
        QCC_SyncPrintf("\n PASSED ");
    } else {
        QCC_SyncPrintf("\n FAILED ");
    }
    printf("\n");

#ifdef ROUTER
    AllJoynRouterShutdown();
#endif
    AllJoynShutdown();
    return 0;
}
