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
package org.alljoyn.devmodules.api.filetransfer;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.annotation.BusSignal;
import org.alljoyn.bus.annotation.BusSignalHandler;

import org.alljoyn.devmodules.APICore;
import org.alljoyn.devmodules.callbacks.CallbackObjectBase;
import org.alljoyn.devmodules.callbacks.TransactionHandler;
import org.alljoyn.devmodules.common.MediaIdentifier;

import android.util.Log;

// This class maps signals from the background service to callbacks to the app
// In general, each method handles a Signal from the background service and calls
// the corresponding Listener callback method

public class FileTransferCallbackObject extends CallbackObjectBase implements FileTransferCallbackInterface, BusObject {
	static FileTransferListener listener;

	// Generic callbacks
	@BusSignalHandler(iface=FileTransferCallbackInterface.SERVICE_NAME, signal="CallbackJSON")
	public void CallbackJSON(int transactionId, String module,
			String jsonCallbackData) {
		APICore.getInstance().EnableConcurrentCallbacks();
		Integer key = Integer.valueOf(transactionId);
		if(transactionList.containsKey(key)) {
			TransactionHandler th = transactionList.get(key);
			th.HandleTransaction(jsonCallbackData, null, 0, 0);
		}
	}
	
	@BusSignalHandler(iface=FileTransferCallbackInterface.SERVICE_NAME, signal="CallbackData")
	public void CallbackData(int transactionId, String module,
			byte[] rawData, int totalParts, int partNumber) {
		APICore.getInstance().EnableConcurrentCallbacks();
		Integer key = Integer.valueOf(transactionId);
		if(transactionList.containsKey(key)) {
			TransactionHandler th = transactionList.get(key);
			th.HandleTransaction(null, rawData, totalParts, partNumber);
		}
	}
	
	@Override
	public String getObjectPath() {
		return this.OBJECT_PATH;
	}

	
	// Service-specific signal handlers/callbacks:
	@BusSignalHandler(iface=FileTransferCallbackInterface.SERVICE_NAME, signal="onTransferComplete")
	public void onTransferComplete(String service, String path, String mtype, String localpath) throws BusException {
		APICore.getInstance().EnableConcurrentCallbacks();
		if(listener != null)
			listener.onTransferComplete(service, path, mtype, localpath);
	}

	@BusSignalHandler(iface=FileTransferCallbackInterface.SERVICE_NAME, signal="onFileOffered")
	public void onFileOffered(String peer, String filename, String path)
			throws BusException {
		APICore.getInstance().EnableConcurrentCallbacks();
		if(listener != null)
			listener.onFileOffered(peer, filename, path);
	}	
}
