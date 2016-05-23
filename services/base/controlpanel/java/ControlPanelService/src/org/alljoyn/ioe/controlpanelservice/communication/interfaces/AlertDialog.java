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

package org.alljoyn.ioe.controlpanelservice.communication.interfaces;

import java.util.Map;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.Variant;
import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusProperty;
import org.alljoyn.bus.annotation.BusSignal;
import org.alljoyn.ioe.controlpanelservice.ControlPanelService;

/**
 * Dialog interface
 */
@BusInterface (name = AlertDialog.IFNAME)
public interface AlertDialog extends AlertDialogSuper {
	public static final String IFNAME = ControlPanelService.INTERFACE_PREFIX + ".Dialog";
	
	public static final short VERSION = 1;
	
	/**
	 * @return Interface version
	 */
	@BusProperty(signature="q")
	public short getVersion() throws BusException;

	/**
	 * @return States bitmask 
	 * @throws BusException
	 */
	@BusProperty(signature="u")
	public int getStates() throws BusException; 

	/**
	 * @return Optional parameters
	 * @throws BusException
	 */
	@BusProperty(signature="a{qv}")
	public Map<Short,Variant> getOptParams() throws BusException;
    
	/**
	 * @return Returns the dialog message
	 * @throws BusException
	 */
	@BusProperty(signature="s")
	public String getMessage() throws BusException;
	
	/**
	 * @return Returns the number of the dialog buttons
	 * @throws BusException
	 */
	@BusProperty(signature="q")
	public short getNumActions() throws BusException;
	
	/**
	 * Call the method if is relevant
	 */
	@BusMethod
	public void Action1() throws BusException;;
	
	/**
	 * Call the method if is relevant
	 */
	@BusMethod
	public void Action2() throws BusException;

	/**
	 * Call the method if is relevant
	 */
	@BusMethod
	public void Action3() throws BusException;

	/**
	 * Signal is sent when the UI container metadata changed 
	 * @param metadata
	 */
	@BusSignal
	public void MetadataChanged() throws BusException;
}
