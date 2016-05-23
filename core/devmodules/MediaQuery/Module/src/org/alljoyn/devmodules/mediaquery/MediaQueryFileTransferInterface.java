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


import org.alljoyn.bus.BusException;
import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.devmodules.common.FileBuffer;
import org.alljoyn.devmodules.common.FileParameters;

// This interface allows the copying of potentially large files between devices
// It is assumed that the requesting side has knowledge of the file location obtained elsewhere
// The basic sequence is:
// - open the file
// - get the transfer parameters (file size, buffer size etc.)
// - iterate, requesting one buffer at a time
// - close the file

@BusInterface (name = "org.alljoyn.devmodules.mediaquery.filetransfer")
public interface MediaQueryFileTransferInterface {

	// Method to open a file. 
	// Positive return value is a file identifier (in case a client has multiple active transfers)
	// Negative return value indicates an error occurred
	@BusMethod
    public int Open (String filename) throws BusException;

	// Method to get the transfer parameters
	@BusMethod (replySignature = "r")
    public FileParameters GetFileParameters (int fileid) throws BusException;

	// Method to get a buffer. Sequence number is supplied by the caller and should be incremented
	// every time a new buffer is requested.
	// the sender will only process the current (maybe a retransmission) or next sequence number
	@BusMethod (replySignature = "r")
    public FileBuffer GetBuffer(int fileid, int seqnum) throws BusException;

	// Method to close the file being transferred
	@BusMethod
    public int Close(int fileid) throws BusException;

	// Method to abort a file transfer
	@BusMethod
    public void Abort(int fileid) throws BusException;

	// Method to abort all file transfers
	@BusMethod
    public void AbortAll() throws BusException;

}
