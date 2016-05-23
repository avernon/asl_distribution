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

#ifndef ACLBUSOBJECT_H_
#define ACLBUSOBJECT_H_

#include <alljoyn/BusAttachment.h>
#include <alljoyn/BusObject.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/gateway/GatewayAcl.h>

namespace ajn {
namespace gw {

/**
 * AclBusObject - BusObject for Acls
 */
class AclBusObject : public BusObject  {
  public:

    /**
     * Constructor for GatewayAclBusObject class
     * @param bus - the bus to create the interface
     * @param objectPath - objectPath of BusObject
     * @param status - success/failure
     */
    AclBusObject(BusAttachment* bus, GatewayAcl* acl, qcc::String const& objectPath, QStatus* status);

    /**
     * Destructor for the BusObject
     */
    virtual ~AclBusObject();

    /**
     * Callback for the ActivateAcl method
     * @param member - the member called
     * @param msg - the message of the method
     */
    void ActivateAcl(const InterfaceDescription::Member* member, Message& msg);

    /**
     * Callback for the GetAcl method
     * @param member - the member called
     * @param msg - the message of the method
     */
    void GetAcl(const InterfaceDescription::Member* member, Message& msg);

    /**
     * Callback for the GetAclStatus method
     * @param member - the member called
     * @param msg - the message of the method
     */
    void GetAclStatus(const InterfaceDescription::Member* member, Message& msg);

    /**
     * Callback for the UpdateAcl method
     * @param member - the member called
     * @param msg - the message of the method
     */
    void UpdateAcl(const InterfaceDescription::Member* member, Message& msg);

    /**
     * Callback for the UpdateMetadata method
     * @param member - the member called
     * @param msg - the message of the method
     */
    void UpdateMetadata(const InterfaceDescription::Member* member, Message& msg);

    /**
     * Callback for the UpdateCustomMetadata method
     * @param member - the member called
     * @param msg - the message of the method
     */
    void UpdateCustomMetadata(const InterfaceDescription::Member* member, Message& msg);

    /**
     * Callback for the DeactivateAcl method
     * @param member - the member called
     * @param msg - the message of the method
     */
    void DeactivateAcl(const InterfaceDescription::Member* member, Message& msg);

    /**
     * Get Property
     * @param interfaceName - name of the interface
     * @param propName - name of the property
     * @param val - msgArg to fill
     * @return status - success/failure
     */
    QStatus Get(const char* interfaceName, const char* propName, MsgArg& val);

    /**
     * Set Property
     * @param interfaceName - name of the interface
     * @param propName - name of the property
     * @param val - msgArg to fill
     * @return status - success/failure
     */
    QStatus Set(const char* interfaceName, const char* propName, MsgArg& val);

  private:

    /**
     * The Acl that contains this BusObject
     */
    GatewayAcl* m_Acl;

    /**
     * The ObjectPath of this ObjectPath
     */
    qcc::String m_ObjectPath;

};

} /* namespace gw */
} /* namespace ajn */

#endif /* ACLBUSOBJECT_H_ */
