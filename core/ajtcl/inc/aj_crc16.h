#ifndef _AJ_CRC16_H
#define _AJ_CRC16_H

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

#include <ajtcl/aj_target.h>

#ifdef __cplusplus
extern "C" {
#endif
/**
 * Computes a 16-bit CRC on a buffer. The caller provides the context for the running CRC.
 *
 * @param buffer         buffer over which to compute the CRC
 * @param bufLen         length of the buffer in bytes
 * @param runningCrc     On input the current CRC, on output the updated CRC.
 */
void AJ_CRC16_Compute(const uint8_t* buffer,
                      uint16_t bufLen,
                      uint16_t* runningCrc);

/**
 * This function completes the CRC computation by rearranging the CRC bits and bytes
 * into the correct order.
 *
 * @param crc       computed crc as calculated by AJ_CRC16_Compute()
 * @param crcBlock  pointer to a 2-byte buffer where the resulting CRC will be stored
 */

void AJ_CRC16_Complete(uint16_t crc,
                       uint8_t* crcBlock);

#ifdef __cplusplus
}
#endif

#endif /* _AJ_CRC16_H */
