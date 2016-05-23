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

#ifndef NOTIFICATIONTRANSPORT_H_
#define NOTIFICATIONTRANSPORT_H_

#include <alljoyn/BusAttachment.h>
#include <alljoyn/BusObject.h>
#include <alljoyn/InterfaceDescription.h>

namespace ajn {
namespace services {

/**
 * A class implementing the BusObject used to create the Notification interface
 * and register it on the bus
 */
class NotificationTransport : public ajn::BusObject {
  public:

    /**
     * Constructor for NotificationTransport. Creates Interface and prepares
     * infrastructure to be able to send Signal
     * @param bus         - BusAttachment that is used
     * @param servicePath - servicePath of BusObject
     * @param status      - success/failure
     */
    NotificationTransport(ajn::BusAttachment* bus, qcc::String const& servicePath,
                          QStatus& status, qcc::String const& interfaceName);

    /**
     * Destructor for NotificationTransport
     */
    virtual ~NotificationTransport() = 0;

    /**
     * Callback for GetProperty
     * @param ifcName
     * @param propName
     * @param val
     * @return
     */
    QStatus Get(const char* ifcName, const char* propName, ajn::MsgArg& val);

    /**
     * Callback for SetProperty
     * @param ifcName
     * @param propName
     * @param val
     * @return
     */
    QStatus Set(const char* ifcName, const char* propName, ajn::MsgArg& val);

  protected:

    /**
     * The pointer used to send signal/register Signal Handler
     */
    const ajn::InterfaceDescription::Member* m_SignalMethod;
};
} //namespace services
} //namespace ajn

#endif /* NOTIFICATIONTRANSPORT_H_ */
