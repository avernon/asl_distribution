# Contributed by Qualcomm Connected Experiences, Inc.,
# with authorization from the AllSeen Alliance, Inc.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# 
# Pursuant to Section 1 of the License, the work of authorship constituting
# a Work and any Contribution incorporated in the Work shall mean only that
# Contributor's code submissions authored by that Contributor.  Any rights
# granted under the License are conditioned upon acceptance of these
# clarifications.
#ifndef _AJ_NET_H
#define _AJ_NET_H

/**
 * @file aj_net.h
 * @defgroup aj_net Network Send and Receive
 * @{
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
#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bufio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define AJ_ADDR_UDP4  0x01      /**< UDP ip4 address */
#define AJ_ADDR_UDP6  0x02      /**< UDP ip6 address */

#define AJ_ADDR_TCP4  0x04      /**< TCP ip4 address */
#define AJ_ADDR_TCP6  0x08      /**< TCP ip6 address */

struct _AJ_Service;
struct _AJ_BusAttachment;

/**
 * Abstracts a network socket
 */
typedef struct _AJ_NetSocket {
    AJ_IOBuffer tx;             /**< transmit network socket */
    AJ_IOBuffer rx;             /**< receive network socket */
} AJ_NetSocket;

/**
 * Connect to bus at an IPV4 or IPV6 address, either UDP or TCP
 *
 * @return        Return AJ_Status
 */
AJ_Status AJ_Net_Connect(struct _AJ_BusAttachment* bus, const struct _AJ_Service* service);

/**
 * Disconnect from the bus
 */
void AJ_Net_Disconnect(AJ_NetSocket* netSock);

/**
 * Send from an I/O buffer
 *
 * @return        Return AJ_Status
 */
AJ_Status AJ_Net_Send(AJ_IOBuffer* txBuf);

/**
 * Send into an I/O buffer
 *
 * @return        Return AJ_Status
 */
AJ_Status AJ_Net_Recv(AJ_IOBuffer* rxBuf, uint32_t len, uint32_t timeout);

/**
 * Abstracts discovery sockets
 */
typedef struct _AJ_MCastSocket {
    AJ_IOBuffer tx;
    AJ_IOBuffer rx;
} AJ_MCastSocket;

/**
 * Enable multicast (for discovery)
 *
 * @return        Return AJ_Status
 */
AJ_Status AJ_Net_MCastUp(AJ_MCastSocket* mcastSock);

/**
 * Disable multicast (for discovery)
 */
void AJ_Net_MCastDown(AJ_MCastSocket* mcastSock);

/**
 * Function that signals AJ_Net_Recv() to bail out early if it
 * is blocking on select.
 */
void AJ_Net_Interrupt(void);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */
#endif
