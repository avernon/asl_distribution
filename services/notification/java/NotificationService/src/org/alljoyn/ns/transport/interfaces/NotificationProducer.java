/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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

package org.alljoyn.ns.transport.interfaces;


import org.alljoyn.bus.BusException;
import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusProperty;
import org.alljoyn.ns.Notification;

/**
 * The interface provides to a notification receiver the functionality to dismiss 
 * the received {@link Notification}.  
 */
@BusInterface(name = NotificationProducer.IFNAME)
public interface NotificationProducer extends BusObject {
	
	/**
	 * The AllJoyn interface name
	 */
	public static final String IFNAME = "org.alljoyn.Notification.Producer";
	
	/**
	 * Notification producer object
	 */
	public static final String OBJ_PATH = "/notificationProducer";
	
	/**
	 * The interface version
	 */
	public static final short VERSION = 1;
		
	/**
	 * When the notification message is dismissed, it's first of all deleted and then a dismiss signal is sent
	 * to all notification consumers to update them that the {@link Notification} has been dismissed   
	 * @param msgId The notification message identifier
	 * @throws BusException
	 */
	@BusMethod(name="Dismiss", signature="i")
	public void dismiss(int msgId) throws BusException;
	
	/**
	 * @return The interface version
	 * @throws BusException
	 */
	@BusProperty(signature="q")
	public short getVersion() throws BusException;
	
}
