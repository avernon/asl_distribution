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

#include <ajtcl/alljoyn.h>
#include <ajtcl/aj_creds.h>
#include <ajtcl/aj_nvram.h>
#include <ajtcl/aj_crypto_ecc.h>
#include <ajtcl/aj_creds.h>

uint8_t dbgNVRAMDUMP = 1;
extern void AJ_NVRAM_Layout_Print();
AJ_Status DumpNVRAM();

void printhex(uint8_t*x, size_t n)
{
    size_t i;
    for (i = 0; i < n; i++) {
        AJ_AlwaysPrintf(("%02X", x[i]));
    }
}

AJ_Status DumpNVRAM()
{
    AJ_Status status;
    uint16_t slot = AJ_CREDS_NV_ID_BEGIN;
    uint16_t type;
    AJ_CredField id;
    uint32_t expiration;
    AJ_CredField data;

    AJ_NVRAM_Layout_Print();
    AJ_AlwaysPrintf(("Remaining Size %d\n", AJ_NVRAM_GetSizeRemaining()));

    AJ_AlwaysPrintf(("SLOT | TYPE | ID | EXPIRATION | DATA\n"));
    for (; slot < AJ_CREDS_NV_ID_END; slot++) {
        if (!AJ_NVRAM_Exist(slot)) {
            continue;
        }
        id.data = NULL;
        data.data = NULL;
        status = AJ_CredentialRead(&type, &id, &expiration, &data, slot);
        if (AJ_OK == status) {
            AJ_AlwaysPrintf(("%04X | %04X | ", slot, type));
            printhex(id.data, id.size);
            AJ_AlwaysPrintf((" | %08X | ", expiration));
            //printhex(data.data, data.size);
            AJ_DumpBytes("", data.data, data.size);
            AJ_AlwaysPrintf(("\n"));
            AJ_CredFieldFree(&id);
            AJ_CredFieldFree(&data);
        }
    }
    return AJ_OK;
}

int AJ_Main()
{
    AJ_Status status = AJ_OK;
    AJ_Initialize();
    //AJ_NVRAM_Clear();
    //AJ_AlwaysPrintf(("Clearing NVRAM\n"));
    status = DumpNVRAM();
    AJ_ASSERT(status == AJ_OK);
    //AJ_DumpPolicy();
    return 0;
}

#ifdef AJ_MAIN
int main()
{
    return AJ_Main();
}
#endif
