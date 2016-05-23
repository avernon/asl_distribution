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
 * The OfferListener is an internal listener that is used by the File Transfer
 * Bus Object to see if there are any pending offers that are awaiting response
 * from a remote session peer. This listener is also used to respond to offers
 * received from remote session peers. 
 * <p>
 * Note: This class is not intended to be used directly. All of the supported
 * functionality of this library is intended to be accessed through the
 * {@link org.alljoyn.cops.filetransfer.FileTransferModule} class.
 */
public interface OfferManagerListener
{
	/**
	 * handleFileRequest()
	 * is triggered by the bus object to notify the Offer Manager that a file
	 * request has been received that is in response to a pending offer.
	 * 
	 * @param fileID  file ID of the file being requested
	 * @param startByte  starting byte of the request relative to the file
	 * @param length  length of request in bytes
	 * @param peer  specifies the peer making the file request
	 * @param maxChunkLength  specifies the max chunk size
	 * @return OK or BAD_FILE_ID
	 */
	public int handleFileRequest(byte[] fileID, int startByte, int length,
			String peer, int maxChunkLength);
	
	/**
	 * handleOffer()
	 * is triggered by the bus object to notify the Offer Manager when a file offer
	 * has been received from a remote session peer.
	 * 
	 * @param file  specifies the file descriptor for the file being offered
	 * @param peer  specifies the peer offering the file
	 * @return OFFER_ACCEPTED or OFFER_REJECTED
	 */
	public int handleOffer(FileDescriptor file, String peer);
	
	/**
	 * isOfferPending()
	 * is triggered by the bus object to query the Offer Manager to see if
	 * the file ID from the most recent file request matches the file ID for
	 * a pending offer. 
	 * 
	 * @param fileID  specifies the file ID of the file being requested
	 * @return boolean
	 */
	public boolean isOfferPending(byte[] fileID);
}
