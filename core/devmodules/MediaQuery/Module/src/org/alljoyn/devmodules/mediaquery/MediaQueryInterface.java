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

package org.alljoyn.devmodules.mediaquery;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusSignal;
import org.alljoyn.bus.annotation.Position;
import org.alljoyn.devmodules.common.MediaIdentifier;
import org.alljoyn.devmodules.common.MediaQueryResult;


@BusInterface (name = "org.alljoyn.devmodules.mediaquery")
public interface MediaQueryInterface {

	//Generic Query Interface
	
	// Method to list photos hosted by this device
	@BusMethod (replySignature = "r")
    public  MediaQueryResult ListMedia(String mtype) throws BusException;

	// Method to get a  thumbnail from this device
	@BusMethod
    public byte[] GetThumbnail(String mtype, String filepath) throws BusException;

	// Method to get a  MediaIdentifier from this device (usually to get the metadata etc.)
	@BusMethod
    public MediaIdentifier GetMediaIdentifier(String mtype, String filepath) throws BusException;
	

	// Method to request activation of a media item on the hosting device
	@BusMethod
	public boolean RequestActivation (String requestor, String mtype, String filepath) throws BusException;
	
	// Method to 'send' a file to another device (really a request for it to copy the file)
	@BusMethod
	public void SendFileRequest (String requestor, String mtype, String filepath) throws BusException;
	
}
