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
package org.alljoyn.devmodules.debug;

// Class for holding global data for the Debug service
public class DebugGlobalData {

	// Flag indicating whether service is enabled or not
	public static boolean   mIsEnabled  = false;
	
	// Filter string for logging (OS-specific)
	public static String    mFilter     = "AndroidRuntime:E dalvikvm:E *:D";
	
	// Object for accessing Debug implementation
	public static DebugImpl mDebugImpl  = null;
	
	// The list of (local) debug information
	public static LocalDebugList mDebugList = null;
	
	// The list of (remote) debug information
	public static RemoteDebugList mRemoteDebugList = null;
	
	// Name of service being advertised
	public static String    mServiceName = "";
	
}
