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
package org.alljoyn.groups.api;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.annotation.*;
import org.alljoyn.devmodules.common.GroupDescriptor;

// AllJoyn interface from app to background service
@BusInterface(name = "org.alljoyn.api.devmodules.groups")
public interface GroupsAPIInterface {
	
	@BusMethod
	// Get the list of groups currently supported
	public String [] GetGroupList() throws BusException;
	
	@BusMethod
	// Get the list of groups currently supported (in GroupListDescriptor format)
	public String GetGroupListDescriptor() throws BusException;
	
	
	@BusMethod
	public String GetGroupDescriptor(String group) throws BusException;

	@BusMethod
	public void AddGroup(String group, String descriptor) throws BusException;
	
	@BusMethod
	public void RemoveGroup(String group) throws BusException;
	
	@BusMethod
	public void SaveGroup(String group) throws BusException;
	
	@BusMethod
	public void DeleteGroup(String group) throws BusException;
	
	@BusMethod
	public void EnableGroup(String group) throws BusException;
	
	@BusMethod
	public void DisableGroup(String group) throws BusException;
	
	@BusMethod
	public boolean IsGroupEnabled(String group) throws BusException;
	
	@BusMethod
	public boolean IsGroupActive(String group) throws BusException;
	
	@BusMethod
	public boolean IsGroupDefined(String group) throws BusException;
	
	@BusMethod
	public void AddMembers(String group, String[] members) throws BusException;
	
	@BusMethod
	public void RemoveMembers(String group, String[] members) throws BusException;
	
	@BusMethod
	public String[] GetAllMembers(String group) throws BusException;
	
	@BusMethod
	public String[] GetActiveMembers(String group) throws BusException;
	
	@BusMethod
	public String[] GetInactiveMembers(String group) throws BusException;
	
	@BusMethod
	public String[] GetRemovedMembers(String group) throws BusException;

	@BusMethod
	public boolean IsMemberActive(String group, String member) throws BusException;
	
	@BusMethod
	public void InviteMembers(String group, String[] members) throws BusException;
	
	@BusMethod
	public void AcceptInvitation(String group) throws BusException;
	
	@BusMethod
	public void RejectInvitation(String group) throws BusException;
	
	@BusMethod
	public void IgnoreInvitation(String group) throws BusException;
	
	
	
	/**
	 * Runs verification tests on groups
	 * Result returned via callback interface
	 */
	@BusMethod
	public void RunGroupsTest() throws BusException;

}
