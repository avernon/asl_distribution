/**
 * @file
 * Sample implementation of an AllJoyn service that provides a raw socket.
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
#include <errno.h>

#include <qcc/Debug.h>
#include <qcc/Environ.h>
#include <qcc/Mutex.h>
#include <qcc/String.h>
#include <qcc/StringUtil.h>
#include <qcc/Thread.h>
#include <qcc/time.h>
#include <qcc/Util.h>

#include <alljoyn/AllJoynStd.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/DBusStd.h>
#include <alljoyn/Init.h>
#include <alljoyn/MsgArg.h>
#include <alljoyn/version.h>

#include <alljoyn/Status.h>


#define QCC_MODULE "ALLJOYN"

using namespace std;
using namespace qcc;
using namespace ajn;

/** Sample constants */
static const SessionPort SESSION_PORT = 33;

/** Static top level message bus object */
static BusAttachment* g_msgBus = NULL;
static String g_wellKnownName = "org.alljoyn.raw_test";

static volatile sig_atomic_t g_interrupt = false;

static void SigIntHandler(int sig)
{
    g_interrupt = true;
}

class MySessionPortListener : public SessionPortListener {

  public:
    MySessionPortListener() : SessionPortListener(), sessionId(0) { }

    bool AcceptSessionJoiner(SessionPort sessionPort, const char* joiner, const SessionOpts& opts)
    {
        if (sessionPort != SESSION_PORT) {
            printf("Rejecting join request for unknown session port %d from %s\n", sessionPort, joiner);
            return false;
        }

        /* Allow the join attempt */
        printf("Accepting JoinSession request from %s on transport 0x%x\n", joiner, opts.transports);
        return true;
    }

    void SessionJoined(SessionPort sessionPort, SessionId sessionId, const char* joiner)
    {
        printf("SessionJoined with %s (id=%u)\n", joiner, sessionId);
        this->sessionId = sessionId;
    }

    SocketFd GetSessionId() { return sessionId; }

  private:
    SessionId sessionId;
};

static void usage(void)
{
    printf("Usage: rawservice [-h] [-n <name>] [-t <transport_mask>]\n\n");
    printf("Options:\n");
    printf("   -h                    = Print this help message\n");
    printf("   -n <name>             = Well-known name to advertise\n");
    printf("   -t                    = Advertise over TCP (enables selective advertising)\n");
    printf("   -l                    = Advertise locally (enables selective advertising)\n");
    printf("   -u                    = Advertise over UDP-based ARDP (enables selective advertising)\n");
}

