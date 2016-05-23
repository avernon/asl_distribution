/**
 * @file NVRAM function declarations
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
/******************************************************************************
 * This code statically links to code available from
 * http://www.st.com/web/en/catalog/tools/ and that code is subject to a license
 * agreement with terms and conditions that you will be responsible for from
 * STMicroelectronics if you employ that code. Use of such code is your responsibility.
 * Neither AllSeen Alliance nor any contributor to this AllSeen code base has any
 * obligations with respect to the STMicroelectronics code that to which you will be
 * statically linking this code. One requirement in the license is that the
 * STMicroelectronics code may only be used with STMicroelectronics processors as set
 * forth in their agreement."
 *******************************************************************************/

#ifndef _AJ_TARGET_PLATFORM_H_
#define _AJ_TARGET_PLATFORM_H_

#include <stm32f4xx_conf.h>
#include <stm32f4xx.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_dma.h>
#include <stm32f4xx_spi.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_flash.h>
#include <stm32f4_discovery.h>
#include <stm32f4xx_usart.h>
#include <stm32f4xx_rng.h>
#include <stm32f4xx_exti.h>
#include <stm32f4xx_syscfg.h>
#include <misc.h>
#include <FreeRTOSConfig.h>

SPI_InitTypeDef AJ_SPIHandle;

#define A_UINT32 uint32_t

#ifdef AJ_NVRAM_SIZE
#undef AJ_NVRAM_SIZE
#define AJ_NVRAM_SIZE (0x20000)
#else
#define AJ_NVRAM_SIZE (0x20000)
#endif

#define AJ_WSL_SPI_DEVICE (void*)0
#define AJ_WSL_SPI_DEVICE_ID 0
#define AJ_WSL_SPI_DEVICE_NPCS 0
#define AJ_WSL_SPI_PCS 0
#define AJ_WSL_SPI_CHIP_PWD_PIN 0  /* currently connected to the Reset pin on the ICSP header*/
#define AJ_WSL_SPI_CHIP_SPI_INT_PIN 0  /* pin D7 on the Arduino Due */
#define AJ_WSL_SPI_CHIP_SPI_INT_BIT 0
#define AJ_WSL_SPI_CHIP_POWER_PIN 0  /* pin D3 on the Arduino Due */
#define AJ_WSL_STACK_SIZE   3000

typedef enum {
    SPI_OK,
    SPI_ERR
}aj_spi_status;

int printf(const char* fmat, ...);

#ifndef NDEBUG
#define AJ_Printf(fmat, ...) \
    do { \
        AJ_EnterCriticalRegion(); \
        printf(fmat, ## __VA_ARGS__); \
        AJ_LeaveCriticalRegion(); \
    } while (0)
#else
#define AJ_Printf(fmat, ...) \
    do { printf(fmat, ## __VA_ARGS__); } while (0)
#endif

#endif
