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
#include "../ajs_heap.h"

#ifndef AJS_USE_NATIVE_MALLOC

static const AJS_HeapConfig heapConfig[] = {
    { 8,      100, AJS_POOL_BORROW, 0 },
    { 16,     600, AJS_POOL_BORROW, 0 },
    { 24,     400, AJS_POOL_BORROW, 0 },
    { 32,     400, AJS_POOL_BORROW, 0 },
    { 48,     300, 0, 0 },
    { 64,     100, 0, 0 },
    { 128,     64, 0, 0 },
    { 256,     32, 0, 0 },
    { 512,     16, 0, 0 },
    { 1024,     8, 0, 0 },
    { 2048,     4, AJS_POOL_BORROW, 0 },
    { 6000,     2, 0, 0 }
};

#define NUM_HEAPS 1

static void* heap[NUM_HEAPS];

AJ_Status AJS_HeapCreate()
{
    int i;
    size_t heapSz[NUM_HEAPS];

    /*
     * Allocate the heap pools
     */
    for (i = 0; i < NUM_HEAPS; ++i) {
        heapSz[i] = AJS_HeapRequired(heapConfig, ArraySize(heapConfig), i);
        heap[i] = malloc(heapSz[i]);
        if (!heap[i]) {
            AJ_ErrPrintf(("AJS_HeapCreate(): Malloc failed to allocate %d bytes\n", heapSz[i]));
            return AJ_ERR_RESOURCES;
        }
        AJ_Printf("Allocated heap[%d] %d bytes\n", i, (int)heapSz[i]);
    }
    return AJS_HeapInit(heap, heapSz, heapConfig, ArraySize(heapConfig), NUM_HEAPS);
}

void AJS_HeapDestroy()
{
    int i;
    for (i = 0; i < NUM_HEAPS; ++i) {
        free(heap[i]);
    }
}

#else

AJ_Status AJS_HeapCreate()
{
    return AJ_OK;
}

void AJS_HeapDestroy()
{
}

void* AJS_Alloc(void* userData, size_t sz)
{
    return malloc(sz);
}

void AJS_Free(void* userData, void* mem)
{
    return free(mem);
}

void* AJS_Realloc(void* userData, void* mem, size_t newSz)
{
    return realloc(mem, newSz);
}

#ifndef NDEBUG
void AJS_HeapDump(void)
{
}
#endif

#endif
