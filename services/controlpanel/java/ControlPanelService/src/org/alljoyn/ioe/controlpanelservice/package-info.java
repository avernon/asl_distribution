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
 * The package includes classes that allow to start the control panel service {@link org.alljoyn.ioe.controlpanelservice.ControlPanelService}, 
 * and manage the list of controllable devices {@link org.alljoyn.ioe.controlpanelservice.ControllableDevice}. <br>
 * The list of controllable devices is managed by the {@link org.alljoyn.ioe.controlpanelservice.DeviceRegistry} interface
 * and its default implementation {@link org.alljoyn.ioe.controlpanelservice.DefaultDeviceRegistry} <br>  
 * For each controllable device there is a list of the device control panels {@link org.alljoyn.ioe.controlpanelservice.ui.DeviceControlPanel}
 * that is passed to the user when {@link org.alljoyn.ioe.controlpanelservice.ControllableDevice#startSession(DeviceEventsListener)}
 * is called. By using the {@link org.alljoyn.ioe.controlpanelservice.ui.DeviceControlPanel} a user may call
 * {@link org.alljoyn.ioe.controlpanelservice.ui.DeviceControlPanel#getRootContainer(String)} to retrieve the root
 * UI container
 */
package org.alljoyn.ioe.controlpanelservice;
