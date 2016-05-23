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

#ifndef SampleContentServiceClient_H
#define SampleContentServiceClient_H

#include <alljoyn/BusListener.h>
#include <alljoyn/about/AnnounceHandler.h>
#include <alljoyn/BusAttachment.h>

#include <list>

namespace mdf {

class ContentBusListenerClient;
class ContentSessionListenerClient;
class ContentSourceClient;

class SampleContentServiceClient : public ajn::BusListener, public ajn::services::AnnounceHandler {

  public:

    SampleContentServiceClient();

    virtual ~SampleContentServiceClient();

    QStatus Init();

    QStatus RunExamples();

  public:

    /*
     * @function ContentSourceAdded
     * @description called when a new content source has been added
     * @param contentSource a reference to the content source that was added
     */
//    virtual void ContentSourceAdded(MdfContentSource& contentSource);

    /*
     * @function ContentSourceLost
     * @description called when a new content source has been removed
     * @param contentSource a reference to the content source that was removed
     */
    // virtual void ContentSourceLost(mdf::MdfContentSource& contentSource);

  private:
    ajn::BusAttachment* CreateBusAttachment();
//    QStatus CreateInterface(ajn::BusAttachment* busAttachment);
    QStatus WaitForJoinSessionCompletion();

    void Announce(uint16_t version, uint16_t port, const char* busName, const ObjectDescriptions& objectDescs, const AboutData& aboutData);

  private:

    ajn::SessionPort m_ClientSessionPort;
    ajn::BusAttachment* m_BusAttachment;
//    ajn::SessionOpts* m_sessionOpts;
    ajn::SessionId m_ClientSessionId;
//    ContentAnnounceHandlerClient* m_ContentAnnounceHandlerClient;

    ContentBusListenerClient* m_ContentBusListenerClient;
    ContentSessionListenerClient* m_ContentSessionListenerClient;
    std::list<ContentSourceClient*> m_ContentSourceClientList;
};

} //mdf

#endif /* SampleContentServiceClient_H */
