/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

#ifndef MY_FIRST_BUS_OBJECT_H_
#define MY_FIRST_BUS_OBJECT_H_

#include <alljoyn/BusObject.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/Status.h>
#include <alljoyn/DBusStd.h>
#include <alljoyn/AllJoynStd.h>
#include <qcc/String.h>

class MyFirstBusObject : public ajn::BusObject {
    public:
        /**
         * Constructor
         */
        MyFirstBusObject(ajn::BusAttachment& mBusAttachment);

        /**
         * Destructor
         */
        ~MyFirstBusObject();

        const uint32_t getNumberOfInterfaces();

        const char * getInterfaceName(uint32_t i); 

        /* Methods to interact with remote BusObjects */
        QStatus doTell(qcc::String uniqueName, qcc::String thought, int sessionId, qcc::String& reply);
        QStatus doShare(qcc::String thought, int sessionId);
        QStatus doBroadcast(qcc::String thought);

    private:
        /* BusMethod methods */
        void handleTell(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);
        /* BusSignal handlers */
        void shareHandler(const ajn::InterfaceDescription::Member* member, const char* srcPath, ajn::Message& msg);
        void broadcastHandler(const ajn::InterfaceDescription::Member* member, const char* srcPath, ajn::Message& msg);

        const ajn::InterfaceDescription::Member* shareMember;
        const ajn::InterfaceDescription::Member* broadcastMember;

};

#endif /* MY_FIRST_BUS_OBJECT_H_ */

