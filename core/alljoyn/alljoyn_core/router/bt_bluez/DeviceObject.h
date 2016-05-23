/**
 * @file
 * DeviceObject managed object class definition.
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
#ifndef _ALLJOYN_DEVICEOBJECT_H
#define _ALLJOYN_DEVICEOBJECT_H

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

class _DeviceObject : public ProxyBusObject,
    private ProxyBusObject::PropertiesChangedListener {
  public:

    _DeviceObject() { }
    _DeviceObject(BusAttachment& bus, const qcc::String& path);
    bool operator==(const _DeviceObject& other) const { return m_address == other.m_address; }

    QStatus SetAddress(const qcc::String addrStr) { return m_address.FromString(addrStr); }
    void SetConnected(bool connected) { m_connected = connected; }
    void SetPaired(bool paired) { m_paired = paired; }
    void SetAllJoyn() { m_alljoyn = true; }
    const qcc::BDAddress& GetAddress() const { return m_address; }
    bool IsConnected() const { return m_connected; }
    bool IsPaired() const { return m_paired; }
    bool IsAllJoyn() const { return m_alljoyn; }

  private:

    void PropertiesChanged(ProxyBusObject& obj,
                           const char* ifaceName,
                           const MsgArg& changed,
                           const MsgArg& invalidated,
                           void* context);
    qcc::BDAddress m_address;
    bool m_connected;
    bool m_paired;
    bool m_alljoyn;
};

typedef qcc::ManagedObj<_DeviceObject> DeviceObject;


} // namespace bluez
} // namespace ajn

#endif
