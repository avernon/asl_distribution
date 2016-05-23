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

#include <alljoyn/controlpanel/Widgets/PropertyWidget.h>
#include <alljoyn/controlpanel/Common/ControlMarshalUtil.h>
#include <alljoyn/controlpanel/Common/DateTimeUtil.h>

void initializePropertyWidget(PropertyWidget* widget)
{
    initializeBaseWidget(&widget->base);
    widget->signature = NULL;
    widget->getValue = NULL;
    widget->propertyType = SINGLE_VALUE_PROPERTY;

    initializePropertyOptParam(&widget->optParams);
    widget->optParams.constraintRange.signature = &widget->signature;

    widget->base.marshalOptParam = &marshalPropertyOptParam;
    widget->base.marshalAllProp = &marshalAllPropertyProperties;
}

AJ_Status marshalPropertyValue(PropertyWidget* widget, AJ_Message* reply, uint16_t language)
{
    switch (widget->propertyType) {
    case SINGLE_VALUE_PROPERTY:
        return MarshalVariant(reply, widget->signature, widget->getValue(widget));

    case DATE_VALUE_PROPERTY:
        return marshalDatePropertyValue(widget->getValue(widget), reply);

    case TIME_VALUE_PROPERTY:
        return marshalTimePropertyValue(widget->getValue(widget), reply);
    }
    return AJ_ERR_UNEXPECTED;
}

AJ_Status unmarshalPropertyValue(PropertyWidget* widget, AJ_Message* message, void* newValue, const char* lockerId)
{
    AJ_Status status = AJ_ERR_UNEXPECTED;

    switch (widget->propertyType) {
    case SINGLE_VALUE_PROPERTY:
        return AJ_UnmarshalArgs(message, widget->signature, newValue);

    case DATE_VALUE_PROPERTY:
        return unmarshalDatePropertyValue(newValue, message);

    case TIME_VALUE_PROPERTY:
        return unmarshalTimePropertyValue(newValue, message);
    }
    return status;
}

void initializePropertyOptParam(PropertyOptParams* optParams)
{
    memset(optParams, 0, sizeof(PropertyOptParams));
    initializeConstraintRange(&optParams->constraintRange);
}

AJ_Status marshalPropertyOptParam(BaseWidget* widget, AJ_Message* reply, uint16_t language)
{
    PropertyOptParams* optParams = &((PropertyWidget*)widget)->optParams;
    AJ_Status status;
    AJ_Arg propertyOptParams;

    status = StartOptionalParams(reply, &propertyOptParams);
    if (status != AJ_OK) {
        return status;
    }

    status = marshalBaseOptParam(widget, reply, language);
    if (status != AJ_OK) {
        return status;
    }

    if (optParams->getUnitOfMeasure) {
        const char* unitOfMeasure = optParams->getUnitOfMeasure((PropertyWidget*)widget, language);
        status = AddBasicOptionalParam(reply, PROPERTY_UNIT_OF_MEASURE, PROPERTY_UNIT_OF_MEASURE_SIG, &unitOfMeasure);
        if (status != AJ_OK) {
            return status;
        }
    } else if (optParams->unitOfMeasure) {
        const char* unitOfMeasure = optParams->unitOfMeasure[language];
        status = AddBasicOptionalParam(reply, PROPERTY_UNIT_OF_MEASURE, PROPERTY_UNIT_OF_MEASURE_SIG, &unitOfMeasure);
        if (status != AJ_OK) {
            return status;
        }
    }

    if ((optParams->constraintList || optParams->getConstraint) && optParams->numConstraints) {
        status = marshalConstraintList(widget, optParams->constraintList, reply, optParams->numConstraints, ((PropertyWidget*)widget)->signature, language);
        if (status != AJ_OK) {
            return status;
        }
    }

    if (optParams->constraintRangeDefined) {
        status = marshalConstraintRange(&optParams->constraintRange, reply);
        if (status != AJ_OK) {
            return status;
        }
    }

    return AJ_MarshalCloseContainer(reply, &propertyOptParams);
}

AJ_Status marshalAllPropertyProperties(BaseWidget* widget, AJ_Message* reply, uint16_t language)
{
    AJ_Status status;
    AJ_Arg propertyGetAllArray;

    status = AJ_MarshalContainer(reply, &propertyGetAllArray, AJ_ARG_ARRAY);
    if (status != AJ_OK) {
        return status;
    }

    status = marshalAllBaseProperties(widget, reply, language);
    if (status != AJ_OK) {
        return status;
    }

    status = AddPropertyForGetAll(reply, PROPERTY_TYPE_OPTPARAMS_NAME, PROPERTY_TYPE_OPTPARAMS_SIG, widget, language, marshalPropertyOptParam);
    if (status != AJ_OK) {
        return status;
    }

    status = AddPropertyForGetAll(reply, PROPERTY_TYPE_VALUE_NAME, PROPERTY_TYPE_VALUE_SIG, widget, language, (MarshalWidgetFptr)marshalPropertyValue);
    if (status != AJ_OK) {
        return status;
    }

    return AJ_MarshalCloseContainer(reply, &propertyGetAllArray);
}
