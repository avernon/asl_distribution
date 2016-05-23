/******************************************************************************
 *
 *
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
#ifndef AJTESTCOMMON_H
#define AJTESTCOMMON_H

#include <qcc/String.h>
#include <alljoyn/BusAttachment.h>
#include "BusEndpoint.h"
/*
 * this header file contains a functions that can be used to replace common
 * actions in the test code.
 */
namespace ajn {

/**
 * Obtain the default connection arg for the OS the test is run on.
 * If running on on windows this should be "tcp:addr=127.0.0.1,port=9955"
 * If running on a unix variant this should be "unix:abstract=alljoyn"
 *
 * The environment variable BUS_ADDRESS is specified it will be used in place
 * of the default address
 *
 * @return a qcc::String containing the default connection arg
 */
qcc::String getConnectArg(const char* envvar = "BUS_ADDRESS");

/**
 * Generate a globally unique name for use in advertising.
 *
 * Advertised names should be unique to avoid multiple running instances
 * of the test suite from interferring with each other.
 */
qcc::String genUniqueName(const BusAttachment& bus);

/**
 * Get the prefix of the uniqueNames used in advertising
 *
 * Advertised names should be unique to avoid multiple running instances
 * of the test suite from interferring with each other.
 */
qcc::String getUniqueNamePrefix(const BusAttachment& bus);

}

/*
 * gtest printers
 */
void PrintTo(const QStatus& status, ::std::ostream* os);
::std::ostream& operator<<(::std::ostream& os, const QStatus& status);

namespace qcc {
void PrintTo(const String& s, ::std::ostream* os);
}

namespace ajn {
::std::ostream& operator<<(::std::ostream& os, const BusEndpoint& ep);
::std::ostream& operator<<(::std::ostream& os, const AllJoynMessageType& type);
}
#endif //AJTESTCOMMON_H
