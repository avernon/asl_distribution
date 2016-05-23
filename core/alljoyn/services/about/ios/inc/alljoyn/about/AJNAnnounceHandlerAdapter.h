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

#ifndef AJNAnnounceHandlerAdapter_H
#define AJNAnnounceHandlerAdapter_H

#import "AnnounceHandler.h"
#import "AJNAnnouncementListener.h"

/**
 AnnounceHandlerAdapter enable bind the C++ AnnounceHandler API with an objective-c announcement listener
 */
class AJNAnnounceHandlerAdapter : public ajn::services::AnnounceHandler {
public:
    // Handle to the objective-c announcement listener
    id<AJNAnnouncementListener> AJNAnnouncementListener;
    
    /**
     Constructor
     */
    AJNAnnounceHandlerAdapter(id<AJNAnnouncementListener> announcementListener);
    
    /**
     Destructor
     */
    ~AJNAnnounceHandlerAdapter();
    
    /**
     Called when a new announcement is received.
     @param version The version of the AboutService.
     @param port The port used by the AboutService.
     @param busName Unique or well-known name of AllJoyn bus.
     @param objectDescs Map of ObjectDescriptions using qcc::String as key std::vector<qcc::String>   as value, describing interfaces
     @param aboutData Map of AboutData using qcc::String as key and ajn::MsgArg as value
     */
    void Announce(uint16_t version, uint16_t port, const char* busName, const ObjectDescriptions& objectDescs, const AboutData& aboutData);
    
};
#endif