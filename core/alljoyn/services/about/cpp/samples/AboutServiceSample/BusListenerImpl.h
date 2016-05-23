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

#ifndef BUSLISTENERIMPL_H_
#define BUSLISTENERIMPL_H_

#include <alljoyn/BusListener.h>
#include <alljoyn/SessionPortListener.h>

class BusListenerImpl : public ajn::BusListener, public ajn::SessionPortListener {

  public:

    /**
     * Constructor of CommonBusListener
     */
    BusListenerImpl();

    /**
     * Constructor of CommonBusListener
     * @param sessionPort - port of listener
     */
    BusListenerImpl(ajn::SessionPort sessionPort);

    /**
     * Destructor of CommonBusListener
     */
    ~BusListenerImpl();

    /**
     * AcceptSessionJoiner - Receive request to join session and decide whether to accept it or not
     * @param sessionPort - the port of the request
     * @param joiner - the name of the joiner
     * @param opts - the session options
     * @return true/false
     */
    bool AcceptSessionJoiner(ajn::SessionPort sessionPort, const char* joiner, const ajn::SessionOpts& opts);

    /**
     * Set the Value of the SessionPort associated with this SessionPortListener
     * @param sessionPort
     */
    void setSessionPort(ajn::SessionPort sessionPort);

    /**
     * Get the SessionPort of the listener
     * @return
     */
    ajn::SessionPort getSessionPort();

  private:

    /**
     * The port used as part of the join session request
     */
    ajn::SessionPort m_SessionPort;
};

#endif /* BUSLISTENERIMPL_H_ */
