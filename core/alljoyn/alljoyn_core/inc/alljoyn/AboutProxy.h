/**
 * @file
 * This contains the AboutProxy class
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

#ifndef _ALLJOYN_ABOUTPROXY_H_
#define _ALLJOYN_ABOUTPROXY_H_

#include <alljoyn/AboutObjectDescription.h>
#include <alljoyn/AboutData.h>
#include <alljoyn/BusAttachment.h>


namespace ajn {

/**
 * AboutProxy give proxy access to the org.alljoyn.About interface AboutProxy
 * class enables the user to interact with the remote About BusObject instance
 * exposing the following methods:
 * - GetObjectDescriptions
 * - GetAboutData
 * - GetVersion
 *
 */
class AboutProxy : public ProxyBusObject {
  public:
    /**
     * AboutProxy Constructor
     *
     * @param  bus reference to BusAttachment
     * @param[in] busName Unique or well-known name of remote AllJoyn bus
     * @param[in] sessionId the session received after joining AllJoyn session
     */
    AboutProxy(BusAttachment& bus, const char* busName, SessionId sessionId = 0);

    /**
     * Destruct AboutProxy
     */
    virtual ~AboutProxy();

    /**
     * Get the ObjectDescription array for specified bus name.
     *
     * @param[out] objectDesc Description of busName's remote objects.
     *
     * @return
     *   - ER_OK if successful.
     *   - ER_BUS_REPLY_IS_ERROR_MESSAGE on unknown failure.
     */
    QStatus GetObjectDescription(MsgArg& objectDesc);

    /**
     * Get the AboutData  for specified bus name.
     *
     * @param[in] languageTag is the language used to request the AboutData.
     * @param[out] data is reference of AboutData that is filled by the function
     *
     * @return
     *    - ER_OK if successful.
     *    - ER_LANGUAGE_NOT_SUPPORTED if the language specified is not supported
     *    - ER_BUS_REPLY_IS_ERROR_MESSAGE on unknown failure
     */
    QStatus GetAboutData(const char* languageTag, MsgArg& data);

    /**
     * GetVersion get the About version
     *
     * @param[out] version of the service.
     *
     * @return ER_OK on success
     */
    QStatus GetVersion(uint16_t& version);
};

}

#endif /* _ALLJOYN_ABOUTPROXY_H_ */
