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

package org.alljoyn.cops.filetransfer.data;

import java.util.ArrayList;

/**
 * The action class defines the different action types that tell the
 * Transmitter which action needs to be taken. This class defines an
 * enumerated type that defines 10 different actions. This class
 * also includes an array of objects because different actions require
 * different parameters to execute the action and the data types vary
 * dramatically. Lastly, the action object contains a variable for peer.
 * This variable tells the Transmitter who to send the signal to or
 * perform a method call on their proxy bus object.
 * <p>
 * Note: the peer will be set to null only when a global signal will
 * be sent to all session peers.
 * <p> 
 * Note: This class is not intended to be used directly. All of the supported
 * functionality of this library is intended to be accessed through the
 * {@link org.alljoyn.cops.filetransfer.FileTransferModule} class.
 */
public class Action 
{
	// Class Enumerator
	public enum ActionType 
	{ 
		ANNOUNCE, 
		REQUEST_ANNOUNCE, 
		REQUEST_OFFER, 
		REQUEST_DATA,
		DATA_CHUNK,
		OFFER_FILE,
		STOP_XFER,
		XFER_CANCELLED,
		FILE_ID_RESPONSE,
		SHUTDOWN_THREAD
	}; 
	
	// Member Variables
	public ActionType actionType;
	public ArrayList<Object> parameters;
	public String peer;
	
	/*------------------------------------------------------------------------*
     * Constructor
     *------------------------------------------------------------------------*/
	/**
	 * Action()
	 * creates an instance of the action class and provides initial values for
	 * all member variables.
	 */
	public Action()
	{
		this.actionType = ActionType.ANNOUNCE;
		this.parameters = new ArrayList<Object>();
		this.peer = null;
	}
}
