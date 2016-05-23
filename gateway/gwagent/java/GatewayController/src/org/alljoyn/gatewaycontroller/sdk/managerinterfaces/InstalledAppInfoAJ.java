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

package org.alljoyn.gatewaycontroller.sdk.managerinterfaces;

import org.alljoyn.bus.annotation.Position;

/**
 * This class stores data of the installed Gateway Connector Application. This
 * class is used only to received the unmarshalled data that is sent over
 * AllJoyn
 */
public class InstalledAppInfoAJ {

    /**
     * Application id
     */
    @Position(0)
    public String appId;

    /**
     * The application friendly name or description
     */
    @Position(1)
    public String friendlyName;

    /**
     * The identification of the application object
     */
    @Position(2)
    public String objectPath;

    /**
     * The application version
     */
    @Position(3)
    public String appVersion;
}