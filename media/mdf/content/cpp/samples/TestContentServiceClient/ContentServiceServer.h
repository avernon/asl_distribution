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

#ifndef CONTENTSERVICESERVER_H_
#define CONTENTSERVICESERVER_H_

#include <stdint.h>
#include <map>
#include <vector>

#include <alljoyn/BusAttachment.h>


using namespace ajn;

namespace mdf {

class ContentServiceSessionHandler;
class ContentAnnounceHandlerServer;
class ContentSourceListener;


class ContentServiceServer {

  public:

    /*
     * @function GetInstance
     * @description singleton constructor method. Only one instance of this should ever be running per machine. This returns the current
     * instance or creates a new one if none exists
     * @return a pointer to the ContentServiceServer instance
     */
    static ContentServiceServer* GetInstance();

    /*
     * @function ~ContentService
     * @description destructor
     */
    ~ContentServiceServer();

    /*
     * @function Init
     * @description this should be called only once on the instance of the server. Calling it more than once will result in an error being thrown
     * A set of parameters are passed to the server containing all information that the server needs
     * @param contentServerParams the parameters the server needs to run
     */
    QStatus Init(ajn::BusAttachment* busAttachment);

    /*
     * @function Shutdown
     * @description Cleanup and get ready for shutdown.
     */
    void Shutdown();

    /*
     * @function GetServerVersion
     * @description Gets the server version
     * @return version
     */
    uint16_t GetServerVersion() const;

    /*
     * @function GetContentServiceSessionHandler
     * @description returns a pointer to the ContentServiceSessionHandler
     * @return ContentServiceSessionHandler*
     */
    ContentServiceSessionHandler* GetContentServiceSessionHandler();

  private:

    //SessionListener
    void SessionLost(SessionId sessionId, ajn::SessionListener::SessionLostReason reason);


  private:

    ContentServiceServer();  // Private so that it can not be called because this is a singleton
    ContentServiceServer(ContentServiceServer const&); // copy constructor is private not be called because this is a singleton
    ContentServiceServer& operator=(ContentServiceServer const&); // assignment operator is private not be called because this is a singleton

    static ContentServiceServer* s_Instance;

    std::vector<const ContentSourceListener*> m_ContentSourceListeners;     //vector of references to contentsourcelisteners

    ContentServiceSessionHandler* m_ContentServerSessionHandler;
    ContentAnnounceHandlerServer* m_ContentAnnounceHandlerServer;

};

} //namespace ajn


#endif /* CONTENTSERVICESERVER_H_ */
