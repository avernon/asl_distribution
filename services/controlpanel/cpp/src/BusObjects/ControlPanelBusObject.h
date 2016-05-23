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

#ifndef CONTROLPANELBUSOBJECT_H_
#define CONTROLPANELBUSOBJECT_H_

#include <alljoyn/BusAttachment.h>
#include <alljoyn/BusObject.h>
#include <alljoyn/InterfaceDescription.h>
#include <vector>
#include "IntrospectionNode.h"

namespace ajn {
namespace services {

/**
 * ControlPanelBusObject class. BusObject for a ControlPanel
 */
class ControlPanelBusObject : public BusObject {
  public:

    /**
     * Constructor for ControlPanelBusObject
     * @param bus - bus used to create the interface
     * @param objectPath - objectPath of BusObject
     * @param status - success/failure
     */
    ControlPanelBusObject(ajn::BusAttachment* bus, qcc::String const& objectPath, QStatus& status);

    /**
     * Destructor of ControlPanelBusObject class
     */
    virtual ~ControlPanelBusObject();

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

  private:

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
#endif /* CONTROLPANELBUSOBJECT_H_ */

