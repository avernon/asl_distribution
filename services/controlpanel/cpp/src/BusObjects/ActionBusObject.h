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

#ifndef ACTIONBUSOBJECT_H_
#define ACTIONBUSOBJECT_H_

#include "WidgetBusObject.h"

namespace ajn {
namespace services {

/**
 * ActionBusObject - BusObject for Actions
 */
class ActionBusObject : public WidgetBusObject {
  public:

    /**
     * Constructor for ActionBusObject class
     * @param bus - the bus to create the interface
     * @param objectPath - objectPath of BusObject
     * @param langIndx - the languageIndex of the BusObject
     * @param status - success/failure
     * @param widget - the widget associated with the BusObject
     */
    ActionBusObject(ajn::BusAttachment* bus, qcc::String const& objectPath,
                    uint16_t langIndx, QStatus& status, Widget* widget);

    /**
     * Destructor for the BusObject
     */
    virtual ~ActionBusObject();

    /**
     * Callback when Execute is called
     * @param member - the member (method) of the interface that was executed
     * @param msg - the Message of the method
     */
    void ActionExecute(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);

    /**
     * Execute this Action's remoteAction
     * @return status - success/failure
     */
    QStatus ExecuteAction();

    /**
     * PropertyChanged - callback when a propertyChanged signal comes in
     * @param member - the member (signal) of the interface that was fired
     * @param srcPath - path of signal
     * @param msg - the arguments
     */
    void PropertyChanged(const InterfaceDescription::Member* member, const char* srcPath, Message& msg);

    /**
     * Introspect to receive childNodes
     * @param childNodes - childNodes found during introspection
     * @return status - success/failure
     */
    QStatus Introspect(std::vector<IntrospectionNode>& childNodes);
};

} /* namespace services */
} /* namespace ajn */
#endif /* ACTIONBUSOBJECT_H_ */
