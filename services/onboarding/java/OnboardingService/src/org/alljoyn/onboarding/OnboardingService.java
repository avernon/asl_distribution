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

package org.alljoyn.onboarding;

import org.alljoyn.bus.BusAttachment;
import org.alljoyn.onboarding.client.OnboardingClient;
import org.alljoyn.services.common.ServiceAvailabilityListener;

/**
 * An interface for both Onboarding client (onboarder) and server (onboardee). 
 */
public interface OnboardingService 
{
	/**
	 * SDK version
	 */
	public static final int PROTOCOL_VERSION = 1;

	/**
	 * Enumeration of authentication types
     * -3 - wpa2_auto, onboardee should try WPA2_TKIP and WPA2_CCMP
	 * -2 - wpa_auto, onboardee should try WPA_TKIP and WPA_CCMP
	 * -1 - any, The onboardee chooses the authentication
	 * 0 - Open Personal AP is open 
	 * 1 - WEP
	 * 2 - WPA_TKIP
	 * 3 - WPA_CCMP
	 * 4 - WPA2_TKIP
	 * 5 - WPA2_CCMP
	 * 6 - WPSS
	 */
	public static enum AuthType {
		WPA2_AUTO ((short)-3),
		WPA_AUTO ((short)-2),
		ANY ((short)-1),
		OPEN ((short)0),
		WEP ((short)1),
		WPA_TKIP ((short)2),
		WPA_CCMP ((short)3),
		WPA2_TKIP ((short)4), 
	    WPA2_CCMP ((short)5),
		WPS ((short)6);

		/**
		 * Type id
		 */
		private short id;
		
		/**
		 * Constructor
		 * @param id
		 */
		private AuthType(short id) {
			this.id = id;
		}
		
		/**
		 * Returns the id of authentication type
		 * @return id of authentication type
		 */
		public short getTypeId() {
			return id;
		}
		
		/**
		 * Search for authentication type with the given Id. If not found returns NULL
		 * @param typeId type id
		 * @return authentication type
		 */
		public static AuthType getAuthTypeById(short typeId) {
			AuthType retType = null;
			for (AuthType type : AuthType.values()) {
				if ( typeId == type.getTypeId() ) {
					retType = type;
					break;
				}
			}
			return retType;
		}
		
	}

	/**
	 * Enumeration of onboarding state
	 * 0 - Personal AP Not Configured
	 * 1 - Personal AP Configured/Not Validated
	 * 2 - Personal AP Configured/Validating
	 * 3 - Personal AP Configured/Validated
	 * 4 - Personal AP Configured/Error
	 * 5 - Personal AP Configured/Retry
	*/
	public static enum OnboardingState {

		PERSONAL_AP_NOT_CONFIGURED ((short)0),
		PERSONAL_AP_CONFIGURED_NOT_VALIDATED ((short)1),
		PERSONAL_AP_CONFIGURED_VALIDATING ((short)2),
		PERSONAL_AP_CONFIGURED_VALIDATED ((short)3),
		PERSONAL_AP_CONFIGURED_ERROR ((short)4),
		PERSONAL_AP_CONFIGURED_RETRY ((short)5);

		/**
		 * Type id
		 */
		private short id;
		
		/**
		 * Constructor
		 * @param id
		 */
		private OnboardingState(short id) {
			this.id = id;
		}
		
		/**
		 * Returns the id of state type
		 * @return id of state type
		 */
		public short getStateId() {
			return id;
		}
		
		/**
		 * Search for Onboarding state with the given Id. If not found returns NULL
		 * @param stateId type id
		 * @return onboarding state
		 */
		public static OnboardingState getStateById(short stateId) {
			OnboardingState retState = null;
			for (OnboardingState state : OnboardingState.values()) {
				if ( stateId == state.getStateId() ) {
					retState = state;
					break;
				}
			}
			return retState;
		}
		
	}

	/**
	 * Get the onboarding state
	 * @return onboarding state
	 */
	public OnboardingState getState();

	/**
	 * Start server mode (onboardee).  The application creates the BusAttachment
	 * @param busAttachment the AllJoyn bus attachment.
	 * @throws Exception
	 */
	public void startOnboardingServer(BusAttachment busAttachment) throws Exception;

	/**
	 * Stop server mode (onboardee)
	 * @throws Exception
	 */
	void stopOnboardingServer() throws Exception;

	/**
	 * Create an Onboarding client for a peer onboardee. 
	 * @param deviceName the remote device
	 * @param serviceAvailabilityListener listener for connection loss
	 * @param port the peer's bound port of the Onboarding server  
	 * @return OnboardingClient for running a session with the peer
	 * @throws Exception
	 */
	OnboardingClient createOnboardingClient(String deviceName,
			ServiceAvailabilityListener serviceAvailabilityListener, short port)
			throws Exception;

	/**
	 * Start client mode (onboarder).  The application creates the BusAttachment
	 * @param bus the AllJoyn bus attachment
	 * @throws Exception
	 */
	void startOnboardingClient(BusAttachment bus) throws Exception;

	/**
	 * Stop client mode (onboarder).
	 */
	void stopOnboardingClient();
}
