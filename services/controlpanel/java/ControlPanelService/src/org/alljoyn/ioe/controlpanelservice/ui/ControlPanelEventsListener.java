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

package org.alljoyn.ioe.controlpanelservice.ui;


/**
 *  The interface to be implemented in order to receive {@link DeviceControlPanel} relevant events
 */
public interface ControlPanelEventsListener {
	
	/**
	 * Notify the interface implementer about the changed value in the {@link UIElement}
	 * @param panel {@link DeviceControlPanel} where the value has changed
	 * @param uielement The {@link UIElement} where the change has occurred
	 * @param newValue The new value
	 */
	public void valueChanged(DeviceControlPanel panel, UIElement uielement, Object newValue);
	
	/**
	 * Notify the interface implementer about the metadata changed in the {@link UIElement}
	 * @param panel {@link DeviceControlPanel} where the metadata has changed
	 * @param uielement The {@link UIElement} where the change has occurred
	 */
	public void metadataChanged(DeviceControlPanel panel, UIElement uielement);
	
	/**
	 * Dismiss the NotificationAction of the given {@link DeviceControlPanel} 
	 * @param panel The NotificationAction control panel to dismissed
	 */
	public void notificationActionDismiss(DeviceControlPanel panel);
	
	/**
	 * Notify the interface implementer about an error in the {@link DeviceControlPanel} activities
	 * @param panel {@link DeviceControlPanel} where the error has occurred
	 * @param reason The error reason
	 */
	public void errorOccurred(DeviceControlPanel panel, String reason);
	
}
