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

#ifndef NOTIFICATIONPRODUCER_H_
#define NOTIFICATIONPRODUCER_H_

#include <alljoyn/BusObject.h>

namespace ajn {
namespace services {

/**
 * NotificationProducer
 * This class has method to dismiss the notification.
 * The producer will send dismiss signal to notify other entities.
 */
class NotificationProducer : public ajn::BusObject {

  public:

    /**
     * Constructor for NotificationProducer. Creates Interface and prepares
     * infrastructure to be able to send Signal
     * @param bus         - BusAttachment that is used
     * @param status      - success/failure
     */
    NotificationProducer(ajn::BusAttachment* bus, QStatus& status);

    /**
     * Destructor for NotificationTransport
     */
    virtual ~NotificationProducer() = 0;
    /**
     * Callback for GetProperty
     * @param ifcName - interface name
     * @param propName - property name to get
     * @param val - value requested
     * @return status
     */
    QStatus Get(const char* ifcName, const char* propName, MsgArg& val);
    /**
     * Callback for SetProperty
     * @param ifcName - interface name
     * @param propName - property name to set
     * @param val - value to set
     * @return status
     */
    QStatus Set(const char* ifcName, const char* propName, MsgArg& val);
  protected:
    /**
     *  pointer to InterfaceDescription
     */
    InterfaceDescription* m_InterfaceDescription;
    /**
     *  pointer to BusAttachment
     */
    ajn::BusAttachment* m_BusAttachment;
  private:

};
} //namespace services
} //namespace ajn

#endif /* NOTIFICATIONPRODUCER_H_ */
