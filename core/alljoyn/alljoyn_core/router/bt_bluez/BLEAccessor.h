/**
 * @file
 * BLEAccessor declaration for BlueZ
 */

/******************************************************************************
 * Copyright (c) 2009-2012, 2014, AllSeen Alliance. All rights reserved.
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
#ifndef _ALLJOYN_BTACCESSOR_H
#define _ALLJOYN_BTACCESSOR_H

#include <qcc/platform.h>

#include <qcc/Event.h>
#include <qcc/ManagedObj.h>
#include <qcc/String.h>
#include <qcc/Timer.h>
#include <qcc/XmlElement.h>
#include <qcc/BDAddress.h>
#include <qcc/BLEStream.h>
#include <qcc/BLEStreamAccessor.h>

#include <alljoyn/BusAttachment.h>
#include <alljoyn/BusListener.h>
#include <alljoyn/MessageReceiver.h>
#include <alljoyn/ProxyBusObject.h>

#include "AdapterObject.h"
#include "DeviceObject.h"
#include "BTController.h"
#include "DaemonBLETransport.h"
#include "RemoteEndpoint.h"

#include <alljoyn/Status.h>


namespace ajn {

class DaemonBLETransport::
BLEAccessor :
    public qcc::BLEStreamAccessor,
    public MessageReceiver,
    public qcc::AlarmListener,
    public BusListener,
    private ProxyBusObject::PropertiesChangedListener {
  public:
    /**
     * Constructor
     *
     * @param transport
     * @param busGuid
     */
    BLEAccessor(DaemonBLETransport* transport, const qcc::String& busGuid);

    /**
     * Destructor
     */
    ~BLEAccessor();

    /**
     * Start the underlying Bluetooth subsystem.
     *
     * @return ER_OK if successful.
     */
    QStatus Start();

    /**
     * Start the underlying Bluetooth subsystem.
     */
    void Stop();

    /**
     * Push Bytes
     */
    QStatus PushBytes(qcc::String remObj, const void* buf, size_t numBytes, size_t& actualBytes);

    /**
     * Make the Bluetooth device connectable.
     *
     * @return  ER_OK if device is now connectable
     */
    QStatus StartConnectable();

    /**
     * Make the Bluetooth device not connectable.
     */
    void StopConnectable();

    /**
     * Accepts an incoming connection from a remote Bluetooth device.
     *
     * @param alljoyn       BusAttachment that will be connected to the resulting endpoint
     * @param connectEvent  The event signalling the incoming connection
     *
     * @return  A newly instatiated remote endpoint for the Bluetooth connection (NULL indicates a failure)
     */
    RemoteEndpoint Accept(BusAttachment& alljoyn,
                          qcc::Event* connectEvent);

    /**
     * Create an outgoing connection to a remote Bluetooth device.  If the
     * L2CAP PSM are not specified, then an SDP query will be performed to get
     * that information.
     *
     * @param alljoyn   BusAttachment that will be connected to the resulting endpoint
     *
     * @return  A newly instatiated remote endpoint for the Bluetooth connection (NULL indicates a failure)
     */
    RemoteEndpoint Connect(BusAttachment& alljoyn, qcc::String objPath);

  private:

    void ConnectBlueZ();
    void DisconnectBlueZ();

    void NameOwnerChanged(const char* busName, const char* previousOwner, const char* newOwner);

    /* Adapter management functions */
    QStatus EnumerateAdapters();
    void AdapterAdded(const char* adapterObjPath);
    void AdapterAdded(const char* adapterObjPath,
                      const MsgArg* props);
    void AdapterRemoved(const char* adapterObjPath);
    void DefaultAdapterChanged(const char* adapterObjPath);

    /* Device presence management signal handlers */
    void RxDataRecvSignalHandler(const InterfaceDescription::Member* member,
                                 const char* sourcePath,
                                 Message& msg);
    void InterfacesAddedSignalHandler(const InterfaceDescription::Member* member,
                                      const char* sourcePath,
                                      Message& msg);
    void InterfacesRemovedSignalHandler(const InterfaceDescription::Member* member,
                                        const char* sourcePath,
                                        Message& msg);

    /* support */
    QStatus ConnectDevice(const char*objStr);
    QStatus InitializeAdapterInformation(bluez::AdapterObject& adapter,
                                         const MsgArg* props);
    void AlarmTriggered(const qcc::Alarm& alarm, QStatus reason);
    QStatus DiscoveryControl(bool start);
    QStatus DiscoveryControl(const InterfaceDescription::Member* method);

    bluez::AdapterObject GetAdapterObject(const qcc::String& adapterObjPath) const
    {
        bluez::AdapterObject adapter;
        assert(!adapter->IsValid());
        adapterLock.Lock(MUTEX_CONTEXT);
        AdapterMap::const_iterator it(adapterMap.find(adapterObjPath));
        if (it != adapterMap.end()) {
            adapter = it->second;
        }
        adapterLock.Unlock(MUTEX_CONTEXT);
        return adapter;
    }

    bluez::AdapterObject GetDefaultAdapterObject() const
    {
        adapterLock.Lock(MUTEX_CONTEXT);
        bluez::AdapterObject adapter(defaultAdapterObj);
        adapterLock.Unlock(MUTEX_CONTEXT);
        return adapter;
    }

    void PropertiesChanged(ProxyBusObject& obj,
                           const char* ifaceName,
                           const MsgArg& changed,
                           const MsgArg& invalidated,
                           void* context);



