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

#ifndef __mdfContentService__ContentSourceClient__
#define __mdfContentService__ContentSourceClient__

#include <alljoyn/BusAttachment.h>
#include <alljoyn/BusListener.h>
#include "ContentProxyBusObject.h"

using namespace ajn;
using namespace qcc;

namespace mdf {

class ContentSourceClient : public SessionListener {
  public:

    ContentSourceClient(BusAttachment* busAttachment, String busName, SessionId sessionId, SessionPort sessionPort);
    virtual ~ContentSourceClient();

    uint16_t GetVersion();
    void SetVersion(uint16_t version);

    bool GetHasSession();

    ContentProxyBusObject* GetContentProxyBusObject();

    QStatus JoinSession();

  private:
    //SessionListener
    void SessionLost(SessionId sessionId, SessionLostReason reason);
    void SetHasSession(bool hasSession);
    SessionListener* GetSessionListener();

  private:
    uint16_t m_Version;
    SessionPort m_SessionPort;
    String m_BusName;
    SessionId m_SessionId;
    BusAttachment* m_BusAttachment;
    SessionOpts* m_SessionOpts;
    bool m_HasSession;
    ContentProxyBusObject* m_ContentProxyBusObject;

};

} //mdf
#endif /* defined(__mdfContentService__ContentSourceClient__) */
