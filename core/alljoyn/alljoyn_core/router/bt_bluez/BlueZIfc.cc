/**
 * @file
 * BTAccessor declaration for BlueZ
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

#include <qcc/Util.h>

#include <alljoyn/Message.h>

#include <alljoyn/InterfaceDescription.h>

#include "BlueZIfc.h"


using namespace ajn;
using namespace ajn::bluez;

namespace ajn {
namespace bluez {

const char* bzBusName = "org.bluez";
const char* bzMgrObjPath = "/";

const char* bzObjMgrIfc = "org.freedesktop.DBus.ObjectManager";
const char* bzAdapter1Ifc = "org.bluez.Adapter1";
const char* bzDevice1Ifc = "org.bluez.Device1";
const char* bzAllJoynIfc = "org.AllSeen.AllJoyn";

const InterfaceDesc bzObjMgrIfcTbl[] = {
    { MESSAGE_METHOD_CALL, "GetManagedObjects", NULL,         "a{oa{sa{sv}}}", NULL, 0 },
    { MESSAGE_SIGNAL,      "InterfacesAdded",   "oa{sa{sv}}", NULL,            NULL, 0 },
    { MESSAGE_SIGNAL,      "InterfacesRemoved", "oas",        NULL,            NULL, 0 },
};

const InterfaceDesc bzAdapter1IfcTbl[] = {
    { MESSAGE_METHOD_CALL, "RemoveDevice",      "o",     NULL,  NULL, 0 },
    { MESSAGE_METHOD_CALL, "StartDiscovery",    NULL,    NULL,  NULL, 0 },
    { MESSAGE_METHOD_CALL, "StopDiscovery",     NULL,    NULL,  NULL, 0 },
    { MESSAGE_INVALID,     "Powered",           "b",     NULL,  NULL, PROP_ACCESS_RW },
    { MESSAGE_INVALID,     "Discovering",       "b",     NULL,  NULL, PROP_ACCESS_READ },
};

const InterfaceDesc bzAllJoynMgrIfcTbl[] = {
    { MESSAGE_METHOD_CALL, "SetUuid",   "s",     NULL,  NULL, 0 },
};

const InterfaceDesc bzAllJoynIfcTbl[] = {
    { MESSAGE_METHOD_CALL, "TxDataSend",   "ay",     NULL,  NULL, 0 },
    { MESSAGE_SIGNAL,      "RxDataRecv",   "ay",     NULL,  NULL, 0 },
};

const InterfaceDesc bzDevice1IfcTbl[] = {
    { MESSAGE_METHOD_CALL, "CancelPairing",       NULL, NULL,    NULL, 0 },
    { MESSAGE_METHOD_CALL, "Connect",             NULL, NULL,    NULL, 0 },
    { MESSAGE_METHOD_CALL, "ConnectProfile",      "s",  NULL,    NULL, 0 },
    { MESSAGE_METHOD_CALL, "Disconnect",          NULL, NULL,    NULL, 0 },
    { MESSAGE_METHOD_CALL, "DisconnectProfile",   "s",  NULL,    NULL, 0 },
    { MESSAGE_METHOD_CALL, "Pair",                NULL, NULL,    NULL, 0 },
    /* Properties */
    { MESSAGE_INVALID,     "UUIDs",               "as", NULL,    NULL, PROP_ACCESS_READ },
    { MESSAGE_INVALID,     "Connected",           "b",  NULL,    NULL, PROP_ACCESS_READ },
    { MESSAGE_INVALID,     "Paired",              "b",  NULL,    NULL, PROP_ACCESS_READ },
};


const InterfaceTable ifcTables[] = {
    { "org.freedesktop.DBus.ObjectManager", bzObjMgrIfcTbl, ArraySize(bzObjMgrIfcTbl) },
    { "org.bluez.Adapter1",       bzAdapter1IfcTbl,     ArraySize(bzAdapter1IfcTbl) },
    { "org.bluez.Device1",        bzDevice1IfcTbl,      ArraySize(bzDevice1IfcTbl) },
    { "org.AllSeen.AllJoynMgr",   bzAllJoynMgrIfcTbl,   ArraySize(bzAllJoynMgrIfcTbl) },
    { "org.AllSeen.AllJoyn",      bzAllJoynIfcTbl,      ArraySize(bzAllJoynIfcTbl) },
};

const size_t ifcTableSize = ArraySize(ifcTables);



} // namespace bluez
} // namespace ajn
