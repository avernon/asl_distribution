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
 * The SendManager Listener is an internal listener that is used by the OfferManager,
 * the bus object, and the Receiver to notify the SendManager that various events 
 * have occurred.  
 * <p>
 * Note: This class is not intended to be used directly. All of the supported
 * functionality of this library is intended to be accessed through the
 * {@link org.alljoyn.cops.filetransfer.FileTransferModule} class.
 */
public interface SendManagerListener 
{
	/**
	 * sendFile()
	 * is triggered by the bus object or the Offer Manager to notify the Send
	 * Manager to begin sending the file matching the specified file ID.
	 * 
	 * @param fileID  specifies the fileId of the file the data belongs to
	 * @param startByte  specifies the starting byte of the chunk relative to the file
	 * @param length  specifies the length of data chunk
	 * @param peer  specifies the peer to send the file to
	 * @param maxChunkLength  specifies the maximum chunk size
	 * @return OK or BAD_FILE_ID
	 */
	public int sendFile(byte[] fileID, int startByte, int length, String peer, int maxChunkLength);
	
	/**
	 * dataSent()
	 * is triggered by the dispatcher when a data chunk action has been 
	 * sent to the transmitter and to notify the Send Manager to queue the
	 * next data chunk if available.
	 */
	public void dataSent();
	
	/**
	 * handleStopDataXfer()
	 * is triggered by the Receiver when a stopDataXfer signal is received from the
	 * file receiver. This callback notifies the Send Manager to stop sending the file
	 * matching the specified file ID.
	 * 
	 * @param fileID  specifies the ID of the file
	 * @param peer  specifies the peer receiving the file
	 */
	public void handleStopDataXfer(byte[] fileID, String peer);
}
