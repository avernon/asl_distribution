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
 * The corresponding flag dbgAJSVCAPP is defined in the containing sample app.
 */
#define AJ_MODULE AJSVCAPP
#include <ajtcl/aj_debug.h>

#include <ajtcl/alljoyn.h>
#include "OnboardingSample.h"
#include <ajtcl/services/OnboardingService.h>
#include <ajtcl/services/OnboardingManager.h>
#include "PropertyStoreOEMProvisioning.h"
#include <ajtcl/services/PropertyStore.h>

#ifndef NDEBUG
extern AJ_EXPORT uint8_t dbgAJSVCAPP;
#endif

static const char* appDeviceManufactureName = NULL;
static const char* appDeviceProductName = NULL;

static char* GenerateSoftAPSSID(char* obSoftAPssid)
{
    const char* deviceId;
    size_t deviceIdLen;
    char manufacture[AJOBS_DEVICE_MANUFACTURE_NAME_LEN + 1] = { 0 };
    size_t manufacureLen;
    char product[AJOBS_DEVICE_PRODUCT_NAME_LEN + 1] = { 0 };
    size_t productLen;
    char serialId[AJOBS_DEVICE_SERIAL_ID_LEN + 1] = { 0 };
    size_t serialIdLen;

    if (obSoftAPssid[0] == '\0') {
        deviceId = AJSVC_PropertyStore_GetValue(AJSVC_PROPERTY_STORE_DEVICE_ID);
        deviceIdLen = strlen(deviceId);
        manufacureLen = min(strlen(deviceManufactureName), AJOBS_DEVICE_MANUFACTURE_NAME_LEN);
        productLen = min(strlen(deviceProductName), AJOBS_DEVICE_PRODUCT_NAME_LEN);
        serialIdLen = min(deviceIdLen, AJOBS_DEVICE_SERIAL_ID_LEN);
        memcpy(manufacture, deviceManufactureName, manufacureLen);
        manufacture[manufacureLen] = '\0';
        memcpy(product, deviceProductName, productLen);
        product[productLen] = '\0';
        memcpy(serialId, deviceId + (deviceIdLen - serialIdLen), serialIdLen);
        serialId[serialIdLen] = '\0';
#ifdef _WIN32
        _snprintf(obSoftAPssid, AJOBS_SSID_MAX_LENGTH + 1, "AJ_%s_%s_%s", manufacture, product, serialId);
#else
        snprintf(obSoftAPssid, AJOBS_SSID_MAX_LENGTH + 1, "AJ_%s_%s_%s", manufacture, product, serialId);
#endif
    }

    return obSoftAPssid;
}

static AJOBS_Settings obSettings = AJOBS_DEFAULT_SETTINGS;

AJ_Status Onboarding_Init(const char* deviceManufactureName, const char* deviceProductName)
{
    AJ_Status status = AJ_OK;

    appDeviceManufactureName = deviceManufactureName;
    appDeviceProductName = deviceProductName;
    if (appDeviceManufactureName == NULL || appDeviceManufactureName[0] == '\0') {
        AJ_AlwaysPrintf(("Onboarding_Init(): DeviceManufactureName is NULL or empty\n"));
        status = AJ_ERR_INVALID;
        goto Exit;
    } else if (appDeviceProductName == NULL || appDeviceProductName[0] == '\0') {
        AJ_AlwaysPrintf(("Onboarding_Init(): DeviceProductName is NULL or empty\n"));
        status = AJ_ERR_INVALID;
        goto Exit;
    }
    GenerateSoftAPSSID(obSettings.AJOBS_SoftAPSSID);
    status = AJOBS_Start(&obSettings);

Exit:

    return status;
}

void Onboarding_DoWork(AJ_BusAttachment* bus)
{
}

AJ_Status Onboarding_Finish()
{
    return AJ_OK;
}
