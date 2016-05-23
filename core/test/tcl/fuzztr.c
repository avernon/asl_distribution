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
#include <stdio.h>
#include <stdlib.h>
#include <alljoyn.h>

#define CONNECT_TIMEOUT    (1000ul * 60)
#define CONNECT_PAUSE      (1000ul * 10)
#define UNMARSHAL_TIMEOUT  (1000ul * 5)

/// globals
AJ_Status status = AJ_OK;
AJ_BusAttachment bus;
uint8_t connected = FALSE;


static const char* const testInterface[] = {
    "foo.bar",
    "!test >s",
    NULL
};

static const AJ_InterfaceDescription testInterfaces[] = {
    testInterface,
    NULL
};

/**
 * Objects implemented by the application
 */
static const AJ_Object AppObjects[] = {
    { "/foo/bar", testInterfaces },
    { NULL }
};

#define APP_TEST  AJ_APP_MESSAGE_ID(0, 0, 0)

/*
 * Let the application do some work
 */

void Do_Connect()
{
    while (!connected) {
        AJ_Status status;
        AJ_Printf("Attempting to connect to bus\n");
        status = AJ_Connect(&bus, NULL, CONNECT_TIMEOUT);
        if (status != AJ_OK) {
            AJ_Printf("Failed to connect to bus sleeping for %lu seconds\n", CONNECT_PAUSE / 1000);
            AJ_Sleep(CONNECT_PAUSE);
            continue;
        }
        connected = TRUE;
        AJ_Printf("Thin client app.connected to bus\n");
    }
}

static void AppDoWork()
{
    AJ_Printf(("do work\n"));
}

int AJ_Main()
{
    AJ_Status status = AJ_OK;
    AJ_Initialize();
    AJ_PrintXML(AppObjects);
    AJ_RegisterObjects(AppObjects, NULL);
    Do_Connect();

    while (TRUE) {
        AJ_Message msg;

        status = AJ_UnmarshalMsg(&bus, &msg, UNMARSHAL_TIMEOUT);
        if (status == AJ_ERR_TIMEOUT) {
            AppDoWork();
            continue;
        }
        if (status == AJ_OK) {
            printf("Message parsed. Id is %u, sender is %s , dest is %s \n", msg.msgId, msg.sender, msg.destination);
            status = AJ_BusHandleBusMessage(&msg);
        }

        AJ_CloseMsg(&msg);
    }

    return 0;
}

#ifdef AJ_MAIN
int main()
{
    return AJ_Main();
}
#endif
