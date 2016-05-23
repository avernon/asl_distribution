/**
 * @file
 */
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

#include "ajs.h"
#include "ajs_storage.h"

/*
 * This file includes a sample implementation for storing and loading AJS
 * scripts into persistent storage. It uses the AllJoyn Thin Client NVRAM API's
 * to implement the required target specific functionality. This implementation
 * can be used for any target but can also be left out, allowing the target to
 * provide its own implementation.
 */

uint32_t AJS_MaxScriptLen()
{
    return (3 * AJ_NVRAM_GetSizeRemaining()) / 4;
}

AJ_Status AJS_OpenScript(uint32_t length, void** ctx)
{
    AJ_NV_DATASET* ds;
    if (length > AJS_MaxScriptLen()) {
        return AJ_ERR_RESOURCES;
    }
    ds = AJ_NVRAM_Open(AJS_SCRIPT_NVRAM_ID, length ? "w" : "r", length);
    if (!ds) {
        return AJ_ERR_FAILURE;
    }
    *ctx = (void*)ds;
    return AJ_OK;
}

AJ_Status AJS_WriteScript(uint8_t* script, uint32_t length, void* ctx)
{
    AJ_NV_DATASET* ds = (AJ_NV_DATASET*)ctx;
    if (ds) {
        if (AJ_NVRAM_Write(script, length, ds) != length) {
            goto WriteFailure;
        }
        return AJ_OK;
    }
WriteFailure:
    AJ_ErrPrintf(("AJS_WriteScript(): Could not write script to NVRAM\n"));
    return AJ_ERR_FAILURE;
}

AJ_Status AJS_ReadScript(uint8_t** script, uint32_t* length, void* ctx)
{
    AJ_NV_DATASET* ds = (AJ_NV_DATASET*)ctx;
    AJ_NV_DATASET* l;
    if (ds) {
        *script = (uint8_t*)AJ_NVRAM_Peek(ds);
        l = AJ_NVRAM_Open(AJS_SCRIPT_SIZE_ID, "r", 0);
        if (l) {
            if (AJ_NVRAM_Read(length, sizeof(uint32_t), l) != sizeof(uint32_t)) {
                goto ReadFailure;
            }
            AJ_NVRAM_Close(l);
            return AJ_OK;
        }
    }
ReadFailure:
    AJ_ErrPrintf(("AJS_ReadScript(): Could not read script\n"));
    if (l) {
        AJ_NVRAM_Close(l);
    }
    return AJ_ERR_FAILURE;
}

AJ_Status AJS_CloseScript(void* ctx)
{
    AJ_NV_DATASET* ds = (AJ_NV_DATASET*)ctx;
    if (ds) {
        AJ_NVRAM_Close(ds);
    }
    return AJ_OK;
}

AJ_Status AJS_DeleteScript(void)
{
    AJ_NVRAM_Delete(AJS_SCRIPT_NVRAM_ID);
    return AJ_OK;
}
