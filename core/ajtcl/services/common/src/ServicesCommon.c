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

/**
 * Per-module definition of the current module for debug logging.  Must be defined
 * prior to first inclusion of aj_debug.h.
 * The corresponding flag dbgAJSVC is defined in ServicesCommon.h and implemented
 * below.
 */
#define AJ_MODULE AJSVC
#include <ajtcl/aj_debug.h>

#include <ajtcl/alljoyn.h>
#include <ajtcl/services/ServicesCommon.h>
#include <ajtcl/services/PropertyStore.h>
#ifdef ONBOARDING_SERVICE
#include <ajtcl/services/OnboardingManager.h>
#endif
#include <ajtcl/aj_link_timeout.h>

/**
 * Turn on per-module debug printing by setting this variable to non-zero value
 * (usually in debugger).
 */
#ifndef NDEBUG
#ifndef ER_DEBUG_AJSVCALL
#define ER_DEBUG_AJSVCALL 0
#endif
#ifndef ER_DEBUG_AJSVC
#define ER_DEBUG_AJSVC 0
#endif
uint8_t dbgAJSVC = ER_DEBUG_AJSVC || ER_DEBUG_AJSVCALL;
#endif

uint8_t AJSVC_IsLanguageSupported(AJ_Message* msg, AJ_Message* reply, const char* language, int8_t* langIndex)
{
    uint8_t supported = TRUE;
    int8_t foundLangIndex = AJSVC_PropertyStore_GetLanguageIndex(language);
    if (foundLangIndex == AJSVC_PROPERTY_STORE_ERROR_LANGUAGE_INDEX) {
        AJ_MarshalErrorMsg(msg, reply, AJSVC_ERROR_LANGUAGE_NOT_SUPPORTED);
        supported = FALSE;
    }
    if (langIndex != NULL) {
        *langIndex = foundLangIndex;
    }
    return supported;
}

AJ_Status AJSVC_MarshalAppIdAsVariant(AJ_Message* msg, const char* appId)
{
    AJ_Status status;
    uint8_t binAppId[UUID_LENGTH];
    uint32_t sz = strlen(appId);

    if (sz > UUID_LENGTH * 2) { // Crop application id that is too long
        sz = UUID_LENGTH * 2;
    }
    status = AJ_HexToRaw(appId, sz, binAppId, UUID_LENGTH);
    if (status != AJ_OK) {
        return status;
    }
    status = AJ_MarshalArgs(msg, "v", APP_ID_SIGNATURE, binAppId, sz / 2);

    return status;
}

AJ_Status AJSVC_MarshalAppId(AJ_Message* msg, const char* appId)
{
    AJ_Status status;
    uint8_t binAppId[UUID_LENGTH];
    uint32_t sz = strlen(appId);

    if (sz > UUID_LENGTH * 2) { // Crop application id that is too long
        sz = UUID_LENGTH * 2;
    }
    status = AJ_HexToRaw(appId, sz, binAppId, UUID_LENGTH);
    if (status != AJ_OK) {
        return status;
    }
    status = AJ_MarshalArgs(msg, APP_ID_SIGNATURE, binAppId, sz / 2);

    return status;
}

AJ_Status AJSVC_UnmarshalAppIdFromVariant(AJ_Message* msg, char* buf, size_t bufLen)
{
    AJ_Status status;
    uint8_t* appId;
    size_t appIdLen;

    if (bufLen < (UUID_LENGTH * 2 + 1)) {
        AJ_ErrPrintf(("UnmarshalAppId: Insufficient buffer size! Should be at least %u but got %u\n", UUID_LENGTH * 2 + 1, (uint32_t)bufLen));
        return AJ_ERR_RESOURCES;
    }
    status = AJ_UnmarshalArgs(msg, "v", APP_ID_SIGNATURE, &appId, &appIdLen);
    if (status != AJ_OK) {
        return status;
    }
    status = AJ_RawToHex((const uint8_t*)appId, appIdLen, buf, ((appIdLen > UUID_LENGTH) ? UUID_LENGTH : appIdLen) * 2 + 1, FALSE);

    return status;
}

AJ_Status AJSVC_UnmarshalAppId(AJ_Message* msg, char* buf, size_t bufLen)
{
    AJ_Status status;
    uint8_t* appId;
    size_t appIdLen;

    if (bufLen < (UUID_LENGTH * 2 + 1)) {
        AJ_ErrPrintf(("UnmarshalAppId: Insufficient buffer size! Should be at least %u but got %u\n", UUID_LENGTH * 2 + 1, (uint32_t)bufLen));
        return AJ_ERR_RESOURCES;
    }
    status = AJ_UnmarshalArgs(msg, APP_ID_SIGNATURE, &appId, &appIdLen);
    if (status != AJ_OK) {
        return status;
    }
    status = AJ_RawToHex((const uint8_t*)appId, appIdLen, buf, ((appIdLen > UUID_LENGTH) ? UUID_LENGTH : appIdLen) * 2 + 1, FALSE);

    return status;
}
