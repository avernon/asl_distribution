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

#import <Foundation/Foundation.h>
#import "AvailabilityMacros.h"

/**
 * Transports mask
 */
typedef uint16_t AJNTransportMask;

/**< no transports */
extern const AJNTransportMask kAJNTransportMaskNone;

/**< Local (same device) transport */
extern const AJNTransportMask kAJNTransportMaskLocal;

/**< Transport using TCP transport */
extern const AJNTransportMask kAJNTransportMaskTCP;

/**< Transport using UDP transport */
extern const AJNTransportMask kAJNTransportMaskUDP;

/**< Placeholder for experimental transport */
extern const AJNTransportMask kAJNTransportMaskExperimental;

/**< Transport using IP-based transport */
extern const AJNTransportMask kAJNTransportMaskIP;

/**< ANY transport */
extern const AJNTransportMask kAJNTransportMaskAny;

/*
 * QCC_DEPRECATED is a macro defined in platform.h on Linux and Windows for C++
 * that is used to mark functions, etc., as deprecated. Windows compilers use
 * the __declspec(deprecated) prefix notation and various flavors of gcc use the
 * __attribute__ ((deprecated)) postfix notation.  Objective-C on the other hand
 * uses a postfix to the initialization value for attribtues which isn't
 * compatible with the use of QCC_DEPRECATED.  Therefore we use the functionality
 * defined for the purpose directly in Objective-C: DEPRECATED_ATTRIBUTE.
 */

/**< Wireless local-area network transport */
extern const AJNTransportMask kAJNTransportMaskWLAN DEPRECATED_ATTRIBUTE;

/**< Wireless wide-area network transport */
extern const AJNTransportMask kAJNTransportMaskWWAN DEPRECATED_ATTRIBUTE;

/**< Wired local-area network transport */
extern const AJNTransportMask kAJNTransportMaskLAN DEPRECATED_ATTRIBUTE;

/**< Transport using Wi-Fi Direct transport */
extern const AJNTransportMask kAJNTransportMaskWiFiDirect DEPRECATED_ATTRIBUTE;



