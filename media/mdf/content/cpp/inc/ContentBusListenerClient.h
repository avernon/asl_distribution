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

#ifndef CONTENTBUSLISTENER_CLIENT_H_
#define CONTENTBUSLISTENER_CLIENT_H_

#include <alljoyn/BusListener.h>
#include <alljoyn/BusAttachment.h>

using namespace ajn;

namespace mdf {

class ContentBusListenerClient : public BusListener {
  public:

    /**
     * Constructor of ContentBusListener
     * @param bus - used to set a session Listener
     * @param daemonDisconnectCB - used to set a callback for when the daemon is disconnected
     */
    ContentBusListenerClient(BusAttachment* busAttachment, SessionListener* sessionListener, SessionPort sessionPort, SessionId sessionId);

    /**
     * Destructor of ContentBusListener
     */
    virtual ~ContentBusListenerClient();

    virtual void FoundAdvertisedName(const char* name, TransportMask transport, const char* namePrefix);


    virtual void NameOwnerChanged(const char* busName, const char* previousOwner, const char* newOwner);

    bool FoundAdvertisedName();

  private:

    SessionId m_SessionId;
    SessionPort m_SessionPort;
    bool m_FoundAdvertisedName;
    BusAttachment* m_BusAttachment;
    SessionListener* m_SessionListner;
};

} /* namespace mdf */

#endif /* CONTENTBUSLISTENER_CLIENT_H_ */
