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

#include "ajTestCommon.h"

#include <qcc/Environ.h>
#include <qcc/String.h>
#include <qcc/StringUtil.h>

qcc::String ajn::getConnectArg(const char* envvar) {
    qcc::Environ* env = qcc::Environ::GetAppEnviron();
#if defined(QCC_OS_GROUP_WINDOWS)
    return env->Find("BUS_ADDRESS", "tcp:addr=127.0.0.1,port=9956");
#else
    return env->Find("BUS_ADDRESS", "unix:abstract=alljoyn");
#endif
}

qcc::String ajn::genUniqueName(const BusAttachment& bus) {
    static uint32_t uniquifier = 0;
    return "test.x" + bus.GetGlobalGUIDString() + ".x" + qcc::U32ToString(uniquifier++);
}

qcc::String ajn::getUniqueNamePrefix(const BusAttachment& bus) {
    return "test.x" + bus.GetGlobalGUIDString() + ".x";
}

void PrintTo(const QStatus& status, ::std::ostream* os) {
    *os << QCC_StatusText(status);
}

::std::ostream& operator<<(::std::ostream& os, const QStatus& status) {
    return os << QCC_StatusText(status);
}

namespace qcc {
void PrintTo(const String& s, ::std::ostream* os) {
    *os << "\"" << s.c_str() << "\"";
}
}

namespace ajn {
::std::ostream& operator<<(::std::ostream& os, const BusEndpoint& ep) {
    return os << "endpoint '" << ep->GetUniqueName().c_str() << "'";
}
::std::ostream& operator<<(::std::ostream& os, const AllJoynMessageType& type) {
    // Extra WS courtesy of uncrustify
    switch (type) {
    case MESSAGE_INVALID:     return os << "INVALID";

    case MESSAGE_METHOD_CALL: return os << "METHOD_CALL";

    case MESSAGE_METHOD_RET:  return os << "METHOD_RET";

    case MESSAGE_ERROR:       return os << "ERROR";

    case MESSAGE_SIGNAL:      return os << "SIGNAL";
    }
    return os;
}
}
