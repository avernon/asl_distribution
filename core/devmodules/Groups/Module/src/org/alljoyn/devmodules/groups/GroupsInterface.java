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

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusSignal;


@BusInterface (name = GroupsConstants.NAME_PREFIX)
public interface GroupsInterface {
	
//THIS IS THE SERVICE TO SERVICE (INTER-DEVICE) INTERFACE
	
	@BusMethod
	// Get the list of groups currently supported
	public String [] GetGroupList() throws BusException;
	
	@BusMethod
	// Get the list of groups currently supported (in GroupListDescriptor format)
	public String GetGroupListDescriptor() throws BusException;
	
	@BusMethod
	// Get the descriptor for the specified group
	public String GetGroupDescriptor (String group) throws BusException;
	
	@BusMethod
	// Get the port number for the specified group
	public short GetPortNumber (String group) throws BusException;
	
	@BusMethod
	//	Request activation of an already-defined group
	public void ActivateGroup (String group) throws BusException;
	
	@BusMethod
	// Invite another user to join  a group
	public void Invite(String originator, String group, String descriptor) throws BusException;
	
	@BusMethod
	// Request to be added to a group
	public void AddRequest(String originator, String group) throws BusException;
	
	@BusMethod
	// Request removal from a group
	public void RemoveRequest(String originator, String group) throws BusException;
	
	@BusMethod
	// Request addition of another user to a group
	public void AddMember(String originator, String group, String member) throws BusException;
	
	@BusMethod
	// Request removal of another user from a group (may fail)
	public void RemoveMember(String originator, String group, String member) throws BusException;
	
	@BusMethod
	// Request the profile of a group member
	public String GetMemberProfile(String group, String member) throws BusException;

	
	@BusSignal
	//	Courtesy notification that user has joined group (easier processing for app)
	void JoinedGroup(String group, String member) throws BusException;
	
	@BusSignal
	//	Courtesy notification that user has left group (easier processing for app)
	void LeftGroup(String group, String member) throws BusException;
	
	@BusSignal
	//	Notification that an invitation has been accepted
	void InvitationAccepted(String group, String member) throws BusException;
	
	@BusSignal
	//	Notification that an invitation has been rejected
	void InvitationRejected(String group, String member) throws BusException;
	
	@BusSignal
	//	Notification that a group has been updated
	void GroupUpdated (String group, String member) throws BusException;
	
}
