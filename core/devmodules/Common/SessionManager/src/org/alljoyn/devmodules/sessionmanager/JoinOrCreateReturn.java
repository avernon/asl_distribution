/******************************************************************************
* Copyright (c) 2013, AllSeen Alliance. All rights reserved.
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
package org.alljoyn.devmodules.sessionmanager;

import org.alljoyn.bus.Status;

/**
 * This class is returned by the joinOrCreate() method of the session manager
 * 
 */
public class JoinOrCreateReturn {
    private Status status;
    private boolean joined;
    
    public JoinOrCreateReturn(Status status, boolean hasJoined) {
        this.status = status;
        this.joined = hasJoined;
    }
    
    /**
     * Get the AllJoyn status return from calling joinOrCreateSession()
     * @return the AllJoyn status return from joinOrCreateSession()
     */
    public Status getStatus() {
        return status;
    }

    /**
     * Get a flag denoting whether the user joined or created the session
     * @return true if the caller joined the session, false if the called created the session
     */
    public boolean hasJoined() {
        return joined;
    }
}
