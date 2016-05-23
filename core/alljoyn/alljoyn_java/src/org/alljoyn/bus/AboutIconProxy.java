/*
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
 */
package org.alljoyn.bus;

import org.alljoyn.bus.AboutIcon;
import org.alljoyn.bus.ifaces.Icon;

public class AboutIconProxy implements Icon{

    /**
     * AboutProxy constructor
     *
     * @param bus the BusAttachment that owns this ProxyBusObject
     * @param busName the unique or well-known name of the remote AllJoyn BusAttachment
     * @param sessionId the session ID this ProxyBusObject will use
     */
    public AboutIconProxy(BusAttachment bus, String busName, int sessionId) {
        ProxyBusObject aboutIconProxy = bus.getProxyBusObject(busName, Icon.OBJ_PATH, sessionId, new Class<?>[] {Icon.class});
        proxy = aboutIconProxy.getInterface(Icon.class);
    }

    /**
     * fill in an AboutIcon by making remote method calls to obtain the
     * Information from a remote AboutIcon BusObject
     *
     * @return An AboutIcon
     *
     * @throws BusException indicating there was a failure trying to obtain the
     * data needed to create an AboutIcon
     */
    public AboutIcon getAboutIcon() throws BusException {
        return new AboutIcon(getMimeType(), getUrl(), getContent());
    }

    /**
     * @return the version of the remote AboutIcon BusObject
     * @throws BusException indicating there was a failure obtaining the version
     * of the remote interface
     */
    @Override
    public short getVersion() throws BusException {
        return proxy.getVersion();
    }

    /**
     * @return the MimeType of the icon from the remote AboutIcon BusObject
     * @throws BusException indicating there was a failure obtaining the MimeType
     */
    @Override
    public String getMimeType() throws BusException {
        return proxy.getMimeType();
    }

    /**
     * @return the size of the icon content from the remote AboutIcon BusObject
     * @throws BusException indication there was a failure obtaining the content
     *         size
     */
    @Override
    public int getSize() throws BusException {
        return proxy.getSize();
    }

    /**
     * @return the URL indicating the cloud location of the icon from the remote
     *         AboutIcon BusObject
     * @throws BusException indicating there was a failure obtaining the URL
     */
    @Override
    public String getUrl() throws BusException {
        return proxy.getUrl();
    }

    /**
     * @return an array of bytes containing the binary content for the icon from
     *         the remote AboutIcon BusObject
     * @throws BusException indicating there was a failure obtaining the icon
     *         content.
     */
    @Override
    public byte[] getContent() throws BusException {
        return proxy.getContent();
    }

    /**
     * An org.alljoyn.Icon ProxyBusObject
     */
    private Icon proxy;

}
