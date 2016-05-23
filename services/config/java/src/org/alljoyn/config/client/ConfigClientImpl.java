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

package org.alljoyn.config.client;

import java.util.Map;

import org.alljoyn.bus.BusAttachment;
import org.alljoyn.bus.BusException;
import org.alljoyn.bus.ProxyBusObject;
import org.alljoyn.bus.Variant;
import org.alljoyn.config.transport.ConfigTransport;
import org.alljoyn.services.common.ClientBaseImpl;
import org.alljoyn.services.common.ServiceAvailabilityListener;
import org.alljoyn.services.common.utils.TransportUtil;

/**
 * A default implementation of the ConfigClient interface
 */ 
public class ConfigClientImpl extends ClientBaseImpl implements ConfigClient
{
	public final static String TAG = ConfigClientImpl.class.getName();
	
	public ConfigClientImpl(String deviceName, BusAttachment bus, ServiceAvailabilityListener serviceAvailabilityListener, short port)
	{
		super(deviceName, bus, serviceAvailabilityListener, ConfigTransport.OBJ_PATH, ConfigTransport.class, port);
	}

	@Override
	public short getVersion() throws BusException {
		ProxyBusObject proxyObj = getProxyObject();
		// We make calls to the methods of the AllJoyn object through one of its interfaces.
		ConfigTransport configTransport =  proxyObj.getInterface(ConfigTransport.class);
		return configTransport.getVersion();
	}

	@Override
	public Map<String, Object> getConfig(String languageTag) throws BusException
	{
		ProxyBusObject proxyObj = getProxyObject();
		// We make calls to the methods of the AllJoyn object through one of its interfaces. */
		ConfigTransport configTransport =  proxyObj.getInterface(ConfigTransport.class);
		Map<String, Variant> configMap = configTransport.GetConfigurations(languageTag);
		return TransportUtil.fromVariantMap(configMap);
	}

	@Override
	public void setConfig(Map<String, Object> config, String languageTag) throws BusException
	{
		ProxyBusObject proxyObj = getProxyObject();
		// We make calls to the methods of the AllJoyn object through one of its interfaces. */
		ConfigTransport configTransport =  proxyObj.getInterface(ConfigTransport.class);
		configTransport.UpdateConfigurations(languageTag, TransportUtil.toVariantMap(config));
	}

	@Override
	public void setPasscode(String daemonRealm, char[] newPasscode)
			throws BusException
	{
		ProxyBusObject proxyObj = getProxyObject();
		// We make calls to the methods of the AllJoyn object through one of its interfaces. */
		ConfigTransport configTransport =  proxyObj.getInterface(ConfigTransport.class);
		configTransport.SetPasscode(daemonRealm, TransportUtil.toByteArray(newPasscode));
	}

	@Override
	public void restart() throws BusException
	{
		ProxyBusObject proxyObj = getProxyObject();
		// We make calls to the methods of the AllJoyn object through one of its interfaces. 
		ConfigTransport configTransport =  proxyObj.getInterface(ConfigTransport.class);
		configTransport.Restart();
	}

	@Override
	public void factoryReset() throws BusException
	{
		ProxyBusObject proxyObj = getProxyObject();
		// We make calls to the methods of the AllJoyn object through one of its interfaces. */
		ConfigTransport configTransport =  proxyObj.getInterface(ConfigTransport.class);
		configTransport.FactoryReset();
	}

	@Override
	public void ResetConfigurations(String language, String[] fieldsToRemove)throws BusException {
		
		ProxyBusObject proxyObj = getProxyObject();
		// We make calls to the methods of the AllJoyn object through one of its interfaces. */
		ConfigTransport configTransport =  proxyObj.getInterface(ConfigTransport.class);
		configTransport.ResetConfigurations(language, fieldsToRemove);
		
	}
}
