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

#ifndef CONTROLPANELSESSIONHANDLER_H_
#define CONTROLPANELSESSIONHANDLER_H_

#include <alljoyn/BusAttachment.h>
#include <alljoyn/SessionListener.h>

namespace ajn {
namespace services {

class ControlPanelDevice;

/**
 * class ControlPanelSessionHandler
 */
class ControlPanelSessionHandler : public ajn::BusAttachment::JoinSessionAsyncCB, public ajn::SessionListener {
  public:

    /**
     * Constructor for ControlPanelSessionHandler
     */
    ControlPanelSessionHandler(ControlPanelDevice* device);

    /**
     * Destructor for ControlPanelSessionHandler
     */
    virtual ~ControlPanelSessionHandler();

    /**
     * SessionLost
     * @param sessionId
     */
    void SessionLost(ajn::SessionId sessionId);

    /**
     * JoinSessionCB
     * @param status
     * @param id
     * @param opts
     * @param context
     */
    void JoinSessionCB(QStatus status, ajn::SessionId id, const ajn::SessionOpts& opts, void* context);

    /**
     * getSessionId
     * @return SessionId
     */
    ajn::SessionId getSessionId() const;

  private:

    /**
     * SessionId for this Device
     */
    ajn::SessionId m_SessionId;

    /**
     * The device of this Session Handler
     */
    ControlPanelDevice* m_Device;

};

} /* namespace services */
} /* namespace ajn */

#endif /* CONTROLPANELSESSIONHANDLER_H_ */
