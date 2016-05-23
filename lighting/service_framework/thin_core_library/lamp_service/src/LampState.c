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

#include <LampState.h>
#include <LampService.h>
#include <OEM_LS_Code.h>

#include <aj_nvram.h>
#include <aj_debug.h>

/**
 * Per-module definition of the current module for debug logging.  Must be defined
 * prior to first inclusion of aj_debug.h
 */
#define AJ_MODULE LAMP_STATE

/**
 * Turn on per-module debug printing by setting this variable to non-zero value
 * (usually in debugger).
 */
#ifndef NDEBUG
uint8_t dbgLAMP_STATE = 1;
#endif

/*
 * The state object that represents the current lamp state.
 * This is mirrored in NVRAM and preserved across power cycles.
 * A signal will be sent when this changes if a session is active.
 */
static LampState TheLampState;

static size_t memscpy(void*dest, size_t dstSize, const void*src, size_t copySize)
{
    size_t minSize = dstSize < copySize ? dstSize : copySize;
    memcpy(dest, src, minSize);
    return minSize;
}

LampResponseCode LAMP_MarshalState(LampState* state, AJ_Message* msg)
{
    AJ_InfoPrintf(("%s\n", __func__));
    AJ_Status status = AJ_MarshalArgs(msg, "{sv}", "Hue", "u", state->hue);
    if (status != AJ_OK) {
        return LAMP_ERR_MESSAGE;
    }

    status = AJ_MarshalArgs(msg, "{sv}", "Saturation", "u", state->saturation);
    if (status != AJ_OK) {
        return LAMP_ERR_MESSAGE;
    }

    status = AJ_MarshalArgs(msg, "{sv}", "ColorTemp", "u", state->colorTemp);
    if (status != AJ_OK) {
        return LAMP_ERR_MESSAGE;
    }

    status = AJ_MarshalArgs(msg, "{sv}", "Brightness", "u", state->brightness);
    if (status != AJ_OK) {
        return LAMP_ERR_MESSAGE;
    }

    status = AJ_MarshalArgs(msg, "{sv}", "OnOff", "b", (state->onOff ? TRUE : FALSE));
    if (status != AJ_OK) {
        return LAMP_ERR_MESSAGE;
    }

    return LAMP_OK;
}

LampResponseCode LAMP_UnmarshalState(LampStateContainer* state, AJ_Message* msg)
{
    AJ_Arg array1, struct1;
    AJ_Status status = AJ_UnmarshalContainer(msg, &array1, AJ_ARG_ARRAY);
    LampResponseCode responseCode = LAMP_OK;

    AJ_DumpMsg("LAMP_UnmarshalState", msg, TRUE);

    // initialize
    memset(state, 0, sizeof(LampStateContainer));

    do {
        char* field;
        char* sig;

        status = AJ_UnmarshalContainer(msg, &struct1, AJ_ARG_DICT_ENTRY);
        if (status != AJ_OK) {
            break;
        }

        status = AJ_UnmarshalArgs(msg, "s", &field);
        if (status != AJ_OK) {
            AJ_ErrPrintf(("AJ_UnmarshalArgs: %s\n", AJ_StatusText(status)));
            return LAMP_ERR_MESSAGE;
        }

        // Process the field!
        status = AJ_UnmarshalVariant(msg, (const char**) &sig);
        if (status != AJ_OK) {
            AJ_ErrPrintf(("AJ_UnmarshalVariant: %s\n", AJ_StatusText(status)));
            return LAMP_ERR_MESSAGE;
        }

        if (0 == strcmp(field, "OnOff")) {
            uint32_t onoff;
            status = AJ_UnmarshalArgs(msg, "b", &onoff);
            state->state.onOff = onoff ? TRUE : FALSE;
            state->stateFieldIndicators |= LAMP_STATE_ON_OFF_FIELD_INDICATOR;
        } else if (0 == strcmp(field, "Hue")) {
            status = AJ_UnmarshalArgs(msg, "u", &state->state.hue);
            state->stateFieldIndicators |= LAMP_STATE_HUE_FIELD_INDICATOR;
        } else if (0 == strcmp(field, "Saturation")) {
            status = AJ_UnmarshalArgs(msg, "u", &state->state.saturation);
            state->stateFieldIndicators |= LAMP_STATE_SATURATION_FIELD_INDICATOR;
        } else if (0 == strcmp(field, "ColorTemp")) {
            status = AJ_UnmarshalArgs(msg, "u", &state->state.colorTemp);
            state->stateFieldIndicators |= LAMP_STATE_COLOR_TEMP_FIELD_INDICATOR;
        } else if (0 == strcmp(field, "Brightness")) {
            status = AJ_UnmarshalArgs(msg, "u", &state->state.brightness);
            state->stateFieldIndicators |= LAMP_STATE_BRIGHTNESS_FIELD_INDICATOR;
        } else {
            AJ_ErrPrintf(("Unknown field: %s\n", field));
            responseCode = LAMP_ERR_MESSAGE;
            AJ_SkipArg(msg);
        }

        status = AJ_UnmarshalCloseContainer(msg, &struct1);
        // if field invalid, throw the whole thing out and return the error
    } while (status == AJ_OK && responseCode == LAMP_OK);
    AJ_UnmarshalCloseContainer(msg, &array1);

    return responseCode;
}

#define LAMP_STATE_FD AJ_NVRAM_ID_FOR_APPS + 1

void LAMP_InitializeState(void)
{
    AJ_NV_DATASET* id = AJ_NVRAM_Open(LAMP_STATE_FD, "r", 0);
    if (id != NULL) {
        AJ_NVRAM_Read(&TheLampState, sizeof(LampState), id);
        AJ_NVRAM_Close(id);
    } else {
        AJ_NV_DATASET* id = AJ_NVRAM_Open(LAMP_STATE_FD, "w", sizeof(LampState));
        OEM_LS_SetFactoryState(&TheLampState);

        if (id != NULL) {
            AJ_NVRAM_Write(&TheLampState, sizeof(LampState), id);
            AJ_NVRAM_Close(id);
        }
    }
}

void LAMP_GetState(LampState* state)
{
    memscpy((void*)(state), sizeof(LampState), (const void*)(&TheLampState), sizeof(LampState));
}

void LAMP_SetState(const LampState* state)
{
    AJ_InfoPrintf(("\n%s\n", __func__));
    int32_t diff = memcmp(state, &TheLampState, sizeof(LampState));

    if (diff) {
        AJ_InfoPrintf(("\n%s: Calling into NVRAM\n", __func__));
        AJ_NV_DATASET* id = AJ_NVRAM_Open(LAMP_STATE_FD, "w", sizeof(LampState));
        memscpy((void*)(&TheLampState), sizeof(LampState), (const void*)(state), sizeof(LampState));

        if (id != NULL) {
            AJ_NVRAM_Write(&TheLampState, sizeof(LampState), id);
            AJ_NVRAM_Close(id);
        }
    }

    // this will cause the signal org.allseen.LSF.LampService.LampStateChanged
    // to be sent if there is a current session.
    LAMP_SendStateChangedSignal();
}

void LAMP_ClearState(void)
{
    memset(&TheLampState, 0, sizeof(LampState));
    AJ_NVRAM_Delete(LAMP_STATE_FD);
}
