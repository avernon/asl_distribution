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

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusProperty;
import org.alljoyn.bus.annotation.BusSignal;
import org.alljoyn.bus.annotation.Secure;
import org.alljoyn.gatewaycontroller.sdk.GatewayController;

/**
 * AllJoyn interface for operating the Gateway Connector Application
 */
@BusInterface(name = Application.IFNAME)
@Secure
public interface Application {

    /**
     * AllJoyn name of the interface
     */
    public static final String IFNAME = GatewayController.IFACE_PREFIX + ".App";

    /**
     * The signal about the status change of the Gateway Connector Application
     */
    public static final String APPLICATION_STATUS_CHANGED = "AppStatusChanged";

    /**
     * Returns the state of the application
     * 
     * @return {@link ApplicationStatusAJ}
     * @throws BusException
     */
    @BusMethod(name = "GetAppStatus", replySignature = "qsqq")
    public ApplicationStatusAJ getApplicationStatus() throws BusException;

    /**
     * Returns lists of interfaces from the manifest of the application
     * 
     * @return {@link ManifestRulesAJ}
     * @throws BusException
     */
    @BusMethod(name = "GetManifestInterfaces", replySignature = "a((obs)a(ssb))a((obs)a(ssb))")
    public ManifestRulesAJ getManifestInterfaces() throws BusException;

    /**
     * Restarts the application
     * 
     * @return Application restart status
     * @throws BusException
     */
    @BusMethod(name = "RestartApp", replySignature = "q")
    public short restartApp() throws BusException;

    /**
     * Returns Manifest file of the application
     * 
     * @return The text of the application manifest
     * @throws BusException
     */
    @BusMethod(name = "GetManifestFile", replySignature = "s")
    public String getManifestFile() throws BusException;

    /**
     * The signal describing the change in the status of the application
     * 
     * @param statusCode
     */
    @BusSignal(name = APPLICATION_STATUS_CHANGED, signature = "qsqq")
    public void applicationStatusChanged(short installStatus, String installDescription, short connectionStatus, short operationalStatus) throws BusException;

    /**
     * @return The version of this interface
     * @throws BusException
     */
    @BusProperty(signature = "q")
    public short getVersion() throws BusException;
}
