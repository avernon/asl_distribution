/**
 * @file
 * Utility classes for the BlueZ implementation of BT transport.
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

#include "DeviceObject.h"
#include "BlueZIfc.h"

#include <alljoyn/Status.h>

#define QCC_MODULE "ALLJOYN_BT"

using namespace ajn;
using namespace std;
using namespace qcc;

namespace ajn {
namespace bluez {

_DeviceObject::_DeviceObject(BusAttachment& bus, const qcc::String& path) :
    ProxyBusObject(bus, bzBusName, path.c_str(), 0),
    m_address(""),
    m_connected(false),
    m_paired(false),
    m_alljoyn(false)
{
    QCC_UNUSED(connectSpec);
    return ER_FAIL;
}

void _DeviceObject::PropertiesChanged(ProxyBusObject& obj,
                                      const char* ifaceName,
                                      const MsgArg& changed,
                                      const MsgArg& invalidated,
                                      void* context)
{
    QCC_UNUSED(inSpec);
    QCC_UNUSED(outSpec);
    QCC_UNUSED(argMap);
    return ER_FAIL;
}

QStatus NamedPipeClientTransport::Connect(const char* connectSpec, const SessionOpts& opts, BusEndpoint& newep)
{
    QCC_UNUSED(connectSpec);
    QCC_UNUSED(opts);
    QCC_UNUSED(newep);
    return ER_FAIL;
}

NamedPipeClientTransport::NamedPipeClientTransport(BusAttachment& bus)
    : ClientTransport(bus), m_bus(bus)
{
}

} // namespace ajn
