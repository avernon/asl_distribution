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

#ifndef ABOUTCLIENTSESSIONJOINER_H_
#define ABOUTCLIENTSESSIONJOINER_H_

#include <alljoyn/about/AboutClient.h>
#include <alljoyn/BusAttachment.h>
#include "AboutClientSessionListener.h"

typedef void (*SessionJoinedCallback)(qcc::String const& busName, ajn::SessionId id);

struct SessionJoinerContext {
    qcc::String busName;
    AboutClientSessionListener* aboutClientSessionListener;

    SessionJoinerContext(qcc::String name, AboutClientSessionListener* absl) :
        busName(name), aboutClientSessionListener(absl) { }
};

class AboutClientSessionJoiner : public ajn::BusAttachment::JoinSessionAsyncCB {

  public:

    AboutClientSessionJoiner(ajn::BusAttachment& bus, const qcc::String& busName, SessionJoinedCallback callback = 0);

    virtual ~AboutClientSessionJoiner();

    void JoinSessionCB(QStatus status, ajn::SessionId id, const ajn::SessionOpts& opts, void* context);

  private:

    ajn::BusAttachment& bus;

    qcc::String m_BusName;

    SessionJoinedCallback m_Callback;
};

#endif /* ABOUTCLIENTSESSIONJOINER_H_ */
