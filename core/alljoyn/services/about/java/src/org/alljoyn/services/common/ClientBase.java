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

package org.alljoyn.services.common;

import org.alljoyn.bus.BusAttachment;
import org.alljoyn.bus.BusException;
import org.alljoyn.bus.Status;

/**
 * A base class for service clients.
 * @deprecated
 */
@Deprecated
public interface ClientBase
{
    /**
     * Stop the AllJoyn session with the device.
     * @deprecated
     */
    @Deprecated
    public void disconnect();

    /**
     * Start an AllJoyn session with the device.
     * @deprecated
     * @return AllJoyn Bus Status
     */
    @Deprecated
    public Status connect();

    /**
     * Is there an open session with the device.
     * @deprecated
     * @return true if there is a session with the device.
     */
    @Deprecated
    public boolean isConnected();

    /**
     * Interface version
     * @deprecated
     * @return Interface version
     * @throws BusException indicating failure obtain Version property
     */
    @Deprecated
    public short getVersion() throws BusException;

    /**
     * The peer device's bus name, as advertised by Announcements
     * @deprecated
     * @return Unique bus name
     */
    @Deprecated
    public String getPeerName();

    /**
     * The id of the open session with the peer device.
     * @deprecated
     * @return AllJoyn session id
     */
    @Deprecated
    public int getSessionId();

    /**
     * Initialize client by passing the BusAttachment
     * @deprecated
     * @param busAttachment BusAttachment associated with this ClientBase instance
     * @throws Exception error indicating failure to initialize the client
     */
    @Deprecated
    void initBus(BusAttachment busAttachment) throws Exception;

}
