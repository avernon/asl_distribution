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

#ifndef ACEVENTSANDACTIONS_H_
#define ACEVENTSANDACTIONS_H_

#include <qcc/platform.h>
#include <qcc/String.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/BusObject.h>
#include <alljoyn/MsgArg.h>
#include <alljoyn/Status.h>

namespace ajn {
namespace services {

/**
 * ACEventsAndActions is the bus object that implements events and actions for the ACServerSample.
 */
class ACEventsAndActions : public ajn::BusObject {
  public:
    /**
     * ACEventsAndActions CTOR.
     * @param bus attachment.
     */
    ACEventsAndActions(ajn::BusAttachment* bus);
    /**
     * ACEventsAndActions DTOR.
     */
    virtual ~ACEventsAndActions();

    /**
     * Get property value.
     * @param ifcName - interface name
     * @param propName - property name
     * @param val - value to get
     * @return status
     */
    QStatus Get(const char* ifcName, const char* propName, MsgArg& val);

    /**
     * Set property value.
     * @param ifcName - interface name
     * @param propName - property name
     * @param val - value to set
     * @return status
     */
    QStatus Set(const char* ifcName, const char* propName, MsgArg& val);

    /**
     * send event method
     * @param actualEvent - send relevant signal for the event
     * @return status
     */
    QStatus SendEvent(const InterfaceDescription::Member* actualEvent);

    /**
     * send events for actions
     */
    void SendEventsForActions();

  private:
    void ActionSetModeToAuto(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);
    void ActionSetModeToCool(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);
    void ActionSetModeToHeat(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);
    void ActionSetModeToFan(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);
    void ActionSetModeToOff(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);
    void Check_MethodReply(const Message& msg, QStatus status);

    void EventsInterface();
    void ActionsInterface();

    BusAttachment* bus;
    const InterfaceDescription::Member* temperature80ReachedMember;
    const InterfaceDescription::Member* temperature60ReachedMember;
    const InterfaceDescription::Member* modeSetToOffMember;
    const InterfaceDescription::Member* modeSetToOnMember;
    qcc::String version;
};

} //namespace services
} //namespace ajn

#endif /* ACEVENTSANDACTIONS_H_ */
