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

/**
 * The File Status object is used by the File Transfer Manager and the File
 * Receive Manager to monitor the progress of files that are being sent and
 * received. From the senders perspective, the file status will show the file
 * ID of the file being transferred, the length of the file, the peer to send
 * the file to, how many bytes have already been sent, and the maximum chunk
 * length specified by the receiver. From the receivers perspective, all of 
 * same data is monitored by the receiver with a few additions. The receiver
 * also keeps track of the save file name and the save file path. This is 
 * essential so the file chunks can be appended to the correct file.  
 * <p>
 * Note: This class is not intended to be used directly. All of the supported
 * functionality of this library is intended to be accessed through the
 * {@link org.alljoyn.cops.filetransfer.FileTransferModule} class.
 */
public class FileStatus 
{
	// Member Variables
	public byte[] fileId;	
	public int startByte;	
	public int length;	
	public String peer;	
	public int numBytesSent;	
	public String saveFileName;
	public String saveFilePath;	
	public int chunkLength;
	
	/*------------------------------------------------------------------------*
     * Constructor
     *------------------------------------------------------------------------*/
	/**
	 * FileStatus()
	 * creates an instance of the FileStatus class.
	 */
	public FileStatus()
	{
		//Intentionally left blank
	}
}
