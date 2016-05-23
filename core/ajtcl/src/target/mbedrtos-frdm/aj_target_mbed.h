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

#ifndef AJ_TARGET_MBED_H_
#define AJ_TARGET_MBED_H_

typedef enum {
    SPI_OK,
    SPI_ERR
}aj_spi_status;

/**
 * Printf function that prints to the serial port on the MBED board
 *
 * @param fmat          Format string (same as printf)
 * @param ...           List of arguments that will be placed in the format string
 *
 * note: Currently this function only supports printing 256 characters per call.
 * Anything over that would need to have successive BoardPrintf calls.
 */
void BoardPrintf(const char* fmat, ...);

/**
 * Initialize the serial port so BoardPrintf can be used. This must be called
 * before BoardPrintf or it will not function.
 *
 * @param baud          Baud rate for the serial port
 */
void BoardPrintfInit(uint32_t baud);

/**
 * Initialize the SPI controller. This function does all the initialization in order for the SPI
 * peripheral to work the the GT-202/QCA4004/2
 */
void AJ_WSL_SPI_InitializeSPIController(void);

/**
 * Sleep for a specified time
 *
 * @param time          Time to sleep in milliseconds
 */
void AJ_Sleep(uint32_t time);

#endif /* AJ_TARGET_MBED_H_ */
