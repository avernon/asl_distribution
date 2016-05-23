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

package org.alljoyn.about;

import java.util.List;

import org.alljoyn.about.transport.AboutTransport;
import org.alljoyn.services.common.BusObjectDescription;

/**
 * An interface that publishes Announcements
 * @see AboutTransport#Announce(short, short, BusObjectDescription[], java.util.Map)
 * @deprecated
 */
@Deprecated
public interface Announcer
{
    /**
     * cause an Announcement to be emitted.
     * @deprecated org.alljoyn.bus.BusAttachment.announce
     */
    @Deprecated
    public void announce();

    /**
     * whether Announcements are emitted.
     * @return true if Announcements are emitted.
     * @deprecated
     */
    @Deprecated
    public boolean isAnnouncing();

    /**
     * set whether Announcements are emitted.
     * @param enable enable Announcement emitting.
     * @deprecated
     */
    @Deprecated
    public void setAnnouncing(boolean enable);

    /**
     * Any service who registered a BusObject in the common BusAttachment,
     * should save it here so that we can announce it
     * and include it in the About contents.
     * @param descriptions list of BusObjectDescriptions to be announced
     * @deprecated
     */
    @Deprecated
    public void addBusObjectAnnouncements(List<BusObjectDescription> descriptions);

    /**
     * Remove the passed BusObjectDescriptions from the Announcement
     * @param descriptions list of BusOBjectDescriptions to remove from the announcement
     * @deprecated
     */
    @Deprecated
    public void removeBusObjectAnnouncements(List<BusObjectDescription> descriptions);

}
