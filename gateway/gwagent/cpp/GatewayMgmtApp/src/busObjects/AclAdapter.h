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

#ifndef ACLADAPTER_H_
#define ACLADAPTER_H_

#include <alljoyn/about/AnnounceHandler.h>
#include <alljoyn/gateway/GatewayAclRules.h>
#include <alljoyn/gateway/GatewayAcl.h>

namespace ajn {
namespace gw {

/**
 * AclAdapter class. Used to marshal and unmarshal Acls
 */
class AclAdapter {

  public:

    /**
     * Constructor for AclAdapter
     */
    AclAdapter();

    /**
     * Destructor for AclAdapter
     */
    virtual ~AclAdapter();

    /**
     * UnmarshalAcl - static function to unmarshal an acl
     * @param msg - message to unmarshal
     * @param aclName - the aclName of the Acl
     * @param aclRules - the rules of the Acl
     * @param metadata - the metadata of the Acl
     * @param customMetadata - the customMetadata of the Acl
     * @return status - success/failure
     */
    static QStatus unmarshalAcl(Message& msg, qcc::String* aclName, GatewayAclRules* aclRules, std::map<qcc::String, qcc::String>* metadata,
                                std::map<qcc::String, qcc::String>* customMetadata);

    /**
     * Unmarshal an ObjectDescription from the message
     * @param objDescArgs - the msgArgArray containing the objectDescription
     * @param numObjDescs - the number of objectDescriptions to unmarshal
     * @param objectDesciptions - the objectDescriptions to fill
     * @return
     */
    static QStatus unmarshalObjectDesciptions(MsgArg* objDescArgs, size_t numObjDescs, GatewayRuleObjectDescriptions& objectDesciptions);

    /**
     * Unmarshal the metadata from the message
     * @param metadataArg - the arg containing the metadata
     * @param metadata - the metadata map to fill
     * @return status
     */
    static QStatus unmarshalMetadata(const MsgArg* metadataArg, std::map<qcc::String, qcc::String>* metadata);

    /**
     * MarshalAcl - static function to marshal an acl
     * @param acl - the acl to marshal
     * @param msgArg - the messageArg to put it into
     * @return status - success/failure
     */
    static QStatus marshalAcl(GatewayAcl* acl, ajn::MsgArg* msgArg);

    /**
     * MarshalMergedAcl - marshal a combination of all the active acls
     * @param acls - array of acls to possibly marshal
     * @param msgArg - msgArg to fill
     * @return status - success/failure
     */
    static QStatus marshalMergedAcl(std::map<qcc::String, GatewayAcl*> const& acls, ajn::MsgArg* msgArg);

    /**
     * MarshalObjectDescriptions - a static function to marshal objectDescriptions
     * @param objects - the objects to marshal
     * @param objectsArray - the array to marshal it into
     * @param objectsIndx - the index in the array to start marshaling into
     * @return status - success/failure
     */
    static QStatus marshalObjectDesciptions(const GatewayRuleObjectDescriptions& objects, MsgArg* objectsArray, size_t* objectsIndx);

    /**
     * marshalMetadata - static function to Marshal the Metadata Array
     * @param metadata - the metadata to marshal
     * @param metadataArray - the array to marshal it into
     * @param metadataIndx - the index in the array to start marshaling into
     * @return status - success/failure
     */
    static QStatus marshalMetadata(const std::map<qcc::String, qcc::String>& metadata, MsgArg* metadataArray, size_t* metadataIndx);
};

} /* namespace gw */
} /* namespace ajn */
#endif /* ACLADAPTER_H_ */

