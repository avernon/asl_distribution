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

#include <stdlib.h>
#include <ajtcl/aj_target.h>
#include <ajtcl/aj_debug.h>
#include "ServerSampleUtil.h"
#include "PropertyStoreOEMProvisioning.h"
#include <ajtcl/services/PropertyStore.h>

/**
 * Allows the DeviceName to be set dynamically from the environment
 */
void ServerSample_SetupEnv()
{
    char* deviceName = getenv("AJ_DEVICE_NAME");
    if (deviceName) {
        AJ_AlwaysPrintf(("Setting DeviceName from env to: %s\n", deviceName));
        /* set the DeviceName for the default language */
        AJSVC_PropertyStore_SetValueForLang(AJSVC_PROPERTY_STORE_DEVICE_NAME, AJSVC_PropertyStore_GetCurrentDefaultLanguageIndex(), deviceName);
    }
}
