/**
 * @file
 * AllJoyn Joystick/Display common bits
 */

/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

#include <signal.h>
#include <stdio.h>

#include <alljoyn/BusAttachment.h>
#include <alljoyn/BusObject.h>
#include <alljoyn/InterfaceDescription.h>

#include "common.h"


using namespace std;
using namespace qcc;
using namespace ajn;


const char* JS_SERVICE_NAME = "org.allseen.aj_tutorial.Joystick";
const SessionPort JS_SERVICE_PORT = 314;
const char* JS_SERVICE_PATH =  "/org/allseen/aj_tutorial/Joystick";
const char* JS_INTERFACE_NAME = "org.allseen.aj_tutorial.Joystick";


static volatile sig_atomic_t quit = false;

static void SignalHandler(int sig)
{
    quit = true;
}


void SetupSignalHandlers()
{
    struct sigaction act, oldact;
    sigset_t sigmask;

    // block all signals by default for all threads
    sigfillset(&sigmask);
    sigdelset(&sigmask, SIGSEGV);
    pthread_sigmask(SIG_BLOCK, &sigmask, NULL);

    act.sa_handler = SignalHandler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO | SA_RESTART;

    sigaction(SIGHUP, &act, &oldact);
    sigaction(SIGINT, &act, &oldact);
    sigaction(SIGTERM, &act, &oldact);
}

void WaitForQuit()
{
    sigset_t waitmask;

    sigfillset(&waitmask);
    sigdelset(&waitmask, SIGHUP);
    sigdelset(&waitmask, SIGINT);
    sigdelset(&waitmask, SIGTERM);

    while (!quit) {
        sigsuspend(&waitmask);
    }
}


bool CreateInterface(BusAttachment& bus)
{
    QStatus status;
    InterfaceDescription* intf = NULL;
    status = bus.CreateInterface(JS_INTERFACE_NAME, intf);
    if ((status == ER_OK) && intf) {
        intf->AddSignal("position", "nn", "x,y", 0);
        intf->AddSignal("buttons", "q", "buttons", 0);
        intf->AddProperty("output_range", "(nnnn)", PROP_ACCESS_RW);
        intf->AddProperty("button_mask", "q", PROP_ACCESS_RW);
        intf->Activate();
    } else {
        printf("failed to create interface\n");
        return false;
    }
    return true;
}


bool SetupAllJoyn(BusAttachment& bus, BusListener& bListener, BusObject* object, SessionPortListener* spListener)
{
    QStatus status;

    bus.RegisterBusListener(bListener);

    status = bus.Start();
    if (status != ER_OK) {
        printf("failed to start bus\n");
        return false;
    }

    if (object) {
        status = bus.RegisterBusObject(*object);
        if (status != ER_OK) {
            printf("failed to register bus object\n");
            return false;
        }
    }

    status = bus.Connect();
    if (status != ER_OK) {
        printf("failed to connect to the router node\n");
        return false;
    }

    if (object) {
        bus.RequestName(JS_SERVICE_NAME, DBUS_NAME_FLAG_DO_NOT_QUEUE);
        if (status != ER_OK) {
            printf("failed to request bus name\n");
            return false;
        }

        SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, false, SessionOpts::PROXIMITY_ANY, TRANSPORT_ANY);
        SessionPort sp = JS_SERVICE_PORT;
        status = bus.BindSessionPort(sp, opts, *spListener);
        if (status != ER_OK) {
            printf("failed to bind session port\n");
            return false;
        }

        bus.AdvertiseName(JS_SERVICE_NAME, TRANSPORT_ANY);
        if (status != ER_OK) {
            printf("failed to advertise bus name\n");
            return false;
        }
    } else {
        status = bus.FindAdvertisedName(JS_SERVICE_NAME);
        if (status != ER_OK) {
            printf("failed to find advertise bus name\n");
            return false;
        }
    }

    return true;
}
