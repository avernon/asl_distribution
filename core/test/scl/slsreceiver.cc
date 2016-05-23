/**
 * @file
 * test program that will receive sessionless signals.
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
#include <signal.h>
#include <stdio.h>
#include <vector>

#include <qcc/Debug.h>
#include <qcc/Environ.h>
#include <qcc/Mutex.h>
#include <qcc/String.h>
#include <qcc/Thread.h>
#include <qcc/time.h>
#include <qcc/Util.h>

#include <alljoyn/BusAttachment.h>
#include <alljoyn/Init.h>
#include <alljoyn/BusObject.h>
#include <alljoyn/DBusStd.h>
#include <alljoyn/AllJoynStd.h>
#include <alljoyn/MsgArg.h>
#include <alljoyn/version.h>

#include <alljoyn/Status.h>

#ifdef _WIN32
#include <sys/timeb.h>
#include <time.h>
#endif

#define QCC_MODULE "SLSRECEIVER TEST PROGRAM"

using namespace std;
using namespace qcc;
using namespace ajn;

namespace org {
namespace alljoyn {
namespace alljoyn_test {
const char* InterfaceName = "org.alljoyn.alljoyn_test";
const char* ObjectPath = "/org/alljoyn/alljoyn_test";
}
}
}

/* Static top level globals */
static BusAttachment* g_msgBus = NULL;
static bool g_debug = false;

static volatile sig_atomic_t g_interrupt = false;
static void GetMyTimeNow(Timespec<qcc::EpochTime>* ts)
{
#ifdef _WIN32
    struct _timeb timebuffer;
    _ftime(&timebuffer);
    ts->seconds = timebuffer.time;
    ts->mseconds = timebuffer.millitm;
#else
    struct timespec _ts;
    clock_gettime(CLOCK_REALTIME, &_ts);
    ts->seconds = _ts.tv_sec;
    ts->mseconds = _ts.tv_nsec / 1000000;
#endif
}

static void CDECL_CALL SigIntHandler(int sig)
{
    QCC_UNUSED(sig);
    g_interrupt = true;
}

class LocalTestObject : public BusObject {

  public:

    LocalTestObject(BusAttachment& bus, const char* path, unsigned long reportInterval) :
        BusObject(path),
        reportInterval(reportInterval)
    {
        QStatus status = ER_OK;

        /* Add the test interface to this object */
        const InterfaceDescription* regTestIntf = bus.GetInterface(::org::alljoyn::alljoyn_test::InterfaceName);
        assert(regTestIntf);
        AddInterface(*regTestIntf);

        /* Register the signal handler with the bus */
        const InterfaceDescription::Member* member = regTestIntf->GetMember("sls_signal");
        assert(member);
        status = bus.RegisterSignalHandler(this,
                                           static_cast<MessageReceiver::SignalHandler>(&LocalTestObject::SignalHandler),
                                           member,
                                           NULL);
        if (ER_OK != status) {
            QCC_LogError(status, ("Failed to register signal handler"));
        }

    }

    void ObjectRegistered(void)
    {
    }

    void SignalHandler(const InterfaceDescription::Member* member,
                       const char* sourcePath,
                       Message& msg)
    {
        QCC_UNUSED(member);
        //g_msgBus->EnableConcurrentCallbacks();
        uint32_t c = 0;
        const MsgArg* arg((msg->GetArg(0)));
        arg->Get("u", &c);

        uint64_t receivedSeconds = 0;
        const MsgArg* arg1((msg->GetArg(1)));
        arg1->Get("t", &receivedSeconds);

        uint16_t receivedMseconds = 0;
        const MsgArg* arg2((msg->GetArg(2)));
        arg2->Get("q", &receivedMseconds);

        if (g_debug) {
            std::cout << "RSec is" << receivedSeconds << ", Rms is " << receivedMseconds << std::endl;
        }
        Timespec<qcc::EpochTime> ts;
        GetMyTimeNow(&ts);
        if (g_debug) {
            std::cout << "Sec is" << ts.seconds << ", ms is " << ts.mseconds << std::endl;
        }
        uint32_t diff = (ts.seconds - receivedSeconds);
        std::cout << "RxSignal: " << sourcePath << " - " << c << std::hex << c << std::dec << " in " << diff * 1000 + (ts.mseconds - receivedMseconds) << std::endl;
    }

