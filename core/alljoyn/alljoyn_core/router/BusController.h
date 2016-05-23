# Contributed by Qualcomm Connected Experiences, Inc.,
# with authorization from the AllSeen Alliance, Inc.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# 
# Pursuant to Section 1 of the License, the work of authorship constituting
# a Work and any Contribution incorporated in the Work shall mean only that
# Contributor's code submissions authored by that Contributor.  Any rights
# granted under the License are conditioned upon acceptance of these
# clarifications.
/**
 * @file
 *
 * BusController is responsible for responding to standard DBus and Bus
 * specific messages directed at the bus itself.
 */

/******************************************************************************
 *
 *
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

#ifndef _ALLJOYN_BUSCONTROLLER_H
#define _ALLJOYN_BUSCONTROLLER_H

#include <qcc/platform.h>

#include <alljoyn/MsgArg.h>

#include "Bus.h"
#include "DBusObj.h"
#include "AllJoynObj.h"
#include "AllJoynDebugObj.h"
#include "SessionlessObj.h"
#include "ProtectedAuthListener.h"

namespace ajn {

/**
 * BusController is responsible for responding to DBus and AllJoyn
 * specific messages directed at the bus itself.
 */
class BusController {
  public:

    /**
     * Constructor
     *
     * @param bus           Bus to associate with this controller.
     * @param authListener  Optional authentication listener
     */
    BusController(Bus& bus, AuthListener* authListener = NULL);

    /**
     * Destructor
     */
    virtual ~BusController();

    /**
     * Initialize the bus controller and start the bus
     *
     * @param listeSpecs  The listen specs for the bus.
     *
     * @return  Returns ER_OK if controller was successfully initialized.
     */
    QStatus Init(const qcc::String& listenSpecs);

    /**
     * Stop the bus controller.
     *
     * @return ER_OK if successful.
     */
    QStatus Stop();

    /**
     * Join the bus controller.
     *
     * @return ER_OK if successful.
     */
    QStatus Join();

    /**
     * Return the daemon bus object responsible for org.alljoyn.Bus.
     *
     * @return The AllJoynObj.
     */
    AllJoynObj& GetAllJoynObj() { return alljoynObj; }

    /**
     * Return the bus associated with this bus controller
     *
     * @return Return the bus
     */
    Bus& GetBus() { return bus; }

    /**
     * ObjectRegistered callback.
     *
     * @param obj   BusObject that has been registered
     */
    void ObjectRegistered(BusObject* obj);

    /**
     * Get the sessionlessObj.
     *
     * @return   The sessionlessObj singleton
     */
    SessionlessObj& GetSessionlessObj() {
        return sessionlessObj;
    }

    /**
     * Get the auth listener for this bus controller
     */
    AuthListener* GetAuthListener() { return authListener; }

  private:

    Bus& bus;

    /** Listener for authenticating clients */
    AuthListener* authListener;

    /** Bus object responsible for org.freedesktop.DBus */
    DBusObj dbusObj;

    /** Bus object responsible for org.alljoyn.Bus */
    AllJoynObj alljoynObj;

    /** Bus object responsible for org.alljoyn.Sessionless */
    SessionlessObj sessionlessObj;

#ifndef NDEBUG
    /** Bus object responsible for org.alljoyn.Debug */
    debug::AllJoynDebugObj alljoynDebugObj;
#endif

    /** Event to wait on while initialization completes */
    bool initComplete;
};

}

#endif
