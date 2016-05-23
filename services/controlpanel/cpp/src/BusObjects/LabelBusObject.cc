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

#include "LabelBusObject.h"
#include "../ControlPanelConstants.h"
#include <alljoyn/controlpanel/ControlPanelService.h>
#include <alljoyn/controlpanel/Label.h>
#include <alljoyn/controlpanel/LogModule.h>

namespace ajn {
namespace services {
using namespace qcc;
using namespace cpsConsts;

LabelBusObject::LabelBusObject(BusAttachment* bus, String const& objectPath, uint16_t langIndx,
                               QStatus& status, Widget* widget) : WidgetBusObject(objectPath, langIndx, status, widget)
{
    if (status != ER_OK) {
        QCC_DbgHLPrintf(("Could not create the BusObject"));
        return;
    }

    m_InterfaceDescription = (InterfaceDescription*) bus->GetInterface(AJ_LABEL_INTERFACE.c_str());
    if (!m_InterfaceDescription) {
        do {
            CHECK_AND_BREAK(bus->CreateInterface(AJ_LABEL_INTERFACE.c_str(), m_InterfaceDescription));
            CHECK_AND_BREAK(addDefaultInterfaceVariables(m_InterfaceDescription));
            CHECK_AND_BREAK(m_InterfaceDescription->AddProperty(AJ_PROPERTY_LABEL.c_str(), AJPARAM_STR.c_str(), PROP_ACCESS_READ));
            m_InterfaceDescription->Activate();
        } while (0);
    }
    if (status != ER_OK) {
        QCC_LogError(status, ("Could not create interface"));
        return;
    }

    status = AddInterface(*m_InterfaceDescription);
    if (status != ER_OK) {
        QCC_LogError(status, ("Could not add interface"));
        return;
    }

    //Get the signal methods for future use
    m_SignalPropertyChanged = m_InterfaceDescription->GetMember(AJ_SIGNAL_PROPERTIES_CHANGED.c_str());
    if (widget->getControlPanelMode() == CONTROLLER_MODE) {
        status = addSignalHandler(bus);
    }
    QCC_DbgPrintf(("Created LabelBusObject successfully"));
}

LabelBusObject::~LabelBusObject() {
}

QStatus LabelBusObject::Get(const char* interfaceName, const char* propName, MsgArg& val)
{
    QCC_DbgTrace(("Get property was called - in LabelBusObject class."));

    if (0 == strcmp(AJ_PROPERTY_LABEL.c_str(), propName)) {
        return ((Label*)m_Widget)->fillLabelArg(val, m_LanguageIndx);
    }

    return WidgetBusObject::Get(interfaceName, propName, val);
}

QStatus LabelBusObject::fillProperty(char* key, MsgArg* variant)
{
    QStatus status = ER_BUS_NO_SUCH_PROPERTY;

    if (strcmp(key, AJ_PROPERTY_LABEL.c_str()) == 0) {
        CHECK_AND_RETURN(((Label*)m_Widget)->readLabelArg(variant))
    }
    return status;
}

} /* namespace services */
} /* namespace ajn */




