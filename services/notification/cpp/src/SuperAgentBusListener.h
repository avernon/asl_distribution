/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

#ifndef SUPER_AGENT_BUS_LISTENER_H_
#define SUPER_AGENT_BUS_LISTENER_H_

#include <string.h>
#include <alljoyn/BusAttachment.h>

namespace ajn {
namespace services {

/**
 * SuperAgentBusListener
 */
class SuperAgentBusListener : public BusListener {

  public:

    SuperAgentBusListener(ajn::BusAttachment* bus);

    virtual ~SuperAgentBusListener();

    void FoundAdvertisedName(const char* name, TransportMask transport, const char* namePrefix);

    void LostAdvertisedName(const char* name, TransportMask transport, const char* prefix);

    void SetBusUniqueName(const char* superAgentBusUniqueName) { m_SuperAgentBusUniqueName = superAgentBusUniqueName; }
  private:
    /**
     * BusAttachment
     */
    BusAttachment* m_Bus;
    /**
     * Super agent bus unique name
     */
    qcc::String m_SuperAgentBusUniqueName;
};
} //namespace services
} //namespace ajn

#endif /* SUPER_AGENT_BUS_LISTENER_H_ */
