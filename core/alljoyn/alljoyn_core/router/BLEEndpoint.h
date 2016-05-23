/**
 * @file
 * BTAccessor declaration for BlueZ
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
#ifndef _ALLJOYN_BTENDPOINT_H
#define _ALLJOYN_BTENDPOINT_H

#include <qcc/platform.h>

#include <qcc/Stream.h>

#include <alljoyn/BusAttachment.h>

#include "RemoteEndpoint.h"


namespace ajn {
class _BLEEndpoint;
typedef qcc::ManagedObj<_BLEEndpoint> BLEEndpoint;

class _BLEEndpoint : public _RemoteEndpoint {
  public:

    /**
     * Bluetooth endpoint constructor
     */
    _BLEEndpoint(BusAttachment& bus,
                 bool incoming,
                 qcc::Stream& stream) :
        _RemoteEndpoint(bus, incoming, "ble:", &stream, "bluetooth")
    { }

    virtual ~_BLEEndpoint() { }
};

} // namespace ajn

#endif
