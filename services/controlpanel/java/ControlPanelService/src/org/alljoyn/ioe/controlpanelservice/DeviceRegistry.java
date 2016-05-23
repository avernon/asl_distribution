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

package org.alljoyn.ioe.controlpanelservice;

import java.util.Map;

/**
 * Used as a callback interface to inform the interface implementer about new discovered devices
 * and changes in their reachability state
 */
public interface DeviceRegistry {
	
	/**
	 * Called when a new controllable device was found in the control panel service proximity <br>
	 * @param device
	 */
	public void foundNewDevice(ControllableDevice device);
	
	/**
	 * Called when a controllable device left the control panel service proximity <br>
	 * The method implementation should be thread safe 
	 * @param device The controllable device
	 * @param isReachable Whether the device is in reachable state
	 */
	public void reachabilityChanged(ControllableDevice device, boolean isReachable);
	
	/**
	 * Remove a device from registry <br>
	 * When a device is removed from the registry it will be inserted back after foundDevice method is called 
	 * @param device
	 */
	public void removeDevice(ControllableDevice device);
	
	/**
	 * @return Returns collection of controllable devices
	 */
	public Map<String, ControllableDevice> getDevices();
	
}
