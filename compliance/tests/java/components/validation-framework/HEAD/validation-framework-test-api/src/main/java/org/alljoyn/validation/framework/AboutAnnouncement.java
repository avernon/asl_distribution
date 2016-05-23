/*******************************************************************************
 *  Copyright AllSeen Alliance. All rights reserved.
 *
 *     Contributed by Qualcomm Connected Experiences, Inc.,
 *     with authorization from the AllSeen Alliance, Inc.
 *     
 *     Licensed under the Apache License, Version 2.0 (the "License");
 *     you may not use this file except in compliance with the License.
 *     You may obtain a copy of the License at
 *     
 *         http://www.apache.org/licenses/LICENSE-2.0
 *     
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *     See the License for the specific language governing permissions and
 *     limitations under the License.
 *     
 *     Pursuant to Section 1 of the License, the work of authorship constituting
 *     a Work and any Contribution incorporated in the Work shall mean only that
 *     Contributor's code submissions authored by that Contributor.  Any rights
 *     granted under the License are conditioned upon acceptance of these
 *     clarifications.
 *******************************************************************************/
package org.alljoyn.validation.framework;

import java.util.Map;

import org.alljoyn.bus.Variant;
import org.alljoyn.services.common.BusObjectDescription;

/**
 * This class contains details of the announcement broadcast by About feature
 * about the device/app and list of supported interfaces.
 * 
 */
public class AboutAnnouncement
{
    private String serviceName;
    private short port;
    private BusObjectDescription[] objectDescriptions;
    private Map<String, Variant> aboutData;

    /**
     * @param serviceName
     *            the bus unique name of the peer exposing the service
     * @param port
     *            the port on which the app will listen
     * @param objectDescriptions
     *            object paths and the list of all interfaces available at the
     *            given object path
     * @param aboutData
     *            app/device details
     */
    public AboutAnnouncement(String serviceName, short port, BusObjectDescription[] objectDescriptions, Map<String, Variant> aboutData)
    {
        this.serviceName = serviceName;
        this.port = port;
        this.objectDescriptions = objectDescriptions;
        this.aboutData = aboutData;
    }

    /**
     * @return the bus unique name of the peer exposing the service
     */
    public String getServiceName()
    {
        return serviceName;
    }

    /**
     * @return port on which the app will listen
     */
    public short getPort()
    {
        return port;
    }

    /**
     * @return array of {@code BusObjectDescription} which contains object paths
     *         and the list of all interfaces available at the given object path
     */
    public BusObjectDescription[] getObjectDescriptions()
    {
        return objectDescriptions;
    }

    /**
     * @return app/device details
     */
    public Map<String, Variant> getAboutData()
    {
        return aboutData;
    }
}