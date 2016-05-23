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

#include <ajtcl/services/Common/ConstraintList.h>
#include <ajtcl/services/Common/ControlMarshalUtil.h>
#include <ajtcl/services/Widgets/PropertyWidget.h>

AJ_Status marshalConstraintList(BaseWidget* widget, ConstraintList* constraints, AJ_Message* reply, uint16_t numConstraints,
                                const char* signature, uint16_t language)
{
    AJ_Status status;
    AJ_Arg arrayArg, opParams;
    uint16_t cnt;
    PropertyWidget* propWidget = (PropertyWidget*)widget;
    const void* value;
    const char* display;

    status = StartComplexOptionalParam(reply, &opParams, PROPERTY_CONSTRAINT_LIST, PROPERTY_CONSTRAINT_LIST_SIG);
    if (status != AJ_OK) {
        return status;
    }

    status = AJ_MarshalContainer(reply, &arrayArg, AJ_ARG_ARRAY);
    if (status != AJ_OK) {
        return status;
    }

    for (cnt = 0; cnt < numConstraints; cnt++) {
        if (propWidget->optParams.getConstraint) {
            display = propWidget->optParams.getConstraint(propWidget, cnt, &value, language);
        } else if (constraints[cnt].getDisplay != 0) {
            value = constraints[cnt].value;
            display = constraints[cnt].getDisplay(language);
        } else {
            value = constraints[cnt].value;
            display = constraints[cnt].display[language];
        }
        status = AddConstraintValue(reply, signature, value, display);
        if (status != AJ_OK) {
            return status;
        }
    }

    status = AJ_MarshalCloseContainer(reply, &arrayArg);
    if (status != AJ_OK) {
        return status;
    }

    return AJ_MarshalCloseContainer(reply, &opParams);
}
