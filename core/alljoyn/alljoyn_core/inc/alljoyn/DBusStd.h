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
#ifndef _ALLJOYN_DBUSSTD_H
#define _ALLJOYN_DBUSSTD_H

/**
 * @file
 * This file provides definitions for standard DBus interfaces
 *
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

#include <alljoyn/DBusStdDefines.h>
#include <alljoyn/Status.h>

namespace ajn {
class BusAttachment;

namespace org {
namespace freedesktop {

/** Interface Definitions for org.freedesktop.DBus */
namespace DBus {
extern const char* ObjectPath;                         /**< Object path */
extern const char* InterfaceName;                      /**< Name of the interface */
extern const char* WellKnownName;                      /**< The well known name */

extern const char* AnnotateNoReply;                    /**< Annotation for reply to a method call */
extern const char* AnnotateDeprecated;                 /**< Annotation for marking entry as depreciated  */
extern const char* AnnotateEmitsChanged;               /**< Annotation for when a property is modified {true,false,invalidates} */

/** Definitions for org.freedesktop.DBus.Properties */
namespace Properties {
extern const char* InterfaceName;                          /**< Name of the interface   */
}

/** Definitions for org.freedesktop.DBus.Peer */
namespace Peer {
extern const char* InterfaceName;                          /**< Name of the interface   */
}

/** Definitions for org.freedesktop.DBus.Introspectable */
namespace Introspectable {
extern const char* InterfaceName;                         /**< Name of the interface   */
extern const char* IntrospectDocType;                     /**< Type of introspection document */
}

/** Create the org.freedesktop.DBus interfaces and sub-interfaces */
QStatus CreateInterfaces(BusAttachment& bus);

}
}
}
}
#endif

#endif
