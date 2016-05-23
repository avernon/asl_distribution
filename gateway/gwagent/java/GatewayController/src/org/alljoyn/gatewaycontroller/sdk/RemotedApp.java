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

import java.util.List;
import java.util.UUID;

/**
 * The application that may be reached by the Gateway Connector Application via
 * the configured interfaces and object paths
 */
public class RemotedApp extends AnnouncedApp {

    /**
     * Configuration of the object paths and interfaces that are used by the
     * Gateway Connector Application to reach this remoted application
     */
    private final List<RuleObjectDescription> ruleObjDescriptions;

    /**
     * Constructor
     *
     * @param appName
     *            The name of the application
     * @param appId
     *            The application id
     * @param deviceName
     *            The name of the device
     * @param deviceId
     *            The device id
     * @param ruleObjDescriptions
     *            object path and interfaces that are used for {@link AclRules} creation
     * @throws IllegalArgumentException
     *             If bad arguments have been received
     */
    public RemotedApp(String appName, UUID appId, String deviceName, String deviceId,
                          List<RuleObjectDescription> ruleObjDescriptions) {

        super(null, appName, appId, deviceName, deviceId);

        if (deviceId == null || deviceId.length() == 0) {
            throw new IllegalArgumentException("DeviceId is undefined");
        }

        if (deviceName == null || deviceName.length() == 0) {
            throw new IllegalArgumentException("DeviceName is undefined");
        }

        if (appId == null) {
            throw new IllegalArgumentException("AppId is undefined");
        }

        if (appName == null || appName.length() == 0) {
            throw new IllegalArgumentException("AppName is undefined");
        }

        if (ruleObjDescriptions == null) {
            throw new IllegalArgumentException("ruleObjDescriptions is undefined");
        }

        this.ruleObjDescriptions = ruleObjDescriptions;
    }

    /**
     * Constructor
     *
     * @param discoveredApp
     *            The {@link AnnouncedApp} to be used to build this
     *            {@link RemotedApp}
     * @param ruleObjDescriptions
     *            object path and interfaces that are used for {@link AclRules} creation
     * @throws IllegalArgumentException
     *             If bad arguments have been received
     */
    public RemotedApp(AnnouncedApp discoveredApp, List<RuleObjectDescription> ruleObjDescriptions) {

        this(discoveredApp.getAppName(), discoveredApp.getAppId(), discoveredApp.getDeviceName(),
                discoveredApp.getDeviceId(), ruleObjDescriptions);
    }

    /**
     * Configuration of the object paths and interfaces that are used by the
     * Gateway Connector Application to reach this remoted application
     *
     * @return List of {@link RuleObjectDescription}
     */
    public List<RuleObjectDescription> getRuleObjectDescriptions() {
        return ruleObjDescriptions;
    }

    /**
     * @see java.lang.Object#toString()
     */
    @Override
    public String toString() {

        StringBuilder sb = new StringBuilder("RemotedApp [");
        sb.append("appName='").append(getAppName()).append("',")
          .append("appId='").append(getAppId()).append("',")
          .append("deviceName='").append(getDeviceName()).append("',")
          .append("deviceId='").append(getDeviceId()).append("']");

        return sb.toString();
    }
}
