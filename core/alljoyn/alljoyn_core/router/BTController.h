/**
 * @file
 * BusObject responsible for controlling/handling Bluetooth delegations.
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
#ifndef _ALLJOYN_BTCONTROLLER_H
#define _ALLJOYN_BTCONTROLLER_H

#include <qcc/platform.h>

#include <list>
#include <map>
#include <set>
#include <vector>

#include <qcc/ManagedObj.h>
#include <qcc/String.h>
#include <qcc/Timer.h>
#include <qcc/BDAddress.h>

#include <alljoyn/BusObject.h>
#include <alljoyn/Message.h>
#include <alljoyn/MessageReceiver.h>

#include "Bus.h"
#include "NameTable.h"

namespace ajn {

typedef qcc::ManagedObj<std::set<qcc::BDAddress> > BDAddressSet;

class BluetoothDeviceInterface {
    friend class BTController;

  public:

    virtual ~BluetoothDeviceInterface() { }

  private:

    /**
     * Tells the Bluetooth transport to start listening for incoming connections.
     *
     * @return  ER_OK if successful
     */
    virtual QStatus StartListen() = 0;

    /**
     * Tells the Bluetooth transport to stop listening for incoming connections.
     */
    virtual void StopListen() = 0;

    virtual QStatus Disconnect(const qcc::String& busName) = 0;
    virtual void ReturnEndpoint(RemoteEndpoint& ep) = 0;
    virtual RemoteEndpoint LookupEndpoint(const qcc::String& busName) = 0;
};


/**
 * BusObject responsible for Bluetooth topology management.  This class is
 * used by the Bluetooth transport for the purposes of maintaining a sane
 * topology.
 */
class BTController :
    public BusObject,
    public NameListener,
    public BusAttachment::JoinSessionAsyncCB,
    public SessionPortListener,
    public SessionListener,
    public qcc::AlarmListener {
  public:
    /**
     * Constructor
     *
     * @param bus    Bus to associate with org.freedesktop.DBus message handler.
     * @param bt     Bluetooth transport to interact with.
     */
    BTController(BusAttachment& bus, BluetoothDeviceInterface& bt);

    /**
     * Destructor
     */
    ~BTController();

    /**
     * Called by the message bus when the object has been successfully
     * registered. The object can perform any initialization such as adding
     * match rules at this time.
     */
    void ObjectRegistered();

    /**
     * Initialize and register this DBusObj instance.
     *
     * @return ER_OK if successful.
     */
    QStatus Init();

    /**
     * Function for the BT Transport to inform a change in the
     * power/availablity of the Bluetooth device.
     *
     * @param on    true if BT device is powered on and available, false otherwise.
     */
    void BLEDeviceAvailable(bool on);

    void NameOwnerChanged(const qcc::String& alias,
                          const qcc::String* oldOwner, SessionOpts::NameTransferType oldOwnerNameTransfer,
                          const qcc::String* newOwner, SessionOpts::NameTransferType newOwnerNameTransfer);


    void JoinSessionCB(QStatus status, SessionId sessionId, const SessionOpts& opts, void* context);


  private:
    struct DispatchInfo {
        typedef enum {
            NAME_LOST,
            BT_DEVICE_AVAILABLE,
        } DispatchTypes;
        DispatchTypes operation;

        DispatchInfo(DispatchTypes operation) : operation(operation) { }
        virtual ~DispatchInfo() { }
    };

    struct NameLostDispatchInfo : public DispatchInfo {
        qcc::String name;
        NameLostDispatchInfo(const qcc::String& name) :
            DispatchInfo(NAME_LOST),
            name(name)
        { }
    };

    struct BLEDevAvailDispatchInfo : public DispatchInfo {
        bool on;
        BLEDevAvailDispatchInfo(bool on) : DispatchInfo(BT_DEVICE_AVAILABLE), on(on) { }
    };

    /**
     * Deals with the power/availability change of the Bluetooth device on the
     * BTController dispatch thread.
     *
     * @param on    true if BT device is powered on and available, false otherwise.
     */
    void DeferredBLEDeviceAvailable(bool on);

    void DeferredNameLostHander(const qcc::String& name);

    qcc::Alarm DispatchOperation(DispatchInfo* op, uint32_t delay = 0)
    {
        void* context = (void*)op;
        qcc::Alarm alarm(delay, this, context);
        dispatcher.AddAlarm(alarm);
        return alarm;
    }


    qcc::Alarm DispatchOperation(DispatchInfo* op, uint64_t dispatchTime)
    {
        void* context = (void*)op;
        qcc::Timespec ts(dispatchTime);
        qcc::Alarm alarm(ts, this, context);
        dispatcher.AddAlarm(alarm);
        return alarm;
    }

    void AlarmTriggered(const qcc::Alarm& alarm, QStatus reason);

    BusAttachment& bus;
    BluetoothDeviceInterface& bt;

    uint8_t maxConnects;           // Maximum number of direct connections
    const uint8_t maxConnections;
    bool listening;
    bool devAvailable;

    mutable qcc::Mutex lock;

    qcc::Timer dispatcher;

    BDAddressSet blacklist;

    qcc::Event connectCompleted;

};

}

#endif
