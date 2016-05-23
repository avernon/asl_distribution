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

#include "WidgetProxyBusObjectListener.h"
#include "../ControlPanelConstants.h"
#include "WidgetBusObject.h"
#include <alljoyn/controlpanel/ControlPanelService.h>
#include <alljoyn/controlpanel/LogModule.h>

namespace ajn {
namespace services {
using namespace cpsConsts;

WidgetProxyBusObjectListener::WidgetProxyBusObjectListener(Widget* widget, WidgetBusObject* busObject) :
    m_Widget(widget), m_BusObject(busObject)
{


}

WidgetProxyBusObjectListener::~WidgetProxyBusObjectListener()
{

}

void WidgetProxyBusObjectListener::GetAllPropertiesCallBack(QStatus status, ProxyBusObject* obj, const MsgArg& values, void* context)
{
    if (!m_Widget || !m_BusObject) {
        QCC_DbgHLPrintf(("WidgetProxyBusObjectListener does not have widget or BusObject set"));
        delete this;     //Finished using listener - needs to be deleted
        return;
    }

    ControlPanelDevice* device = m_Widget->getDevice();
    ControlPanelListener* listener = device ? device->getListener() : NULL;
    if (status != ER_OK) {
        QCC_DbgHLPrintf(("Something went wrong reloading properties"));
        if (listener) {
            listener->errorOccured(device, status, REFRESH_PROPERTIES, "Something went wrong reloading properties");
        }
        delete this;     //Finished using listener - needs to be deleted
        return;
    }

    status = m_BusObject->fillAllProperties(values);
    if (status != ER_OK) {
        QCC_LogError(status, ("Something went wrong reloading properties"));
        if (listener) {
            listener->errorOccured(device, status, REFRESH_PROPERTIES, "Something went wrong reloading properties");
        }
        delete this;     //Finished using listener - needs to be deleted
        return;
    }

    if (listener) {
        listener->signalPropertiesChanged(device, m_Widget);
    }

    delete this;     //Finished using listener - needs to be deleted
}

} /* namespace services */
} /* namespace ajn */
