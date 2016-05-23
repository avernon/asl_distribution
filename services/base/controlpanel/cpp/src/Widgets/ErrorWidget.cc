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

#include "alljoyn/controlpanel/ErrorWidget.h"
#include "../ControlPanelConstants.h"

#define ERROR_WIDGET_LABEL "NOT AVAILABLE"

namespace ajn {
namespace services {
using namespace cpsConsts;

ErrorWidget::ErrorWidget(qcc::String const& name, Widget* rootWidget, Widget* originalWidget, ControlPanelDevice* device) :
    Widget(name, rootWidget, device, WIDGET_TYPE_ERROR), m_OriginalWidget(originalWidget)
{
    m_Label.assign(ERROR_WIDGET_LABEL);
}

ErrorWidget::~ErrorWidget()
{
    if (m_OriginalWidget) {
        delete m_OriginalWidget;
    }
}

WidgetBusObject* ErrorWidget::createWidgetBusObject(BusAttachment* bus, qcc::String const& objectPath,
                                                    uint16_t langIndx, QStatus& status)
{
    QCC_UNUSED(bus);
    QCC_UNUSED(objectPath);
    QCC_UNUSED(langIndx);
    QCC_UNUSED(status);
    return NULL;
}

QStatus ErrorWidget::registerObjects(BusAttachment* bus, qcc::String const& objectPath)
{
    QCC_UNUSED(bus);
    QCC_UNUSED(objectPath);
    return ER_OK;
}

QStatus ErrorWidget::unregisterObjects(BusAttachment* bus)
{
    if (m_OriginalWidget) {
        return m_OriginalWidget->unregisterObjects(bus);
    }
    return ER_OK;
}

Widget* ErrorWidget::getOriginalWidget() const
{
    return m_OriginalWidget;
}

} /* namespace services */
} /* namespace ajn */
