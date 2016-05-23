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
    { 16,     200, 0, 0 },
    { 24,     800, 0, 0 },
    { 32,     800, 0, 0 },
    { 48,     800, 0, 0 },
    { 64,     800, 0, 0 },
    { 96,     800, 0, 0 },
    { 128,     64, 0, 0 },
    { 256,     64, 0, 0 },
    { 512,     16, 0, 0 },
    { 1024,    16, 0, 0 },
    { 2048,     8, 0, 0 },
    { 3000,     8, 0, 0 },
    { 4096,     2, 0, 0 },
    { 16384,    2, 0, 0 }
};

static uint32_t heap[500000 / 4];

AJ_Status AJS_HeapCreate()
{
    size_t heapSz[1];
    uint8_t* heapPtr[1];
    heapPtr[0] = &heap;
    /*
     * Allocate the heap pools
     */
    heapSz[0] = AJS_HeapRequired(heapConfig, ArraySize(heapConfig), 0);
    if (heapSz[0] > sizeof(heap)) {
        AJ_ErrPrintf(("Heap space is too small %d required %d\n", (int)sizeof(heap), (int)heapSz[0]));
        return AJ_ERR_RESOURCES;
    }
    AJ_Printf("Allocated heap %d bytes\n", (int)heapSz);
    AJS_HeapInit(heapPtr, heapSz, heapConfig, ArraySize(heapConfig), 1);
    return AJ_OK;
}

void AJS_HeapDestroy()
{
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
void AJS_HeapDump()
{
}
#endif

#endif
