/**
 * @file
 * Utility classes for the BlueZ implementation of BT transport.
 */

/******************************************************************************
 * Copyright (c) 2009-2011, 2014, AllSeen Alliance. All rights reserved.
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

#include <ctype.h>
#include <vector>
#include <errno.h>
#include <fcntl.h>

#include <qcc/Event.h>
#include <qcc/Socket.h>
#include <qcc/String.h>
#include <qcc/time.h>
#include <qcc/BDAddress.h>

#include <alljoyn/BusAttachment.h>
#include <alljoyn/ProxyBusObject.h>

#include "AdapterObject.h"
#include "BlueZIfc.h"

#include <alljoyn/Status.h>

#define QCC_MODULE "ALLJOYN_BT"

using namespace ajn;
using namespace std;
using namespace qcc;

namespace ajn {
namespace bluez {

_AdapterObject::_AdapterObject(BusAttachment& bus, const qcc::String& path) :
    ProxyBusObject(bus, bzBusName, path.c_str(), 0),
    id(0),
    discovering(false),
    powered(false)
{
    size_t i = path.size();
    while (i > 0) {
        --i;
        char c = path[i];
        if (!isdigit(c)) {
            break;
        }
        id *= 10;
        id += c - '0';
    }
}

void _AdapterObject::PropertiesChanged(ProxyBusObject& obj,
                                       const char* ifaceName,
                                       const MsgArg& changed,
                                       const MsgArg& invalidated,
                                       void* context)
{
}

} // namespace bluez
} // namespace ajn
