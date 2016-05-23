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

package org.alljoyn.ioe.controlpanelservice;

import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

import android.util.Log;

/**
 * The default implementation of the DeviceRegistry interface. <br>
 * Inherit this class in order to be notified about changes in the {@link DeviceRegistry}.  
 */
public class DefaultDeviceRegistry implements DeviceRegistry {
	private static final String TAG = "cpan" + DefaultDeviceRegistry.class.getSimpleName();
	
	/**
	 * The devices that in the proximity and may be controlled
	 */
	private Map<String, ControllableDevice> controllableDevices;
	
	/**
	 * Constructor
	 */
	public DefaultDeviceRegistry() {
		controllableDevices = new HashMap<String, ControllableDevice>();
	}

	/**
	 * Adds the device to the registry
	 * @see org.alljoyn.ioe.controlpanelservice.DeviceRegistry#foundNewDevice(org.alljoyn.ioe.controlpanelservice.ControllableDevice)
	 */
	@Override
	public void foundNewDevice(ControllableDevice device) {
		controllableDevices.put(device.getDeviceId(), device);
		Log.d(TAG, "Added device, deviceId: '" + device.getDeviceId() + "'");
	}

	/**
	 * Mark the device as not active
	 * @see org.alljoyn.ioe.controlpanelservice.DeviceRegistry#reachabilityChanged(org.alljoyn.ioe.controlpanelservice.ControllableDevice, boolean)
	 */
	@Override
	public void reachabilityChanged(ControllableDevice device, boolean isReachable) {
		Log.d(TAG, "ReachabilityChanged for device: '" + device.getDeviceId() + "' the device isReachable: '" + isReachable + "'");
	}

	/**
	 * Removes the device from the registry
	 * @see org.alljoyn.ioe.controlpanelservice.DeviceRegistry#removeDevice(org.alljoyn.ioe.controlpanelservice.ControllableDevice)
	 */
	@Override
	public void removeDevice(ControllableDevice device) {
		Log.d(TAG, "Remove device called, deviceId: '" + device.getDeviceId() + "', cancelFindAdvertise name and remove the device from the registry");
		device.stopDeviceActivities();
		controllableDevices.remove(device.getDeviceId());
	}

	/**
	 * Returns the devices list
	 * @see org.alljoyn.ioe.controlpanelservice.DeviceRegistry#getDevices()
	 */
	@Override
	public Map<String, ControllableDevice> getDevices() {
		return Collections.unmodifiableMap(controllableDevices);
	}

}//DefaultDeviceRegistry
