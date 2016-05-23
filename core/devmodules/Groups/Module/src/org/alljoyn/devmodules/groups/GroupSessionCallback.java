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

import java.util.ArrayList;
import java.util.HashMap;

import org.alljoyn.devmodules.sessionmanager.SessionManager;
import org.alljoyn.devmodules.common.GroupDescriptor;
import org.alljoyn.devmodules.common.GroupListDescriptor;
import org.alljoyn.devmodules.common.Utilities;
import org.alljoyn.storage.GroupCache;

import android.util.Log;



public interface GroupSessionCallback {
	
	// called when another member joins the hosted group session 
	// @param group The name of the group
	// @param member The ID of the user that joined
	public void onMemberJoined (String group, String member);
	
	// called when another member leaves the hosted group session 
	// @param group The name of the group
	// @param member The ID of the user that left
	public void onMemberLeft   (String group, String member);
	
	// Called when a group session that we had joined ends (probably unexpectedly)
	// @param group The name of the group
	// @param member The ID of the user hosting the session
	public void onSessionEnded (String group, String member);
} // GroupSessionCallback
