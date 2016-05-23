/******************************************************************************
 * Copyright (c) 2013, AllSeen Alliance. All rights reserved.
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

#ifndef NOTIFICATIONACTIONBUSOBJECT_H_
#define NOTIFICATIONACTIONBUSOBJECT_H_

#include <alljoyn/BusAttachment.h>
#include <alljoyn/BusObject.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/controlpanel/NotificationAction.h>
#include <vector>
#include "IntrospectionNode.h"

namespace ajn {
namespace services {

/**
 * NotificationActionBusObject class. BusObject for a NotificationAction
 */
class NotificationActionBusObject : public BusObject {
  public:

    /**
     * Constructor for NotificationActionBusObject
     * @param bus - bus used to create the interface
     * @param objectPath - objectPath of BusObject
     * @param status - success/failure
     */
    NotificationActionBusObject(BusAttachment* bus, qcc::String const& objectPath,
                                QStatus& status, NotificationAction* notificationAction = 0);

    /**
     * Destructor of NotificationActionBusObject class
     */
    virtual ~NotificationActionBusObject();

    /**
     * Callback for Alljoyn when GetProperty is called on this BusObject
     * @param interfaceName - the name of the Interface
     * @param propName - the name of the Property
     * @param val - the MsgArg to fill
     * @return status - success/failure
     */
    QStatus Get(const char* interfaceName, const char* propName, MsgArg& val);

    /**
     * Callback for Alljoyn when SetProperty is called on this BusObject
     * @param interfaceName - the name of the Interface
     * @param propName - the name of the Property
     * @param val - the MsgArg that contains the new Value
     * @return status - success/failure
     */
    QStatus Set(const char* ifcName, const char* propName, MsgArg& val);

    /**
     * Send a Dismiss Signal for This Notification Action
     * @return
     */
    QStatus SendDismissSignal();

    /**
     * Callback for DismissSignal signal
     * @param member - signal received
     * @param srcPath - objectPath of signal
     * @param msg - Message received
     */
    void DismissSignal(const InterfaceDescription::Member* member, const char* srcPath, Message& msg);

    /**
     * Set RemoteController
     * @param bus - busAttachment
     * @param deviceBusName
     * @param sessionId
     * @return
     */
    QStatus setRemoteController(BusAttachment* bus, qcc::String const& deviceBusName, SessionId sessionId);

    /**
     * Check compatibility of the versions
     * @return status - success/failure
     */
    QStatus checkVersions();

    /**
     * Introspect to receive childNodes
     * @param childNodes - childNodes found during introspection
     * @return status - success/failure
     */
    QStatus Introspect(std::vector<IntrospectionNode>& childNodes);

    /**
     * remove the SignalHandler of the BusObject
     * @param bus - busAttachment used to remove the signalHandlers
     * @return status - success/failure
     */
    virtual QStatus UnregisterSignalHandler(BusAttachment* bus);

  private:

    /**
     * The pointer used to send signal/register Signal Handler
     */
    const ajn::InterfaceDescription::Member* m_SignalDismiss;

    /**
     * The NotificationAction of this BusObject
     */
    NotificationAction* m_NotificationAction;

    /**
     * Pointer to ProxybusObject for this widget
     */
    ProxyBusObject* m_Proxy;

    /**
     * ObjectPath of the BusObject
     */
    qcc::String m_ObjectPath;

    /**
     * InterfaceDescription of the BusObject
     */
    InterfaceDescription* m_InterfaceDescription;

};

} /* namespace services */
} /* namespace ajn */
#endif /* NOTIFICATIONACTIONBUSOBJECT_H_ */
