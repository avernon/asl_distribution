/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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

#ifndef WIDGETPROXYBUSOBJECTLISTENER_H_
#define WIDGETPROXYBUSOBJECTLISTENER_H_

#include <alljoyn/BusAttachment.h>
#include "WidgetBusObject.h"
#include <alljoyn/controlpanel/Widget.h>

namespace ajn {
namespace services {

/**
 * WidgetProxyBusObjectListener class - used as listener for GetAllProperties Async Call
 */
class WidgetProxyBusObjectListener : public ProxyBusObject::Listener {

  public:

    /**
     * Constructor of WidgetProxyBusObjectListener class
     * @param widget - widget getallproperties is being executed for
     * @param busObject - busObject being used for call
     */
    WidgetProxyBusObjectListener(Widget* widget, WidgetBusObject* busObject);

    /**
     * Destructor of WidgetProxyBusObjectListener class
     */
    virtual ~WidgetProxyBusObjectListener();

    /**
     * GetAllProperties callback
     * @param status - status of call: success/failure
     * @param obj - proxybusobject used for call
     * @param values - response MsgArg
     * @param context - context passed in to call
     */
    void GetAllPropertiesCallBack(QStatus status, ProxyBusObject* obj, const MsgArg& values, void* context);

  private:

    /**
     * The widget getAllProperties was being executed for
     */
    Widget* m_Widget;

    /**
     * The BusObject getAllProperties was being executed from
     */
    WidgetBusObject* m_BusObject;
};

} /* namespace services */
} /* namespace ajn */

#endif /* WIDGETPROXYBUSOBJECTLISTENER_H_ */
