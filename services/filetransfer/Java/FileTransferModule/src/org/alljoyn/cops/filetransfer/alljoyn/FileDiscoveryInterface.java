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

package org.alljoyn.cops.filetransfer.alljoyn;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusSignal;
import org.alljoyn.cops.filetransfer.data.FileDescriptor;

/**
 * The File Discovery Interface specifies the AllJoyn signals and methods that are
 * associated with file discovery. The main behaviors of this interface include:
 * file announcing, requesting file announcements from session peers, and offering 
 * files to session peers.
 * <p>
 * Note: This interface is not intended to be used directly. All of the supported
 * functionality of this library is intended to be accessed through the
 * {@link org.alljoyn.cops.filetransfer.FileTransferModule} class.
 */
@BusInterface(name="org.alljoyn.Cops.FileDiscovery")
public interface FileDiscoveryInterface
{
	/**
	 * announce()
	 * is specified as an AllJoyn signal that is used to send file announcements to session
	 * peers over AllJoyn. The signal can be a directed or global signal. The fileList parameter 
	 * denotes the list of files that are announced by the sender and are available for immediate
	 * transfer. The fileList is passed over to the AnnouncementManager to be stored.	  			 
	 * 
	 * @param fileList  specifies a list of files available for transfer
	 * @param isFileIDResponse  specifies if the announcement is in response to an offer request
	 * @throws BusException  thrown in the case of an AllJoyn error
	 */
	@BusSignal
	public void announce(FileDescriptor[] fileList, boolean isFileIDResponse) throws BusException;
	
	/**
	 * requestAnnouncement()
	 * is specified as an AllJoyn signal and allows the user to send an announcement request to a  
	 * session peer for all the files they have made available for transfer. This handler calls 
	 * handleAnnouncementRequest() on the AnnouncementManager which will insert an announce action 
	 * into the dispatcher.	  			 
	 * 
	 * @throws BusException  thrown in the case of an AllJoyn error
	 */	
	@BusSignal
	public void requestAnnouncement() throws BusException;
	
	/**
	 * requestOffer()
	 * is specified as an AllJoyn method and is used to request files that have not been explicitly
	 * announced or shared. This handler tells the announcer to handle the offer request.	  			
	 *  
	 * @param filepath  absolute path of file being requested
	 * @throws BusException  thrown in the case of an AllJoyn error
	 */
	@BusMethod
	public int requestOffer(String filepath) throws BusException;
	
	/**
	 * offerFile()
	 * is specified as an AllJoyn method and is used to send file offers to session peers. The method
	 * handler will alert the Receive Manager when an offer is received so they can respond accordingly.
	 * 
	 * @param file  file descriptor of offered file
	 * @throws BusException  thrown in the case of an AllJoyn error
	 */
	@BusMethod
	public int offerFile(FileDescriptor file) throws BusException;
}
