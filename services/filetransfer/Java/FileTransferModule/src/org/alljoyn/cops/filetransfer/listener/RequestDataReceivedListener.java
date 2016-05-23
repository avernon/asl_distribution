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

package org.alljoyn.cops.filetransfer.listener;

/**
 * The RequestDataListener is an optional listener that the developer can implement
 * so it can be notified when a file has been requested by a session peer. This
 * listener is not mandatory and will not impede file transfer functionality if not
 * implemented.
 * <p>
 * See {@link org.alljoyn.cops.filetransfer.FileTransferModule#setRequestDataReceivedListener}
 */
public interface RequestDataReceivedListener 
{
	/**
	 * fileRequestReceived()
	 * is triggered to notify the user when a file request is received.
	 * 
	 * @param fileName  specifies the name of the file being requested
	 */
	public void fileRequestReceived(String fileName);
}
