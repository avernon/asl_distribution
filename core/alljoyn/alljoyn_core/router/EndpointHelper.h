/**
 * @file
 * Helper functions for dealing with endpoints
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
#ifndef _ENDPOINT_HELPER_H
#define _ENDPOINT_HELPER_H

#include <qcc/platform.h>

#include "BusEndpoint.h"
#include "RemoteEndpoint.h"
#include "VirtualEndpoint.h"
#include "LocalTransport.h"

namespace ajn {

inline bool operator ==(const BusEndpoint& ep, const VirtualEndpoint& vep) {
    return ep.iden(vep);
}
inline bool operator ==(const VirtualEndpoint& vep, const BusEndpoint& ep) {
    return ep.iden(vep);
}
inline bool operator !=(const BusEndpoint& ep, const VirtualEndpoint& vep) {
    return !ep.iden(vep);
}
inline bool operator !=(const VirtualEndpoint& vep, const BusEndpoint& ep) {
    return !ep.iden(vep);
}

inline bool operator ==(const BusEndpoint& ep, const RemoteEndpoint& rep)  {
    return ep.iden(rep);
}
inline bool operator ==(const RemoteEndpoint& rep, const BusEndpoint& ep)  {
    return ep.iden(rep);
}
inline bool operator !=(const BusEndpoint& ep, const RemoteEndpoint& rep)  {
    return !ep.iden(rep);
}
inline bool operator !=(const RemoteEndpoint& rep, const BusEndpoint& ep)  {
    return !ep.iden(rep);
}

inline bool operator ==(const BusEndpoint& ep, const LocalEndpoint& lep)   {
    return ep.iden(lep);
}
inline bool operator ==(const LocalEndpoint& lep, const BusEndpoint& ep)   {
    return ep.iden(lep);
}
inline bool operator !=(const BusEndpoint& ep, const LocalEndpoint& lep)   {
    return !ep.iden(lep);
}
inline bool operator !=(const LocalEndpoint& lep, const BusEndpoint& ep)   {
    return !ep.iden(lep);
}

}

#endif