  private:
    map<qcc::String, size_t> rxCounts;
    unsigned long reportInterval;
};

static void usage(void)
{
    printf("Usage: slsreceiver [-n <name>] [-i #] \n\n");
    printf("Options:\n");
    printf("   -h                    = Print this help message\n");
    printf("   -?                    = Print this help message\n");
    printf("   -i #                  = Signal report interval (number of signals rx per update; default = 1000)\n");
    printf("   -n <well-known name>  = Well-known name to advertise\n");
    printf("   -d                    = enable debug print\n");
}

int TestAppMain(int argc, char** argv)
{
    QStatus status = ER_OK;
    unsigned long reportInterval = 1000;

    std::cout << "AllJoyn Library version: " << ajn::GetVersion() << std::endl;
    std::cout << "AllJoyn Library build info: " << ajn::GetBuildInfo() << std::endl;

    /* Install SIGINT handler */
    signal(SIGINT, SigIntHandler);

    /* Parse command line args */
    for (int i = 1; i < argc; ++i) {
        if (0 == strcmp("-h", argv[i]) || 0 == strcmp("-?", argv[i])) {
            usage();
            exit(0);
        } else if (0 == strcmp("-i", argv[i])) {
            ++i;
            if (i == argc) {
                printf("option %s requires a parameter\n", argv[i - 1]);
                usage();
                exit(1);
            } else {
                reportInterval = strtoul(argv[i], NULL, 10);
            }
        } else if (0 == strcmp("-n", argv[i])) {
            ++i;
            if (i == argc) {
                printf("option %s requires a parameter\n", argv[i - 1]);
                usage();
                exit(1);
            }
        } else if (0 == strcmp("-d", argv[i])) {
            g_debug = true;
        } else {
            status = ER_FAIL;
            printf("Unknown option %s\n", argv[i]);
            usage();
            exit(1);
        }
    }

    /* Get env vars */
    Environ* env = Environ::GetAppEnviron();
    qcc::String clientArgs = env->Find("BUS_ADDRESS");

    /* Create message bus */
    g_msgBus = new BusAttachment("slsreceiver", true);

    /* Add org.alljoyn.alljoyn_test interface */
    InterfaceDescription* testIntf = NULL;
    status = g_msgBus->CreateInterface(::org::alljoyn::alljoyn_test::InterfaceName, testIntf);
    if (ER_OK == status) {
        testIntf->AddSignal("sls_signal", "utq", NULL, 0);
        testIntf->Activate();
    } else {
        QCC_LogError(status, ("Failed to create interface %s", ::org::alljoyn::alljoyn_test::InterfaceName));
    }


    /* Start the msg bus */
    if (ER_OK == status) {
        status = g_msgBus->Start();
    } else {
        QCC_LogError(status, ("BusAttachment::Start failed"));
        exit(1);
    }

    /* Register local objects and connect to the daemon */
    LocalTestObject testObj(*g_msgBus, ::org::alljoyn::alljoyn_test::ObjectPath, reportInterval);
    g_msgBus->RegisterBusObject(testObj);

    /* Connect to the daemon */
    if (clientArgs.empty()) {
        status = g_msgBus->Connect();
    } else {
        status = g_msgBus->Connect(clientArgs.c_str());
    }
    if (ER_OK != status) {
        QCC_LogError(status, ("Failed to connect to \"%s\"", clientArgs.c_str()));
        exit(-1);
    }

    //Add match rule to start receiving sls signals.
    status = g_msgBus->AddMatch("sessionless='t'");


    if (ER_OK == status) {
        while (g_interrupt == false) {
            qcc::Sleep(100);
        }
    }

    g_msgBus->UnregisterBusObject(testObj);

    /* Clean up msg bus */
    delete g_msgBus;

    printf("%s exiting with status %d (%s)\n", argv[0], status, QCC_StatusText(status));

    return (int) status;
}

/** Main entry point */
int CDECL_CALL main(int argc, char** argv)
{
    QStatus status = AllJoynInit();
    if (ER_OK != status) {
        return 1;
    }
#ifdef ROUTER
    status = AllJoynRouterInit();
    if (ER_OK != status) {
        AllJoynShutdown();
        return 1;
    }
#endif

    int ret = TestAppMain(argc, argv);

#ifdef ROUTER
    AllJoynRouterShutdown();
#endif
    AllJoynShutdown();

    return ret;
}
