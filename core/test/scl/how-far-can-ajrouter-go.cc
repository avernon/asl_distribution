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

#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS // Android needs this #define to get UINT*_MAX
#include <stdint.h>
#undef __STDC_LIMIT_MACROS
#endif

#include <iostream>

#include <cassert>
#include <csignal>
#include <ctime>

#include <qcc/Debug.h>
#include <qcc/String.h>

#include <alljoyn/BusAttachment.h>
#include <alljoyn/Status.h>
#include <alljoyn/AllJoynStd.h>
#include <alljoyn/version.h>

// Based on guidelines at http://www.freebsd.org/cgi/man.cgi?query=sysexits
enum retval_t {
    EXIT_OK = 0,
    EXIT_SOFTWARE = 70
};

int main(const int argc, const char* argv[])
{
    std::cout << "AllJoyn Library version: " << ajn::GetVersion() <<
        std::endl << "AllJoyn Library build info: " << ajn::GetBuildInfo() <<
        std::endl;

    ajn::BusAttachment bus("max-unique-address", false, 1);

    if (ER_OK != bus.Start()) {
        std::cout << "Failed to start bus attachment." << std::endl;
        return EXIT_SOFTWARE;
    }

    for (uint64_t i = 0; i < UINT32_MAX; i++) {
        if (ER_OK != bus.Connect()) {
            // Lets give it another good ol college try
            continue;
        }

        const qcc::String uniqueNameObtained = bus.GetUniqueName();

        bus.Disconnect();

        if (0 == i % UINT16_MAX) {
            std::cout << "The unique address (iter: " << i << ") is " << uniqueNameObtained.c_str() << std::endl;
        }
    }

    bus.Stop();

    return EXIT_OK;
}
