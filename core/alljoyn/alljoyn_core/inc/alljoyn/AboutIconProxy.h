/**
 * @file
 * Implementation of a ProxyBusObject used to interact with a org.alljoyn.Icon
 * interface
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
#ifndef _ALLJOYN_ABOUTICONPROXY_H
#define _ALLJOYN_ABOUTICONPROXY_H

#include <alljoyn/BusAttachment.h>
#include <alljoyn/AboutIcon.h>

namespace ajn {
/**
 * AboutIconProxy enables the user of the class to interact with the remote
 * AboutIcon BusObject.
 */
class AboutIconProxy : public ProxyBusObject {
  public:
    /**
     * Construct an AboutIconProxy Object.
     *
     * @param bus reference to BusAttachment
     * @param[in] busName Unique or well-known name of an AllJoyn bus you have joined
     * @param[in] sessionId the session received after joining an AllJoyn session
     */
    AboutIconProxy(BusAttachment& bus, const char* busName, SessionId sessionId = 0);

    /**
     * Destruct the AboutIconProxy Object.
     */
    virtual ~AboutIconProxy() {
    }

    /**
     * This method makes multiple ProxyBusObject method calls to fill in the
     * content of the AboutIcon. Its possible for any of the method calls to
     * fail causing this member function to return an error status.
     *
     * @param[out] icon AboutIcon class that holds icon content
     * @return
     *  - #ER_OK if successful
     *  - an error status indicating failure to get the icon content
     */
    QStatus GetIcon(AboutIcon& icon);

    /**
     * @param[out] version the version of the remote AboutIcon BusObject
     *
     * @return
     * - #ER_OK if successful
     * - an error status indicating failure
     */
    QStatus GetVersion(uint16_t& version);
};
}

#endif /* _ALLJOYN_ABOUTICONPROXY_H */
