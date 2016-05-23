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

#include <alljoyn/controlpanel/Action.h>
#include <alljoyn/controlpanel/ControlPanelService.h>
#include "../BusObjects/ActionBusObject.h"
#include "../ControlPanelConstants.h"
#include <alljoyn/controlpanel/LogModule.h>

namespace ajn {
namespace services {
using namespace cpsConsts;

Action::Action(qcc::String const& name, Widget* rootWidget) : Widget(name, rootWidget, ACTION)
{
}

Action::Action(qcc::String const& name, Widget* rootWidget, ControlPanelDevice* device) :
    Widget(name, rootWidget, device, ACTION)
{

}

Action::~Action()
{
}

WidgetBusObject* Action::createWidgetBusObject(BusAttachment* bus, qcc::String const& objectPath,
                                               uint16_t langIndx, QStatus& status)
{
    return new ActionBusObject(bus, objectPath, langIndx, status, this);
}

QStatus Action::executeAction()
{
    if (m_ControlPanelMode == CONTROLLEE_MODE) {
        QCC_DbgHLPrintf(("Cannot execute Action. Widget is a Controllee widget"));
        return ER_NOT_IMPLEMENTED;
    }

    if (!m_BusObjects.size()) {
        QCC_DbgHLPrintf(("Cannot execute Action. BusObject is not set"));
        return ER_BUS_BUS_NOT_STARTED;
    }

    return ((ActionBusObject*)m_BusObjects[0])->ExecuteAction();
}

bool Action::executeCallBack()
{
    return false;
}

} /* namespace services */
} /* namespace ajn */
