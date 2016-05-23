/**
 * @file  UART transport Tester
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
#include <ajtcl/alljoyn.h>
#include <ajtcl/aj_util.h>
#include <ajtcl/aj_debug.h>
#include <ajtcl/aj_bufio.h>
#include <ajtcl/aj_serial.h>


#define BITRATE B115200
#define AJ_SERIAL_WINDOW_SIZE   4
#define AJ_SERIAL_ENABLE_CRC    1
#define AJ_SERIAL_PACKET_SIZE  104

static uint8_t txBuffer[32];
static uint8_t rxBuffer[32];


void TimerCallbackEndProc(uint32_t timerId, void* context)
{
    AJ_AlwaysPrintf(("TimerCallback %.6d \n", timerId));
    exit(0);
}


#ifdef AJ_MAIN
int main()
{
    AJ_Status status;
    memset(&rxBuffer, 'R', sizeof(rxBuffer));

#ifdef READTEST
    status = AJ_SerialInit("/dev/ttyUSB0", BITRATE, AJ_SERIAL_WINDOW_SIZE, AJ_SERIAL_ENABLE_CRC, AJ_SERIAL_PACKET_SIZE);
#else
    status = AJ_SerialInit("/dev/ttyUSB1", BITRATE, AJ_SERIAL_WINDOW_SIZE, AJ_SERIAL_ENABLE_CRC, AJ_SERIAL_PACKET_SIZE);
#endif

    AJ_AlwaysPrintf(("serial init was %u\n", status));

    uint32_t timerEndProc = 9999;
    status = AJ_TimerRegister(10000, &TimerCallbackEndProc, NULL, &timerEndProc);
    AJ_AlwaysPrintf(("Added id %u\n", timerEndProc));




    uint16_t echocount = 0;
    while (1) {
        snprintf((char*)&txBuffer, sizeof(txBuffer), "echo t %i", ++echocount);

#ifdef READTEST
        uint16_t recv;
        AJ_SerialRecv(rxBuffer, sizeof(rxBuffer), 2000, &recv);
        AJ_DumpBytes("Post serial recv", rxBuffer, sizeof(rxBuffer));

#else
        AJ_Sleep(500);
        AJ_SerialSend(txBuffer, sizeof(txBuffer));
        AJ_AlwaysPrintf(("post serial send\n"));
#endif

        AJ_Sleep(400);
    }


    return(0);
}
#endif
