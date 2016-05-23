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

#ifndef ASYNCSESSIONJOINER_H_
#define ASYNCSESSIONJOINER_H_

#include <alljoyn/BusAttachment.h>

#if defined(QCC_OS_GROUP_WINDOWS)
/* Disabling warning C 4100. Function doesnt use all passed in parameters */
#pragma warning(push)
#pragma warning(disable: 4100)
#endif

typedef void (*SessionJoinedCallback)(qcc::String const& busName, ajn::SessionId id);

/**
 * class AsyncSessionJoiner
 */
class AsyncSessionJoiner : public ajn::BusAttachment::JoinSessionAsyncCB {

  public:
    /**
     * Constructor
     * @param name
     * @param callback
     */
    AsyncSessionJoiner(const char* name, SessionJoinedCallback callback = 0);

    /**
     * destructor
     */
    virtual ~AsyncSessionJoiner();

    /**
     * JoinSessionCB
     * @param status
     * @param id
     * @param opts
     * @param context
     */
    void JoinSessionCB(QStatus status, ajn::SessionId id, const ajn::SessionOpts& opts, void* context);

  private:

    qcc::String m_Busname;

    SessionJoinedCallback m_Callback;
};

#endif /* ASYNCSESSIONJOINER_H_ */
