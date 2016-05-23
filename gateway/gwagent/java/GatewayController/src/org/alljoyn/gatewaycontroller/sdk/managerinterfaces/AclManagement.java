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

package org.alljoyn.gatewaycontroller.sdk.managerinterfaces;

import java.util.Map;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusProperty;
import org.alljoyn.bus.annotation.Secure;
import org.alljoyn.gatewaycontroller.sdk.GatewayController;

/**
 * AllJoyn interface for managing Access Control List of a Gateway Connector
 * Application
 */
@BusInterface(name = AclManagement.IFNAME)
@Secure
public interface AclManagement {

    /**
     * AllJoyn name of the interface
     */
    public static final String IFNAME = GatewayController.IFACE_PREFIX + ".AclMgmt";

    /**
     * Creating the ACL
     * 
     * @param aclName
     * @param exposedServices
     * @param remotedApps
     * @param internalMetadata
     * @param customMetadata
     * @return The status of the ACL creation
     * @throws BusException
     */
    @BusMethod(name = "CreateAcl", signature = "sa(obas)a(saya(obas))a{ss}a{ss}", replySignature = "qso")
    public CreateAclStatusAJ createAcl(String aclName, ManifestObjectDescriptionAJ[] exposedServices, RemotedAppAJ[] remotedApps, Map<String, String> internalMetadata,
            Map<String, String> customMetadata) throws BusException;

    /**
     * Delete the ACL
     * 
     * @param aclId
     * @return ACL Response Code
     * @throws BusException
     */
    @BusMethod(name = "DeleteAcl", signature = "s", replySignature = "q")
    public short deleteAcl(String aclId) throws BusException;

    /**
     * Returns a list of the existing ACLs
     * 
     * @return {@link AclInfoAJ} list of the existing ACLs
     * @throws BusException
     */
    @BusMethod(name = "ListAcls", replySignature = "a(ssqo)")
    public AclInfoAJ[] listAcls() throws BusException;

    /**
     * @return The version of this interface
     * @throws BusException
     */
    @BusProperty(signature = "q")
    public short getVersion() throws BusException;
}
