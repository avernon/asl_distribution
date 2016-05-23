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
package org.alljoyn.devmodules.debug.api;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.annotation.*;

@BusInterface(name = "org.alljoyn.api.devmodules.debug")
public interface DebugAPIInterface {
////////////////////////////////////////////////
	// Control of Local Service 
	////////////////////////////////////////////////
	
	// Check status
	@BusMethod
    public boolean IsEnabled() throws BusException;

	// Enable Logging
	@BusMethod
    public void Enable() throws BusException;

	// Disable Logging
	@BusMethod
    public void Disable() throws BusException;

	// Get current filter string (OS-Specific)
	@BusMethod
    public String GetFilter() throws BusException;

	// Set filter string (OS-Specific)
	@BusMethod
    public void SetFilter(String filter) throws BusException;
	
	
	
	////////////////////////////////////////////////
	// Interaction with Remote Debug Services
	////////////////////////////////////////////////
	
	// Connect to a particular service (just use prefix for all services)
	@BusMethod
	public void Connect (String Device, String service) throws BusException;
	
	// Disconnect from a particular service
	@BusMethod
	public void Disconnect (String Device, String service) throws BusException;

	// List connected services
	@BusMethod
	public String[] GetServiceList () throws BusException;
	
	// Get the list of messages received from a particular service
	@BusMethod
	public DebugMessageDescriptor[] GetMessageList (String service) throws BusException;
}
