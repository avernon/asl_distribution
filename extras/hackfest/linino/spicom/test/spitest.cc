/**
 * @file
 * SPICom test
 */

/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <aj_tutorial/spicom.h>

#define ITERATIONS 10000

void DumpBuf(const char* name, const uint8_t* buf, size_t len)
{
    size_t i;
    printf("%s:", name);
    for (i = 0; i < len; ++i) {
        printf(" %02x", buf[i]);
    }
    printf("\n");
}

void invert(uint8_t* buffer, int size)
{
  while (size > 0) {
    --size;
    buffer[size] = ~buffer[size];
  }
}

int main(void)
{
    SPICom spicom;
    uint8_t txbuf[SPICom::MAX_MSG_LEN + 10];
    uint8_t rxbuf[sizeof(txbuf)];
    uint32_t i;
    int ret;

    for (i = 0; i < sizeof(txbuf); ++i) {
        printf("\rFill %u: ", i); fflush(stdout);
        txbuf[i] = (i & 0xff);
        memset(rxbuf, 0, sizeof(rxbuf));
        if (i > 0) {
            ret = spicom.Write(txbuf, i);
            if ((ret < 0) && (i <= SPICom::MAX_MSG_LEN)) {
                printf("Failed to send %u bytes\n", i);
                sleep(1);
            } else if ((ret > 0) && (i > SPICom::MAX_MSG_LEN)) {
                printf("Sent too large buffer: %d bytes\n", ret);
                sleep(1);
            }
            if ((ret > 0) && (i <= SPICom::MAX_MSG_LEN)) {
                invert(txbuf, i);
                ret = spicom.Read(rxbuf, sizeof(rxbuf));
                if (ret < 0) {
                    printf("Failed to read message: %d\n", ret);
                } else if (ret == 0) {
                    printf("Read timed out\n");
                } else if ((ret > 0) && (memcmp(txbuf, rxbuf, ret) != 0)) {
                    printf("Data received does not match data sent.\n");
                    DumpBuf("tx", txbuf, i);
                    DumpBuf("rx", rxbuf, ret);
                }
                invert(txbuf, i);
            }
        }
    }

    for (i = 0; i < ITERATIONS; ++i) {
        printf("\rIter %u: ", i); fflush(stdout);
        *(uint32_t*)txbuf = i;
        memset(rxbuf, 0, sizeof(rxbuf));
        ret = spicom.Write(txbuf, SPICom::MAX_MSG_LEN);
        if (ret < 0) {
            printf("Failed to send sequence %u\n", i);
            sleep(1);
            continue;
        }
        invert(txbuf, SPICom::MAX_MSG_LEN);
        ret = spicom.Read(rxbuf, sizeof(rxbuf));
        if (ret < SPICom::MAX_MSG_LEN) {
            printf("Failed to receive message sequence %u: %d\n", i, ret);
        } else if ((ret > 0) && (memcmp(txbuf, rxbuf, ret) != 0)) {
            printf("Data received does not match data sent for sequence %u\n", i);
            DumpBuf("tx", txbuf, SPICom::MAX_MSG_LEN);
            DumpBuf("rx", rxbuf, ret);
        }
        invert(txbuf, i);
    }
    printf("Done\n");

    return 0;
}
