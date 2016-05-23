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

#include <alljoyn/controlpanel/Common/DateTimeUtil.h>
#include <alljoyn/controlpanel/Common/ControlMarshalUtil.h>

AJ_Status marshalDatePropertyValue(DatePropertyValue* datePropertyValue, AJ_Message* reply)
{
    AJ_Status status;
    AJ_Arg outerStructArg, innerStructArg;

    status = AJ_MarshalVariant(reply, DATE_PROPERTY_SIG);
    if (status != AJ_OK) {
        return status;
    }
    status = AJ_MarshalContainer(reply, &outerStructArg, AJ_ARG_STRUCT);
    if (status != AJ_OK) {
        return status;
    }
    status = AJ_MarshalArgs(reply, "q", DATE_PROPERTY);
    if (status != AJ_OK) {
        return status;
    }
    status = AJ_MarshalContainer(reply, &innerStructArg, AJ_ARG_STRUCT);
    if (status != AJ_OK) {
        return status;
    }

    status = AJ_MarshalArgs(reply, "qqq", datePropertyValue->mDay, datePropertyValue->month, datePropertyValue->fullYear);
    if (status != AJ_OK) {
        return status;
    }

    status = AJ_MarshalCloseContainer(reply, &innerStructArg);
    if (status != AJ_OK) {
        return status;
    }
    return AJ_MarshalCloseContainer(reply, &outerStructArg);
}

AJ_Status marshalTimePropertyValue(TimePropertyValue* timePropertyValue, AJ_Message* reply)
{
    AJ_Status status;
    AJ_Arg outerStructArg, innerStructArg;

    status = AJ_MarshalVariant(reply, TIME_PROPERTY_SIG);
    if (status != AJ_OK) {
        return status;
    }
    status = AJ_MarshalContainer(reply, &outerStructArg, AJ_ARG_STRUCT);
    if (status != AJ_OK) {
        return status;
    }
    status = AJ_MarshalArgs(reply, "q", TIME_PROPERTY);
    if (status != AJ_OK) {
        return status;
    }
    status = AJ_MarshalContainer(reply, &innerStructArg, AJ_ARG_STRUCT);
    if (status != AJ_OK) {
        return status;
    }

    status = AJ_MarshalArgs(reply, "qqq", timePropertyValue->hour, timePropertyValue->minute, timePropertyValue->second);
    if (status != AJ_OK) {
        return status;
    }

    status = AJ_MarshalCloseContainer(reply, &innerStructArg);
    if (status != AJ_OK) {
        return status;
    }
    return AJ_MarshalCloseContainer(reply, &outerStructArg);
}

AJ_Status unmarshalDatePropertyValue(DatePropertyValue* datePropertyValue, AJ_Message* message)
{
    AJ_Status status;
    AJ_Arg outerStructArg, innerStructArg;
    uint16_t widgetType;

    status = AJ_UnmarshalContainer(message, &outerStructArg, AJ_ARG_STRUCT);
    if (status != AJ_OK) {
        return status;
    }
    status = AJ_UnmarshalArgs(message, "q", &widgetType);
    if (status != AJ_OK) {
        return status;
    }

    if (widgetType != DATE_PROPERTY) {
        return AJ_ERR_UNEXPECTED;
    }
    status = AJ_UnmarshalContainer(message, &innerStructArg, AJ_ARG_STRUCT);
    if (status != AJ_OK) {
        return status;
    }
    status = AJ_UnmarshalArgs(message, "qqq", &datePropertyValue->mDay, &datePropertyValue->month, &datePropertyValue->fullYear);
    if (status != AJ_OK) {
        return status;
    }

    status = AJ_UnmarshalCloseContainer(message, &innerStructArg);
    if (status != AJ_OK) {
        return status;
    }
    return AJ_UnmarshalCloseContainer(message, &outerStructArg);
}

AJ_Status unmarshalTimePropertyValue(TimePropertyValue* timePropertyValue, AJ_Message* message)
{
    AJ_Status status;
    AJ_Arg outerStructArg, innerStructArg;
    uint16_t widgetType;

    status = AJ_UnmarshalContainer(message, &outerStructArg, AJ_ARG_STRUCT);
    if (status != AJ_OK) {
        return status;
    }
    status = AJ_UnmarshalArgs(message, "q", &widgetType);
    if (status != AJ_OK) {
        return status;
    }

    if (widgetType != TIME_PROPERTY) {
        return AJ_ERR_UNEXPECTED;
    }
    status = AJ_UnmarshalContainer(message, &innerStructArg, AJ_ARG_STRUCT);
    if (status != AJ_OK) {
        return status;
    }
    status = AJ_UnmarshalArgs(message, "qqq", &timePropertyValue->hour, &timePropertyValue->minute, &timePropertyValue->second);
    if (status != AJ_OK) {
        return status;
    }

    status = AJ_UnmarshalCloseContainer(message, &innerStructArg);
    if (status != AJ_OK) {
        return status;
    }
    return AJ_UnmarshalCloseContainer(message, &outerStructArg);
}

