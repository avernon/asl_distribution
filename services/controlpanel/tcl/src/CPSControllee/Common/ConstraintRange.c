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

#include <alljoyn/controlpanel/Common/ConstraintRange.h>
#include <alljoyn/controlpanel/Common/ControlMarshalUtil.h>

void initializeConstraintRange(ConstraintRange* constraints)
{
    constraints->minValue = NULL;
    constraints->maxValue = NULL;
    constraints->increment = NULL;
}

AJ_Status marshalConstraintRange(ConstraintRange* constraints, AJ_Message* reply)
{
    AJ_Status status;
    AJ_Arg constraintRange;

    status = StartComplexOptionalParam(reply, &constraintRange, PROPERTY_CONSTRAINT_RANGE, PROPERTY_CONSTRAINT_RANGE_SIG);
    if (status != AJ_OK) {
        return status;
    }

    status = AddConstraintRange(reply, *constraints->signature, constraints->minValue, constraints->maxValue, constraints->increment);
    if (status != AJ_OK) {
        return status;
    }

    return AJ_MarshalCloseContainer(reply, &constraintRange);
}
