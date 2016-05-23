/**
 * @file
 * test program that will register and unregister bus objects with the bus.
 * The bus objects are created after connecting to the bus.
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


#define QCC_MODULE "REGISTERBUSOBJECTS TEST PROGRAM"
#define NO_OF_BUS_OBJECTS 20000

using namespace std;
using namespace qcc;
using namespace ajn;


/* Static top level globals */
static BusAttachment* g_msgBus = NULL;

static volatile sig_atomic_t g_interrupt = false;
static Mutex lock;
static bool startDeregistering = false;
static bool startFreeing = false;

static void CDECL_CALL SigIntHandler(int sig)
{
    QCC_UNUSED(sig);
    g_interrupt = true;
}

class LocalTestObject : public BusObject {

  public:

    LocalTestObject(BusAttachment& bus, const char* path) :
        BusObject(path), objPath(path)
    { QCC_UNUSED(bus); }

    void ObjectRegistered(void)
    {
        static int count = 0;
        lock.Lock();
        count++;
        printf("Object[%d] registered  path is %s \n", count, objPath.c_str());
        if (count == NO_OF_BUS_OBJECTS) { startDeregistering = true; }
        lock.Unlock();
    }

    void ObjectUnregistered(void)
    {
        static int count = NO_OF_BUS_OBJECTS;
        lock.Lock();
        printf("Object[%d] unregistered path is %s \n", count, objPath.c_str());
        count--;
        if (count == 0) { startFreeing = true; }
        lock.Unlock();
    }

    String objPath;
};

static void usage(void)
{
    printf("Usage: slsreceiver [-n <name>] [-i #] \n\n");
    printf("Options:\n");
    printf("   -h                    = Print this help message\n");
    printf("   -?                    = Print this help message\n");
}

int TestAppMain(int argc, char** argv)
{
    QStatus status = ER_OK;

    printf("AllJoyn Library version: %s\n", ajn::GetVersion());
    printf("AllJoyn Library build info: %s\n", ajn::GetBuildInfo());

    /* Install SIGINT handler */
    signal(SIGINT, SigIntHandler);

    /* Parse command line args */
    for (int i = 1; i < argc; ++i) {
        if (0 == strcmp("-h", argv[i]) || 0 == strcmp("-?", argv[i])) {
            usage();
            exit(0);
        } else {
            status = ER_FAIL;
            printf("WARN: Ignoring Unknown option %s\n", argv[i]);
        }
    }

    /* Get env vars */
    Environ* env = Environ::GetAppEnviron();
    qcc::String clientArgs = env->Find("BUS_ADDRESS");

    /* Create message bus */
    g_msgBus = new BusAttachment("registerbusobjects", true);

    /* Start the msg bus */
    if (ER_OK == status) {
        status = g_msgBus->Start();
    } else {
        QCC_LogError(status, ("BusAttachment::Start failed"));
        exit(1);
    }

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

    /* Register local objects and connect to the daemon */
    LocalTestObject*testObj[NO_OF_BUS_OBJECTS];
    for (int i = 0; i < NO_OF_BUS_OBJECTS; i++) {
        char obj_path[200];
        sprintf(obj_path, "/com/cool%d", i);
        testObj[i] = new LocalTestObject(*g_msgBus, obj_path);
        g_msgBus->RegisterBusObject(*testObj[i]);
    }

    while (!startDeregistering && !g_interrupt)
        qcc::Sleep(100);

    for (int i = NO_OF_BUS_OBJECTS - 1; i >= 0; i--) {
        g_msgBus->UnregisterBusObject(*testObj[i]);
    }

    while (!startFreeing && !g_interrupt)
        qcc::Sleep(100);

    for (int i = 0; i < NO_OF_BUS_OBJECTS; i++)
        delete testObj[i];


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
