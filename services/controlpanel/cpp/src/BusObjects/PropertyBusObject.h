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

#ifndef PROPERTYBUSOBJECT_H_
#define PROPERTYBUSOBJECT_H_

#include "WidgetBusObject.h"

namespace ajn {
namespace services {

/**
 * PropertyBusObject - BusObject for Property
 */
class PropertyBusObject : public WidgetBusObject {
  public:

    /**
     * Constructor for PropertyBusObject class
     * @param bus - the bus to create the interface
     * @param objectPath - objectPath of BusObject
     * @param langIndx - the languageIndex of the BusObject
     * @param status - success/failure
     * @param widget - the widget associated with the BusObject
     */
    PropertyBusObject(ajn::BusAttachment* bus, qcc::String const& objectPath,
                      uint16_t langIndx, QStatus& status, Widget* widget);

    /**
     * Destructor for the BusObject
     */
    virtual ~PropertyBusObject();

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
    QStatus Set(const char* interfaceName, const char* propName, MsgArg& val);

    /**
     * Send a signal when the property's value has changed
     * @return status - success/failure
     */
    QStatus SendValueChangedSignal();

    /**
     * Value Change Signal Callback
     * @param member - signal sent
     * @param srcPath - objectPath it was sent for
     * @param msg - the Message sent
     */
    void ValueChanged(const InterfaceDescription::Member* member, const char* srcPath, Message& msg);

    /**
     * Set the value of the remote property
     * @param value - value to be set
     * @return status - success/failure
     */
    QStatus SetValue(MsgArg& value);

    /**
     * remove the SignalHandler of the BusObject
     * @param bus - busAttachment used to remove the signalHandlers
     * @return status - success/failure
     */
    QStatus UnregisterSignalHandler(BusAttachment* bus);

  private:

    /**
     * Store member to send Value Changed signal
     */
    const ajn::InterfaceDescription::Member* m_SignalValueChanged;

    /**
     * Fill Property in Widget
     * @param key - keyName of Property
     * @param variant - the value of the Property
     * @return status - success/failure
     */
    QStatus fillProperty(char* key, MsgArg* variant);

    /**
     * Add the SignalHandler for propertyChanged signal
     * @param bus - bus used to add signal
     * @return status - success/failure
     */
    QStatus addSignalHandler(BusAttachment* bus);
};

} /* namespace services */
} /* namespace ajn */
#endif /* PROPERTYBUSOBJECT_H_ */
