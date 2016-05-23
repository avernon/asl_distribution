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

#ifndef ANNOUNCEHANDLERSAMPLE_H_
#define ANNOUNCEHANDLERSAMPLE_H_
#include <alljoyn/AboutListener.h>
#include <alljoyn/AboutData.h>

#if defined(QCC_OS_GROUP_WINDOWS)
/* Disabling warning C 4100. Function doesnt use all passed in parameters */
#pragma warning(push)
#pragma warning(disable: 4100)
#endif


typedef void (*BasicAnnounceHandlerCallback)(qcc::String const& busName, unsigned short port);
typedef void (*FullAnnounceHandlerCallback)(qcc::String const& busName, unsigned short version,
                                            unsigned short port, const ajn::AboutObjectDescription& objectDescription,
                                            const ajn::AboutData& aboutData);
/**
 * class AnnounceHandlerImpl
 */
class AnnounceHandlerImpl : public ajn::AboutListener {

  public:

    /**
     * Announced - announced callback
     * @param busName
     * @param version
     * @param port
     * @param objectDescriptionArg
     * @param aboutDataArg
     */
    virtual void Announced(const char* busName, uint16_t version, ajn::SessionPort port, const ajn::MsgArg& objectDescriptionArg, const ajn::MsgArg& aboutDataArg);
    /**
     * AnnounceHandlerImpl
     * @param basicCallback
     * @param fullCallback
     */
    AnnounceHandlerImpl(BasicAnnounceHandlerCallback basicCallback = 0, FullAnnounceHandlerCallback fullCallback = 0);

    /**
     * ~AnnounceHandlerImpl
     */
    ~AnnounceHandlerImpl();

  private:

    BasicAnnounceHandlerCallback m_BasicCallback;

    FullAnnounceHandlerCallback m_FullCallback;
};

#endif /* ANNOUNCEHANDLERSAMPLE_H_ */
