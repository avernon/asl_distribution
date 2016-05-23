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
package org.alljoyn.devmodules.common;

import org.alljoyn.bus.annotation.Position;

// Class that represents media description data

public class MediaIdentifier {

	// size in bytes
	@Position(0)
	public int    size;

	// file path on the hosting device
	@Position(1)
	public String path;

	// Location of Thumbnail/icon path, if any
	@Position(2)
	public String thumbpath;

	// (file) name, without directories
	@Position(3)
	public String name;

	// MIME type
	@Position(4)
	public String type;

	// Descriptive title (use this for UIs, not 'name')
	@Position(5)
	public String title;

	// User name/id of the source
	@Position(6)
	public String userid;

	// Media type (see MediaQueryConstants)
	@Position(7)
	public String mediatype;

	// path where file is stored on local device (not remote/source device)
	@Position(8)
	public String localpath;

	// Timestamp associated with Item action
	@Position(9)
	public long timestamp;
	
	@Position(10)
	public int transactionId;

	
	public MediaIdentifier(){
		size = 0;
		path = "";
		thumbpath = "";
		name = "";
		type = "";
		title = "";
		userid = "";
		mediatype = "";
		localpath = "";
		timestamp = 0;
		transactionId = 0;
	}
}
