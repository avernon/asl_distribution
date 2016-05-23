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

#include <LampAboutData.h>
#include <LampService.h>
#include <LampState.h>
#include <LampValues.h>
#include <OEM_LS_Provisioning.h>

#include <aj_msg.h>
#include <aj_debug.h>
#include <aj_creds.h>
#include <aj_nvram.h>
#include <aj_config.h>

#include <OEM_LS_Code.h>

#ifdef ONBOARDING_SERVICE
    #include <alljoyn/onboarding/OnboardingManager.h>
#endif

#include <alljoyn/config/ConfigService.h>
#include <alljoyn/services_common/PropertyStore.h>
#include <alljoyn/services_common/ServicesCommon.h>

/**
 * Per-module definition of the current module for debug logging.  Must be defined
 * prior to first inclusion of aj_debug.h
 */
#define AJ_MODULE LAMP_ABOUT_DATA

/**
 * Turn on per-module debug printing by setting this variable to non-zero value
 * (usually in debugger).
 */
#ifndef NDEBUG
uint8_t dbgLAMP_ABOUT_DATA = 1;
#endif

const char* LAMP_GetID(void)
{
    AJ_InfoPrintf(("\n%s\n", __func__));
    return AJSVC_PropertyStore_GetValue(AJSVC_PROPERTY_STORE_DEVICE_ID);
}

const char* LAMP_GetName(void)
{
    AJ_InfoPrintf(("\n%s\n", __func__));
    return AJSVC_PropertyStore_GetValue(AJSVC_PROPERTY_STORE_DEVICE_NAME);
}

void LAMP_SetName(const char* name)
{
    AJ_InfoPrintf(("\n%s\n", __func__));
    AJSVC_PropertyStore_SetValue(AJSVC_PROPERTY_STORE_DEVICE_NAME, name);
    AJSVC_PropertyStore_SaveAll();
}

static AJ_Status FactoryReset(void)
{
    AJ_InfoPrintf(("\n%s\n", __func__));
    AJSVC_PropertyStore_ResetAll();

    // this will clear onboarding data, state, and credentials
    AJ_NVRAM_Clear();

    // we must persist the device id!
    SavePersistentDeviceId();

    // reinitialize!
    PropertyStore_Init();

    OEM_LS_DoFactoryReset();

    // Force disconnect of AJ and services and reconnection of WiFi on restart of app
    return AJ_ERR_RESTART_APP;
}

static AJ_Status Restart(void)
{
    AJ_InfoPrintf(("\n%s\n", __func__));
    OEM_LS_Restart();
    return AJ_ERR_RESTART_APP;
}

static AJ_Status SetPasscode(const char* routerRealm, const uint8_t* newPasscode, uint8_t newPasscodeLen)
{
    char newStringPasscode[PASSWORD_VALUE_LENGTH + 1];
    AJ_Status status;

    AJ_InfoPrintf(("\n%s\n", __func__));

    status = AJ_RawToHex(newPasscode, newPasscodeLen, newStringPasscode, sizeof(newStringPasscode), FALSE);
    if (status != AJ_OK) {
        return status;
    }

    if (AJSVC_PropertyStore_SetValue(AJSVC_PROPERTY_STORE_REALM_NAME, routerRealm) &&
        AJSVC_PropertyStore_SetValue(AJSVC_PROPERTY_STORE_PASSCODE, newStringPasscode)) {

        status = AJSVC_PropertyStore_SaveAll();
        if (status != AJ_OK) {
            return status;
        }

        AJ_ClearCredentials();
        //Force disconnect of AJ and services to refresh current sessions
        status = AJ_ERR_READ;
    } else {
        status = AJSVC_PropertyStore_LoadAll();
        if (status != AJ_OK) {
            return status;
        }
    }

    return status;
}

static uint8_t IsValueValid(const char* key, const char* value)
{
    AJ_InfoPrintf(("\n%s\n", __func__));
    return TRUE;
}

#define INITIAL_PASSCODE "000000"

uint32_t LAMP_PasswordCallback(uint8_t* buffer, uint32_t bufLen)
{
    AJ_Status status = AJ_OK;
    const char* hexPassword = AJSVC_PropertyStore_GetValue(AJSVC_PROPERTY_STORE_PASSCODE);
    size_t hexPasswordLen;
    uint32_t len = 0;

    if (hexPassword == NULL) {
        AJ_ErrPrintf(("Password is NULL!\n"));
        return len;
    }

    AJ_InfoPrintf(("Configured password=%s\n", hexPassword));
    hexPasswordLen = strlen(hexPassword);
    len = hexPasswordLen / 2;
    status = AJ_HexToRaw(hexPassword, hexPasswordLen, buffer, bufLen);
    if (status == AJ_ERR_RESOURCES) {
        len = 0;
    }

    return len;
}

void LAMP_SetupAboutConfigData(void)
{
    AJ_InfoPrintf(("\n%s\n", __func__));
    AJCFG_Start(&FactoryReset, &Restart, &SetPasscode, &IsValueValid);
    AJ_AboutSetIcon(aboutIconContent, aboutIconSize, aboutIconMimetype, aboutIconUrl);

    // first read in the data from the propertystore
    PropertyStore_Init();
}
