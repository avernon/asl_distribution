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
    { 128,    100, 0, 0 },
    { 256,    30, 0, 0 },
    { 512,    16, 0, 0 },
    { 1024,   8, 0, 0 },
    { 2048,   6, 0, 0 },
#ifdef DUK_FIXED_SIZE_ST
    { DUK_FIXED_SIZE_ST* sizeof(void*), 1, 0, 0 }
#else
    { 4296,     3, 0, 0 }
#endif
};
/*
 * Static heap for the pool allocator.
 * TODO: Tune this heap, 128k is much bigger than is needed.
 */
static uint8_t heapRAM[128756];

AJ_Status AJS_HeapCreate()
{
    size_t heapSz[1];
    uint8_t* heapArray[1];
    /*
     * Calculate the sizes for each heap
     */
    heapSz[0] = AJS_HeapRequired(heapConfig, ArraySize(heapConfig), 0); //RAM
    if (heapSz[0] > sizeof(heapRAM)) {
        AJ_ErrPrintf(("Not enough memory to allocate %u bytes\n", heapSz[0]));
        return AJ_ERR_RESOURCES;
    }

    AJ_InfoPrintf(("Allocated heap %d bytes\n", (int)heapSz[0]));

    heapArray[0] = (uint8_t*)&heapRAM;

    AJS_HeapInit((void**)heapArray, heapSz, heapConfig, ArraySize(heapConfig), 1);

    return AJ_OK;
}

void AJS_HeapDestroy()
{
    return;
}
