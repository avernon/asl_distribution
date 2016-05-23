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
import org.alljoyn.devmodules.common.GroupDescriptor;
import org.alljoyn.devmodules.common.GroupListDescriptor;
import org.alljoyn.devmodules.common.ProfileDescriptor;
import org.alljoyn.storage.ProfileCache;

import android.util.Log;

public class GroupsObject implements GroupsInterface, BusObject {

	private static GroupManager mGroupManager = GroupManager.getInstance();
	private static GroupsImpl   mGroupsImpl = GroupsImpl.getInstance();
	private static String       mMyId = "";

	private static final String TAG = "GroupsObject"; 

	// routine to initialise if necessary
	// Note that these methods can be called from various threads, so there's no guarantee
	// that static initialisation has been done, so call this just to be safe
	private static void init(){
		if (mGroupManager==null) mGroupManager = GroupManager.getInstance();
		if (mGroupsImpl==null)   mGroupsImpl = GroupsImpl.getInstance();
		if ((mMyId==null) || (mMyId.length()==0)) mMyId = mGroupsImpl.getId();
	}

	@Override
	public String[] GetGroupList() throws BusException {
		init();
		return GroupManager.getActiveGroupList();
	}

	@Override
	public String GetGroupListDescriptor() throws BusException {
		init();
		return GroupManager.getGroupListDescriptor().toString();
	}

	@Override
	public String GetGroupDescriptor(String group) throws BusException {
		String gdesc=ProfileDescriptor.EMPTY_PROFILE_STRING;
		// check that requestor is part of group (weak security)
		try{
			init();
			//mGroupsImpl.getSessionManager().getBusAttachment().enableConcurrentCallbacks();
			MessageContext mcontext ;
			mcontext = mGroupsImpl.getSessionManager().getBusAttachment().getMessageContext();
			String requestor = mcontext.sender;
			String reqid = GroupSessionManager.getMemberFromBusId(requestor);
			Log.v(TAG, "GetMemberProfile() Requestor="+requestor+" Member="+reqid);

			// check that requested ID is part of group (more weak security)
			if (GroupManager.isMember(group, reqid)){
				gdesc = GroupManager.getGroupDescriptor(group).toString();
			} else {
				Log.w(TAG, "Requesting member ("+reqid+") not part of group: "+group);
			}

		} catch (Exception e){
			Log.e(TAG, "GetGroupDescriptor(). Error processing message context: "+e.toString());
		}
		return gdesc;
	}

	@Override
	public void ActivateGroup(String group) throws BusException {
		init();
		// TODO Auto-generated method stub

	}

	@Override
	public void Invite(String originator, String group, String descriptor) throws BusException {
		init();
		// For now, just accept the invitation if it's valid
		
		Log.v(TAG, "Invite("+originator+", "+group+")");
		if (!GroupManager.isDefined(group)){
			GroupDescriptor gd = new GroupDescriptor();
			gd.setString(descriptor);
			GroupManager.addGroup(group, gd);
			mGroupsImpl.getInterface().InvitationAccepted(group, mMyId);
			mGroupsImpl.scanGroups(group, originator);
		} else {
			Log.e(TAG, "Invite() Error, group already exists: "+group);
			mGroupsImpl.getInterface().InvitationRejected(group, mMyId);
		}

	}

	@Override
	public void AddRequest(String originator, String group) throws BusException {
		init();
		// TEMP: just accept any request for now
		String[] mlist = new String[1];
		mlist[0] = originator;
		GroupManager.addMembers(group, mlist);
		mGroupsImpl.scanGroups(group, originator);
	}

	@Override
	public void RemoveRequest(String originator, String group) throws BusException {
		init();
		// TEMP: just accept any request for now
		String[] mlist = new String[1];
		mlist[0] = originator;
		GroupManager.removeMembers(group, mlist);
		mGroupsImpl.scanGroups(group, originator);
	}

	@Override
	public void AddMember(String originator, String group, String member) throws BusException {
		init();
		String[] mlist = new String[1];
		mlist[0] = member;
		GroupManager.addMembers(group, mlist);
		mGroupsImpl.scanGroups(group, originator);
	}

	@Override
	public void RemoveMember(String originator, String group, String member) throws BusException {
		init();
		String[] mlist = new String[1];
		mlist[0] = member;
		GroupManager.removeMembers(group, mlist);
		mGroupsImpl.scanGroups(group, originator);
	}

	@Override
	public String GetMemberProfile(String group, String member) throws BusException {
		String profile="{}";
		// check that requestor is part of group (weak security)
		try{
			init();
			//mGroupsImpl.getSessionManager().getBusAttachment().enableConcurrentCallbacks();
			MessageContext mcontext ;
			mcontext = mGroupsImpl.getSessionManager().getBusAttachment().getMessageContext();
			String requestor = mcontext.sender;
			String reqid = GroupSessionManager.getMemberFromBusId(requestor);
			Log.v(TAG, "GetMemberProfile() Requestor="+requestor+" Member="+reqid);

			// check that requested ID is part of group (more weak security)
			if (GroupManager.isMember(group, member)){
				if (GroupManager.isMember(group, reqid)){

					// retrieve profile from cache
					if (ProfileCache.isPresent(ProfileCache.getProfilePath(member))){
						profile = ProfileCache.getProfile(member).toString();
					}
				} else {
					Log.w(TAG, "Requesting member ("+reqid+") not part of group: "+group);
				}
			} else {
				Log.w(TAG, "Requested member ("+member+") not part of group: "+group);
			}

		} catch (Exception e){
			Log.e(TAG, "GetMemberProfile(). Error processing message context: "+e.toString());
		}
		return profile;
	}

	@Override
	public short GetPortNumber(String group) throws BusException {
		short port=-1;
		// check that requestor is part of group (weak security, since they can add themselves)
		init();

		port = GroupSessionManager.getSessionPort(group);
		Log.d(TAG, "GetPortNumber("+group+"): "+port);
		return port;
	}

	/******************************************************************
	 ** Blank templates for Signals (handlers are in the Impl class) **
	 ******************************************************************/
	@Override
	public void JoinedGroup(String group, String member) throws BusException {}

	@Override
	public void LeftGroup(String group, String member) throws BusException {}

	@Override
	public void InvitationAccepted(String group, String member) throws BusException {}

	@Override
	public void InvitationRejected(String group, String member) throws BusException {}

	@Override
	public void GroupUpdated(String group, String member) throws BusException {}

}
