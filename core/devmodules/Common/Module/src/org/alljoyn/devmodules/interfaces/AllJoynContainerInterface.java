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
package org.alljoyn.devmodules.interfaces;

import java.util.ArrayList;

import org.alljoyn.bus.BusAttachment;
import org.alljoyn.bus.SessionOpts;
import org.alljoyn.bus.SessionPortListener;
import org.alljoyn.bus.Status;
import org.alljoyn.devmodules.sessionmanager.SessionManager;

//Interface that a developer would implement that contains the container that holds the references to the different services
public interface AllJoynContainerInterface {	
	public static final String SERVICE_NAME = "org.alljoyn.devmodules";
	
	public String getUniqueID();
	
	//legacy will remove
	public SessionManager getSessionManager();
	
	/*
	 * This method will return a sessionId of a group if groups is supported
	 * otherwise it will throw an exception if groups is not supported
	 */
	public int getGroupSessionId(String groupName) throws Exception;
	
	public BusAttachment getBusAttachment(); 
	
	//optional but maybe provide in helper class
	public Status createSession(String sessionName, short sessionPort, SessionPortListener sessionPortListener, SessionOpts sessionOpts);

	//Should probably remove as sessionManager specific
	public ArrayList<String> getParticipants(String uID);
}


