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
package org.alljoyn.devmodules.debug;

import org.alljoyn.bus.BusException;

///////////////////////////////////////////////////////////////////
// Application (Remote) Debug Callback Handling
// This is for allowing the app to register callbacks for specific events, 
// mostly needed for coordinating startup and (maybe) shutdown
///////////////////////////////////////////////////////////////////

//Class to hold callback functions
public class DebugCallback {

	public DebugCallback(){
		//nothing to do
	}
	
	// called when a new debug service is detected/connected
	// @param service the name of the Debug service detected
	public void onDebugServiceConnected(String service) {
	}

	// called when a debug service is 'lost'
	// @param service the name of the Debug service that has been lost
	public void onDebugServiceDisconnected(String service) {
	}
	
	// called when a debug message is received
	// @param service the name of the Debug service issuing the message
	// @param level   the urgency level (0=lowest) 
	// @param message the (text) contents of the message
    public void onDebugMessageReceived (String service, int level, String message){
    	
    }

}//ClientCallback
