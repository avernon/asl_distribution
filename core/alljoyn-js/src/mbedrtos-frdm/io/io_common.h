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
#ifndef IO_COMMON_H_
#define IO_COMMON_H_

/*
 * This struct is used as a hack way to get the actual pin
 * number mapped from the io_info struct to the various
 * peripherals supported. Each peripheral (GPIO, I2C, ADC etc.)
 * has its own struct with mappings to the real pin number that
 * is always needed to initialize each peripheral. If this pin
 * number is always a uint8_t and always the first element it
 * can be cast to the GenericPinInfo struct to get just the pin.
 */
typedef struct _GenericPinInfo {
    uint8_t pinNum;
} GenericPinInfo;

/*
 * Get the pin index from the physicalPin
 */
#ifdef __cplusplus
extern "C" {
#endif
uint8_t AJS_GetPinNum(void* infoStruct, uint8_t physicalPin);
#ifdef __cplusplus
}
#endif
#endif /* IO_COMMON_H_ */
