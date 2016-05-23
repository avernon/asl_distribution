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
package org.alljoyn.api.filetransfer;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.SignalEmitter;
import org.alljoyn.bus.annotation.BusSignal;
import org.alljoyn.devmodules.interfaces.ModuleAPIInterface;

public class FileTransferAPIImpl implements ModuleAPIInterface {
	//callback interface so that specific callback can be invoked
	//Signal emitter - so we have multiple apps that receive callback data
	
	class FileTransferCallbackObject implements FileTransferCallbackInterface, BusObject {

		public void CallbackJSON(int transactionId, String module,
				String jsonCallbackData) {
			
		}

		public void CallbackData(int transactionId, String module,
				byte[] rawData, int totalParts, int partNumber) {
			
		}
		//These methods are blank and only used because they must be added
		//in order to invoke signals

		public void onTransferComplete(String service, String path,
				String mtype, String localpath) throws BusException {
			
		}

		public void onFileOffered(String peer, String filename, String path)
				throws BusException {
			
		}
	}
	
	private FileTransferCallbackObject callbackObject = new FileTransferCallbackObject();
	public static FileTransferCallbackInterface callback; //look into possibly just folding this in with the regular impl so I don't have to static var this and link it with the ChatImpl
	
	public FileTransferAPIImpl() {
	}

	@Override
	public void connectCallbackObject(int sessionId, String joiner) {
		SignalEmitter emitter = new SignalEmitter(callbackObject, sessionId, SignalEmitter.GlobalBroadcast.Off);
		callback = emitter.getInterface(FileTransferCallbackInterface.class);
	}

	//Standard do not alter
	@Override
	public BusObject getBusObject() {
		return new FileTransferAPIObject();
	}

	@Override
	public String getBusObjectPath() {
		return FileTransferAPIObject.OBJECT_PATH;
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
