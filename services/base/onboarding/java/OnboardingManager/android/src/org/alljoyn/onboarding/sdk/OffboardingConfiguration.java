/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
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
package org.alljoyn.onboarding.sdk;

/**
 *Holder of offboarding data: service name ,port
 */
public class OffboardingConfiguration {

    /**
     * The service name of the device
     */
    private final String serviceName;

    /**
     * The port of the onboarding service
     */
    private final short port;

    /**
     * Constructor of OffboardingConfiguration
     *
     * @param serviceName
     *            {@link #serviceName}
     * @param port
     *            {@link #port}
     *
     */
    public OffboardingConfiguration(String serviceName, short port) {
        this.serviceName = serviceName;
        this.port = port;
    }

    /**
     * Get {@link #serviceName}
     *
     * @return the device's service name {@link #serviceName}
     */
    public String getServiceName() {
        return serviceName;
    }

    /**
     * Get {@link #port}
     *
     * @return the devices's port {@link #port}
     */
    public short getPort() {
        return port;
    }

}
