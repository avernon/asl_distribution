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
#include <ajtcl/aj_security.h>

static const char* routingNodeName = "org.alljoyn.BusNode";

static const uint16_t CONNECT_TIMEOUT = 60000;
static const uint16_t UNMARSHAL_TIMEOUT = 5000;
static const uint32_t suites[] = { AUTH_SUITE_ECDHE_ECDSA, AUTH_SUITE_ECDHE_PSK, AUTH_SUITE_ECDHE_NULL };
//static const uint32_t suites[] = { AUTH_SUITE_ECDHE_NULL };

static AJ_Status AuthListenerCallback(uint32_t authmechanism, uint32_t command, AJ_Credential* cred)
{
    AJ_Status status = AJ_ERR_INVALID;

    AJ_AlwaysPrintf(("AuthListenerCallback authmechanism %d command %d\n", authmechanism, command));

    switch (authmechanism) {
    case AUTH_SUITE_ECDHE_NULL:
        cred->expiration = 0xFFFFFFFF;
        status = AJ_OK;
        break;

    default:
        break;
    }
    return status;
}

void AJ_Main(void)
{
    AJ_Status status = AJ_OK;
    AJ_BusAttachment bus;
    AJ_Message msg;

    AJ_Initialize();
    //AJ_SetSelectionTimeout(2000);

    status = AJ_StartService(&bus, routingNodeName, CONNECT_TIMEOUT, FALSE, 5, "innocent.app", AJ_NAME_REQ_DO_NOT_QUEUE, NULL);
    if (AJ_OK == status) {
        AJ_Printf("Connected to routing node (protocol version = %u). Got unique name - %s\n", AJ_GetRoutingProtoVersion(), AJ_GetUniqueName(&bus));
    } else {
        AJ_Printf("!!!Unexpected!!! failure when connecting to routing node: %s (code: %u)\n", AJ_StatusText(status), status);
    }

    //status = AJ_SecurityInit(&bus);
    AJ_SecuritySetClaimConfig(&bus, APP_STATE_CLAIMABLE, CLAIM_CAPABILITY_ECDHE_NULL, 0);
    AJ_BusEnableSecurity(&bus, suites, ArraySize(suites));
    AJ_BusSetAuthListenerCallback(&bus, AuthListenerCallback);
    status = AJ_BusAdvertiseName(&bus, AJ_GetUniqueName(&bus), AJ_TRANSPORT_ANY, AJ_BUS_START_ADVERTISING, 0);

    while (TRUE) {

        status = AJ_UnmarshalMsg(&bus, &msg, UNMARSHAL_TIMEOUT);
        if (status == AJ_ERR_TIMEOUT) {
            printf("Nothing to do.. \n");
            continue;
        } else if (status == AJ_OK)   {
            switch (msg.msgId) {
            default:
                status = AJ_BusHandleBusMessage(&msg);
                break;
            }
        }

        AJ_CloseMsg(&msg);
    }
}

#ifdef AJ_MAIN
int main(void)
{
    /* AJ_Main is not expected to return */
    AJ_Main();

    return 0;
}
#endif
