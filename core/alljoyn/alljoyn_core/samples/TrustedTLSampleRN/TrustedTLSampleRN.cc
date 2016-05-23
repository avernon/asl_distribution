/**
 * @file
 * TrustedTLSampleRN is a sample Routing Node that provides credentials allowing
 * trusted thin client applications connect.
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

#include <alljoyn/BusAttachment.h>
#include <alljoyn/Init.h>
#include <alljoyn/PasswordManager.h>
#include <alljoyn/Status.h>
#include <alljoyn/version.h>

#include <qcc/Debug.h>
#include <qcc/Event.h>
#include <qcc/String.h>
#include <qcc/StringUtil.h>
#include <qcc/Thread.h>

#include <iostream>
#include <vector>

#include <csignal>

#define QCC_MODULE "TRUSTED_TL_SAMPLE_RN"

using namespace ajn;
using namespace qcc;
using namespace std;

namespace org {
namespace alljoyn {
namespace TrustedTLSampleRN {
const char* DefaultRNBusName = "org.alljoyn.BusNode.TestingPurposesOnly";

const char* ThinClientAuthMechanism = "ALLJOYN_PIN_KEYX";
const char* ThinClientDefaultBusPwd = "1234";
}
}
}

static volatile sig_atomic_t g_interrupted = false;
static void SigIntHandler(int sig)
{
    g_interrupted = true;
}

static void usage(void)
{
    printf("Usage: TrustedTLSampleRN [-h] [-n <well-known-name>]\n\n");
    printf("Options:\n");
    printf("   -h                        = Print this help message\n");
    printf("   -n <well-known name>      = Well-known bus name advertised by Routing Node\n");
    printf("\n");
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

    printf("AllJoyn Library version: %s\n", ajn::GetVersion());
    printf("AllJoyn Library build info: %s\n", ajn::GetBuildInfo());

    // Register SIGNT (Ctrl-C) handler
    signal(SIGINT, SigIntHandler);

    String nameToAdvertise = ::org::alljoyn::TrustedTLSampleRN::DefaultRNBusName;

    // Parse command line arguments, if any
    for (int i = 1; i < argc; i++) {
        if (0 == strcmp("-h", argv[i])) {
            usage();
            exit(0);
        } else if (0 == strcmp("-n", argv[i])) {
            if (argc == ++i) {
                printf("option %s requires a parameter\n", argv[i - 1]);
                usage();
                exit(1);
            } else {
                nameToAdvertise = argv[i];
            }
        } else {
            printf("Unknown option %s\n", argv[i]);
            usage();
            exit(1);
        }
    }

    BusAttachment* msgBus = new BusAttachment("TrustedTLSampleRN", true);

    QStatus status = ER_FAIL;
    status = msgBus->Start();

    if (ER_OK == status) {
        // Set the credential that thin clients have to offer to connect
        // to this TrustedTLSampleRN in a trusted manner.
        PasswordManager::SetCredentials(
            ::org::alljoyn::TrustedTLSampleRN::ThinClientAuthMechanism,
            ::org::alljoyn::TrustedTLSampleRN::ThinClientDefaultBusPwd
            );

        // Force connecting to bundled router (i.e. null transport) to ensure
        // that credentials are correctly set.
        //
        // NOTE: The above SetCredentials call doesn't take effect
        //       when connecting to a RN.
        status = msgBus->Connect("null:");

        if (ER_OK == status) {
            // Quietly advertise the name to be discovered by thin clients only
            // over the TCP Transport since they currently only support that
            // mechanism.
            nameToAdvertise = "quiet@" + nameToAdvertise;
            status = msgBus->AdvertiseName(nameToAdvertise.c_str(), TRANSPORT_TCP);
            if (ER_OK != status) {
                QCC_LogError(status, ("Unable to quietly advertise the name %s", nameToAdvertise.c_str()));
            }
        }
    }

    // Wait for Ctrl-C to exit
    while (!g_interrupted) {
        qcc::Sleep(100);
    }

    delete msgBus;
    printf("%s exiting with status %u (%s)\n", argv[0], status, QCC_StatusText(status));
#ifdef ROUTER
    AllJoynRouterShutdown();
#endif
    AllJoynShutdown();
    return (int) status;
}
