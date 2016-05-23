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

package org.alljoyn.ns.transport.producer;

import java.util.EnumMap;
import java.util.Map;

import org.alljoyn.bus.Variant;
import org.alljoyn.ns.Notification;
import org.alljoyn.ns.NotificationMessageType;
import org.alljoyn.ns.transport.TransportNotificationText;
import org.alljoyn.ns.transport.interfaces.NotificationTransport;

/** 
 * The class is used to send {@link Notification} session less signals
 */
class NotificationTransportProducer implements NotificationTransport {

	/**
	 * Stores AJ BusObject identifiers
	 * Maps from Message type to ServicePath string
	 */
	private static Map<NotificationMessageType, String> servicePath;


	static {
		servicePath = new EnumMap<NotificationMessageType, String>(NotificationMessageType.class);
		servicePath.put(NotificationMessageType.EMERGENCY, "/emergency");
		servicePath.put(NotificationMessageType.WARNING, "/warning");
		servicePath.put(NotificationMessageType.INFO, "/info");
	}
	
	/**
	 * Returns the servicePath for each of the transport objects
	 * @return
	 */
	public static Map<NotificationMessageType, String> getServicePath() {
		return servicePath;
	}
	
	/**
	 * Use this method to send session less signals
	 * @see org.alljoyn.ns.transport.interfaces.NotificationTransport#notify(int, int, short, String, String, byte[], String, Map, Map, TransportNotificationText[])
	 */
	@Override
	public void notify(int version, int msgId,
			short messageType, String deviceId, String deviceName, byte[] appId, String appName,
			Map<Integer, Variant> attributes,
			Map<String, String> customAttributes,
			TransportNotificationText[] text) {}
}
