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

package org.alljoyn.login.dashboard.security;

/**
 * A handler for AllJoyn security callbacks.
 * The OnboardingServer accesses secure AllJoyn interfaces like Config and Onboarding
 * This handler addresses the callbacks that AllJoyn security generates
 */
public interface AuthPasswordHandler 
{
	/**
	 * When a client tries to access one of the board's secure interfaces, AllJoyn Bus will ask the board
	 * for a password and match it with the one it receives from the client.
	 * @param peerName the AllJoyn bus name of the peer
	 * @return the password
	 */
	public char[] getPassword(String peerName);
	
	/**
	 * AllJoyn Bus communicates the result of a security check, and lets the board handle it.
	 * On the board's side this is pretty much FYI, not as important as on the client's side where failures mean
	 * denial of service and require user's attention.
	 * @param mechanism the Authentication mechanism
	 * @param authPeer the Bus name of the peer
	 * @param authenticated the result: failure/success
	 */
	public void completed(String mechanism, String authPeer, boolean authenticated);
}