/******************************************************************************/


    typedef std::map<qcc::String, qcc::BLEController*> DeviceMap;
    typedef std::map<qcc::String, bluez::DeviceObject*> DeviceProxyMap;
    typedef std::map<qcc::StringMapKey, bluez::AdapterObject> AdapterMap;

    class FoundInfo {
      public:
        FoundInfo() :
            uuidRev(bt::INVALID_UUIDREV),
            timeout(0)
        { }
        uint32_t uuidRev;
        uint64_t timeout;
    };
    typedef std::map<qcc::BDAddress, FoundInfo> FoundInfoMap;
    typedef std::multimap<uint64_t, qcc::BDAddress> FoundInfoExpireMap;

    BusAttachment bzBus;
    const qcc::String busGuid;
    qcc::String connectArgs;

    ProxyBusObject bzManagerObj;
    bluez::AdapterObject defaultAdapterObj;
    bluez::AdapterObject anyAdapterObj;
    AdapterMap adapterMap;
    DeviceMap deviceMap;
    DeviceProxyMap deviceProxyMap;
    mutable qcc::Mutex adapterLock; // Generic lock for adapter related objects, maps, etc.

    DaemonBLETransport* transport;

    uint32_t recordHandle;

    mutable qcc::Mutex deviceLock; // Generic lock for device related objects, maps, etc.
    FoundInfoMap foundDevices;  // Map of found AllJoyn devices w/ UUID-Rev and expire time.
    FoundInfoExpireMap foundExpirations;
    qcc::Timer timer;
    qcc::Alarm stopAdAlarm;
    BDAddressSet ignoreAddrs;

    std::set<qcc::StringMapKey> createdDevices;  // Set of devices we created

    bool bluetoothAvailable;
    bool discoverable;
    volatile int32_t discoveryCtrl;

    qcc::SocketFd l2capLFd;
    qcc::Event* l2capEvent;

    uint32_t cod;

    struct {
        struct {
            struct {
                const InterfaceDescription* interface;
                // Methods (not all; only those needed)
                const InterfaceDescription::Member* GetManagedObjects;
                // Signals
                const InterfaceDescription::Member* InterfacesAdded;
                const InterfaceDescription::Member* InterfacesRemoved;
            } ObjMgr;

            struct {
                const InterfaceDescription* interface;
                // Methods (not all; only those needed)
                const InterfaceDescription::Member* RemoveDevice;
                const InterfaceDescription::Member* StartDiscovery;
                const InterfaceDescription::Member* StopDiscovery;
            } Adapter1;

            struct {
                const InterfaceDescription* interface;
                // Methods (not all; only those needed)
                const InterfaceDescription::Member* SetUuid;
            } AllJoynMgr;

            struct {
                const InterfaceDescription* interface;
                // Methods (not all; only those needed)
                const InterfaceDescription::Member* TxDataSend;
                // Signals
                const InterfaceDescription::Member* RxDataRecv;
            } AllJoyn;

            struct {
                const InterfaceDescription* interface;
                // Methods (not all; only those needed)
                const InterfaceDescription::Member* Connect;
                const InterfaceDescription::Member* Disconnect;
                const InterfaceDescription::Member* ConnectProfile;
                const InterfaceDescription::Member* DisconnectProfile;
                const InterfaceDescription::Member* Pair;
                const InterfaceDescription::Member* CancelPairing;
            } Device1;
        } bluez;
    } org;

};


} // namespace ajn


#endif
