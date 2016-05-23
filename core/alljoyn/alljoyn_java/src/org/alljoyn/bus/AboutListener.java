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

package org.alljoyn.bus;

import java.util.Map;

/**
 * Interface implemented by AllJoyn users to receive About interface related
 * events
 */
public interface AboutListener {
    /**
     * Called by the bus when an announcement containing information about the
     * application and interfaces is found
     *
     * @param busName   well know name of the remote BusAttachment
     * @param version   version of the Announce signal from the remote About Object
     * @param port      SessionPort used by the announcer
     * @param objectDescriptions a list of object paths and interfaces in the announcement
     * @param aboutData a dictionary of key/value pairs of the AboutData
     */
    public void announced(String busName, int version, short port, AboutObjectDescription[] objectDescriptions, Map<String, Variant> aboutData);
}
