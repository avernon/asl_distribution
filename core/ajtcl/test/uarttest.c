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

#define B115200 111520
#define BITRATE B115200
#define AJ_SERIAL_WINDOW_SIZE   4
#define AJ_SERIAL_ENABLE_CRC    1
#define LOCAL_DATA_PACKET_SIZE  100
#define AJ_SERIAL_PACKET_SIZE  LOCAL_DATA_PACKET_SIZE

static uint8_t txBuffer[1600];
static uint8_t rxBuffer[1600];


void TimerCallbackEndProc(uint32_t timerId, void* context)
{
    AJ_AlwaysPrintf(("TimerCallbackEndProc %.6d \n", timerId));
#ifdef READTEST
    if (0 == memcmp(txBuffer, rxBuffer, sizeof(rxBuffer))) {
        AJ_AlwaysPrintf(("Passed: buffers match.\n"));
    } else {
        AJ_AlwaysPrintf(("FAILED: buffers mismatch.\n"));
        exit(-1);
    }
#endif
    exit(0);
}


int AJ_Main()
{
    AJ_Status status;
    memset(&txBuffer, 'T', sizeof(txBuffer));
    memset(&rxBuffer, 'R', sizeof(rxBuffer));

    int blocks;
    int blocksize = LOCAL_DATA_PACKET_SIZE;
    for (blocks = 0; blocks < 16; blocks++) {
        memset(txBuffer + (blocks * blocksize), 0x41 + (uint8_t)blocks, blocksize);
    }

#ifdef READTEST
    status = AJ_SerialInit("/dev/ttyUSB0", BITRATE, AJ_SERIAL_WINDOW_SIZE, AJ_SERIAL_PACKET_SIZE);
#else
    status = AJ_SerialInit("/dev/ttyUSB1", BITRATE, AJ_SERIAL_WINDOW_SIZE, AJ_SERIAL_PACKET_SIZE);
#endif

    AJ_AlwaysPrintf(("serial init was %u\n", status));




#ifdef READTEST
    AJ_Sleep(2000); // wait for the writing side to be running, this should test the queuing of data.
    // try to read everything at once
    int i = 0;

    //for ( ; i < 10000; ++i) {
    while (1) {
        AJ_SerialRecv(rxBuffer, sizeof(rxBuffer), 50000, NULL);
    }


/*
    //Read small chunks of a packet at one time.
    for (blocks = 0 ; blocks < 16*4; blocks++) {
        AJ_SerialRecv(rxBuffer+(blocks*blocksize/4), blocksize/4, 2000, NULL);
   //        AJ_Sleep(200);
    }
 */
    AJ_DumpBytes("Post serial recv", rxBuffer, sizeof(rxBuffer));
    AJ_Sleep(500);
#else
    AJ_Sleep(5000);
    int i = 0;


    while (1) {
        AJ_SerialSend(txBuffer, sizeof(txBuffer));
        ++i;
        if (i % 500 == 0) {
            AJ_AlwaysPrintf(("Hit iteration %d\n", i));
        }
    }

    AJ_AlwaysPrintf(("post serial send\n"));
#endif


    while (1) {
        AJ_StateMachine();
    }


    return(0);
}

#ifdef AJ_MAIN
int main()
{
    return AJ_Main();
}
#endif
