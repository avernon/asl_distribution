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

import org.alljoyn.bus.AuthListener;
import org.alljoyn.services.common.DefaultGenericLogger;
import org.alljoyn.services.common.utils.GenericLogger;

/**
 * This class implements org.alljoyn.bus.AuthListener and delegates calls to {@link AuthPasswordHandler}
 */
public class SrpAnonymousKeyListener implements AuthListener
{

	private String TAG = "SrpAnonymousKeyListener";

	// ---------------- AuthListener Implementation -------------------- 

	public static String KEY_STORE_FINE_NAME;
	public static final char [] DEFAULT_PINCODE = new char[]{'0','0','0','0','0','0'};
	
	AuthPasswordHandler m_passwordHandler;
	private GenericLogger m_logger;

	public SrpAnonymousKeyListener(AuthPasswordHandler passwordHandler, GenericLogger logger)
	{
		m_logger = logger;
		if (m_logger == null)
		{
			m_logger =  new DefaultGenericLogger();
		}
		m_passwordHandler = passwordHandler;
	}

	/* 
	 * (non-Javadoc)
	 * @see org.alljoyn.bus.AuthListener#requested(java.lang.String, java.lang.String, int, java.lang.String, org.alljoyn.bus.AuthListener.AuthRequest[])
	 */
	@Override
	public boolean requested(String mechanism, String peer, int count, String userName,  AuthRequest[] requests) 
	{
		m_logger.info(TAG, " ** " + "requested, mechanism = " + mechanism + " peer = " + peer);
		if (!mechanism.equals("ALLJOYN_PIN_KEYX") && !mechanism.equals("ALLJOYN_SRP_KEYX"))
		{
			return false;
		}
		else
		{
			if (!(requests[0] instanceof PasswordRequest)) 
			{
				return false;
			}
			char [] pinCode = DEFAULT_PINCODE;
			
			// if pincode not set for this peer, the function will return null, at that case, use the default one.
			if (m_passwordHandler != null && m_passwordHandler.getPassword(peer)!= null)
			{
				pinCode = m_passwordHandler.getPassword(peer);
			}
			
			// The C++ way... writing the result into one of the passed arguments
			((PasswordRequest) requests[0]).setPassword(pinCode);
			return true;
		}
	}
   
	/* (non-Javadoc)
	 * @see org.alljoyn.bus.AuthListener#completed(java.lang.String, java.lang.String, boolean)
	 */
	@Override
	public void completed(String mechanism, String authPeer, boolean authenticated) 
	{
		m_passwordHandler.completed(mechanism, authPeer, authenticated);
	}

}
