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

package org.alljoyn.gatewaycontroller.sdk;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.UUID;

import org.alljoyn.bus.BusAttachment;
import org.alljoyn.bus.BusException;
import org.alljoyn.bus.ProxyBusObject;
import org.alljoyn.bus.Variant;
import org.alljoyn.gatewaycontroller.sdk.managerinterfaces.ApplicationManagement;
import org.alljoyn.gatewaycontroller.sdk.managerinterfaces.InstalledAppInfoAJ;

import android.util.Log;

/**
 * The Gateway found on the network
 */
public class GatewayMgmtApp extends AnnouncedApp {
    private static final String TAG = "gwc" + GatewayMgmtApp.class.getSimpleName();

    /**
     * Constructor
     *
     * @param gwBusName
     *            The name of the {@link BusAttachment} of the Gateway Management App
     * @throws IllegalArgumentException
     *             is thrown if bad arguments have been received
     */
    public GatewayMgmtApp(String gwBusName) {

        super(gwBusName, null, null, null, null);

        if (gwBusName == null || gwBusName.length() == 0) {
            throw new IllegalArgumentException("Received undefined gwBusName");
        }
    }

    /**
     * Constructor
     *
     * @param gwBusName
     *            The name of the {@link BusAttachment} of the Gateway Management App that sent
     *            the Announcement
     * @param aboutData
     *            The data sent with the Announcement
     * @throws IllegalArgumentException
     *             is thrown if bad gwBusName has been received
     */
    public GatewayMgmtApp(String gwBusName, Map<String, Variant> aboutData) {

        super(gwBusName, aboutData);

        if (gwBusName == null || gwBusName.length() == 0) {
            throw new IllegalArgumentException("Received undefined gwBusName");
        }

        String deviceId = getDeviceId();
        UUID appId = getAppId();

        if (deviceId == null || deviceId.length() == 0) {
            throw new IllegalArgumentException("DeviceId is undefined");
        }

        if (appId == null) {
            throw new IllegalArgumentException("AppId is undefined");
        }
    }

    /**
     * Retrieve the list of Connector Applications managed by the Gateway Management App identified by
     * the given gwBusName
     *
     * @param sessionId
     *            The id of the session established with the Gateway Management App
     * @return The {@link ConnectorApp}
     * @throws GatewayControllerException
     */
    public List<ConnectorApp> retrieveConnectorApps(int sessionId) throws GatewayControllerException {

        final String gwBusName = getBusName();
        BusAttachment bus      = GatewayController.getInstance().getBusAttachment();

        ProxyBusObject proxy   = bus.getProxyBusObject(getBusName(), "/gw", sessionId,
                                                       new Class<?>[] { ApplicationManagement.class });

        Log.d(TAG, "Retreiving list of the Connector Applications for the GW: '" + gwBusName + "'");

        ApplicationManagement appMng = proxy.getInterface(ApplicationManagement.class);

        InstalledAppInfoAJ[] appInfoArr;
        try {
            appInfoArr = appMng.getInstalledApps();
        } catch (BusException be) {

            Log.e(TAG, "Failed to retreive list of the Connector Applications for the GW: '" + gwBusName + "'");

            throw new GatewayControllerException("Failed to retreive list of the Connector Applications, Error: '"
                                                     + be.getMessage() + "'", be);
        }

        List<ConnectorApp> connectorApps = new ArrayList<ConnectorApp>(appInfoArr.length);
        for (InstalledAppInfoAJ appInfo : appInfoArr) {

            connectorApps.add(new ConnectorApp(gwBusName, appInfo));
        }

        return connectorApps;
    }
}
