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
package org.alljoyn.bus;

import java.util.Map;

import org.alljoyn.bus.ifaces.About;

/**
 * Get proxy access to the org.alljoyn.About interface.
 *
 * This class enables the user to interact with the remote About BusObject
 */
public class AboutProxy {
    /**
     * AboutProxy constructor
     *
     * @param bus the BusAttachment that owns this ProxyBusObject
     * @param busName the unique or well-known name of the remote AllJoyn BusAttachment
     * @param sessionId the session ID this ProxyBusObject will use
     */
    public AboutProxy(BusAttachment bus, String busName, int sessionId) {
        ProxyBusObject aboutProxy = bus.getProxyBusObject(busName, About.OBJ_PATH, sessionId, new Class<?>[] {About.class});
        proxy = aboutProxy.getInterface(About.class);
    }

    /**
     * Get a list of object paths and the interfaces that are being announced
     *
     * @return
     * An array of AboutObjectDescriptions. Each AboutObjectDescription contains
     * the path of a remote BusObject and a list of interfaces contained at that
     * path.
     * @throws BusException
     *   throws an exception indicating failure to make the remote method call
     */
    public AboutObjectDescription[] getObjectDescription() throws BusException {
        return proxy.getObjectDescription();
    }

    /**
     * Get all of the AboutData from the remote BusAttachment. Not all AboutData
     * is contained in the Announced AboutData. This method can be used to get
     * all of the AboutData for a specified language.
     *
     * @param languageTag a String formated as an IETF language tag specified by RFC 5646
     * @return
     * A map containing the fields specified in the About Interface
     *
     * @throws BusException
     *   throws an exception indicating failure to make the remote method call
     */
    public Map<String, Variant> getAboutData(String languageTag) throws BusException {
        return proxy.getAboutData(languageTag);
    }

    /**
     * Get the version of the remote About interface
     * @return the version of the remote About interface
     * @throws BusException
     *   throws an exception indicating failure to make the remote method call
     */
    public short getVersion() throws BusException {
        return proxy.getVersion();
    }

    About proxy;
}
