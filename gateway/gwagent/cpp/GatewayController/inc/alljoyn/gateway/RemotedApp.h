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

#ifndef RemotedApp_H
#define RemotedApp_H

#include <vector>
#include <alljoyn/gateway/AnnouncedApp.h>
#include <alljoyn/gateway/RuleObjectDescription.h>

namespace ajn {
namespace gwc {
class RemotedApp : public AnnouncedApp {
  public:

    /**
     * Constructor - must call appropriate init
     */
    RemotedApp() { }

    /**
     * init
     * @param busUniqueName The name of the {@link BusAttachment} of the remoted application
     * @param appName The name of the application
     * @param appId The application id
     * @param deviceName The name of the device
     * @param deviceId The device id
     * @param ruleObjDescriptions Configuration of the object paths and interfaces that are
     * used by the Connector App to reach this remoted application
     * @return {@link QStatus}
     */
    QStatus init(const qcc::String& busUniqueName, const qcc::String& appName, uint8_t*appId, const qcc::String& deviceName, const qcc::String& deviceId, const std::vector<RuleObjectDescription*>& ruleObjDescriptions);

    /**
     * init
     * @param remotedAppInfo MsgArg with the information for this remoted app
     * @param ruleObjDescriptions vector with object description rules for the remoted app
     * @param internalMetadata map of the internal metadata
     * @return {@link QStatus}
     */
    QStatus init(const ajn::MsgArg*remotedAppInfo, const std::vector<RuleObjectDescription*>& ruleObjDescriptions, const std::map<qcc::String, qcc::String>& internalMetadata);

    /**
     * init
     * @param aboutData Announcement's about data object
     * @param ruleObjDescriptions vector with object description rules for the remoted app
     * @return {@link QStatus}
     */
    QStatus init(ajn::services::AboutClient::AboutData const& aboutData, const std::vector<RuleObjectDescription*>& ruleObjDescriptions);


    /**
     * init
     * @param announcedApp The {@link AnnouncedApp} to be used to build this {@link RemotedApp}
     * @param ruleObjDescriptions Configuration of the object paths and interfaces that are
     * used by the Connector App to reach this remoted application
     * @return {@link QStatus}
     */
    QStatus init(AnnouncedApp* announcedApp, const std::vector<RuleObjectDescription*>& ruleObjDescriptions);

    /**
     * Destructor
     */
    virtual ~RemotedApp();

    /**
     * Configuration of the object paths and interfaces that are
     * used by the Connector App to reach this remoted application
     * @return List of {@link RuleObjectDescription} objects
     */
    const std::vector<RuleObjectDescription*>& getRuleObjDesciptions();

    /**
     * release allocations and empty object. must be called before deletion of object.
     * @return {@link QStatus}
     */
    QStatus release();

  private:
    /**
     * Configuration of the object paths and interfaces that are
     * used by the Connector App to reach this remoted application
     */
    std::vector<RuleObjectDescription*> m_RuleObjDescriptions;

    void emptyVector();
};
}
}

#endif /* defined(RemotedApp_H) */
