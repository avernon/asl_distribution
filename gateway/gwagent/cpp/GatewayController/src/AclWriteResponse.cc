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

#include <alljoyn/gateway/AclWriteResponse.h>


namespace ajn {
namespace gwc {

AclWriteResponse::AclWriteResponse(const qcc::String& id, AclResponseCode code, AclRules*invalidRules, const qcc::String& objPath) : m_AclId(id), m_AclCode(code), m_ObjectPath(objPath), m_InvalidRules(invalidRules)
{
}

AclWriteResponse::~AclWriteResponse()
{

}
const qcc::String& AclWriteResponse::getAclId() {
    return m_AclId;
}



AclResponseCode AclWriteResponse::getResponseCode() {
    return m_AclCode;
}


AclRules* AclWriteResponse::getInvalidRules() {
    return m_InvalidRules;
}

const qcc::String& AclWriteResponse::getObjectPath()
{
    return m_ObjectPath;
}

QStatus AclWriteResponse::release() {
    if (m_InvalidRules) {
        m_InvalidRules->release();
        delete m_InvalidRules;
        m_InvalidRules = NULL;
    }
    return ER_OK;
}
}
}
