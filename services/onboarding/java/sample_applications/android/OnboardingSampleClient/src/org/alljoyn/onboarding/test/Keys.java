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

package org.alljoyn.onboarding.test;

/**
 * This class provides all the intent actions and
 * extras that the onboarding application can send.
 */
public class Keys {

	class Actions {

		/**
		 * An action indicating an error has occurred.
		 * Has an extra string called Keys.Extras.EXTRA_ERROR provides the error msg.
		 */
		public static final String ACTION_ERROR = "ACTION_ERROR";
		
		/**
		 * An action indicating a new device was found.
		 * Has an extra string called Keys.Extras.EXTRA_DEVICE_ID provides the device id.
		 */
		public static final String ACTION_DEVICE_FOUND = "ACTION_DEVICE_FOUND";
		
		/**
		 * An action indicating a device was lost.
		 * Has an extra string called Keys.Extras.EXTRA_BUS_NAME provides the device bus name.
		 */
		public static final String ACTION_DEVICE_LOST = "ACTION_DEVICE_LOST";
		
		/**
		 * An action indicating we are connected to a network. Has an extra string
		 * called Keys.Extras.EXTRA_NETWORK_SSID provides the network ssid.
		 * Id we are connecting/connected to a network, the EXTRA_NETWORK_SSID indicates that.
		 */
		public static final String ACTION_CONNECTED_TO_NETWORK = "ACTION_CONNECTED_TO_NETWORK";

		/**
		 * An action indicating the password we gave do not match to the device password. 
		 */
		public static final String ACTION_PASSWORD_IS_INCORRECT = "ACTION_PASSWORD_IS_INCORRECT";
	}
	
	class Extras {
		
		/**
		 * The lookup key for a String object indicating the error message that occurred.
		 * Retrieve with getStringExtra(String).
		 */
		public static final String EXTRA_ERROR = "extra_error";
		
		/**
		 * The lookup key for a String object indicating a device id.
		 * Retrieve with intent.getExtras().getString(String).
		 * To get the device itself call getApplication().getDevice(String);
		 */
		public static final String EXTRA_DEVICE_ID = "extra_deviceId";
		
		/**
		 * The lookup key for a String object indicating a device bus name.
		 * Retrieve with getExtras().getString(String).
		 */
		public static final String EXTRA_BUS_NAME = "extra_BusName";
		
		/**
		 * The lookup key for a String object indicating the network ssid to which we are connected.
		 * Retrieve with intent.getStringExtra(String).
		 */
		public static final String EXTRA_NETWORK_SSID = "extra_network_ssid";
		
	}
	
}
