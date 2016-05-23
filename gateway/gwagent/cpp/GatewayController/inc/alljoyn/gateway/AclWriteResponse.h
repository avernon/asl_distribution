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

#ifndef AclWriteResponse_H
#define AclWriteResponse_H
#include <qcc/String.h>
#include <alljoyn/gateway/Enums.h>
#include <alljoyn/gateway/AclRules.h>

namespace ajn {
namespace gwc {
class AclWriteResponse {

  public:
    /**
     * Constructor
     * @param id ACL id
     * @param code {@link AclResponseCode}
     * @param invalidRules {@link AclRules}
     * @param objPath Object path
     */
    AclWriteResponse(const qcc::String& id, AclResponseCode code, AclRules*invalidRules, const qcc::String& objPath);


    /**
     * Destructor
     */
    virtual ~AclWriteResponse();

    /**
     * @return The id of the ACL that the write operation was referred to
     */
    const qcc::String& getAclId();


    /**
     * @return {@link AclResponseCode} of the ACL write action
     */
    AclResponseCode getResponseCode();

    /**
     * @return {@link AclRules} with the rules that don't comply with the {@link ConnectorCapabilities}
     */
    AclRules* getInvalidRules();

    /**
     * @return {@link Acl} object path
     */
    const qcc::String& getObjectPath();

    /**
     * release allocations and empty object. must be called before deletion of object.
     * @return {@link QStatus}
     */
    QStatus release();
  private:
    /**
     * Acl id
     */
    qcc::String m_AclId;

    /**
     * Response code
     */
    AclResponseCode m_AclCode;

    /**
     * ACL object path
     */
    qcc::String m_ObjectPath;

    /**
     * The rules that don't comply with the {@link ConnectorCapabilities}
     */
    AclRules*m_InvalidRules;

};
}
}
#endif /* defined(AclWriteResponse_H) */
