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

package org.alljoyn.ns.transport.consumer;

import java.util.UUID;

import org.alljoyn.bus.BusException;
import org.alljoyn.ns.NotificationServiceException;
import org.alljoyn.ns.PayloadAdapter;
import org.alljoyn.ns.commons.GenericLogger;
import org.alljoyn.ns.transport.Transport;
import org.alljoyn.ns.transport.interfaces.NotificationDismisser;

/**
 * The class provides a functionality of receiving AllJoyn Dismiss session-less-signals 
 */
class DismissConsumer implements NotificationDismisser {
	private static final String TAG = "ioe" + DismissConsumer.class.getSimpleName();
	
	public static final String OBJ_PATH = "/dismissReceiver";
	
	/**
	 * @see org.alljoyn.ns.transport.interfaces.NotificationDismisser#dismiss(int, byte[])
	 */
	@Override
	public void dismiss(int msgId, byte[] bAppId) throws BusException {
		
		Transport transport = Transport.getInstance();
		transport.getBusAttachment().enableConcurrentCallbacks();
		
		GenericLogger logger;
		
		try {
			logger = transport.getLogger();
		}
		catch(NotificationServiceException nse) {
			System.out.println(TAG + ": Unexpected error occured: " + nse.getMessage());
			return;
		}
		
		UUID appId = PayloadAdapter.byteArrayToUUID(bAppId);
		if ( appId == null ) {
			logger.error(TAG, "Received the Dismiss signal for the notifId: '" + msgId + "' with an invalid ApplicationId");
			return;
		}
		
		logger.debug(TAG, "Received a dismiss signal for notifId: '" + msgId + "', from appId: '" + appId + "', handling...");
		transport.onReceivedNotificationDismiss(msgId, appId);
	}//dismiss

	/**
	 * @see org.alljoyn.ns.transport.interfaces.NotificationDismisser#getVersion()
	 */
	@Override
	public short getVersion() throws BusException {
		return VERSION;
	}//getVersion

}
