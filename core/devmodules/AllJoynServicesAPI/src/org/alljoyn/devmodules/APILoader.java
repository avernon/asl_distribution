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
package org.alljoyn.devmodules;

import org.alljoyn.remotecontrol.api.RemoteControlCallbackObject;
import org.alljoyn.devmodules.api.debug.DebugCallbackObject;
import org.alljoyn.devmodules.api.mediaquery.MediaQueryCallbackObject;
import org.alljoyn.devmodules.api.profilemanager.ProfileManagerCallbackObject;
import org.alljoyn.devmodules.api.filetransfer.FileTransferCallbackObject;
import org.alljoyn.devmodules.api.groups.GroupsCallbackObject;
import org.alljoyn.whiteboard.api.WhiteboardCallbackObject;
import org.alljoyn.chat.api.*;
import org.alljoyn.notify.api.*;

public class APILoader {
	private static final String TAG = "APILoader";
	
	//----------------
	
	public static void LoadAPI(APICore instance) {
		instance.objectList.clear();
		instance.objectList.add(new ProfileManagerCallbackObject());
		instance.objectList.add(new FileTransferCallbackObject());
		instance.objectList.add(new ChatCallbackObject());
		instance.objectList.add(new MediaQueryCallbackObject());
		instance.objectList.add(new GroupsCallbackObject());
		instance.objectList.add(new RemoteControlCallbackObject());
		instance.objectList.add(new DebugCallbackObject());
		instance.objectList.add(new NotifyCallbackObject());
		instance.objectList.add(new WhiteboardCallbackObject());
	}
	
}
