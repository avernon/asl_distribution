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

#ifndef ContentSessionListener_H_
#define ContentSessionListener_H_

//#include <vector>

#include <alljoyn/SessionListener.h>

namespace mdf {

class ContentSessionListener : public ajn::SessionListener {

  public:

    /**
     * Constructor of ContentSessionListener
     * @param bus - used to set a session Listener
     * @param daemonDisconnectCB - used to set a callback for when the daemon is disconnected
     */
    ContentSessionListener();

    /**
     * Destructor of ContentSessionListener
     */
    ~ContentSessionListener();

    /**
     * Callback for when Session is lost
     * @param sessionId
     * @param reason for session lost
     */
    void SessionLost(ajn::SessionId sessionId, SessionLostReason reason);


  private:
    /**
     * The sessionIds for the port
     */
    //std::vector<ajn::SessionId> m_SessionIds;

};

} /* namespace mdf */

#endif /* ContentSessionListener_H_ */
