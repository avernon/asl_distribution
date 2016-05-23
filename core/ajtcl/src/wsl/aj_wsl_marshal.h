/**
 * @file Marshaling function declarations
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

#ifndef AJ_WSL_MARSHAL_H_
#define AJ_WSL_MARSHAL_H_

#include <stdarg.h>

#include "aj_wsl_wmi.h"
#include "aj_wsl_spi_constants.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Marshal a list of arguments into a AJ_BufList.
 *
 * @param data      The AJ_BufList to contain the marshaled data
 * @param sig       The signature matching the parameters following it
 * @param ...       The arguments that will be marshaled into the AJ_BufList
 *                  in the order they appear.
 *
 * @return          1 If the data was successfully marshaled
 *                  0 If there was an error
 */
uint8_t WMI_MarshalArgsBuf(AJ_BufList* data, const char* sig, uint16_t size, va_list* argpp);

/**
 * Marshals the header onto an already existing packet.
 *
 * @param data      The AJ_BufList already containing the packet data
 */
void WMI_MarshalHeader(AJ_BufList* packet, uint8_t endpoint, uint8_t flags);

/**
 * Marshals an entire packet to send over SPI
 *
 * @param command   The command ID you are marshaling
 * @param AJ_BufList  An empty, malloc'ed buffer list to hold the packet data
 * @param ...       The list of arguments to put into the packet.
 *                  (note: the list of arguments must match the signature of the
 *                  packet you are trying to marshal. This includes, starting with,
 *                  the command ID followed by a 32 bit unsigned int (usually 0),
 *                  then the arguments for the packet.)
 *
 * @return          The size of the packet that was marshaled (not including header)
 *                  0 If there was an error
 */
void WSL_MarshalPacket(AJ_BufList* packet, wsl_wmi_command_list command, ...);

/**
 * Marshal a IPv6 sendTo packet.
 *
 * @param packet    The buf list where the marshalled data will be stored
 * @param sock      The socket your sending the packet over
 * @param data      Pointer to the data your sending
 * @param size      Size of the data your sending
 * @param addr      Endpoint address your sending to
 * @param port      The port your sending over
 */
void WMI_MarshalSendTo6(AJ_BufList* packet, uint32_t sock, AJ_BufNode* data, uint16_t size, uint8_t* addr, uint16_t port);

/**
 * Marshal a IPv4 sendTo packet.
 *
 * @param packet    The buf list where the marshalled data will be stored
 * @param sock      The socket your sending the packet over
 * @param data      Pointer to the data your sending
 * @param size      Size of the data your sending
 * @param addr      Endpoint address your sending to
 * @param port      The port your sending over
 */
void WMI_MarshalSendTo(AJ_BufList* packet, uint32_t sock, AJ_BufNode* data, uint16_t size, uint32_t addr, uint16_t port);

/**
 * Marshal a IPv4 send packet.
 *
 * @param packet    The buf list where the marshalled data will be stored
 * @param sock      The socket your sending the packet over
 * @param data      Pointer to the data your sending
 * @param size      Size of the data your sending
 */
void WMI_MarshalSend(AJ_BufList* packet, uint32_t sock, AJ_BufNode* data, uint16_t size);

#ifdef __cplusplus
}
#endif

#endif /* AJ_WSL_MARSHAL_H_ */
