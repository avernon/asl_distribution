/**
 * @file
 * MessageReceiver responsible for receiving the Announce signal from the org.alljoyn.About interface
 */
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

#ifndef ANNOUNCELISTENER_H_
#define ANNOUNCELISTENER_H_

#include <map>
#include <vector>
#include <alljoyn/BusAttachment.h>

namespace ajn {
namespace services {

/**
 * AnnounceHandler is a helper class used by an AllJoyn IoE client application to receive AboutService signal notification.
 * The user of the class need to implement virtual void Announce(...) function
 *
 * @deprecated The AnnounceHandler class has been deprecated please see the
 * AboutListener class for similar functionality as the AnnounceHandler class.
 */

class AnnounceHandler : public ajn::MessageReceiver {

    friend class AnnouncementRegistrar;
  public:
    /**
     * map of AboutData using qcc::String as key and ajn::MsgArg as value.
     */
    typedef std::map<qcc::String, ajn::MsgArg> AboutData;

    /**
     * map of ObjectDescriptions using qcc::String as key std::vector<qcc::String>   as value, describing interfaces
     */
    typedef std::map<qcc::String, std::vector<qcc::String> > ObjectDescriptions;

    /**
     * Construct an AnnounceHandler.
     *
     * @deprecated The AnnounceHandler class has been deprecated please see the
     * AboutListener class.
     */
    QCC_DEPRECATED(AnnounceHandler());

    /**
     * Destruct AnnounceHandler
     *
     * @deprecated The AnnounceHandler class has been deprecated please see the
     * AboutListener class.
     */
    QCC_DEPRECATED(~AnnounceHandler());

    /**
     * @deprecated The AnnounceHandler::Announce callback function has been
     * deprecated please see the AboutListener::Announced callback function.
     *
     * @param[in] version of the AboutService.
     * @param[in] port used by the AboutService
     * @param[in] busName unique bus name of the service
     * @param[in] objectDescs map of ObjectDescriptions using qcc::String as key std::vector<qcc::String>   as value, describing interfaces
     * @param[in] aboutData map of AboutData using qcc::String as key and ajn::MsgArg as value
     */
    QCC_DEPRECATED(virtual void Announce(uint16_t version, uint16_t port, const char* busName, const ObjectDescriptions &objectDescs,
                                         const AboutData &aboutData)) = 0;

};
inline AnnounceHandler::~AnnounceHandler() {
}

}
}

#endif /* ANNOUNCELISTENER_H_ */
