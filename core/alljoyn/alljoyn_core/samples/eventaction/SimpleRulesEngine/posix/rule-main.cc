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
#include <alljoyn/version.h>
#include <qcc/Log.h>
#include <qcc/platform.h>
#include <signal.h>
#include <stdio.h>
#include <alljoyn/Init.h>
#include "MyAllJoynCode.h"

using namespace std;
using namespace qcc;
using namespace ajn;

/* Static data */
static volatile sig_atomic_t s_interrupt = false;

static void SigIntHandler(int sig)
{
    s_interrupt = true;
}

/** Wait for SIGINT before continuing. */
void WaitForSigInt(void)
{
    while (s_interrupt == false) {
#ifdef _WIN32
        Sleep(100);
#else
        usleep(100 * 1000);
#endif
    }
}

int main(int argc, char** argv, char** envArg)
{
    QCC_UNUSED(envArg);
    if (AllJoynInit() != ER_OK) {
        return 1;
    }
#ifdef ROUTER
    if (AllJoynRouterInit() != ER_OK) {
        AllJoynShutdown();
        return 1;
    }
#endif

    printf("AllJoyn Library version: %s.\n", ajn::GetVersion());
    printf("AllJoyn Library build info: %s.\n", ajn::GetBuildInfo());

    /* Parse command line args */
    if (argc != 3 || (argc == 3 && 0 != ::strcmp("-n", argv[1]))) {
        printf("Please provide rule engine name via -n \"<name>\"\n");
        return 1;
    }

    /* Install SIGINT handler. */
    signal(SIGINT, SigIntHandler);

    /* Set AllJoyn logging */
    //QCC_SetLogLevels("ALLJOYN=7;ALL=1");
    //QCC_UseOSLogging(true);

    MyAllJoynCode* myAllJoynCode = new MyAllJoynCode();
    myAllJoynCode->initialize(argv[2]);

    WaitForSigInt();

    delete myAllJoynCode;
#ifdef ROUTER
    AllJoynRouterShutdown();
#endif
    AllJoynShutdown();
    return 0;
}
