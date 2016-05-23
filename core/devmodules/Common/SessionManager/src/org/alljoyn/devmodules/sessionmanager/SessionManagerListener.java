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

/**
 * The SessionManagerListener is an additional listener that can be used to 
 * listen for the busStopping(), foundAdvertisedname(), lostAdvertisedName(), 
 * nameOwnerChanged(), sessionJoined(), sessionLost(), sessionMemberAdded(), 
 * and sessionMemberRemoved() signals. The desired callback methods need to 
 * be overridden. 
 * 
 */
public class SessionManagerListener {
    
    public void busStopping() {
        return;
    }
    
    public void foundAdvertisedName(String name, short transport, String namePrefix) {
        return;
    }
    
    public void lostAdvertisedName(String name, short transport, String namePrefix) {
        return;
    }
    
    public void nameOwnerChanged(String busName, String previousOwner, String newOwner) {
        return;
    }
    
    public void sessionJoined(short sessionPort, int id, String joiner) {
        return;
    }
    
    public void sessionLost(int sessionId) {
        return;
    }
    
    public void sessionMemberAdded(int sessionId, String uniqueName) {
        return;
    }
    
    public void sessionMemberRemoved(int sessionId, String uniqueName) {
        return;
    }
}
