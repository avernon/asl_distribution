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

#include <alljoyn/controlpanel/Label.h>
#include "../ControlPanelConstants.h"
#include "../BusObjects/LabelBusObject.h"

namespace ajn {
namespace services {
using namespace cpsConsts;

Label::Label(qcc::String const& name, Widget* rootWidget) :
    Widget(name, rootWidget, WIDGET_TYPE_LABEL), m_LabelWidgetGetLabels(0)
{
}

Label::Label(qcc::String const& name, Widget* rootWidget, ControlPanelDevice* device) :
    Widget(name, rootWidget, device, WIDGET_TYPE_LABEL), m_LabelWidgetGetLabels(0)
{
}

Label::~Label()
{
}

WidgetBusObject* Label::createWidgetBusObject(BusAttachment* bus, qcc::String const& objectPath,
                                              uint16_t langIndx, QStatus& status)
{
    return new LabelBusObject(bus, objectPath, langIndx, status, this);
}

const std::vector<qcc::String>& Label::getLabels() const
{
    return m_LabelWidgetLabels;
}

void Label::setLabels(const std::vector<qcc::String>& labels)
{
    m_LabelWidgetLabels = labels;
}

GetStringFptr Label::getGetLabels() const
{
    return m_LabelWidgetGetLabels;
}

void Label::setGetLabels(GetStringFptr getLabels)
{
    m_LabelWidgetGetLabels = getLabels;
}

QStatus Label::fillLabelArg(MsgArg& val, uint16_t languageIndx)
{
    if (!(m_LabelWidgetLabels.size() > languageIndx) && !m_LabelWidgetGetLabels) {
        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    }

    return val.Set(AJPARAM_STR.c_str(), m_LabelWidgetGetLabels ? m_LabelWidgetGetLabels(languageIndx) :
                   m_LabelWidgetLabels[languageIndx].c_str());
}

QStatus Label::readLabelArg(MsgArg* val)
{
    QStatus status = ER_OK;
    char* label;
    CHECK_AND_RETURN(val->Get(AJPARAM_STR.c_str(), &label))
    m_Label = label;
    return status;
}

} /* namespace services */
} /* namespace ajn */
