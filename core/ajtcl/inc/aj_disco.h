#ifndef _AJ_DISCO_H
#define _AJ_DISCO_H

/**
 * @file
 */
/******************************************************************************
 * Copyright (c) 2012-2015, AllSeen Alliance. All rights reserved.
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
#include <ajtcl/aj_bufio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Information about the remote service
 */
typedef struct _AJ_Service {
    uint8_t addrTypes;         /**< address type */
    uint16_t transportMask;    /**< restricts the transports the advertisement */
    uint16_t ipv4port;         /**< port number of ipv4 */
    uint16_t ipv6port;         /**< port number of ipv6 */
    uint32_t ipv4;             /**< ipv4 address */
    uint16_t priority;         /**< priority */
    uint32_t pv;               /**< protocol version */
    uint32_t ipv6[4];          /**< ipv6 address */

    uint16_t ipv4portUdp;      /**< port number of ipv4 */
    uint16_t ipv6portUdp;      /**< port number of ipv6 */
    uint32_t ipv4Udp;          /**< ipv4 address */
    uint32_t ipv6Udp[4];       /**< ipv6 address */
} AJ_Service;

/**
 * Discover a remote service
 *
 * @param prefix            The service name prefix
 * @param service           Information about the service that was found
 * @param timeout           How long to wait to discover the service
 * @param selectionTimeout  How long to wait to receive router responses
 *
 * @return                  Return AJ_Status
 */
AJ_Status AJ_Discover(const char* prefix, AJ_Service* service, uint32_t timeout, uint32_t selectionTimeout);

#ifdef __cplusplus
}
#endif

#endif
