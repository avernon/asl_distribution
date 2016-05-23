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
package org.alljoyn.aroundme.MainApp;

import org.alljoyn.aroundme.Debug.DebugFunctionsFragment;
import org.alljoyn.aroundme.Peers.NearbyUsersPagerFragment;
import org.alljoyn.aroundme.Peers.PeerDetailsFragment;

import android.os.Bundle;

/**
 * This interface is used by Fragments to interact with other fragments via the main application.
 * This is because fragments can't really communicate directly and Intents don't seem to work consistently
 * @author pprice
 *
 */
public interface TaskControlInterface {
	
	/**
	 * Inner class to hold constants. It's just done this way to make the scope look correct 
	 * and allow multiple files to access the same constants
	 */
	public class Functions {
		public static final int HOME                    =  0 ;
		public static final int ABOUT                   =  1 ;
		public static final int SETTINGS                =  2 ;
		public static final int NEARBY_USERS            =  3 ;
		public static final int USER_DETAILS            =  4 ;
		public static final int USER_SPECIFIC_FUNCTIONS =  5 ;
		public static final int DEBUG_FUNCTIONS         =  6 ;
		public static final int TRANSACTIONS            =  7 ;
		public static final int MANAGE_GROUPS           =  8 ;
		public static final int CHAT                    =  9 ;
		public static final int NOTIFICATIONS           = 10 ;
		public static final int WHITEBOARD              = 11 ;
	}
	
	/**
	 * Start a 'function', which is just a logical thing
	 * @param function the id (see class Functions) that identifies the function
	 * @param args a Bundle containing data to pass to the function (can be null)
	 */
	public void startFunction (int function, Bundle args);
}
