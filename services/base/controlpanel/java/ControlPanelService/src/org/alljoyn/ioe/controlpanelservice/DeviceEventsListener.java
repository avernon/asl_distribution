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

import java.util.Collection;

import org.alljoyn.ioe.controlpanelservice.ui.DeviceControlPanel;

/**
 *  The interface to be implemented in order to receive {@link ControllableDevice} relevant events
 */
public interface DeviceEventsListener {
	
	/**
	 * Notify the interface implementer about session establishment with the remote device
	 * @param device The {@link ControllableDevice}
	 * @param controlPanelContainer Used to request the Root UI Container and a relevant to it information
	 * @see DeviceControlPanel 
	 */
	public void sessionEstablished(ControllableDevice device, Collection<ControlPanelCollection> controlPanelContainer);
	
	/**
	 * Notify the interface implementer about loosing session with the remote device
	 * @param device The {@link ControllableDevice} where the session has lost
	 */
	public void sessionLost(ControllableDevice device);
	
	/**
	 * Notify the interface implementer about an error in the device activities
	 * @param device The {@link ControllableDevice} where the error has occurred
	 * @param reason The error reason
	 */
	public void errorOccurred(ControllableDevice device, String reason);
}
