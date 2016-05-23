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

#ifndef RuleObjectDescription_H
#define RuleObjectDescription_H

#include <set>
#include <vector>
#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/MsgArg.h>

namespace ajn {
namespace gwc {

class ConnectorCapabilities;

class RuleInterface {
  public:

    /**
     * Constructor
     * @param name AllJoyn name of the interface
     * @param friendlyName The interface friendly name
     * @param isSecured Whether the interface is secured
     */
    RuleInterface(const qcc::String& name, const qcc::String& friendlyName, bool isSecured);

    /**
     * Copy Constructor
     * @param other Object to copy from
     */
    RuleInterface(const RuleInterface& other) { m_Name = other.m_Name; m_FriendlyName = other.m_FriendlyName; m_IsSecured = other.m_IsSecured; }

    /**
     * Destructor
     */
    virtual ~RuleInterface() { }

    /**
     * Returns a name of the interface.
     * @return interface name
     */
    const qcc::String& getName() const;

    /**
     * Returns a friendly name of the interface.
     * The friendly name may be presented to the end user.
     * @return Interface friendly name
     */
    const qcc::String& getFriendlyName() const;

    /**
     * @return TRUE if the interface is secured
     */
    bool isSecured() const;

    /**
     * operator less than
     * @param to check if the object is less than this param
     * @return TRUE if the object is less than 'to'
     */
    bool operator<(const RuleInterface to) const;


  private:
    /**
     * The interface name
     */
    qcc::String m_Name;

    /**
     * The interface friendly name
     */
    qcc::String m_FriendlyName;

    /**
     * TRUE of the interface is secured
     */
    bool m_IsSecured;

};

class RuleObjectPath {
  public:

    /**
     * Constructor
     * @param objectPath AllJoyn object identification
     * @param friendlyName The friendly name of the object path. This name may be presented
     * @param isPrefix TRUE if the object path is a prefix for the full object path
     * @param isPrefixAllowed TRUE if the object path is allowed to be a prefix according
     * to the end user.
     */
    RuleObjectPath(const qcc::String& objectPath, const qcc::String& friendlyName, bool isPrefix, bool isPrefixAllowed);

    /**
     * Destructor
     */
    virtual ~RuleObjectPath();

    /**
     * AllJoyn object identification
     * @return The value of the object path
     */
    const qcc::String& getPath() const;

    /**
     * Returns the friendly name  of the object path.
     * This name may be presented to the end user.
     * @return Object path friendly name
     */
    const qcc::String& getFriendlyName();

    /**
     * @return Returns whether this object path is a prefix
     */
    bool isPrefix() const;

    /**
     * @param isPrefix set the prefix flag to isPrefix
     */
    void setPrefix(bool isPrefix);

    /**
     * @return TRUE if the object path is allowed to be a prefix according
     * to the {@link ConnectorApp} manifest
     */
    bool isPrefixAllowed() const;

    /**
     * @param isPrefixAllowed Set whether the object path is allowed to be a prefix according
     * to the {@link ConnectorApp} manifest
     */
    void setPrefixAllowed(bool isPrefixAllowed);

    /**
     * operator less than
     * @param other check if the object is less than this param
     * @return TRUE if the object is less than 'other'
     */

    bool operator<(const RuleObjectPath& other) const {
        if (m_IsPrefix != other.m_IsPrefix) {
            return true;
        }


        return m_ObjectPath < other.m_ObjectPath;
    }

  private:
    /**
     * AllJoyn object identification
     */
    qcc::String m_ObjectPath;

    /**
     * The friendly name of the object path. This name may be presented
     * to the end user.
     */
    qcc::String m_FriendlyName;

    /**
     * Gets TRUE if the object path is a prefix for the full object path
     */
    bool m_IsPrefix;

    /**
     * Gets TRUE if the object path is allowed by the manifest to be a prefix
     */
    bool m_isPrefixAllowed;
};

class RuleObjectDescription {

  public:


    /**
     * Constructor
     * @param objectPath AllJoyn object identification
     * @param interfaces Set of the interfaces related to the given object path
     */
    RuleObjectDescription(const RuleObjectPath& objectPath, std::set<RuleInterface> interfaces);

    /**
     * Constructor
     * @param objectPath AllJoyn object identification
     * @param interfaces Set of the interfaces related to the given object path
     * @param configured  Set TRUE to permit this {@link RuleObjectDescription} object path and interfaces
     * to be remoted by the Connector App
     */
    RuleObjectDescription(const RuleObjectPath& objectPath, std::set<RuleInterface> interfaces, bool isConfigured);

    /**
     * Destructor
     */
    virtual ~RuleObjectDescription();

    /**
     * The object path supported by the Service Provider Application manifest
     * @return Object path
     */
    RuleObjectPath* getObjectPath() const;

    /**
     * The interfaces supported by the Service Provider Application manifest
     * @return Set of the {@link RuleInterface} objects
     */
    const std::set<RuleInterface>*getInterfaces() const;

    /**
     * The flag has TRUE if this {@link RuleObjectDescription} is configured
     * to permit the object path and interfaces to be remoted by the Connector App
     * @return configured state
     */
    bool isConfigured() const;

    /**
     * Set TRUE to permit this {@link RuleObjectDescription} object path and interfaces
     * to be remoted by the Connector App
     * @param configured
     */
    void setConfigured(bool configured);

    /**
     * release allocations and empty object. must be called before deletion of object.
     * @return {@link QStatus}
     */
    QStatus release();

  private:


    /**
     * The flag has TRUE if this {@link RuleObjectDescription} is configured
     * to permit the object path and interfaces to be remoted by the Connector App
     */
    bool m_IsConfigured;

    /**
     * The object path supported by the Service Provider Application manifest
     */
    RuleObjectPath*m_ObjectPath;

    /**
     * The interfaces supported by the Service Provider Application manifest
     */
    std::set<RuleInterface> m_Interfaces;
};
}
}
#endif /* defined(RuleObjectDescription_H) */
