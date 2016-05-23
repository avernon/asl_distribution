/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

package org.alljoyn.gatewaycontroller.sdk.announcement;

import java.util.Map;

import org.alljoyn.bus.AboutListener;
import org.alljoyn.bus.AboutObjectDescription;
import org.alljoyn.bus.Variant;
import org.alljoyn.gatewaycontroller.sdk.AnnouncedApp;
import org.alljoyn.services.common.BusObjectDescription;

/**
 * This class contains announcement data received from a device on the network
 */
public class AnnouncementData {

    /**
     * The about port number
     */
    private final short portNumber;

    /**
     * The announced object descriptions
     */
    private final AboutObjectDescription[] objDescArr;

    /**
     * The announcement data
     */
    private final Map<String, Variant> aboutData;

    /**
     * The application data from this {@link AnnouncementData}
     */
    private final AnnouncedApp app;

    /**
     * Constructor
     * 
     * @param portNumber
     * @param objectDescArr
     * @param aboutData
     * @param app
     */
    AnnouncementData(short portNumber, AboutObjectDescription[] objDescArr, Map<String, Variant> aboutData,
                         AnnouncedApp app) {

        this.portNumber = portNumber;
        this.objDescArr = objDescArr;
        this.aboutData  = aboutData;
        this.app        = app;
    }

    /**
     * @return The Port number which was sent with the Announcement
     */
    public short getPortNumber() {
        return portNumber;
    }

    /**
     * @return The {@link AboutListener} data which was sent with the
     *         Announcement
     */
    public Map<String, Variant> getAboutData() {
        return aboutData;
    }

    /**
     * @return The application data that is created based on the received with
     *         the Announcement AboutData
     */
    public AnnouncedApp getApplicationData() {
        return app;
    }

    /**
     * @return The array of {@link BusObjectDescription}
     */
    public AboutObjectDescription[] getObjDescArr() {
        return objDescArr;
    }

}
