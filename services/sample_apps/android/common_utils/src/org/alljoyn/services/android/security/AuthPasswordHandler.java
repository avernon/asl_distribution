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

package org.alljoyn.services.android.security;

/**
 * An API between the {@link SrpAnonymousKeyListener} and the application.  
 * The application will implement a password handler.
 * When the bus requires authentication with a remote device, it will let the password handler (the application) handle it.
 * When the bus receives a result of an authentication attempt with a remote device, it will let the password handler (the application) handle it.
 * @see AuthPasswordHandler
 */
 public interface AuthPasswordHandler 
{
	/**
	 * Get the password for this peer. The application should store a password per peer 
	 * @param peerName the alljoyn bus name of the peer we want to authenticate with
	 * @return the password for this peer
	 */
	public char[] getPassword(String peerName);
	
	/**
	 * Once the authentication has finished the completed(...) call-back method is called.
	 * The application can then show a popup, a toast, etc.
	 * @param mechanism The authentication mechanism that was just completed
	 * @param authPeer The peerName (well-known name or unique name)
	 * @param authenticated A boolean variable indicating if the authentication attempt completed successfuly.
	 */
	public void completed(String mechanism, String authPeer, boolean authenticated);
}
