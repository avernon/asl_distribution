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

#ifndef GatewayConnectorAppCapability_H_
#define GatewayConnectorAppCapability_H_

#include <qcc/String.h>
#include <vector>

namespace ajn {
namespace gw {

/**
 * Class used to define an ObjectDescription
 */
class GatewayConnectorAppCapability {

  public:

    /**
     * struct to define an Interface, its secure flag and its friendly Name
     */
    typedef struct {
        qcc::String interfaceName;           ///< The name of the interface
        qcc::String interfaceFriendlyName;   ///< The friendly name of the interface
        bool isSecured;                      ///< The secured flag of the interface
    } InterfaceDesc;

    /**
     * Constructor for the GatewayConnectorAppCapability class
     */
    GatewayConnectorAppCapability();

    /**
     * Constructor for the GatewayConnectorAppCapability class
     * @param objectPath - objectPath of the ObjectDescription
     * @param objectPathFriendly - friendly name of the objectPath of the ObjectDescription
     * @param isPrefix - is the objectPath a Prefix
     * @param interfaces - interfaces of the ObjectDescription
     */
    GatewayConnectorAppCapability(qcc::String const& objectPath, qcc::String const& objectPathFriendly, bool isPrefix,
                                  std::vector<InterfaceDesc> const& interfaces);

    /**
     * Destructor of the GatewayConnectorAppCapability class
     */
    virtual ~GatewayConnectorAppCapability();

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
     * Get the IsObjectPathPrefix flag of the ObjectDescription
     * @return true/false
     */
    bool getIsObjectPathPrefix() const;

    /**
     * Set the IsObjectPathPrefix flag of the ObjectDescription
     * @param isObjectPathPrefix - set whether the objectPath is a prefix
     */
    void setIsObjectPathPrefix(bool isObjectPathPrefix);

    /**
     * Get the interfaces of the ObjectDescription
     * @return interfaces vector
     */
    const std::vector<InterfaceDesc>& getInterfaces() const;

    /**
     * Set the interfaces of the ObjectDescription
     * @param interfaces
     */
    void setInterfaces(const std::vector<InterfaceDesc>& interfaces);

    /**
     * Get the ObjectPath FriendlyName of the ObjectDescription
     * @return objectPath
     */
    const qcc::String& getObjectPathFriendlyName() const;

    /**
     * Set the ObjectPath Friendly Name of the ObjectDescription
     * @param objectPathFriendlyName - set the objectPathFriendlyName
     */
    void setObjectPathFriendlyName(const qcc::String& objectPathFriendlyName);

  private:

    /**
     * The ObjectPath of the ObjectDescription
     */
    qcc::String m_ObjectPath;

    /**
     * The ObjectPath FriendlyName of the ObjectDescription
     */
    qcc::String m_ObjectPathFriendlyName;

    /**
     * Is the ObjectPath a Prefix
     */
    bool m_IsObjectPathPrefix;

    /**
     * The Interfaces of the ObjectDescription
     */
    std::vector<InterfaceDesc> m_Interfaces;
};

} /* namespace gw */
} /* namespace ajn */

#endif /* GatewayConnectorAppCapability_H_ */
