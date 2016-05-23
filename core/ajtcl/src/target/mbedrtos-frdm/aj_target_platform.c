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

#include <ajtcl/aj_nvram.h>
#include <ajtcl/aj_target_platform.h>
#include <ajtcl/aj_debug.h>

void _AJ_PlatformInit(void)
{
    BoardPrintfInit(115200);
    return;
}
uint16_t AJ_ByteSwap16(uint16_t x)
{
    return ((((x) >> 8) & 0xff) | (((x) & 0xff) << 8));
}

uint32_t swap32(uint32_t x)
{
    return AJ_ByteSwap32(x);
}

uint32_t AJ_ByteSwap32(uint32_t x)
{
    return ((x >> 24) & 0x000000FF) | ((x >> 8) & 0x0000FF00) |
           ((x << 24) & 0xFF000000) | ((x << 8) & 0x00FF0000);
}

uint64_t AJ_ByteSwap64(uint64_t x)
{
    return ((x >> 56) & 0x00000000000000FF) | ((x >> 40) & 0x000000000000FF00) |
           ((x << 56) & 0xFF00000000000000) | ((x << 40) & 0x00FF000000000000) |
           ((x >> 24) & 0x0000000000FF0000) | ((x >>  8) & 0x00000000FF000000) |
           ((x << 24) & 0x0000FF0000000000) | ((x <<  8) & 0x000000FF00000000);
}

uint8_t AJ_SeedRNG(void)
{
    return 1;
}

void _exit(int i)
{
    while (1);
}
int _kill(int pid)
{
    return 1;
}
int _getpid()
{
    return 0;
}
void _gettimeofday()
{
    return;
}

