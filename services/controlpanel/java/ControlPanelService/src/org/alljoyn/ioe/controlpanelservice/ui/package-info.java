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
/**
 * The package includes classes that represent the UI widgets and its metadata<br>
 * The UI widget classes are used to receive the initial values that were set by the remotely controllable device. <br>
 * In addition these classes used to perform the remote control of the device.
 * For example: <br>
 * {@link org.alljoyn.ioe.controlpanelservice.ui.ActionWidget#exec()} is used to invoke an action 
 * on the remote device <br>
 * {@link org.alljoyn.ioe.controlpanelservice.ui.PropertyWidget#setCurrentValue(Object)} is used to set a
 * new property value on the remote device <br>  
 * {@link org.alljoyn.ioe.controlpanelservice.ui.PropertyWidget#getCurrentValue()} is used to receive the current
 * property value <br>
 * Each UI widget has its signal handler to be notified about the state changes in the remote device.
 * The user receives these notifications by implementing the {@link org.alljoyn.ioe.controlpanelservice.ui.ControlPanelEventsListener} interface <br>
 * The signal {@link org.alljoyn.ioe.controlpanelservice.ui.ControlPanelEventsListener#metadataChanged(DeviceControlPanel, UIElement)}
 * notifies about a possible change in a widget UI state. <br>
 * The method refreshProperties, i.e: {@link org.alljoyn.ioe.controlpanelservice.ui.PropertyWidget#refreshProperties()}
 * is used to receive the updated state of a Property 
 */
package org.alljoyn.ioe.controlpanelservice.ui;
