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
#ifndef _AJ_STATUS_H
#define _AJ_STATUS_H
/**
 * @file aj_status.h
 * @defgroup aj_status AllJoyn Status (Return) Codes
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

/**
 * Status codes
 */
typedef enum {

    AJ_OK               = 0,  /**< Success status */
    AJ_ERR_NULL         = 1,  /**< Unexpected NULL pointer */
    AJ_ERR_UNEXPECTED   = 2,  /**< An operation was unexpected at this time */
    AJ_ERR_INVALID      = 3,  /**< A value was invalid */
    AJ_ERR_IO_BUFFER    = 4,  /**< An I/O buffer was invalid or in the wrong state */
    AJ_ERR_READ         = 5,  /**< An error while reading data from the network */
    AJ_ERR_WRITE        = 6,  /**< An error while writing data to the network */
    AJ_ERR_TIMEOUT      = 7,  /**< A timeout occurred */
    AJ_ERR_MARSHAL      = 8,  /**< Marshaling failed due to badly constructed message argument */
    AJ_ERR_UNMARSHAL    = 9,  /**< Unmarshaling failed due to a corrupt or invalid message */
    AJ_ERR_END_OF_DATA  = 10, /**< Not enough data */
    AJ_ERR_RESOURCES    = 11, /**< Insufficient memory to perform the operation */
    AJ_ERR_NO_MORE      = 12, /**< Attempt to unmarshal off the end of an array */
    AJ_ERR_SECURITY     = 13, /**< Authentication or decryption failed */
    AJ_ERR_CONNECT      = 14, /**< Network connect failed */
    AJ_ERR_UNKNOWN      = 15, /**< A unknown value */
    AJ_ERR_NO_MATCH     = 16, /**< Something didn't match */
    AJ_ERR_SIGNATURE    = 17, /**< Signature is not what was expected */
    AJ_ERR_DISALLOWED   = 18, /**< An operation was not allowed */
    AJ_ERR_FAILURE      = 19, /**< A failure has occurred */
    AJ_ERR_RESTART      = 20, /**< The OEM event loop must restart */
    AJ_ERR_LINK_TIMEOUT = 21, /**< The bus link is inactive too long */
    AJ_ERR_DRIVER       = 22, /**< An error communicating with a lower-layer driver */
    AJ_ERR_OBJECT_PATH  = 23, /**< Object path was not specified */
    AJ_ERR_BUSY         = 24, /**< An operation failed and should be retried later */
    AJ_ERR_DHCP         = 25, /**< A DHCP operation has failed */
    AJ_ERR_ACCESS       = 26, /**< The operation specified is not allowed */
    AJ_ERR_SESSION_LOST = 27, /**< The session was lost */
    AJ_ERR_LINK_DEAD    = 28, /**< The network link is now dead */
    AJ_ERR_HDR_CORRUPT  = 29, /**< The message header was corrupt */
    AJ_ERR_RESTART_APP  = 30, /**< The application must cleanup and restart */
    AJ_ERR_INTERRUPTED  = 31, /**< An I/O operation (READ) was interrupted */
    AJ_ERR_REJECTED     = 32, /**< The connection was rejected */
    AJ_ERR_RANGE        = 33, /**< Value provided was out of range */
    AJ_ERR_ACCESS_ROUTING_NODE = 34, /**< Access defined by routing node */
    AJ_ERR_KEY_EXPIRED  = 35, /**< The key has expired */
    AJ_ERR_SPI_NO_SPACE = 36, /**< Out of space error */
    AJ_ERR_SPI_READ     = 37, /**< Read error */
    AJ_ERR_SPI_WRITE    = 38, /**< Write error */
    AJ_ERR_OLD_VERSION  = 39, /**< Router you connected to is old and unsupported */
    AJ_ERR_NVRAM_READ   = 40, /**< Error while reading from NVRAM */
    AJ_ERR_NVRAM_WRITE  = 41, /**< Error while writing to NVRAM */
    AJ_ERR_WOULD_BLOCK  = 42, /**< Last operation would block */
    AJ_ERR_ARDP_DISCONNECTED            = 43, /**< Local ARDP disconnect */
    AJ_ERR_ARDP_DISCONNECTING           = 44, /**< ARDP waiting for Send queue to drain before complete disconnect */
    AJ_ERR_ARDP_REMOTE_CONNECTION_RESET = 45, /**< Remote ARDP disconnect */
    AJ_ERR_ARDP_PROBE_TIMEOUT           = 46, /**< ARDP connection timeout */
    AJ_ERR_ARDP_BACKPRESSURE            = 47, /**< The Send queue is full */
    AJ_ERR_ARDP_SEND_EXPIRED            = 48, /**< The outgoing message has expired */
    AJ_ERR_ARDP_RECV_EXPIRED            = 49, /**< The incoming message has expired */
    AJ_ERR_ARDP_VERSION_NOT_SUPPORTED   = 50, /**< Error to indicate ARDP protocol mismatch */
    AJ_ERR_SECURITY_DIGEST_MISMATCH       = 51, /**< Security error for digest mismatch */
    AJ_ERR_SECURITY_INVALID_CERTIFICATE   = 52, /**< Security error for invalid certificate */
    AJ_ERR_SECURITY_DUPLICATE_CERTIFICATE = 53, /**< Security error for duplicate certificate */
    AJ_ERR_SECURITY_POLICY_NOT_NEWER      = 54, /**< Security error for invalid policy update */
    AJ_ERR_SECURITY_CERTIFICATE_NOT_FOUND = 55, /**< Security error for certificate not found */
    /*
     * REMINDER: Update AJ_StatusText in aj_debug.c if adding a new status code.
     */
    AJ_STATUS_LAST      = 56  /**< The last error status code */

} AJ_Status;

/**
 * @}
 */
#endif
