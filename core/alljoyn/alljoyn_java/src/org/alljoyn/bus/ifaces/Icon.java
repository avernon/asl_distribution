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

package org.alljoyn.bus.ifaces;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusProperty;

/**
 * Definition of the Icon BusInterface
 */
@BusInterface (name = Icon.INTERFACE_NAME, announced="true")
public interface Icon
{
    public static final String INTERFACE_NAME = "org.alljoyn.Icon";
    public final static String OBJ_PATH = "/About/DeviceIcon";

    /**
     * @return Interface version
     * @throws BusException indicating failure to retrieve Version property
     */
    @BusProperty(signature="q")
    public short getVersion() throws BusException;

    /**
     * @return Mime type for the icon
     * @throws BusException indicating failure to retrieve MimeType property
     */
    @BusProperty(signature="s")
    public String getMimeType() throws BusException;

    /**
     * @return Size of the icon
     * @throws BusException indicating failure to retrieve Size property
     */
    @BusProperty(signature="u")
    public int getSize() throws BusException;

    /**
     * Returns the URL if the icon is hosted on the cloud
     * @return the URL if the icon is hosted on the cloud
     * @throws BusException indicating failure to make GetUrl method call
     */
    @BusMethod(name="GetUrl", replySignature="s")
    public String getUrl() throws BusException;

    /**
     * Returns binary content for the icon
     * @return binary content for the icon
     * @throws BusException indicating failure to make GetContent method call
     */
    @BusMethod(name="GetContent", replySignature="ay")
    public byte[] getContent() throws BusException;
}
