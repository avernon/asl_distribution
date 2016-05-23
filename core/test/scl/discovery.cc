/**
 * @file
 * Stress test for discovery
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
#include <qcc/Debug.h>
#include <qcc/Thread.h>

#include <signal.h>
#include <stdio.h>
#include <assert.h>
#include <vector>
#include <inttypes.h>
#include <qcc/Environ.h>
#include <qcc/Event.h>
#include <qcc/String.h>
#include <qcc/StringUtil.h>
#include <qcc/Util.h>
#include <qcc/time.h>
#include <qcc/Mutex.h>

#include <alljoyn/BusAttachment.h>
#include <alljoyn/DBusStd.h>
#include <alljoyn/AllJoynStd.h>
#include <alljoyn/version.h>

#include <alljoyn/Status.h>

#define QCC_MODULE "ALLJOYN"


using namespace std;
using namespace qcc;
using namespace ajn;

/** Static data */
static BusAttachment* g_msgBus = NULL;
static uint32_t g_count = 0;
static Mutex lock;

class MyBusListener : public BusListener {
  public:

    void FoundAdvertisedName(const char* name, TransportMask transport, const char* namePrefix)
    {
        lock.Lock();
        g_count++;
        printf("FoundAdvertisedName(name=%s, transport=0x%x, prefix=%s, count=%u)\n", name, transport, namePrefix, g_count);
        lock.Unlock();
    }

    void LostAdvertisedName(const char* name, TransportMask transport, const char* prefix)
    {
        lock.Lock();
        g_count--;
        printf("LostAdvertisedName(name=%s, transport=0x%x, prefix=%s, count=%lu)\n", name, transport, prefix, (unsigned long) g_count);
        lock.Unlock();
    }
};

/** Static bus listener */
static MyBusListener* g_busListener;

static volatile sig_atomic_t g_interrupt = false;
static bool g_discovery = false;

static void SigIntHandler(int sig)
{
    g_interrupt = true;
}

static void usage(void)
{
    printf("Usage: discovery\n\n");
    printf("Options:\n");
    printf("   -d                        = Discovery mode\n");
    printf("\n");
}


int main(int argc, char** argv)
{
    QStatus status = ER_OK;

    printf("AllJoyn Library version: %s\n", ajn::GetVersion());
    printf("AllJoyn Library build info: %s\n", ajn::GetBuildInfo());

    /* Install SIGINT handler */
    signal(SIGINT, SigIntHandler);

    /* Parse command line args */
    for (int i = 1; i < argc; ++i) {
        if (0 == strcmp("-d", argv[i])) {
            g_discovery = true;
        } else {
            status = ER_FAIL;
            printf("Unknown option %s\n", argv[i]);
            usage();
            exit(1);
        }
    }

    g_msgBus = new BusAttachment("discoverytest", true);
    if (g_discovery) {
        g_busListener = new MyBusListener();
        g_msgBus->RegisterBusListener(*g_busListener);
    }
    status = g_msgBus->Start();
    if (ER_OK != status) {
        QCC_LogError(status, ("BusAttachment::Start failed"));
        return status;
    }

    /* Connect to the bus */
    status = g_msgBus->Connect();
    if (ER_OK != status) {
        QCC_LogError(status, ("BusAttachment::Connect() failed"));
        return status;
    }

    if (!g_discovery) {
        //Advertise names
        for (int i = 0; i < 500 && !g_interrupt; i++) {
            char buf[512];
            sprintf(buf, "discovery.abcdefghijklmnopqrstuvwxyz%d.zyxwvutsrqponmlkjihgfedcab%d.alljoyn_core%d.common%d.build_core%d", i, i, i, i, i);
            status = g_msgBus->AdvertiseName(buf, TRANSPORT_WLAN);
            if (status  != ER_OK) {
                QCC_LogError(status, ("Failed to advertise name %s", buf));
            }
        }
    }

    if (g_discovery) {
        status = g_msgBus->FindAdvertisedNameByTransport("discovery", TRANSPORT_WLAN);
        if (status != ER_OK) {
            QCC_LogError(status, ("FindAdvertisedName failed"));
            return status;
        }
    }

    while (g_interrupt == false) {
        qcc::Sleep(100);
    }

    /* Deallocate bus */
    delete g_msgBus;

    if (g_discovery) {
        delete g_busListener;
    }

    printf("discovery exiting with status %d (%s)\n", status, QCC_StatusText(status));
    return (int) status;
}
