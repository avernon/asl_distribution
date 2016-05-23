/**
 * @file
 * AdapterObject managed object class definition.  BT HCI device access class.
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
#ifndef _ALLJOYN_ADAPTEROBJECT_H
#define _ALLJOYN_ADAPTEROBJECT_H

#include <qcc/platform.h>

#include <vector>

#include <qcc/ManagedObj.h>
#include <qcc/Socket.h>
#include <qcc/BDAddress.h>

#include <alljoyn/BusAttachment.h>
#include <alljoyn/ProxyBusObject.h>

#include "BTTransportConsts.h"

#include <alljoyn/Status.h>


namespace ajn {
namespace bluez {

class _AdapterObject : public ProxyBusObject,
    private ProxyBusObject::PropertiesChangedListener {
  public:

    _AdapterObject() { }
    _AdapterObject(BusAttachment& bus, const qcc::String& path);
    bool operator==(const _AdapterObject& other) const { return address == other.address; }

    QStatus SetAddress(const qcc::String addrStr) { return address.FromString(addrStr); }
    const qcc::BDAddress& GetAddress() const { return address; }
    bool IsDiscovering() const { return discovering; }
    void SetDiscovering(bool disc) { discovering = disc; }
    bool IsPowered() const { return powered; }
    void SetPowered(bool p) { powered = p; }

  private:

    void PropertiesChanged(ProxyBusObject& obj,
                           const char* ifaceName,
                           const MsgArg& changed,
                           const MsgArg& invalidated,
                           void* context);


    uint16_t id;
    qcc::BDAddress address;
    bool discovering;
    bool powered;
};

typedef qcc::ManagedObj<_AdapterObject> AdapterObject;


} // namespace bluez
} // namespace ajn

#endif
