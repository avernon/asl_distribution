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
package org.alljoyn.devmodules.loader;


import org.alljoyn.api.filetransfer.FileTransferAPIImpl;
import org.alljoyn.chat.api.ChatAPIImpl;
import org.alljoyn.groups.api.GroupsAPIImpl;
import org.alljoyn.mediaquery.api.MediaQueryAPIImpl;
import org.alljoyn.notify.api.NotifyAPIImpl;
import org.alljoyn.profilemanager.api.ProfileManagerAPIImpl;
import org.alljoyn.remotecontrol.api.RemoteControlAPIImpl;
import org.alljoyn.devmodules.filetransfer.FileTransferImpl;
import org.alljoyn.devmodules.api.ModuleAPIManager;
import org.alljoyn.devmodules.debug.api.DebugAPIImpl;
import org.alljoyn.devmodules.chat.ChatImpl;
import org.alljoyn.devmodules.debug.DebugImpl;
import org.alljoyn.devmodules.groups.GroupsImpl;
import org.alljoyn.devmodules.mediaquery.MediaQueryImpl;
import org.alljoyn.devmodules.notify.NotifyImpl;
import org.alljoyn.devmodules.profilemanager.ProfileManagerImpl;
import org.alljoyn.devmodules.remotecontrol.RemoteControlImpl;
import org.alljoyn.devmodules.service.AllJoynContainer;
import org.alljoyn.devmodules.whiteboard.WhiteboardImpl;
import org.alljoyn.whiteboard.api.WhiteboardAPIImpl;

import android.content.Context;

public class ContainerLoader {
	private static final String TAG = "ContainerLoader";
	
	//----------------
	
	public static void LoadAPIImpl(ModuleAPIManager instance) {
		instance.moduleList.add(new GroupsAPIImpl());
	    instance.moduleList.add(new ProfileManagerAPIImpl());
	    instance.moduleList.add(new FileTransferAPIImpl());
	    instance.moduleList.add(new MediaQueryAPIImpl());
		instance.moduleList.add(new ChatAPIImpl());
	    instance.moduleList.add(new RemoteControlAPIImpl());
	    instance.moduleList.add(new DebugAPIImpl());
	    instance.moduleList.add(new NotifyAPIImpl());
	    instance.moduleList.add(new WhiteboardAPIImpl());
	}
	
	public static void LoadImpl(AllJoynContainer instance, Context context) {
		instance.modules.add(new GroupsImpl(instance));
		instance.modules.add(new ProfileManagerImpl(instance, context));
		instance.modules.add(new FileTransferImpl(instance));
		instance.modules.add(new MediaQueryImpl(instance, context));
		instance.modules.add(new ChatImpl(instance));
		instance.modules.add(new RemoteControlImpl(instance));
		instance.modules.add(new DebugImpl(instance, context));
		instance.modules.add(new NotifyImpl(instance, context));
		instance.modules.add(new WhiteboardImpl(instance));
	}
	
}
