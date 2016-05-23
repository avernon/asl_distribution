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
package org.alljoyn.notify.api;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.SignalEmitter;
import org.alljoyn.bus.annotation.BusSignal;
import org.alljoyn.devmodules.common.NotificationData;
import org.alljoyn.devmodules.interfaces.ModuleAPIInterface;

public class NotifyAPIImpl implements ModuleAPIInterface {
	//callback interface so that specific callback can be invoked
	//Signal emitter - so we have multiple apps that receive callback data
	
	class ThisNotifyCallbackObject implements NotifyCallbackInterface, BusObject {
		public void CallbackJSON(int transactionId, String module,
				String jsonCallbackData) {
			
		}

		public void CallbackData(int transactionId, String module,
				byte[] rawData, int totalParts, int partNumber) {
			
		}

		public void onNotification(String peer, NotificationData msg)
				throws BusException {
			
		}		
	}
	
	private ThisNotifyCallbackObject callbackObject = new ThisNotifyCallbackObject();
	public static NotifyCallbackInterface callback; //look into possibly just folding this in with the regular impl so I don't have to static var this and link it with the ChatImpl
	
	public NotifyAPIImpl() {
	}

	@Override
	public void connectCallbackObject(int sessionId, String joiner) {
		//System.out.println("Connected callback object so we should be able to broadcast a callback signal");
		SignalEmitter emitter = new SignalEmitter(callbackObject, sessionId, SignalEmitter.GlobalBroadcast.Off);
		callback = emitter.getInterface(NotifyCallbackInterface.class);
	}

	@Override
	public BusObject getBusObject() {
		return new NotifyAPIObject();
	}

	@Override
	public String getBusObjectPath() {
		return NotifyAPIObject.OBJECT_PATH;
	}

	@Override
	public BusObject getCallbackBusObject() {
		// TODO Auto-generated method stub
		return callbackObject;
	}

	@Override
	public String getCallbackBusObjectPath() {
		// TODO Auto-generated method stub
		return callbackObject.OBJECT_PATH;
	}
	
}
