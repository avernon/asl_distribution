#ifndef _AJ_TARGET_NVRAM_H_
#define _AJ_TARGET_NVRAM_H_

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

/*
 * Identifies an AJ NVRAM block
 */
#define AJ_NV_SENTINEL ('A' | ('J' << 8) | ('N' << 16) | ('V' << 24))
#define INVALID_ID (0)
#define INVALID_DATA (0xFFFF)
#define INVALID_DATA_BYTE (0xFF)
#define SENTINEL_OFFSET (4)

typedef struct _NV_EntryHeader {
    uint16_t id;           /**< The unique id */
    uint16_t capacity;     /**< The data set size */
} NV_EntryHeader;

#define ENTRY_HEADER_SIZE (sizeof(NV_EntryHeader))
#define AJ_NVRAM_END_ADDRESS (AJ_NVRAM_BASE_ADDRESS + AJ_NVRAM_SIZE)

/**
 * Write a block of data to NVRAM
 *
 * @param dest  Pointer a location of NVRAM
 * @param buf   Pointer to data to be written
 * @param size  The number of bytes to be written
 */
void _AJ_NV_Write(void* dest, const void* buf, uint16_t size);

/**
 * Read a block of data from NVRAM
 *
 * @param src   Pointer a location of NVRAM
 * @param buf   Pointer to data to be written
 * @param size  The number of bytes to be written
 */
void _AJ_NV_Read(void* src, void* buf, uint16_t size);


/**
 * Erase the whole NVRAM sector and write the sentinel data
 */
void _AJ_NVRAM_Clear();

#endif
