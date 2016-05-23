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

#ifndef GatewayRuleObjectDescription_H_
#define GatewayRuleObjectDescription_H_

#include <qcc/String.h>
#include <vector>

namespace ajn {
namespace gw {

/**
 * Class used to define an ObjectDescription
 */
class GatewayRuleObjectDescription {

  public:

    /**
     * Constructor for the GatewayRuleObjectDescription class
     */
    GatewayRuleObjectDescription();

    /**
     * Constructor for the GatewayRuleObjectDescription class
     * @param objectPath - objectPath of the ObjectDescription
     * @param isPrefix - isPrefix of the ObjectDescription
     * @param interfaces - interfaces of the ObjectDescription
     */
    GatewayRuleObjectDescription(qcc::String const& objectPath, bool isPrefix, std::vector<qcc::String> const& interfaces);

    /**
     * Destructor of the GatewayRuleObjectDescription class
     */
    virtual ~GatewayRuleObjectDescription();

    /**
     * Get the interfaces of the ObjectDescription
     * @return interfaces vector
     */
    const std::vector<qcc::String>& getInterfaces() const;

    /**
     * Set the interfaces of the ObjectDescription
     * @param interfaces
     */
    void setInterfaces(const std::vector<qcc::String>& interfaces);

    /**
     * Get the ObjectPath of the ObjectDescription
     * @return objectPath
     */
    const qcc::String& getObjectPath() const;

    /**
     * Set the ObjectPath of the ObjectDescription
     * @param objectPath
     */
    void setObjectPath(const qcc::String& objectPath);

    /**
     * Get the isPrefix boolean of the ObjectDescription
     * @return isPrefix
     */
    bool getIsPrefix() const;

    /**
     * Set the isPrefix boolean of the ObjectDescriptions
     * @param isPrefix
     */
    void setIsPrefix(bool isPrefix);

  private:

    /**
     * The ObjectPath of the ObjectDescription
     */
    qcc::String m_ObjectPath;

    /**
     * Is the ObjectPath a Prefix
     */
    bool m_IsPrefix;

    /**
     * The Interfaces of the ObjectDescription
     */
    std::vector<qcc::String> m_Interfaces;
};

} /* namespace gw */
} /* namespace ajn */

#endif /* GatewayRuleObjectDescription_H_ */
