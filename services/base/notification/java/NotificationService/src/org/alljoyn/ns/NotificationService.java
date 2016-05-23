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

package org.alljoyn.ns;

import org.alljoyn.bus.BusAttachment;
import org.alljoyn.ns.commons.GenericLogger;
import org.alljoyn.ns.commons.NativePlatform;
import org.alljoyn.ns.commons.NativePlatformFactory;
import org.alljoyn.ns.commons.NativePlatformFactoryException;
import org.alljoyn.ns.transport.Transport;
import org.alljoyn.services.common.PropertyStore;


/**
 * The entry point of the Notification service <br>
 * The class is a singleton
 */
public class NotificationService  {
	private static final String TAG = "ioe" + NotificationService.class.getSimpleName();
	
	/**
	 * Initialize the class object
	 */
	private static final NotificationService SELF = new NotificationService();
	
	/**
	 * The protocol version that is sent in the {@link Notification} message
	 */
	public static final int PROTOCOL_VERSION = 2;
	
	/**
	 * Reference to transport object
	 */
	private Transport transport;
	
	/**
	 * Reference to native platform object
	 */
	private NativePlatform nativePlatform;
	
	/**
	 * Constructor
	 */
	private NotificationService() {}//constructor
	
	/**
	 * @return Returns the {@link NotificationService} object
	 */
	public static NotificationService getInstance() {
		return SELF;
	}//getInstance
	
	/**
	 * Establishes the notification sender service to later allow sending notifications 
	 * See {@link NotificationSender}
	 * @param bus The {@link BusAttachment} to be used by the service
	 * @param propertyStore Service configuration {@link PropertyStore}
	 * @return {@link NotificationSender}
	 * @throws NotificationServiceException Is thrown if an error occurred during the sender initialization 
	 */
	public NotificationSender initSend(BusAttachment bus, PropertyStore propertyStore) throws NotificationServiceException {
		init();
		
		GenericLogger logger = nativePlatform.getNativeLogger();

		if ( propertyStore == null ) {
			throw new NotificationServiceException("PropertyStore is NULL");
		}
		
		logger.debug(TAG, "Init Send invoked, calling Transport");
		transport.startSenderTransport(bus, propertyStore);
		
		logger.debug(TAG, "Creating and returning NotificationSender");
		return new NotificationSender();
	}//initSend

	/**
	 * Establishes the notification receiver service to later receive notifications. 
	 * See {@link NotificationReceiver}
	 * @param bus The {@link BusAttachment} to be used by the service
	 * @param receiver
	 * @throws NotificationServiceException if a malfunction occurred on building NotificationService
	 */
	public void initReceive(BusAttachment bus, NotificationReceiver receiver) throws NotificationServiceException {
		init();
		
		GenericLogger logger = nativePlatform.getNativeLogger();
		logger.debug(TAG, "Init Receive called, calling Transport");
		if ( receiver == null ) {
			throw new NotificationServiceException("NotificationReceiver interface should be implemented in order to receive notifications, received null pointer");
		}
		
		transport.startReceiverTransport(bus, receiver);
	}//initReceive

	/**
	 * Set a logger Object to enable logging capabilities
	 * @param logger GenericLogger object 
	 * @throws NotificationServiceException Is thrown if failed to set a logger
	 */	
	public void setLogger(GenericLogger logger) throws NotificationServiceException {
		init();
		
		if ( logger == null ) {
			throw new NullPointerException("Provided logger is NULL");
		}
		nativePlatform.setNativeLogger(logger);
	}//setLogger

	/**
	 * Shutdown notification service
	 * @throws NotificationServiceException
	 */
	public void shutdown() throws NotificationServiceException {
		init();
		transport.shutdown();
	}//shutdown

	/**
	 * Stops notification sender service
	 * @throws NotificationServiceException Throws if the service wasn't started previously 
	 */
	public void shutdownSender() throws NotificationServiceException {
		init();
		transport.shutdownSender();
	}//stopSender

	/**
	 * Stops notification receiver service
	 * @throws NotificationServiceException Throws if the service wasn't started previously 
	 */
	public void shutdownReceiver() throws NotificationServiceException {
		init();
		transport.shutdownReceiver();
	}//stopReceiver

	//=========================================================//
	
	/**
	 * Initializes the {@link NotificationService} object
	 * @throws NotificationServiceException Is thrown if failed to initialized the object
	 */
	private void init() throws NotificationServiceException {
		if ( nativePlatform != null &&  transport != null ) {
			return;
		}
		
		try {
			nativePlatform       = NativePlatformFactory.getPlatformObject();
			GenericLogger logger = nativePlatform.getNativeLogger();
			logger.info(TAG,  "Notification Service created");
			transport = Transport.getInstance();
		} catch (NativePlatformFactoryException npfe) {
			throw new NotificationServiceException("Failed to create Notification Service: " + npfe.getMessage());			
		} catch (Exception e) {
			throw new NotificationServiceException("Failed to create Notification Service: General Error");
		}
	}//init
	
}//NotificationServiceImpl
