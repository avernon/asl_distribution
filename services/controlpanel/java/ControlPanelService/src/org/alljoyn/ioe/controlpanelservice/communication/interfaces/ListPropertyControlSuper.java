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

package org.alljoyn.ioe.controlpanelservice.communication.interfaces;

import java.util.Map;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.Variant;
import org.alljoyn.ioe.controlpanelservice.ui.ajstruct.ListPropertyWidgetRecordAJ;

/**
 * List property super interface 
 */
public interface ListPropertyControlSuper {
	
	/**
	 * @return Interface version
	 */
	public short getVersion() throws BusException;

	/**
	 * @return States bitmask 
	 * @throws BusException
	 */
	public int getStates() throws BusException; 

	/**
	 * @return Optional parameters
	 * @throws BusException
	 */
	public Map<Short,Variant> getOptParams() throws BusException;
	
	/**
	 * @return The array of list records
	 * @throws BusException
	 */
	public ListPropertyWidgetRecordAJ[] getValue() throws BusException;
	
	/**
	 * Prepare the input form for adding a new record to the list
	 * @throws BusException
	 */
	public void Add() throws BusException;
	
	/**
	 * Prepare the form for view the record prior to the delete action.
	 * @param recordId
	 * @throws BusException
	 */
	public void Delete(short recordId) throws BusException;
	
	/**
	 * Prepare the display form to view the record identified by the recordID.
	 * @param recordId
	 * @throws BusException
	 */
	public void View(short recordId) throws BusException;
	
	/**
	 * Prepare the input form to view the record identified by the recordID and allow the end-user to modify the fields.
	 * @param recordId
	 * @throws BusException
	 */
	public void Update(short recordId) throws BusException;
	
	/**
	 * Confirm the action and save the change requested
	 * @throws BusException
	 */
	public void Confirm() throws BusException;
	
	/**
	 * Cancel the current action
	 * @throws BusException
	 */
	public void Cancel() throws BusException;
	
	/**
	 * The signal is sent when a list property value has changed, i.e. a record was added or removed from the records list
	 * @throws BusException
	 */
	public void ValueChanged() throws BusException;
	
	/**
	 * The signal is sent when there is a change in the list property metadata
	 * @throws BusException
	 */
	public void MetadataChanged() throws BusException;	
}
