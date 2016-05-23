#ifndef _AJ_TARGET_PLATFORM_H_
#define _AJ_TARGET_PLATFORM_H_
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

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <ajtcl/aj_target_mbed.h>

#define AJ_Printf BoardPrintf


#define A_UINT32 uint32_t

#ifdef AJ_NVRAM_SIZE
#undef AJ_NVRAM_SIZE
#define AJ_NVRAM_SIZE (0x10000)
#else
#define AJ_NVRAM_SIZE (0x10000)
#endif

#define AJ_WSL_SPI_DEVICE 0
#define AJ_WSL_SPI_DEVICE_ID 0
#define AJ_WSL_SPI_DEVICE_NPCS 0
#define AJ_WSL_SPI_PCS 0
#define AJ_WSL_SPI_CHIP_PWD_PIN 0
#define AJ_WSL_SPI_CHIP_SPI_INT_PIN 0
#define AJ_WSL_SPI_CHIP_SPI_INT_BIT 0
#define AJ_WSL_SPI_CHIP_POWER_PIN 0
#define AJ_WSL_STACK_SIZE   3000

void _AJ_NVRAM_Clear(void);
void AJ_NVRAM_Init(void);
void _AJ_PlatformInit(void);
uint8_t AJ_SeedRNG(void);

/*
 * AJ_Reboot() is a NOOP on this platform
 */
#define AJ_Reboot() _AJ_Reboot()

#ifdef __cplusplus
}
#endif


#endif
