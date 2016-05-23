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

package org.alljoyn.gatewaycontroller.adapters;

import java.util.EnumMap;
import java.util.Map;

import org.alljoyn.gatewaycontroller.sdk.ConnectorApp;
import org.alljoyn.gatewaycontroller.sdk.ConnectorAppStatus;
import org.alljoyn.gatewaycontroller.sdk.ConnectorAppStatus.ConnectionStatus;
import org.alljoyn.gatewaycontroller.sdk.ConnectorAppStatus.InstallStatus;
import org.alljoyn.gatewaycontroller.sdk.ConnectorAppStatus.OperationalStatus;

/**
 * {@link ConnectorApp} to be visualized by the
 * {@link ConnectorAppsAdapter}
 */
public class VisualConnectorApp implements VisualItem {

    /**
     * {@link ConnectionStatus} color
     */
    private static Map<ConnectionStatus, String> connStatusColor = new EnumMap<ConnectionStatus, String>(ConnectionStatus.class);

    /**
     * {@link InstallStatus} color
     */
    private static Map<InstallStatus, String> installStatusColor = new EnumMap<InstallStatus, String>(InstallStatus.class);

    /**
     * {@link OperationalStatus} color
     */
    private static Map<OperationalStatus, String> operationalStatusColor = new EnumMap<OperationalStatus, String>(OperationalStatus.class);

    static {

        connStatusColor.put(ConnectionStatus.GW_CS_NOT_INITIALIZED, "#61210B");
        connStatusColor.put(ConnectionStatus.GW_CS_IN_PROGRESS, "#0404B4");
        connStatusColor.put(ConnectionStatus.GW_CS_CONNECTED, "#088A08");
        connStatusColor.put(ConnectionStatus.GW_CS_NOT_CONNECTED, "#F7750C");
        connStatusColor.put(ConnectionStatus.GW_CS_ERROR, "#DF0101");

        installStatusColor.put(InstallStatus.GW_IS_INSTALLED, "#088A08");
        installStatusColor.put(InstallStatus.GW_IS_INSTALL_IN_PROGRESS, "#0404B4");
        installStatusColor.put(InstallStatus.GW_IS_UPGRADE_IN_PROGRESS, "#0404B4");
        installStatusColor.put(InstallStatus.GW_IS_UNINSTALL_IN_PROGRESS, "#0404B4");
        installStatusColor.put(InstallStatus.GW_IS_INSTALL_FAILED, "#DF0101");

        operationalStatusColor.put(OperationalStatus.GW_OS_RUNNING, "#088A08");
        operationalStatusColor.put(OperationalStatus.GW_OS_STOPPED, "#F7750C");
    }

    // =========================================//

    /**
     * {@link ConnectorApp}
     */
    private ConnectorApp app;

    /**
     * {@link ConnectorAppStatus}
     */
    private ConnectorAppStatus appStatus;

    /**
     * Constructor
     * 
     * @param app
     * @param appStatus
     */
    public VisualConnectorApp(ConnectorApp app, ConnectorAppStatus appStatus) {

        this.app       = app;
        this.appStatus = appStatus;
    }

    /**
     * Get connection status color
     * 
     * @param status
     * @return
     */
    public static String getConnStatusColor(ConnectionStatus status) {
        return connStatusColor.get(status);
    }

    /**
     * @return {@link ConnectorAppStatus}
     */
    public ConnectorAppStatus getAppStatus() {
        return appStatus;
    }

    /**
     * @param appStatus
     *            {@link ConnectorAppStatus}
     */
    public void setAppStatus(ConnectorAppStatus appStatus) {
        this.appStatus = appStatus;
    }

    /**
     * Get intallation status color
     * 
     * @param status
     * @return
     */
    public static String getInstallStatusColor(InstallStatus status) {
        return installStatusColor.get(status);
    }

    /**
     * Get operational status color
     * 
     * @param status
     * @return
     */
    public static String getOperationalStatusColor(OperationalStatus status) {
        return operationalStatusColor.get(status);
    }

    /**
     * @return {@link ConnectorApp}
     */
    public ConnectorApp getApp() {
        return app;
    }

    /**
     * Call clean on {@link ConnectorApp}
     */
    public void clear() {
        app.clear();
    }
}