/** Main entry point */
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
    TransportMask transportMask = TRANSPORT_NONE;

    printf("AllJoyn Library version: %s\n", ajn::GetVersion());
    printf("AllJoyn Library build info: %s\n", ajn::GetBuildInfo());

    /* Install SIGINT handler */
    signal(SIGINT, SigIntHandler);

    /* Parse command line args */
    for (int i = 1; i < argc; ++i) {
        if (0 == strcmp("-h", argv[i])) {
            usage();
            exit(0);
        } else if (0 == strcmp("-n", argv[i])) {
            ++i;
            if (i == argc) {
                printf("option %s requires a parameter\n", argv[i - 1]);
                usage();
                exit(1);
            } else {
                g_wellKnownName = argv[i];
            }
        } else if (0 == strcmp("-t", argv[i])) {
            transportMask |= TRANSPORT_TCP;
        } else if (0 == strcmp("-u", argv[i])) {
            transportMask |= TRANSPORT_UDP;
        } else if (0 == strcmp("-l", argv[i])) {
            transportMask |= TRANSPORT_LOCAL;
        } else {
            status = ER_FAIL;
            printf("Unknown option %s\n", argv[i]);
            usage();
            exit(1);
        }
    }
    /* If no transport option was specifie, then make session options very open */
    if (transportMask == 0) {
        transportMask = TRANSPORT_ANY;
    }
    /* Get env vars */
    Environ* env = Environ::GetAppEnviron();
    qcc::String clientArgs = env->Find("DBUS_STARTER_ADDRESS");

    if (clientArgs.empty()) {
        clientArgs = env->Find("BUS_ADDRESS");
    }

    /* Create message bus */
    g_msgBus = new BusAttachment("rawservice", true);
    MySessionPortListener mySessionPortListener;

    /* Start the msg bus */
    status = g_msgBus->Start();
    if (status != ER_OK) {
        QCC_LogError(status, ("BusAttachment::Start failed"));
    }

    /* Create a bus listener and connect to the local daemon */
    if (status == ER_OK) {
        /* Connect to the daemon */
        if (clientArgs.empty()) {
            status = g_msgBus->Connect();
        } else {
            status = g_msgBus->Connect(clientArgs.c_str());
        }
        if (status != ER_OK) {
            QCC_LogError(status, ("Failed to connect to \"%s\"", clientArgs.c_str()));
        }
    }

    /* Request a well-known name */
    if (status == ER_OK) {
        QStatus status = g_msgBus->RequestName(g_wellKnownName.c_str(), DBUS_NAME_FLAG_REPLACE_EXISTING | DBUS_NAME_FLAG_DO_NOT_QUEUE);
        if (status != ER_OK) {
            QCC_LogError(status, ("Failed to request name %s", g_wellKnownName.c_str()));
        }
    }

    /* Bind the session port */
    SessionOpts opts(SessionOpts::TRAFFIC_RAW_RELIABLE, false, SessionOpts::PROXIMITY_ANY, transportMask);
    SessionPort sp = SESSION_PORT;
    status = g_msgBus->BindSessionPort(sp, opts, mySessionPortListener);
    if (status != ER_OK) {
        QCC_LogError(status, ("BindSessionOpts failed"));
    }

    /* Begin Advertising the well-known name */
    if (status == ER_OK) {
        status = g_msgBus->AdvertiseName(g_wellKnownName.c_str(), opts.transports);
        if (status != ER_OK) {
            QCC_LogError(status, ("AdvertiseName failed"));
        }
    }

    SessionId lastSessionId = 0;
    while ((status == ER_OK) && (!g_msgBus->IsStopping()) && !g_interrupt) {
        /* Wait for someone to join our session */
        SessionId id = mySessionPortListener.GetSessionId();
        if (id == lastSessionId) {
            qcc::Sleep(100);
            continue;
        }
        printf("Found a new joiner with session id = %u\n", id);
        lastSessionId = id;

        /* Get the socket */
        SocketFd sockFd;
        status = g_msgBus->GetSessionFd(id, sockFd);
        if (status != ER_OK) {
            QCC_LogError(status, ("Failed to get socket from GetSessionFd args"));
        }

        /* Write test message on socket */
        if (status == ER_OK) {
            const char* testMessage = "abcdefghijklmnopqrstuvwxyz";
            size_t testMessageLen = ::strlen(testMessage);
            size_t sent;
            status = qcc::Send(sockFd, testMessage, testMessageLen, sent);
            if (status == ER_OK) {
                printf("Wrote %lu of %lu bytes of testMessage to socket\n", (long unsigned int) sent, (long unsigned int) testMessageLen);
            } else {
                printf("Failed to write testMessage (%s)\n", ::strerror(errno));
                status = ER_FAIL;
            }
            qcc::Sleep(100);
#ifdef WIN32
            closesocket(sockFd);
#else
            ::shutdown(sockFd, SHUT_RDWR);
            ::close(sockFd);
#endif
        }
    }

    while (g_interrupt == false) {
        qcc::Sleep(100);
    }

    /* Delete the bus */
    delete g_msgBus;

    printf("%s exiting with status %x (%s)\n", argv[0], status, QCC_StatusText(status));

#ifdef ROUTER
    AllJoynRouterShutdown();
#endif
    AllJoynShutdown();
    return (int) status;
}
