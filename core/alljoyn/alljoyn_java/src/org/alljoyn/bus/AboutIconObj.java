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

import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.AboutIcon;
import org.alljoyn.bus.ifaces.Icon;

/**
 * AboutIconObj is an AllJoyn BusObject that implements the org.alljoyn.Icon
 * standard interface. Applications that provide AllJoyn IoE services to receive
 * info about the Icon of the service.
 */
public class AboutIconObj implements Icon, BusObject{
    /**
     * version of the org.alljoyn.Icon interface
     */
    public static final short VERSION = 1;

    /**
     * Create an About Icon BusObject
     *
     * @param bus BusAttachment instance associated with this BusObject
     * @param icon instance of an AboutIcon which holds the icon image
     */
    AboutIconObj(BusAttachment bus, AboutIcon icon) {
        if(bus == null) {
            throw new NullPointerException("bus must not be null");
        }
        if(icon == null) {
            throw new NullPointerException("icon must not be null");
        }
        m_icon = icon;
        bus.registerBusObject(this, Icon.OBJ_PATH);
    }

    /**
     * @return The about Icon interface version.
     */
    @Override
    public short getVersion() throws BusException {
        return VERSION;
    }

    /**
     * @return A string indicating the image MimeType
     */
    @Override
    public String getMimeType() throws BusException {
        return m_icon.getMimeType();
    }

    /**
     * @return The size of the icon content.
     */
    @Override
    public int getSize() throws BusException {
        if(m_icon.getContent() == null) {
            return 0;
        }
        return m_icon.getContent().length;
    }


    /**
     * @return The URL indicating the cloud location of the icon
     */
    @Override
    public String getUrl() throws BusException {
        return m_icon.getUrl();
    }

    /**
     * @return an array of bytes containing the binary content for the icon
     */
    @Override
    public byte[] getContent() throws BusException {
        if (m_icon.getContent() == null) {
            return new byte[0];
        }
        return m_icon.getContent();
    }

    /**
     * AboutIcon used by the AboutIcon BusObject
     */
    private AboutIcon m_icon;
}
