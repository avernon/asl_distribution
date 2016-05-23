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

import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * This class defines access rules for the {@link Acl}
 */
public class AclRules {

    /**
     * The interfaces that the Gateway Connector Application exposes to its
     * clients
     */
    private final List<RuleObjectDescription> exposedServices;

    /**
     * The applications that may be reached by the Gateway Connector Application
     * via the configured interfaces and object paths
     */
    private final List<RemotedApp> remotedApps;

    /**
     * This {@link AclRules} metadata
     */
    private Map<String, String> metadata;

    /**
     * Constructor
     * 
     * @param exposedServices
     *            The interfaces that the Gateway Connector Application exposes
     *            to its clients
     * @param remotedApps
     *            The applications that may be reached by the Gateway Connector
     *            Application via the configured interfaces and object paths
     * @throws IllegalArgumentException
     *             is thrown if bad arguments have been received
     */
    public AclRules(List<RuleObjectDescription> exposedServices, List<RemotedApp> remotedApps) {

        if (exposedServices == null) {
            throw new IllegalArgumentException("exposedServices is undefined");
        }

        if (remotedApps == null) {
            throw new IllegalArgumentException("remotedApps is undefined");
        }

        this.exposedServices = exposedServices;
        this.remotedApps     = remotedApps;
        metadata             = new HashMap<String, String>();
    }

    /**
     * The interfaces that Gateway Connector Application exposes to its clients
     * 
     * @return List of exposed services
     */
    public List<RuleObjectDescription> getExposedServices() {
        return exposedServices;
    }

    /**
     * The applications that may be reached by the Gateway Connector Application
     * via the configured interfaces and object paths
     * 
     * @return List of the remoted applications
     */
    public List<RemotedApp> getRemotedApps() {
        return remotedApps;
    }

    /**
     * Returns current metadata
     * 
     * @return metadata
     */
    public Map<String, String> getMetadata() {

        return metadata;
    }

    /**
     * Set the metadata
     * 
     * @param metadata
     */
    public void setMetadata(Map<String, String> metadata) {

        this.metadata = metadata;
    }

}