/*
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
 */
#ifndef _SESSIONOPTSHOST_H
#define _SESSIONOPTSHOST_H

#include "ScriptableObject.h"
#include <alljoyn/Session.h>
#include <qcc/ManagedObj.h>

class _SessionOptsHost : public ScriptableObject {
  public:
    _SessionOptsHost(Plugin& plugin, const ajn::SessionOpts& opts);
    virtual ~_SessionOptsHost();

  private:
    const ajn::SessionOpts opts;

    bool getTraffic(NPVariant* result);
    bool getIsMultipoint(NPVariant* result);
    bool getProximity(NPVariant* result);
    bool getTransports(NPVariant* result);
};

typedef qcc::ManagedObj<_SessionOptsHost> SessionOptsHost;

#endif // _SESSIONOPTSHOST_H
