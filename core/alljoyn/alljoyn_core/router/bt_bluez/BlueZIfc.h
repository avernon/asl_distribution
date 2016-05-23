/**
 * @file
 * org.bluez interface table definitions
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
#ifndef _ALLJOYN_BLUEZIFC_H
#define _ALLJOYN_BLUEZIFC_H

#include <qcc/platform.h>

#include <alljoyn/Message.h>


namespace ajn {
namespace bluez {

struct InterfaceDesc {
    AllJoynMessageType type;
    const char* name;
    const char* inputSig;
    const char* outSig;
    const char* argNames;
    uint8_t annotation;
};

struct InterfaceTable {
    const char* ifcName;
    const InterfaceDesc* desc;
    size_t tableSize;
};

#define ALLJOYN_UUID "414a0000-1c25-481f-9dfb-59193d238280"

extern const InterfaceDesc bzObjMgrIfcTbl[];
extern const InterfaceDesc bzAdapter1IfcTbl[];
extern const InterfaceDesc bzDevice1IfcTbl[];
extern const InterfaceDesc bzAllJoynMgrIfcTbl[];
extern const InterfaceDesc bzAllJoynIfcTbl[];
extern const char* bzObjMgrIfc;
extern const char* bzAdapter1Ifc;
extern const char* bzAllJoynIfc;
extern const char* bzDevice1Ifc;

extern const InterfaceTable ifcTables[];
extern const size_t ifcTableSize;

extern const char* bzBusName;
extern const char* bzMgrObjPath;


} // namespace bluez
} // namespace ajn

#endif
