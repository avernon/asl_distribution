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

#ifndef GATEWAY_MERGED_ACL_H_
#define GATEWAY_MERGED_ACL_H_

#include <alljoyn/Message.h>

#include <list>

namespace ajn {
namespace gw {

static const uint16_t UUID_LENGTH = 16;

/**
 * Class that contains the MergedAcl information
 */
class GatewayMergedAcl {
  public:

    /**
     * Function to unmarshal a message and retrieve MergedAcl data
     * @param msg - msg to unmarshal
     * @return status - success/failure
     */
    QStatus unmarshal(Message& msg);

    /**
     * ObjectDescription structure
     */
    struct ObjectDescription {

        /**
         * the objectPath of the object
         */
        qcc::String objectPath;

        /**
         * Boolean that dictates whether the ObjectPath is a prefix
         */
        bool isPrefix;

        /**
         * The interfaces of the Object
         */
        std::list<qcc::String> interfaces;
    };

    /**
     * Struct representing a Remoted App
     */
    struct RemotedApp {

        /**
         * The deviceId of the App
         */
        qcc::String deviceId;

        /**
         * The AppId of the App
         */
        uint8_t appId[UUID_LENGTH];

        /**
         * The objectDescriptions of the App
         */
        std::list<ObjectDescription> objectDescs;
    };

    /**
     * The exposed Services of the Acls
     */
    std::list<ObjectDescription> m_ExposedServices;

    /**
     * The remoted Apps of the Acls
     */
    std::list<RemotedApp> m_RemotedApps;

  private:

    /**
     * private function used to unmarshal ObjectDescriptions
     * @param objDescArgs - msgArg to unmarshal
     * @param numObjDescs - number of objectDescriptions
     * @param dest - destination to unmarshal them into
     * @return status - sucess/failure
     */
    QStatus unmarshalObjectDescriptions(MsgArg* objDescArgs, size_t numObjDescs, std::list<ObjectDescription>& dest);
};

} //namespace gw
} //namespace ajn

#endif
