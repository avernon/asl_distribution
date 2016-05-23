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

#ifdef _WIN32
/* Disable deprecation warnings */
#pragma warning(disable: 4996)
#endif

#include <alljoyn/controlpanel/RootWidget.h>
#include <alljoyn/controlpanel/ControlPanelService.h>
#include "../BusObjects/NotificationActionBusObject.h"
#include <alljoyn/controlpanel/LogModule.h>

namespace ajn {
namespace services {

RootWidget::RootWidget(qcc::String const& name, Widget* rootWidget, WidgetType widgetType) :
    Widget(name, rootWidget, widgetType), m_NotificationActionBusObject(0), m_ObjectPath("")
{
}

RootWidget::RootWidget(qcc::String const& name, Widget* rootWidget, qcc::String const& objectPath, ControlPanelDevice* device,
                       WidgetType widgetType) :
    Widget(name, rootWidget, device, widgetType), m_NotificationActionBusObject(0), m_ObjectPath(objectPath)
{
}

RootWidget::~RootWidget()
{
}

QStatus RootWidget::SendDismissSignal()
{
    if (!m_NotificationActionBusObject) {
        return ER_BUS_OBJECT_NOT_REGISTERED;
    }

    return ((NotificationActionBusObject*)m_NotificationActionBusObject)->SendDismissSignal();
}

QStatus RootWidget::setNotificationActionBusObject(BusObject* notificationActionBusObject)
{
    if (!notificationActionBusObject) {
        QCC_DbgHLPrintf(("Could not add a NULL notificationActionBusObject"));
        return ER_BAD_ARG_1;
    }

    if (m_NotificationActionBusObject) {
        QCC_DbgHLPrintf(("Could not set notificationActionBusObject. NotificationActionBusObject already set"));
        return ER_BUS_PROPERTY_ALREADY_EXISTS;
    }

    m_NotificationActionBusObject = notificationActionBusObject;
    return ER_OK;
}

QStatus RootWidget::unregisterObjects(BusAttachment* bus)
{
    QStatus status = Widget::unregisterObjects(bus);
    if (status != ER_OK) {
        QCC_LogError(status, ("Could not unregister BusObjects"));
    }

    if (m_NotificationActionBusObject) {
        bus->UnregisterBusObject(*m_NotificationActionBusObject);
        delete m_NotificationActionBusObject;
        m_NotificationActionBusObject = 0;
    }
    return status;
}

QStatus RootWidget::registerObjects(BusAttachment* bus)
{
    return Widget::registerObjects(bus, m_ObjectPath);
}

QStatus RootWidget::registerObjects(BusAttachment* bus, qcc::String const& objectPath)
{
    return Widget::registerObjects(bus, objectPath);
}

QStatus RootWidget::registerObjects(BusAttachment* bus, LanguageSet const& languageSet, qcc::String const& objectPathPrefix,
                                    qcc::String const& objectPathSuffix, bool isRoot)
{
    return Widget::registerObjects(bus, languageSet, objectPathPrefix, objectPathSuffix, isRoot);
}

} /* namespace services */
} /* namespace ajn */
