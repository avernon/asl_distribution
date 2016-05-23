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
#include <ajtcl/aj_debug.h>
#include <ajtcl/aj_config.h>
#include <ajtcl/aj_creds.h>
#include <ajtcl/aj_link_timeout.h>

#include "ajs_ctrlpanel.h"
#include "ajs_services.h"
#include "ajs_propstore.h"

#include <ajtcl/services/ConfigService.h>
#include <ajtcl/services/NotificationProducer.h>
#include <ajtcl/services/PropertyStore.h>

static AJ_Status SetPasscode(const char* routerRealm, const uint8_t* newPasscode, uint8_t newPasscodeLen)
{
    AJ_Status status = AJ_OK;
    char newStringPasscode[PASSWORD_VALUE_LENGTH + 1];

    status = AJ_RawToHex(newPasscode, newPasscodeLen, newStringPasscode, sizeof(newStringPasscode), FALSE);
    if (status != AJ_OK) {
        return status;
    }
    if (AJSVC_PropertyStore_SetValue(AJSVC_PROPERTY_STORE_REALM_NAME, routerRealm) && AJSVC_PropertyStore_SetValue(AJSVC_PROPERTY_STORE_PASSCODE, newStringPasscode)) {
        status = AJSVC_PropertyStore_SaveAll();
        if (status != AJ_OK) {
            return status;
        }
        AJ_ClearCredentials(AJ_CRED_TYPE_GENERIC);
        status = AJ_ERR_READ;     //Force disconnect of AJ and services to refresh current sessions
    } else {
        status = AJSVC_PropertyStore_LoadAll();
        if (status != AJ_OK) {
            return status;
        }
    }
    return status;
}

AJ_Status AJS_FactoryReset(void)
{
    AJ_Status status = AJ_OK;

    AJ_WarnPrintf(("FactoryReset\n"));
    status = AJSVC_PropertyStore_ResetAll();
    if (status != AJ_OK) {
        return status;
    }
#ifdef ONBOARDING_SERVICE
    status = AJOBS_ClearInfo();
    if (status != AJ_OK) {
        return status;
    }
#endif
    AJ_ClearCredentials(AJ_CRED_TYPE_GENERIC);
    return AJ_ERR_RESTART;
}

static uint8_t IsValueValid(const char* key, const char* value)
{
    return TRUE;
}

static AJ_Status Restart(void)
{
    AJ_WarnPrintf(("Restart\n"));
    AJ_AboutSetShouldAnnounce();
    return AJ_ERR_RESTART;
}

AJ_Status AJS_ServicesInit(AJ_BusAttachment* aj)
{
    AJ_Status status = AJ_OK;

    AJ_BusSetPasswordCallback(aj, AJS_PasswordCallback);
    status = AJCFG_Start(AJS_FactoryReset, Restart, SetPasscode, IsValueValid);
    if (status != AJ_OK) {
        goto Exit;
    }
    status = AJNS_Producer_Start();
    if (status != AJ_OK) {
        goto Exit;
    }

Exit:
    return status;
}

AJ_Status AJS_ServicesMsgHandler(AJ_Message* msg)
{
    AJ_Status status = AJ_OK;
    AJSVC_ServiceStatus svcStatus;

    svcStatus = AJSVC_MessageProcessorAndDispatcher(msg->bus, msg, &status);
    if (svcStatus == AJSVC_SERVICE_STATUS_NOT_HANDLED) {
        return AJ_ERR_NO_MATCH;
    } else {
        return status;
    }
}
