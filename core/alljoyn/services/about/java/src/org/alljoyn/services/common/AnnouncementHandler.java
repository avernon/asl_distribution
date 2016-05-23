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

import java.util.Map;

import org.alljoyn.about.AboutKeys;
import org.alljoyn.about.transport.AboutTransport;
import org.alljoyn.bus.Variant;


/**
 * An interface to be implemented in order to receive Announcements
 * @deprecated org.alljoyn.bus.AboutListener
 */
@Deprecated
public interface AnnouncementHandler
{
    /**
     * Handle a received About Announcement
     * @deprecated org.alljoyn.bus.AboutListener
     * @param serviceName the peer's AllJoyn bus name
     * @param port the peer's bound port for accepting About session connections
     * @param objectDescriptions the peer's BusInterfaces and BusObjects
     * @param aboutData a map of peer's properties.
     * @see AboutKeys
     * @see AboutTransport#Announce(short, short, BusObjectDescription[], java.util.Map)
     */
    @Deprecated
    public void onAnnouncement(String serviceName, short port, BusObjectDescription[] objectDescriptions, Map<String, Variant> aboutData);

    /**
     * Handle a loss of connectivity with this bus name
     * @deprecated
     * @param serviceName the AllJoyn bus name of the lost peer
     */
    @Deprecated
    public void onDeviceLost(String serviceName);
}
