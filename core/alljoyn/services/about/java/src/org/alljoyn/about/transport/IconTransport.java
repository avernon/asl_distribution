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

package org.alljoyn.about.transport;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusProperty;

/**
 * Definition of the Icon BusInterface
 * @deprecated see org.alljoyn.bus.ifaces.Icon
 */
@Deprecated
@BusInterface (name = IconTransport.INTERFACE_NAME)
public interface IconTransport extends BusObject
{
    public static final String INTERFACE_NAME = "org.alljoyn.Icon";
    public final static String OBJ_PATH = "/About/DeviceIcon";

    /**
     * @deprecated see org.alljoyn.bus.ifaces.Icon
     * @return Interface version
     * @throws BusException indicating failure to obtain Version property
     */
    @Deprecated
    @BusProperty(signature="q")
    public short getVersion() throws BusException;

    /**
     * @deprecated see org.alljoyn.bus.ifaces.Icon
     * @return Mime type for the icon
     * @throws BusException indicating failure to obtain MimeType property
     */
    @Deprecated
    @BusProperty(signature="s")
    public String getMimeType() throws BusException;

    /**
     * @deprecated see org.alljoyn.bus.ifaces.Icon
     * @return Size of the icon
     * @throws BusException indicating failure to obtain Size property
     */
    @Deprecated
    @BusProperty(signature="u")
    public int getSize() throws BusException;

    /**
     * Returns the URL if the icon is hosted on the cloud
     * @deprecated see org.alljoyn.bus.ifaces.Icon
     * @return the URL if the icon is hosted on the cloud
     * @throws BusException indicating failure to make GetUrl method call
     */
    @Deprecated
    @BusMethod(replySignature="s")
    public String GetUrl() throws BusException;

    /**
     * Returns binary content for the icon
     * @deprecated see org.alljoyn.bus.ifaces.Icon
     * @return binary content for the icon
     * @throws BusException indicating failure to make GetContent method call
     */
    @Deprecated
    @BusMethod(replySignature="ay")
    public byte[] GetContent() throws BusException;
}
