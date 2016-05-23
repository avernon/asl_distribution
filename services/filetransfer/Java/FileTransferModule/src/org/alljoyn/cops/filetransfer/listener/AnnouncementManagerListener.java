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

import org.alljoyn.cops.filetransfer.data.FileDescriptor;

/**
 * The AnnouncementManagerListener is an internal listener that is used by the
 * Receiver to notify the AnnouncementManager that various events have occurred.
 * <p>
 * Note: This class is not intended to be used directly. All of the supported
 * functionality of this library is intended to be accessed through the
 * {@link org.alljoyn.cops.filetransfer.FileTransferModule} class.
 */
public interface AnnouncementManagerListener 
{
	/**
	 * handleAnnounced()
	 * is triggered by the Receiver when a normal announcement is received from
	 * a remote session peer.
	 * 
	 * @param fileList  specifies the list of announced files
	 * @param peer  specifies the peer who sent the announcement
	 */
	public void handleAnnounced(FileDescriptor[] fileList, String peer);
	
	/**
	 * handleAnnouncementRequest()
	 * is triggered by the Receiver when an announcement request is received from
	 * a remote session peer.
	 * 
	 * @param peer  specifies the peer that made the announcement request
	 */
	public void handleAnnouncementRequest(String peer);
}
