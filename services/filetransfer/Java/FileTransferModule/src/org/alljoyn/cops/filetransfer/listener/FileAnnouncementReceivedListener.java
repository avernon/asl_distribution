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
 * The FileAnnouncementReceivedListener can be utilized so the developer is notified
 * that an array of announced files has been received from a session peer. This
 * listener is entirely optional but is necessary if the developer wishes to
 * be able to send announcement requests to session peers. 
 * <p>
 * See {@link org.alljoyn.cops.filetransfer.FileTransferModule#setFileAnnouncementReceivedListener}
 */
public interface FileAnnouncementReceivedListener
{
	/**
	 * receivedAnnouncement()
	 * is triggered when an announcement is received and notifies the user
	 * which files are now available.
	 * 
	 * @param fileList  array of files available for transmission
	 * @param isFileIdResponse  indicates whether the announcement received is in response to a file offer request
	 */
	public void receivedAnnouncement(FileDescriptor[] fileList, boolean isFileIdResponse);	
}
