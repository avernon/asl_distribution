/******************************************************************************
 * Copyright (c) 2013 - 2014, AllSeen Alliance. All rights reserved.
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

#include <alljoyn/controlpanel/Widgets/LabelWidget.h>
#include <alljoyn/controlpanel/Definitions.h>
#include <alljoyn/controlpanel/Common/ControlMarshalUtil.h>

void initializeLabelWidget(LabelWidget* widget)
{
    initializeBaseWidget(&widget->base);
    widget->label = NULL;
    widget->getLabel = NULL;

    widget->base.marshalAllProp = &marshalAllLabelProperties;
}

AJ_Status marshalLabelLabel(LabelWidget* widget, AJ_Message* reply, uint16_t language)
{
    if (language >= widget->base.numLanguages) {
        return AJ_ERR_UNEXPECTED;
    }

    if (widget->getLabel) {
        return AJ_MarshalArgs(reply, PROPERTY_TYPE_LABEL_SIG, widget->getLabel(widget, language));
    }
    return AJ_MarshalArgs(reply, PROPERTY_TYPE_LABEL_SIG, widget->label[language]);
}

AJ_Status marshalAllLabelProperties(BaseWidget* widget, AJ_Message* reply, uint16_t language)
{
    AJ_Status status;
    AJ_Arg labelGetAllArray;

    status = AJ_MarshalContainer(reply, &labelGetAllArray, AJ_ARG_ARRAY);
    if (status != AJ_OK) {
        return status;
    }

    status = marshalAllBaseProperties(widget, reply, language);
    if (status != AJ_OK) {
        return status;
    }

    status = AddPropertyForGetAll(reply, PROPERTY_TYPE_LABEL_NAME, PROPERTY_TYPE_LABEL_SIG, widget, language, (MarshalWidgetFptr)marshalLabelLabel);
    if (status != AJ_OK) {
        return status;
    }

    status = AddPropertyForGetAll(reply, PROPERTY_TYPE_OPTPARAMS_NAME, PROPERTY_TYPE_OPTPARAMS_SIG, widget, language, marshalOnlyBaseOptParam);
    if (status != AJ_OK) {
        return status;
    }

    return AJ_MarshalCloseContainer(reply, &labelGetAllArray);
}
