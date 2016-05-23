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
#include <ajtcl/aj_debug.h>

static const char ServiceName[] = "org.alljoyn.ajlite";

#define CONNECT_TIMEOUT    (1000 * 60)
#define UNMARSHAL_TIMEOUT  (1000 * 5)

int AJ_Main()
{
    AJ_Status status;
    AJ_BusAttachment bus;

    AJ_Initialize();

    status = AJ_FindBusAndConnect(&bus, NULL, CONNECT_TIMEOUT);
    if (status == AJ_OK) {
        status = AJ_BusRequestName(&bus, ServiceName, AJ_NAME_REQ_DO_NOT_QUEUE);
    }
    while (status == AJ_OK) {
        AJ_Message msg;
        status = AJ_UnmarshalMsg(&bus, &msg, UNMARSHAL_TIMEOUT);
        if (status == AJ_OK) {
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
