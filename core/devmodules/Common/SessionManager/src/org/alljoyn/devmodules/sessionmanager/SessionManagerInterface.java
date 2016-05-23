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

import java.util.ArrayList;

import org.alljoyn.bus.AuthListener;
import org.alljoyn.bus.BusAttachment;
import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.Mutable;
import org.alljoyn.bus.SessionListener;
import org.alljoyn.bus.SessionOpts;
import org.alljoyn.bus.SessionPortListener;
import org.alljoyn.bus.Status;

public interface SessionManagerInterface {
    
    public Status createSession (String sessionName, short sessionPort, SessionPortListener sessionPortListener);

    public Status createSession (String sessionName, short sessionPort, 
            SessionPortListener sessionPortListener, SessionOpts sessionOpts);
    
    public void destroySession (String sessionName);
    
    public Status joinSession (String sessionName, short sessionPort, Mutable.IntegerValue sessionId,
            SessionOpts sessionOpts, SessionListener sessionListener);
    
    public Status leaveSession (String sessionName);
    
    public JoinOrCreateReturn joinOrCreateSession (String sessionName, short sessionPort, 
            Mutable.IntegerValue sessionId, SessionOpts sessionOpts, 
            SessionListener sessionListener, SessionPortListener sessionPortListener);
    
    public Status registerBusObject(BusObject busObject, String objectPath);
    
    public Status registerBusObjects(ArrayList<BusObjectData> busObjects);
    
    public void unregisterBusObject(BusObject busObject);
    
    public void unregisterBusObjects(ArrayList<BusObjectData> busObjects);
    
    public void unregisterAllBusObjects();
    
    public ArrayList<String> listSessions ();
    
    public ArrayList<String> listHostedSessions ();
    
    public ArrayList<String> listJoinedSessions ();
    
    public ArrayList<String> getParticipants (String sessionName);
    
    public int getNumParticipants(String sessionName);
    
    public int getSessionId(String sessionName);
    
    public BusAttachment getBusAttachment();
    
    public Status registerSignalHandlers(Object classWithSignalHandlers);
    
    public void addSessionManagerListener(SessionManagerListener sessionMgrListener);
    
    public boolean isBusConnected();
    
    public Status registerAuthListener(String authMechanisms, AuthListener listener,
            String keyStoreFileName, boolean isShared);
    
    public Status registerAuthListener(String authMechanisms, AuthListener listener,
            String keyStoreFileName);
    
    public Status registerAuthListener(String authMechanisms, AuthListener listener);
    
    public Status addAlias(String sessionName, String masterSessionName, SessionOpts sessionOpts);
    
    public void removeAlias(String sessionName);
    
    public ArrayList<String> listAliases();
    
    public String getSessionName(String wellKnownName);
    
    // TODO: Implement methods below
//    public void breakOutSession (String[] ids, int waitTime);
//    
//    public void mergeSessions (String sessionName, String[] sessions);
//    
//    public void kickParticipants (String sessionName, String[] ids);
//    
//    public void banParticipants (String[] ids);
//    
//    public void unbanParticipants (String[] ids);

    
}
