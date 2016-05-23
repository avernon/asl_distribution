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
#include <alljoyn/BusAttachment.h>
#include <qcc/Thread.h>
#include <qcc/Util.h>
#include <signal.h>

#define QCC_MODULE "ALLJOYN"

using namespace std;
using namespace qcc;
using namespace ajn;

static const char* rule = "interface='org.alljoyn.bus.test.sessions',sessionless='t'";
static const uint32_t waitTimeoutMs = 10000;

static const char* InterfaceName = "org.alljoyn.bus.test.sessions";
static const char* ObjectPath = "/sessions";

static volatile sig_atomic_t running = true;

static void SigIntHandler(int sig)
{
    running = false;
}

static InterfaceDescription* CreateInterface(BusAttachment* bus, size_t numSignals = 10)
{
    InterfaceDescription* intf = NULL;
    bus->CreateInterface(InterfaceName, intf);
    intf->AddSignal("Chat", "s",  "str", 0);
    for (size_t i = 0; i < numSignals; ++i) {
        char member[] = "Chat00";
        sprintf(member, "Chat%02ld", i);
        intf->AddSignal(member, "s",  "str", 0);
    }
    intf->Activate();
    return intf;
}

class Sender : public BusObject {
  public:
    BusAttachment* bus;

    Sender(const char* connectSpec)
        : BusObject(ObjectPath)
        , bus(new BusAttachment("Sender", true))
    {
        InterfaceDescription* intf = CreateInterface(bus);
        AddInterface(*intf);
        bus->RegisterBusObject(*this);

        bus->Start();
        bus->Connect(connectSpec ? connectSpec : "null:");
    }

    virtual ~Sender() {
        delete bus;
    }

    void SendSignal(const char* signal = "Chat00", const char* s = "schat") {
        const InterfaceDescription* intf = bus->GetInterface(InterfaceName);
        const InterfaceDescription::Member* member = intf->GetMember(signal);

        MsgArg arg("s", s);
        Message msg(*bus);
        Signal(NULL, 0, *member, &arg, 1, 0, ALLJOYN_FLAG_SESSIONLESS, &msg);
    }
};

class Receiver : public MessageReceiver {
  public:
    BusAttachment* bus;
    volatile unsigned int signalled;

    Receiver(const char* connectSpec)
        : bus(new BusAttachment("Receiver", true))
        , signalled(0)
    {
        InterfaceDescription* intf = CreateInterface(bus);

        size_t numMembers = intf->GetMembers();
        const ajn::InterfaceDescription::Member** members = new const ajn::InterfaceDescription::Member* [numMembers];
        intf->GetMembers(members, numMembers);
        for (size_t i = 0; i < numMembers; ++i) {
            bus->RegisterSignalHandler(this, static_cast<MessageReceiver::SignalHandler>(&Receiver::SignalHandler),
                                       members[i], NULL);
        }
        delete[] members;

        bus->Start();
        bus->Connect(connectSpec ? connectSpec : "null:");
    }

    virtual ~Receiver() {
        delete bus;
    }

    void SignalHandler(const InterfaceDescription::Member* member, const char* path, Message& message) {
        QCC_LogError(ER_OK, ("[%p] Received sender='%s',interface='%s',member='%s',path='%s'\n", this,
                             message->GetSender(),
                             message->GetInterface(),
                             message->GetMemberName(),
                             message->GetObjectPath()));
        ++signalled;
    }

    QStatus WaitForSignal(uint32_t msecs = waitTimeoutMs) {
        for (uint32_t i = 0; !signalled && (i < msecs); i += 100) {
            qcc::Sleep(100);
        }
        QStatus status = signalled ? ER_OK : ER_TIMEOUT;
        --signalled;
        return status;
    }
};

int main(int argc, char* argv[])
{
    int ret = 0;
    const char* role;
    const char* behavior;
    Sender* sender = NULL;
    Receiver* receiver = NULL;

    signal(SIGINT, SigIntHandler);

    if (argc < 2) {
        ret = 1;
        goto exit;
    }
    role = argv[1];
    behavior = (argc < 3) ? "simple" : argv[2];

    if (!strcmp(role, "sender")) {
        sender = new Sender(getenv("BUS_ADDRESS"));
        if (!strcmp(behavior, "simple")) {
            sender->SendSignal("Chat");
            while (running) {
                Sleep(500);
            }
        } else if (!strcmp(behavior, "random")) {
            uint32_t n = 0;
            while (running) {
                sender->SendSignal("Chat");
                fprintf(stderr, "Sent %u signals\n", ++n);
                Sleep(Rand8() / 16 * 1000);
            }
        }

    } else if (!strcmp(role, "receiver")) {
        receiver = new Receiver(getenv("BUS_ADDRESS"));
        receiver->bus->AddMatch(rule);
        while (running) {
            Sleep(500);
        }

    } else {
        ret = 1;
        goto exit;
    }

exit:
    delete receiver;
    delete sender;
    return ret;
};
