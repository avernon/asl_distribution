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

import org.alljoyn.devmodules.APICoreImpl;

// These are the APIs available to applications for the "Groups" service
public class FileTransferAPI {
	
	
	private static int transactionId = 0;
	
	// prevent instantiation via an explicit clone() call
	public Object clone() throws CloneNotSupportedException {
		throw new CloneNotSupportedException();
	}
	
	// the interface to the background service
	private static FileTransferAPIInterface apiInterface = null;
	
	// sets up the interface to the background service
	private static void setupInterface() {
		if(apiInterface == null) {
			apiInterface = 	APICoreImpl.getInstance().getProxyBusObject("filetransfer",
					new Class[] {FileTransferAPIInterface.class}).getInterface(FileTransferAPIInterface.class);
		}
	}
		
	// register callback listener
	public static void RegisterListener(FileTransferListener listener) {
		FileTransferCallbackObject.listener = listener;
	}
	
	
	// Service-specific interfaces:
	public static void GetFile(String peer, String path) throws Exception {
		if(apiInterface == null)
			setupInterface();
		apiInterface.getFile(peer,path);
	}

	public static void OfferFile(String file, String path) throws Exception {
		if(apiInterface == null)
			setupInterface();
		apiInterface.offerFile(file, path);
	}
	
	public static void PushFile(String peer, String path) throws Exception {
		if(apiInterface == null)
			setupInterface();
		apiInterface.pushFile(peer,path);
	}
}
