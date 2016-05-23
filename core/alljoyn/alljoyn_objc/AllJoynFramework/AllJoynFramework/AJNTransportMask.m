////////////////////////////////////////////////////////////////////////////////
// Copyright AllSeen Alliance. All rights reserved.
//
//    Contributed by Qualcomm Connected Experiences, Inc.,
//    with authorization from the AllSeen Alliance, Inc.
//    
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//    
//        http://www.apache.org/licenses/LICENSE-2.0
//    
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//    
//    Pursuant to Section 1 of the License, the work of authorship constituting
//    a Work and any Contribution incorporated in the Work shall mean only that
//    Contributor's code submissions authored by that Contributor.  Any rights
//    granted under the License are conditioned upon acceptance of these
//    clarifications.
////////////////////////////////////////////////////////////////////////////////

#import "AJNTransportMask.h"

const AJNTransportMask kAJNTransportMaskNone         = 0x0000;   /**< no transports */
const AJNTransportMask kAJNTransportMaskLocal        = 0x0001;   /**< Local (same device) transport */
const AJNTransportMask kAJNTransportMaskTCP          = 0x0004;   /**< TCP/IP transport */
const AJNTransportMask kAJNTransportMaskUDP          = 0x0100;   /**< UDP/IP transport */
const AJNTransportMask kAJNTransportMaskExperimental = 0x8000;   /**< Placeholder for experimental transport */
const AJNTransportMask kAJNTransportMaskIP           = (kAJNTransportMaskTCP + kAJNTransportMaskUDP); /**< An IP-based transport */
const AJNTransportMask kAJNTransportMaskAny          = (kAJNTransportMaskLocal + kAJNTransportMaskIP); /**< Any non-experimental transport */

const AJNTransportMask kAJNTransportMaskWLAN         = 0x0004;   /**< Wireless local-area network transport */
const AJNTransportMask kAJNTransportMaskWWAN         = 0x0008;   /**< Wireless wide-area network transport */
const AJNTransportMask kAJNTransportMaskLAN          = 0x0010;   /**< Wired local-area network transport */
const AJNTransportMask kAJNTransportMaskWiFiDirect   = 0x0080;   /**< Transport using Wi-Fi Direct transport */
