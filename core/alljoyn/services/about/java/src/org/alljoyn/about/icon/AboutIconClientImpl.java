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

package org.alljoyn.about.icon;

import org.alljoyn.about.transport.IconTransport;
import org.alljoyn.bus.BusAttachment;
import org.alljoyn.bus.BusException;
import org.alljoyn.bus.ProxyBusObject;
import org.alljoyn.services.common.ClientBaseImpl;
import org.alljoyn.services.common.ServiceAvailabilityListener;

@Deprecated
public class AboutIconClientImpl extends ClientBaseImpl implements AboutIconClient
{
    @Deprecated
    public final static String TAG = AboutIconClientImpl.class.getName();

    @Deprecated
    public AboutIconClientImpl(String peerName, BusAttachment bus, ServiceAvailabilityListener serviceAvailabilityListener, short port)
    {
        super(peerName, bus, serviceAvailabilityListener, IconTransport.OBJ_PATH, new Class<?>[] { IconTransport.class }, port);
    }

    @Override
    @Deprecated
    public short getVersion() throws BusException {
        ProxyBusObject proxyObj = getProxyObject();
        /* We make calls to the methods of the AllJoyn object through one of its interfaces. */
        IconTransport aboutIconTransport =  proxyObj.getInterface(IconTransport.class);
        return aboutIconTransport.getVersion();
    }

    @Override
    @Deprecated
    public String getMimeType() throws BusException {
        ProxyBusObject proxyObj = getProxyObject();
        /* We make calls to the methods of the AllJoyn object through one of its interfaces. */
        IconTransport aboutIconTransport =  proxyObj.getInterface(IconTransport.class);
        return aboutIconTransport.getMimeType();
    }

    @Override
    @Deprecated
    public int getSize() throws BusException {
        ProxyBusObject proxyObj = getProxyObject();
        /* We make calls to the methods of the AllJoyn object through one of its interfaces. */
        IconTransport aboutIconTransport =  proxyObj.getInterface(IconTransport.class);
        return aboutIconTransport.getSize();
    }

    @Override
    @Deprecated
    public String GetUrl() throws BusException {
        ProxyBusObject proxyObj = getProxyObject();
        /* We make calls to the methods of the AllJoyn object through one of its interfaces. */
        IconTransport aboutIconTransport =  proxyObj.getInterface(IconTransport.class);
        return aboutIconTransport.GetUrl();
    }

    @Override
    @Deprecated
    public byte[] GetContent() throws BusException {
        ProxyBusObject proxyObj = getProxyObject();
        /* We make calls to the methods of the AllJoyn object through one of its interfaces. */
        IconTransport aboutIconTransport =  proxyObj.getInterface(IconTransport.class);
        return aboutIconTransport.GetContent();
    }


}
