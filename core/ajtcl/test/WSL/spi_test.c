/**
 * @file Unit tests for AJ_WSL SPI list.
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


#ifdef __cplusplus
extern "C" {
#endif



#define AJ_MODULE WSL_UNIT_TEST

#include <ajtcl/aj_target.h>

#include "../../src/wsl/aj_buf.h"
#include "../../src/wsl/aj_wsl_htc.h"
#include "../../src/wsl/aj_wsl_spi.h"
#include "../../src/wsl/aj_wsl_wmi.h"
#include "../../src/wsl/aj_wsl_net.h"
#include <ajtcl/aj_debug.h>


/**
 * Turn on per-module debug printing by setting this variable to non-zero value
 * (usually in debugger).
 */
#ifndef NDEBUG
uint8_t dbgWSL_UNIT_TEST = 5;
#endif


static void run_fill_mbox(const struct test_case* test)
{
    uint16_t MBoxSpaceAvailable = 0;
    AJ_BufList* list1 = AJ_BufListCreate();
    AJ_BufNode* pNode1;
    AJ_BufNode* pNode2;

    AJ_AlwaysPrintf(("\n\n**************\nTEST:  %s\n\n", __FUNCTION__));
    AJ_WSL_SPI_RegisterRead(AJ_WSL_SPI_REG_WRBUF_SPC_AVA, &MBoxSpaceAvailable);

    // fill up a mailbox with 'Z'
    pNode1 = AJ_BufListCreateNode(MBoxSpaceAvailable);
    memset(pNode1->bufferStart, 0x5A, MBoxSpaceAvailable);
    AJ_BufListPushHead(list1, pNode1);

    // fill up a mailbox with '!'
    pNode2 = AJ_BufListCreateNode(MBoxSpaceAvailable);
    memset(pNode2->bufferStart, 0x21, MBoxSpaceAvailable);
    AJ_BufListPushTail(list1, pNode2);


    AJ_WSL_WriteBufListToMBox(0, MBoxSpaceAvailable, list1);
    AJ_WSL_WriteBufListToMBox(0, MBoxSpaceAvailable * 2, list1);

    AJ_BufListFree(list1, TRUE);

};

static void run_read_from_mbox(const struct test_case* test)
{

    uint8_t* rawMboxMessage;
    uint16_t MBoxSpaceAvailable = 0;
    AJ_AlwaysPrintf(("\n\n**************\nTEST:  %s\n\n", __FUNCTION__));

    AJ_WSL_ReadFromMBox(0, &MBoxSpaceAvailable, &rawMboxMessage);

    AJ_Free(rawMboxMessage);
};


/**
 * Run buffer list tests.
 */
int main(void)
{
    AJ_WSL_ModuleInit();

    toTarget.fakeWireCurr = toTarget.fakeWireBuffer;
    toTarget.fakeWireRead = toTarget.fakeWireBuffer;
    toTarget.fakeWireWrite = toTarget.fakeWireBuffer;
    fromTarget.fakeWireCurr = fromTarget.fakeWireBuffer;
    fromTarget.fakeWireRead = fromTarget.fakeWireBuffer;
    fromTarget.fakeWireWrite = fromTarget.fakeWireBuffer;

    //// hook the SPI operations to run without SPI hardware
    //AJ_WSL_SPI_RegisterRead = &Hooked_AJ_WSL_RegisterRead;
    //AJ_WSL_SPI_RegisterWrite = &Hooked_AJ_WSL_RegisterWrite;
    //AJ_WSL_SPI_OPS.writeDMA = &Hooked_AJ_WSL_DMAWrite;
    //AJ_WSL_SPI_OPS.readDMA = &Hooked_AJ_WSL_DMARead;
    //AJ_WSL_SPI_WriteByte8 = &Hooked_AJ_WSL_WriteByte8;
    //AJ_WSL_SPI_WriteByte16 = &Hooked_AJ_WSL_WriteByte16;
//
    run_fill_mbox(NULL);
    run_read_from_mbox(NULL);
}


#ifdef __cplusplus
}
#endif

