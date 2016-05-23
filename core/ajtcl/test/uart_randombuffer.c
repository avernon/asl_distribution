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
#define RANDOM_BYTES_MAX 5000

#ifdef ECHO
static uint8_t txBuffer[RANDOM_BYTES_MAX];
#endif
static uint8_t rxBuffer[RANDOM_BYTES_MAX];



int AJ_Main()
{
    AJ_Status status;

    status = AJ_SerialInit("/dev/ttyUSB1", BITRATE, AJ_SERIAL_WINDOW_SIZE, AJ_SERIAL_PACKET_SIZE);
    AJ_AlwaysPrintf(("serial init was %u\n", status));
    uint16_t txlen;
    uint16_t rxlen;
    int i = 0;

#ifdef ECHO
    while (1) {
        AJ_AlwaysPrintf(("Iteration %d\n", i++));
        status = AJ_SerialRecv(rxBuffer, RANDOM_BYTES_MAX, 5000, &rxlen);
        if (status == AJ_ERR_TIMEOUT) {
            continue;
        }
        if (status != AJ_OK) {
            AJ_AlwaysPrintf(("AJ_SerialRecv returned %d\n", status));
            exit(1);
        }
        AJ_Sleep(rand() % 5000);

        status = AJ_SerialSend(rxBuffer, rxlen);
        if (status != AJ_OK) {
            AJ_AlwaysPrintf(("AJ_SerialSend returned %d\n", status));
            exit(1);
        }

        AJ_Sleep(rand() % 5000);
    }
#else
    txlen = 0;
    while (1) {
        AJ_AlwaysPrintf(("Iteration %d\n", i++));
        txlen = rand() % 5000;
        for (int i = 0; i < txlen; i++) {
            txBuffer[i] = rand() % 256;
            rxBuffer[i] = 1;
        }
        status = AJ_SerialSend(txBuffer, txlen);
        if (status != AJ_OK) {
            AJ_AlwaysPrintf(("AJ_SerialSend returned %d\n", status));
            exit(1);
        }
        AJ_Sleep(rand() % 5000);
        status = AJ_SerialRecv(rxBuffer, txlen, 50000, &rxlen);
        if (status != AJ_OK) {
            AJ_AlwaysPrintf(("AJ_SerialRecv returned %d\n", status));
            exit(1);
        }
        if (rxlen != txlen) {
            AJ_AlwaysPrintf(("Failed: length match rxlen=%d txlen=%d.\n", rxlen, txlen));
            exit(-1);
        }
        if (0 != memcmp(txBuffer, rxBuffer, rxlen)) {
            AJ_AlwaysPrintf(("Failed: buffers match.\n"));
            exit(-1);
        }

    }
#endif
    return(0);
}

#ifdef AJ_MAIN
int main()
{
    return AJ_Main();
}
#endif
