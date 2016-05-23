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
 * The ReceiveManagerListener is an internal listener used by the OfferManager and
 * Receiver to notify the ReceiveManager that certain events have occurred. Such
 * events include initiating a file request, handle an incoming file chunk, and 
 * handling a sender initiated 
 * <p>
 * Note: This class is not intended to be used directly. All of the supported
 * functionality of this library is intended to be accessed through the
 * {@link org.alljoyn.cops.filetransfer.FileTransferModule} class.
 */
public interface ReceiveManagerListener 
{
	/**
	 * requestFile()
	 * is triggered by the OfferManager to initiate a file request with the Receive
	 * Manage when the user accepts a file offer from a remote session peer.
	 * 
	 * @param file  specifies the file being requested
	 * @param saveFileName  specifies the name to save the file as
	 * @param saveDirectory  specifies the location to save the file
	 * @param useDispatcher  specifies whether the request should use the dispatcher
	 * @return OK or BAD_FILE_PATH
	 */
	public int requestFile(FileDescriptor file, String saveFileName, String saveDirectory, 
			boolean useDispatcher);
	
	/** 
	 * handleDataXferCancelled()
	 * is triggered when the Receiver receives a dataXferCancelled from the file receiver.
	 * This function will notify the ReceiveManager to stop sending the file matching the
	 * specified file ID.	  			 
	 * 
	 * @param fileID  specifies the ID of file being cancelled
	 * @param peer  specifies peer who cancelled the transfer
	 */
	public void handleDataXferCancelled(byte[] fileID, String peer);
	
	/** 
	 * handleFileChunk()
	 * is called when a chunk of a given file is received from a remote peer. This function determines
	 * which temporary file this chunk belongs to, updates the sending progress, and sends the chunk
	 * to the FileSystemAbstraction to be appended to the appropriate temporary file.			 
	 * 
	 * @param fileID  specifies the id of the file the chunk belongs to
	 * @param startByte  specifies the starting index of chunk relative to file
	 * @param chunkLength  specifies the length of chunk
	 * @param chunk  actual file data
	 */
	public void handleFileChunk(byte[] fileID, int startByte, int chunkLength, byte[] chunk);
}
