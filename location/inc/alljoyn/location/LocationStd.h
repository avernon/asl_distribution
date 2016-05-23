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
#ifndef _ALLJOYN_LOCATIONSTD_H
#define _ALLJOYN_LOCATIONSTD_H

/**
 * @file
 * This file provides definitions for standard Location interfaces
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

#ifdef __cplusplus

#include <qcc/platform.h>

#include <alljoyn/Status.h>

namespace ajn {

namespace org {
namespace alljoyn {

/** Interface Definitions for org.alljoyn.locationservices */
namespace locationservices {
extern const char* InterfaceName; /**< Name of the interface */
extern const char* InterfaceXml; /**< XML description of the interface */

/** Definitions for org.alljoyn.locationservices.PresenceTracker */
namespace PresenceTracker {
extern const char* InterfaceName; /**< Name of the interface */
extern const char* InterfaceXml; /**< XML description of the interface */
}

/** Definitions for org.alljoyn.locationservices.DistanceTracker */
namespace DistanceTracker {
extern const char* InterfaceName; /**< Name of the interface */
extern const char* InterfaceXml; /**< XML description of the interface */
}

/** Definitions for org.alljoyn.locationservices.GeofenceTracker */
namespace GeofenceTracker {
extern const char* InterfaceName; /**< Name of the interface */
extern const char* InterfaceXml; /**< XML description of the interface */
}

/** Definitions for org.alljoyn.locationservices.LocationTracker */
namespace LocationTracker {
extern const char* InterfaceName; /**< Name of the interface */
extern const char* InterfaceXml; /**< XML description of the interface */
}

}

}
}

}

#endif

#endif
