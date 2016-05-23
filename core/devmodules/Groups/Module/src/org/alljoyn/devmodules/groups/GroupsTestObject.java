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
package org.alljoyn.devmodules.groups;

// Method handlers for external Interfaces

import org.alljoyn.bus.BusAttachment;
import org.alljoyn.bus.BusException;
import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.MessageContext;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusSignal;
import org.alljoyn.devmodules.common.GroupListDescriptor;
import org.alljoyn.storage.ProfileCache;

import android.util.Log;

public class GroupsTestObject implements GroupsTestInterface, BusObject {

	private static final String TAG = "GroupsTestObject"; 

	/********************************************************************************
	 ** Blank templates for Signals (handlers are in the GroupsTestImpl class) **
	 ********************************************************************************/

	@Override
	public void PingRequest(String group, String userid, String pingString) throws BusException {}

	@Override
	public void PingResponse(String group, String userid, String pingString) throws BusException {}

}