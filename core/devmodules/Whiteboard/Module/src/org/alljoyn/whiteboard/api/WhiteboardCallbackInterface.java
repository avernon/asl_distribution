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
package org.alljoyn.whiteboard.api;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.annotation.*;
import org.alljoyn.devmodules.callbacks.CallbackInterface;
import org.alljoyn.devmodules.common.WhiteboardLineInfo;

@BusInterface(name = WhiteboardCallbackInterface.SERVICE_NAME)
public interface WhiteboardCallbackInterface {
	public static final String SERVICE_NAME = "org.alljoyn.devmodules.api.whiteboard";
	public static final String OBJECT_PATH = "/whiteboardCallbackObject";
	
	@BusSignal
	public void onDraw(WhiteboardLineInfo lineInfo) throws BusException;
	
	@BusSignal
	public void onGroupDraw(String group, WhiteboardLineInfo lineInfo) throws BusException;
	
	@BusSignal
	public void onClear() throws BusException;
	
	@BusSignal
	public void onGroupClear(String group) throws BusException;
}
