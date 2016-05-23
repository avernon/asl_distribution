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

#include <ajtcl/services/Common/DateTimeUtil.h>
#include <ajtcl/services/Common/ControlMarshalUtil.h>

AJ_Status marshalDatePropertyValue(DatePropertyValue* datePropertyValue, AJ_Message* reply)
{
    AJ_Status status;
    AJ_Arg structArg;

    status = AJ_MarshalVariant(reply, DATE_PROPERTY_SIG);
    if (status != AJ_OK) {
        return status;
    }
    status = AJ_MarshalContainer(reply, &structArg, AJ_ARG_STRUCT);
    if (status != AJ_OK) {
        return status;
    }
    status = AJ_MarshalArgs(reply, "q(qqq)", DATE_PROPERTY, datePropertyValue->mDay, datePropertyValue->month, datePropertyValue->fullYear);
    if (status != AJ_OK) {
        return status;
    }

    return AJ_MarshalCloseContainer(reply, &structArg);
}

AJ_Status marshalTimePropertyValue(TimePropertyValue* timePropertyValue, AJ_Message* reply)
{
    AJ_Status status;
    AJ_Arg structArg;

    status = AJ_MarshalVariant(reply, TIME_PROPERTY_SIG);
    if (status != AJ_OK) {
        return status;
    }
    status = AJ_MarshalContainer(reply, &structArg, AJ_ARG_STRUCT);
    if (status != AJ_OK) {
        return status;
    }
    status = AJ_MarshalArgs(reply, "q(qqq)", TIME_PROPERTY, timePropertyValue->hour, timePropertyValue->minute, timePropertyValue->second);
    if (status != AJ_OK) {
        return status;
    }

    return AJ_MarshalCloseContainer(reply, &structArg);
}

AJ_Status unmarshalDatePropertyValue(DatePropertyValue* datePropertyValue, AJ_Message* message)
{
    AJ_Status status;
    AJ_Arg structArg;
    uint16_t widgetType;

    status = AJ_UnmarshalContainer(message, &structArg, AJ_ARG_STRUCT);
    if (status != AJ_OK) {
        return status;
    }
    status = AJ_UnmarshalArgs(message, "q(qqq)", &widgetType, &datePropertyValue->mDay, &datePropertyValue->month, &datePropertyValue->fullYear);
    if (status != AJ_OK) {
        return status;
    }
    if (widgetType != DATE_PROPERTY) {
        return AJ_ERR_UNEXPECTED;
    }

    return AJ_UnmarshalCloseContainer(message, &structArg);
}

AJ_Status unmarshalTimePropertyValue(TimePropertyValue* timePropertyValue, AJ_Message* message)
{
    AJ_Status status;
    AJ_Arg structArg;
    uint16_t widgetType;

    status = AJ_UnmarshalContainer(message, &structArg, AJ_ARG_STRUCT);
    if (status != AJ_OK) {
        return status;
    }
    status = AJ_UnmarshalArgs(message, "q(qqq)", &widgetType, &timePropertyValue->hour, &timePropertyValue->minute, &timePropertyValue->second);
    if (status != AJ_OK) {
        return status;
    }
    if (widgetType != TIME_PROPERTY) {
        return AJ_ERR_UNEXPECTED;
    }

    return AJ_UnmarshalCloseContainer(message, &structArg);
}

