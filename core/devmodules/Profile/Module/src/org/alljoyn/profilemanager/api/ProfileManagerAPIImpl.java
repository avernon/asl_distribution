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
package org.alljoyn.profilemanager.api;

import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.SignalEmitter;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.devmodules.interfaces.ModuleAPIInterface;

public class ProfileManagerAPIImpl implements ModuleAPIInterface {
	//callback interface so that specific callback can be invoked
	//Signal emitter - so we have multiple apps that receive callback data
	
	class ProfileManagerCallbackObject implements ProfileManagerCallbackInterface, BusObject {
		public void onProfileFound(String peer) {	}

		public void onProfileLost(String peer) {	}

		public void CallbackJSON(int transactionId, String module,
				String jsonCallbackData) {
			
		}

		public void CallbackData(int transactionId, String module,
				byte[] rawData, int totalParts, int partNumber) {
			
		}
	}
	
	private ProfileManagerCallbackObject profileCallbackObject = new ProfileManagerCallbackObject();
	public static ProfileManagerCallbackInterface profileCallback; //look into possibly just folding this in with the regular imple so I don't have to static var this and link it with the ChatImpl
	
	public ProfileManagerAPIImpl() {
	}
	
	@Override
	public void connectCallbackObject(int sessionId, String joiner) {
		SignalEmitter emitter = new SignalEmitter(profileCallbackObject, sessionId, SignalEmitter.GlobalBroadcast.Off);
		profileCallback = emitter.getInterface(ProfileManagerCallbackInterface.class);
	}

	@Override
	public BusObject getBusObject() {
		return new ProfileManagerAPIObject();
	}

	@Override
	public String getBusObjectPath() {
		return ProfileManagerAPIObject.OBJECT_PATH;
	}

	@Override
	public BusObject getCallbackBusObject() {
		// TODO Auto-generated method stub
		return profileCallbackObject;
	}

	@Override
	public String getCallbackBusObjectPath() {
		// TODO Auto-generated method stub
		return profileCallbackObject.OBJECT_PATH;
	}
	
}
