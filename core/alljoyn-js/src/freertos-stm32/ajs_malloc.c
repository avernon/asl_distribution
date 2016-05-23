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

#include "../ajs.h"
#include "../ajs_util.h"
#include "../ajs_target.h"
#include "../ajs_ctrlpanel.h"
#include <ajtcl/aj_util.h>
#include "../ajs_heap.h"

/**
 * Turn on per-module debug printing by setting this variable to non-zero value
 * (usually in debugger).
 */
#ifndef NDEBUG
uint8_t dbgAJS_MALLOC = 0;
#endif

static const AJS_HeapConfig heapConfig[] = {
    { 12,      20, AJS_POOL_BORROW, 0 },
    { 20,     100, AJS_POOL_BORROW, 0 },
    { 24,     100, AJS_POOL_BORROW, 0 },
    { 32,     700, AJS_POOL_BORROW, 0 },
    { 40,     250, 0, 0 },
    { 48,     400, 0, 0 },
    { 128,    80, 0, 0 },
    { 256,    30, 0, 1 },
    { 512,    16, 0, 1 },
    { 1024,   6, 0, 1 },
    { 2048,   6, 0, 1 },
#ifdef DUK_FIXED_SIZE_ST
    { DUK_FIXED_SIZE_ST* sizeof(void*), 1, 0, 1 }
#else
    { 4296,     3, 0, 1 }
#endif
};
/*
 * Special section of RAM on the STM32F4. It is not in a continuous address space
 * as normal ram so it must have its own heap in the pool allocator
 */
static uint32_t heapCCM[63928 / 4] __attribute__ ((section(".ccm")));
/*
 * Regular RAM section. This can be dynamically allocated out of the FreeRTOS heap
 */
static uint32_t* heapRAM;

AJ_Status AJS_HeapCreate()
{
    size_t heapSz[2];
    uint8_t* heapArray[2];
    /*
     * Calculate the sizes for each heap
     */
    heapSz[0] = AJS_HeapRequired(heapConfig, ArraySize(heapConfig), 0); //RAM
    heapSz[1] = AJS_HeapRequired(heapConfig, ArraySize(heapConfig), 1); //CCM
    heapRAM = AJ_Malloc(heapSz[0]);
    if (!heapRAM) {
        AJ_ErrPrintf(("Not enough memory to allocate %u bytes\n", heapSz[0]));
        return AJ_ERR_RESOURCES;
    }

    if (heapSz[1] > sizeof(heapCCM)) {
        AJ_ErrPrintf(("Heap space is too small %d required %d\n", (int)sizeof(heapCCM), (int)heapSz[1]));
        return AJ_ERR_RESOURCES;
    }

    AJ_Printf("Allocated heap %d bytes\n", (int)heapSz[0]);

    heapArray[0] = heapRAM;
    heapArray[1] = &heapCCM;

    AJS_HeapInit(heapArray, heapSz, heapConfig, ArraySize(heapConfig), 2);
}

void AJS_HeapDestroy()
{
    AJ_Free(heapRAM);
}
