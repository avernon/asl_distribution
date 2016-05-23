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
#ifndef _ALLJOYN_TRANPORTMASK_H
#define _ALLJOYN_TRANPORTMASK_H
/**
 * @file
 * Transport type definitions
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

#include <qcc/platform.h>

namespace ajn {

/** Bitmask of all transport types */
typedef uint16_t TransportMask;

const TransportMask TRANSPORT_NONE          = 0x0000;  /**< no transports */
const TransportMask TRANSPORT_LOCAL         = 0x0001;  /**< Local (same device) transport */
const TransportMask TRANSPORT_TCP           = 0x0004;  /**< Transport using TCP as the underlying mechanism */
const TransportMask TRANSPORT_UDP           = 0x0100;  /**< Transport using UDP as the underlying mechanism */

/**
 * A placeholder for an experimental transport that has not yet reached the
 * performance, stability or testing requirements of a commercialized transport.
 *
 * It is expected that each experimental Transport will alias this bit if
 * included in an AllJoyn release and then allocate one of the reserved mask
 * bits upon attaining commercialized status.
 *
 * For example,
 *     const TransportMask TRANSPORT_CAN_AND_STRING = TRANSPORT_EXPERIMENTAL
 */
const TransportMask TRANSPORT_EXPERIMENTAL  = 0x8000;
const TransportMask TRANSPORT_MQTT = TRANSPORT_EXPERIMENTAL;    /**< Transport using MQTT as the underlying mechanism */

/**
 * A constant indicating that any IP-based transport is acceptable.  It is left
 * up to the system to decide which of the available transports is "best."
 */
const TransportMask TRANSPORT_IP        = (TRANSPORT_TCP | TRANSPORT_UDP);

/**
 * A constant indicating that any commericalized transport is acceptable.  As
 * more transports are introduced and reach commercial quality, we expect the
 * corresponding mask bits to be added here.
 */
const TransportMask TRANSPORT_ANY       = (TRANSPORT_LOCAL | TRANSPORT_IP);

/**
 * Obsolete mask indicating that any transport as long as it is running over the
 * local wireless local area network is acceptable.
 *
 * @deprecated February 2015 for 15.04 release
 */
QCC_DEPRECATED(const TransportMask TRANSPORT_WLAN) = 0x0004;   /**< Wireless local-area network transport (same as TRANSPORT_TCP) */

/**
 * Obsolete mask indicating that any transport as long as it is running over the
 * local wireless wide area network is acceptable.
 *
 * @deprecated February 2015 for 15.04 release
 */
QCC_DEPRECATED(const TransportMask TRANSPORT_WWAN) = 0x0008;   /**< Wireless wide-area network transport */

/**
 * Obsolete mask indicating that any transport as long as it is running over the
 * (non-wireless) local area network -- Ethernet -- is acceptable.
 *
 * @deprecated February 2015 for 15.04 release
 */
QCC_DEPRECATED(const TransportMask TRANSPORT_LAN) = 0x0010;   /**< Wired local-area network transport */

/**
 * Obsolete mask indicating that the Wi-Fi Direct Transport is acceptable.
 *
 * @deprecated February 2015 for 15.04 release
 */
QCC_DEPRECATED(const TransportMask TRANSPORT_WFD) = 0x0080;   /**< Transport using Wi-Fi Direct transport (currently unused) */

}

#endif
