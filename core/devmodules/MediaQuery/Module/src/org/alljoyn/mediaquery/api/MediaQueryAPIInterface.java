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
package org.alljoyn.mediaquery.api;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.annotation.*;

@BusInterface(name = "org.alljoyn.api.devmodules.mediaquery")
public interface MediaQueryAPIInterface {
	// Initiate (background) collection of media available. The return value is the transaction ID
	@BusMethod
    public  void CollectMediaList(int transactionId, String service, String mtype) throws BusException;
 
	@BusMethod
    public  void CollectMyMediaList(int transactionId, String mtype) throws BusException;
	
    // Request copying of file from remote device
	@BusMethod
    public  int RequestMedia(int transactionId, String service, String mtype, String path) throws BusException;
	
	@BusMethod
    public  int RequestMyMedia(int transactionId, String service, String mtype, String path) throws BusException;
   
    // Request Activation of file on remote device
	@BusMethod
	public void RequestActivation (int transactionId, String peer, String mtype, String path) throws BusException;
	
	// Method to 'send' a file to another device (really a request for it to copy the file)
	@BusMethod
	public void SendFileRequest (String service, String mtype, String filepath) throws BusException;

}
