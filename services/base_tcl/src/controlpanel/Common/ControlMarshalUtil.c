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

#include <ajtcl/services/Common/ControlMarshalUtil.h>
#include <ajtcl/services/Common/BaseWidget.h>

#define ROOT_INTERFACE_VERSION 1

AJ_Status AddHints(AJ_Message* reply, const uint16_t hints[], uint16_t numHints)
{
    AJ_Status status;
    AJ_Arg arrayArg;
    uint16_t cnt;

    status = AJ_MarshalContainer(reply, &arrayArg, AJ_ARG_ARRAY);
    if (status != AJ_OK) {
        return status;
    }
    for (cnt = 0; cnt < numHints; cnt++)
        status = AJ_MarshalArgs(reply, "q", hints[cnt]);
    if (status != AJ_OK) {
        return status;
    }

    return AJ_MarshalCloseContainer(reply, &arrayArg);
}

AJ_Status AddConstraintValue(AJ_Message* reply, const char* sig, const void* value, const char* displayValue)
{
    AJ_Status status;
    AJ_Arg structArg;

    status = AJ_MarshalContainer(reply, &structArg, AJ_ARG_STRUCT);
    if (status != AJ_OK) {
        return status;
    }
    status = MarshalVariant(reply, sig, value);
    if (status != AJ_OK) {
        return status;
    }
    status = AJ_MarshalArgs(reply, "s", displayValue);
    if (status != AJ_OK) {
        return status;
    }

    return AJ_MarshalCloseContainer(reply, &structArg);
}

AJ_Status AddConstraintRange(AJ_Message* reply, const char* valueSig, const void* min, const void* max, const void* increment)
{
    AJ_Status status;
    AJ_Arg structArg;

    status = AJ_MarshalContainer(reply, &structArg, AJ_ARG_STRUCT);
    if (status != AJ_OK) {
        return status;
    }
    status = MarshalVariant(reply, valueSig, min);
    if (status != AJ_OK) {
        return status;
    }
    status = MarshalVariant(reply, valueSig, max);
    if (status != AJ_OK) {
        return status;
    }
    status = MarshalVariant(reply, valueSig, increment);
    if (status != AJ_OK) {
        return status;
    }

    return AJ_MarshalCloseContainer(reply, &structArg);
}

AJ_Status StartComplexOptionalParam(AJ_Message* reply, AJ_Arg* arg, uint16_t key, const char* sig)
{
    AJ_Status status;

    status = AJ_MarshalContainer(reply, arg, AJ_ARG_DICT_ENTRY);
    if (status != AJ_OK) {
        return status;
    }
    status = AJ_MarshalArgs(reply, "q", key);
    if (status != AJ_OK) {
        return status;
    }

    return AJ_MarshalVariant(reply, sig);
}

AJ_Status AddBasicOptionalParam(AJ_Message* reply, uint16_t key, const char* sig, const void* value)
{
    AJ_Status status;
    AJ_Arg dictArg;

    status = AJ_MarshalContainer(reply, &dictArg, AJ_ARG_DICT_ENTRY);
    if (status != AJ_OK) {
        return status;
    }
    status = AJ_MarshalArgs(reply, "q", key);
    if (status != AJ_OK) {
        return status;
    }
    status = MarshalVariant(reply, sig, value);
    if (status != AJ_OK) {
        return status;
    }

    return AJ_MarshalCloseContainer(reply, &dictArg);
}

AJ_Status AddPropertyForGetAll(AJ_Message* reply, char* key, const char* sig,
                               BaseWidget* widget, uint16_t language, MarshalWidgetFptr functionPtr)
{
    AJ_Status status;
    AJ_Arg dictArg;

    status = AJ_MarshalContainer(reply, &dictArg, AJ_ARG_DICT_ENTRY);
    if (status != AJ_OK) {
        return status;
    }
    status = AJ_MarshalArgs(reply, "s", key);
    if (status != AJ_OK) {
        return status;
    }
    status = AJ_MarshalVariant(reply, sig);
    if (status != AJ_OK) {
        return status;
    }
    status = functionPtr(widget, reply, language);
    if (status != AJ_OK) {
        return status;
    }

    return AJ_MarshalCloseContainer(reply, &dictArg);
}

AJ_Status MarshalVariant(AJ_Message* reply, const char* sig, const void* value)
{
    AJ_Status status;
    status = AJ_MarshalVariant(reply, sig);
    if (status != AJ_OK) {
        return status;
    }

    if (value == 0) {
        return AJ_ERR_UNEXPECTED;
    }
    if (strcmp(sig, "s") == 0) {
        return AJ_MarshalArgs(reply, sig, *((char**)value));
    } else if (strcmp(sig, "i") == 0) {
        return AJ_MarshalArgs(reply, sig, *((int*)value));
    } else if (strcmp(sig, "b") == 0) {
        return AJ_MarshalArgs(reply, sig, *((uint8_t*)value));
    } else if (strcmp(sig, "q") == 0) {
        return AJ_MarshalArgs(reply, sig, *((uint16_t*)value));
    } else if (strcmp(sig, "u") == 0) {
        return AJ_MarshalArgs(reply, sig, *((uint32_t*)value));
    } else if (strcmp(sig, "d") == 0) {
        return AJ_MarshalArgs(reply, sig, *((double*)value));
    } else if (strcmp(sig, "g") == 0) {
        return AJ_MarshalArgs(reply, sig, *((char**)value));
    } else if (strcmp(sig, "o") == 0) {
        return AJ_MarshalArgs(reply, sig, *((char**)value));
    } else if (strcmp(sig, "n") == 0) {
        return AJ_MarshalArgs(reply, sig, *((int16_t*)value));
    } else if (strcmp(sig, "t") == 0) {
        return AJ_MarshalArgs(reply, sig, *((uint64_t*)value));
    } else if (strcmp(sig, "x") == 0) {
        return AJ_MarshalArgs(reply, sig, *((int64_t*)value));
    } else if (strcmp(sig, "y") == 0) {
        return AJ_MarshalArgs(reply, sig, *((char*)value));
    } else if (strcmp(sig, "h") == 0) {
        return AJ_MarshalArgs(reply, sig, *((int*)value));
    }
    return AJ_ERR_UNEXPECTED;
}

AJ_Status MarshalAllRootProperties(AJ_Message* reply)
{
    AJ_Status status;
    AJ_Arg rootGetAllArray;
    AJ_Arg dictArg;

    status = AJ_MarshalContainer(reply, &rootGetAllArray, AJ_ARG_ARRAY);
    if (status != AJ_OK) {
        return status;
    }
    status = AJ_MarshalContainer(reply, &dictArg, AJ_ARG_DICT_ENTRY);
    if (status != AJ_OK) {
        return status;
    }
    status = AJ_MarshalArgs(reply, "s", PROPERTY_TYPE_VERSION_NAME);
    if (status != AJ_OK) {
        return status;
    }
    status = AJ_MarshalVariant(reply, PROPERTY_TYPE_VERSION_SIG);
    if (status != AJ_OK) {
        return status;
    }
    status = MarshalVersionRootProperties(reply);
    if (status != AJ_OK) {
        return status;
    }
    status = AJ_MarshalCloseContainer(reply, &dictArg);
    if (status != AJ_OK) {
        return status;
    }
    return AJ_MarshalCloseContainer(reply, &rootGetAllArray);
}

AJ_Status MarshalVersionRootProperties(AJ_Message* reply)
{
    return AJ_MarshalArgs(reply, PROPERTY_TYPE_VERSION_SIG, ROOT_INTERFACE_VERSION);
}
