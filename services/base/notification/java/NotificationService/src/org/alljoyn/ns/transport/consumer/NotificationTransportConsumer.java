/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
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

import java.util.Map;

import org.alljoyn.bus.BusAttachment;
import org.alljoyn.bus.Variant;
import org.alljoyn.ns.NotificationServiceException;
import org.alljoyn.ns.PayloadAdapter;
import org.alljoyn.ns.commons.GenericLogger;
import org.alljoyn.ns.commons.NativePlatformFactory;
import org.alljoyn.ns.commons.NativePlatformFactoryException;
import org.alljoyn.ns.transport.Transport;
import org.alljoyn.ns.transport.TransportNotificationText;
import org.alljoyn.ns.transport.interfaces.NotificationTransport;


/**
 * The class is used to receive AllJoyn notify session-less-signals
 */
class NotificationTransportConsumer implements NotificationTransport {
	private static final String TAG = "ioe" + NotificationTransportConsumer.class.getSimpleName();
	
	/**
	 * Identify object that receives signals arrived from producer
	 */
	public static final String FROM_PRODUCER_RECEIVER_PATH    = "/producerReceiver";

	/**
	 * The service path identifying the object 
	 */
	private String servicePath;
	
	/**
	 * The object service path
	 * @param objServicePath
	 */
	public NotificationTransportConsumer(String objServicePath) {
		servicePath = objServicePath;
	}

	/**
	 * Return the object service path
	 * @return
	 */
	public String getServicePath() {
		return servicePath;
	}

	/**
	 * This method will be called by the AJ bus when a notification is received
	 * @see org.alljoyn.ns.transport.interfaces.NotificationTransport#notify(int, int, short, String, String, byte[], String, Map, Map, TransportNotificationText[])
	 */
	@Override
	public void notify(int version, int msgId, short messageType, String deviceId, String deviceName, byte[] appId, String appName, Map<Integer, Variant> attributes, Map<String, String> customAttributes, TransportNotificationText[] text) {
		
		Transport transport         = Transport.getInstance();
		BusAttachment busAttachment = transport.getBusAttachment();
		busAttachment.enableConcurrentCallbacks();
		
		try {
			
			GenericLogger logger = NativePlatformFactory.getPlatformObject().getNativeLogger();
			
			try {
				String sender = busAttachment.getMessageContext().sender;
				logger.debug(TAG, "Received notification from: '" + sender + "' by '" + servicePath + "' object, notification id: '" + msgId + "', handling");
				
				logger.debug(TAG, "Forwarding the received notification id: '" + msgId + "' to PayloadAdapter");
				PayloadAdapter.receivePayload(version, msgId, sender, messageType, deviceId, deviceName, appId, appName, attributes, customAttributes, text);
			} catch (NotificationServiceException nse) {
				logger.error(TAG, "Failed to read the received notification, Error: " + nse.getMessage());
			}
		}
		catch (NativePlatformFactoryException npfe) {
			System.out.println(TAG + ": Unexpected error occured: " + npfe.getMessage());
		}
	}//notify

}
