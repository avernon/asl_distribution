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

package org.alljoyn.config;

import org.alljoyn.bus.BusAttachment;
import org.alljoyn.config.client.ConfigClient;
import org.alljoyn.config.server.ConfigChangeListener;
import org.alljoyn.config.server.FactoryResetHandler;
import org.alljoyn.config.server.PassphraseChangedListener;
import org.alljoyn.config.server.RestartHandler;
import org.alljoyn.config.server.SetPasswordHandler;
import org.alljoyn.services.common.PropertyStore;
import org.alljoyn.services.common.ServiceAvailabilityListener;
import org.alljoyn.services.common.ServiceCommon;

/**
 * An interface for both Config client (consumer) and server (producer). 
 * An application may want to implement both, but still use one bus, so for convenience both functionalities are encapsulated here.
 */
public interface ConfigService extends ServiceCommon
{
	/**
	 * The Config protocol version.
	 */
	public static final int PROTOCOL_VERSION = 1;

	/**
	 * Start server mode.  The application creates the BusAttachment
	 * @param propertyStore a map of device/application properties. 
	 * @param configChangeListener listener to configuration changes coming from remote client peers.
	 * @param restartHandler handler for restart requests coming from remote client peers.
	 * @param factoryResetHandler handler for factory reset requests coming from remote client peers.
	 * @param passphraseChangeListener listener to password changes coming from remote client peers.
	 * @param bus the AllJoyn bus attachment.
	 * @throws Exception
	 * @see AboutKeys
	 */
	void startConfigServer(PropertyStore propertyStore,ConfigChangeListener configChangeListener,RestartHandler restartHandler,
			FactoryResetHandler factoryResetHandler,PassphraseChangedListener passphraseChangeListener, BusAttachment bus) throws Exception;

	/**
	 * Stop server mode.
	 * @throws Exception
	 */
	public void stopConfigServer() throws Exception;

	/**
	 * Start client mode.  The application creates the BusAttachment
	 * @param bus the AllJoyn bus attachment
	 * @throws Exception
	 */
	public void startConfigClient(BusAttachment bus) throws Exception;
	
	/**
	 * Create an Config client for a peer. 
	 * @param deviceName the remote device
	 * @param serviceAvailabilityListener listener for connection loss
	 * @param port the peer's bound port of the About server  
	 * @return ConfigClient for running a session with the peer
	 * @throws Exception
	 */
	public ConfigClient createFeatureConfigClient(String deviceName, ServiceAvailabilityListener serviceAvailabilityListener, short port) throws Exception;
	
	/**
	 * Stop client mode. Disconnect all sessions.
	 * @throws Exception
	 */
	public void stopConfigClient() throws Exception;
	
	/**
	 * Handler of passpword change requests coming from remote peer clients.
	 * @param setPasswordHandler the application
	 */
	public void setSetPasswordHandler(SetPasswordHandler setPasswordHandler);
}
