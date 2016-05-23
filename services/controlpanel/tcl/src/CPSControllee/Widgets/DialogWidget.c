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

#include <alljoyn/controlpanel/Widgets/DialogWidget.h>
#include <alljoyn/controlpanel/Definitions.h>
#include <alljoyn/controlpanel/Common/ControlMarshalUtil.h>

void initializeDialogWidget(DialogWidget* widget)
{
    initializeBaseWidget(&widget->base);
    widget->numActions = 0;
    widget->message = NULL;
    widget->getMessage = NULL;

    widget->base.marshalOptParam = &marshalDialogOptParam;
    widget->base.marshalAllProp = &marshalAllDialogProperties;

    initializeDialogOptParam(&widget->optParams);
}

AJ_Status marshalDialogMessage(DialogWidget* widget, AJ_Message* reply, uint16_t language)
{
    if (language >= widget->base.numLanguages) {
        return AJ_ERR_UNEXPECTED;
    }

    if (widget->getMessage) {
        return AJ_MarshalArgs(reply, PROPERTY_TYPE_MESSAGE_SIG, widget->getMessage(widget, language));
    }
    return AJ_MarshalArgs(reply, PROPERTY_TYPE_MESSAGE_SIG, widget->message[language]);
}

AJ_Status marshalDialogNumActions(DialogWidget* widget, AJ_Message* reply, uint16_t language)
{
    return AJ_MarshalArgs(reply, PROPERTY_TYPE_NUM_ACTIONS_SIG, widget->numActions);
}

void initializeDialogOptParam(DialogOptParams* optParam)
{
    optParam->labelAction1 = NULL;
    optParam->getLabelAction1 = NULL;
    optParam->labelAction2 = NULL;
    optParam->getLabelAction2 = NULL;
    optParam->labelAction3 = NULL;
    optParam->getLabelAction3 = NULL;
}

AJ_Status marshalDialogOptParam(BaseWidget* widget, AJ_Message* reply, uint16_t language)
{
    if (language >= widget->numLanguages) {
        return AJ_ERR_UNEXPECTED;
    }
    DialogOptParams* optParams = &((DialogWidget*)widget)->optParams;
    AJ_Status status;
    AJ_Arg dialogOptParams;

    status = StartOptionalParams(reply, &dialogOptParams);
    if (status != AJ_OK) {
        return status;
    }

    status = marshalBaseOptParam(widget, reply, language);
    if (status != AJ_OK) {
        return status;
    }

    if (optParams->getLabelAction1) {
        const char* labelAction1 = optParams->getLabelAction1((DialogWidget*)widget, language);
        status = AddBasicOptionalParam(reply, DIALOG_LABEL_ACTION1, DIALOG_LABEL_ACTION1_SIG, &labelAction1);
        if (status != AJ_OK) {
            return status;
        }
    } else if (optParams->labelAction1) {
        status = AddBasicOptionalParam(reply, DIALOG_LABEL_ACTION1, DIALOG_LABEL_ACTION1_SIG, &optParams->labelAction1[language]);
        if (status != AJ_OK) {
            return status;
        }
    }

    if (optParams->getLabelAction2) {
        const char* labelAction2 = optParams->getLabelAction2((DialogWidget*)widget, language);
        status = AddBasicOptionalParam(reply, DIALOG_LABEL_ACTION2, DIALOG_LABEL_ACTION2_SIG, &labelAction2);
        if (status != AJ_OK) {
            return status;
        }
    } else if (optParams->labelAction2) {
        status = AddBasicOptionalParam(reply, DIALOG_LABEL_ACTION2, DIALOG_LABEL_ACTION2_SIG, &optParams->labelAction2[language]);
        if (status != AJ_OK) {
            return status;
        }
    }

    if (optParams->getLabelAction3) {
        const char* labelAction3 = optParams->getLabelAction3((DialogWidget*)widget, language);
        status = AddBasicOptionalParam(reply, DIALOG_LABEL_ACTION3, DIALOG_LABEL_ACTION3_SIG, &labelAction3);
        if (status != AJ_OK) {
            return status;
        }
    } else if (optParams->labelAction3) {
        status = AddBasicOptionalParam(reply, DIALOG_LABEL_ACTION3, DIALOG_LABEL_ACTION3_SIG, &optParams->labelAction3[language]);
        if (status != AJ_OK) {
            return status;
        }
    }

    return AJ_MarshalCloseContainer(reply, &dialogOptParams);
}

AJ_Status marshalAllDialogProperties(BaseWidget* widget, AJ_Message* reply, uint16_t language)
{
    AJ_Status status;
    AJ_Arg dialogGetAllArray;

    status = AJ_MarshalContainer(reply, &dialogGetAllArray, AJ_ARG_ARRAY);
    if (status != AJ_OK) {
        return status;
    }

    status = marshalAllBaseProperties(widget, reply, language);
    if (status != AJ_OK) {
        return status;
    }

    status = AddPropertyForGetAll(reply, PROPERTY_TYPE_OPTPARAMS_NAME, PROPERTY_TYPE_OPTPARAMS_SIG, widget, language, marshalDialogOptParam);
    if (status != AJ_OK) {
        return status;
    }

    status = AddPropertyForGetAll(reply, PROPERTY_TYPE_MESSAGE_NAME, PROPERTY_TYPE_MESSAGE_SIG, widget, language,
                                  (MarshalWidgetFptr)marshalDialogMessage);
    if (status != AJ_OK) {
        return status;
    }

    status = AddPropertyForGetAll(reply, PROPERTY_TYPE_NUM_ACTIONS_NAME, PROPERTY_TYPE_NUM_ACTIONS_SIG, widget, language,
                                  (MarshalWidgetFptr)marshalDialogNumActions);
    if (status != AJ_OK) {
        return status;
    }

    return AJ_MarshalCloseContainer(reply, &dialogGetAllArray);
}
