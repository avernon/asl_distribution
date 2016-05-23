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

import org.alljoyn.bus.BusObject;

/**
 * This interface defines the methods that must be implemented by a 'module'
 * These are mostly used to automate common functions such as advertising the 
 * service name, adding objects to the bus once established etc.
 *
 */
public interface ModuleInterface {
	
	public void RegisterSignalHandlers();
	
	public void InitAPI(AllJoynContainerInterface coreLogic);
	
	public void SetupSession(); //Initiates the module and uses SessionManager to bind a session and setup callbacks
	
	public String getServiceName(); //to register the service
	
	public BusObject getBusObject();
	
	public String getObjectPath();
	
	public String getAdvertisedName();
	
	public void shutdown();	//Cleanup
	
	public void foundAdvertisedName(String name, short transport, String namePrefix);
	
	public void lostAdvertisedName(String name, short transport, String namePrefix);
	
	//start stop, restart
}


