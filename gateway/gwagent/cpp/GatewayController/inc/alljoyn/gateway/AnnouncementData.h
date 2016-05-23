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

#ifndef _ANNOUNCEMENTDATA_H_
#define _ANNOUNCEMENTDATA_H_

#include <vector>
#include <alljoyn/Status.h>
#include <alljoyn/about/AboutClient.h>

namespace ajn {
namespace gwc {
/**
 * Announcement data - information coming from the announcement
 * The application should create and maintain a vector of AnnouncementData objects based on the current set of announcement in the network. See sample application for more.
 */
class AnnouncementData {
  public:
    /**
     * AnnouncementData
     * @param portNumber Announcemt port number
     * @param aboutData As was received from the announcement handler
     * @param objectDescriptions As was received from the announcement handler
     */

    AnnouncementData(uint16_t portNumber, const ajn::services::AboutClient::AboutData& aboutData, const ajn::services::AboutClient::ObjectDescriptions& objectDescriptions);

    /**
     * GetObjectDescriptions
     * @return objectDescriptions As was received from the announcement handler
     */

    const ajn::services::AboutClient::ObjectDescriptions& GetObjectDescriptions() const { return m_ObjectDescriptions; }

    /**
     * GetAboutData
     * @return aboutData As was received from the announcement handler
     */

    const ajn::services::AboutClient::AboutData& GetAboutData() const { return m_AboutData; }

    const short getPortNumber() const { return m_PortNumber; }

  private:
    ajn::services::AboutClient::AboutData m_AboutData;
    ajn::services::AboutClient::ObjectDescriptions m_ObjectDescriptions;
    short m_PortNumber;


};
}
}



#endif /* defined(_ANNOUNCEMENTDATA_H_) */
