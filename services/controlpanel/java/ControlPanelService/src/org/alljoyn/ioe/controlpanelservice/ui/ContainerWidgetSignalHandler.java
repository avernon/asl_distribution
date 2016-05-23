/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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

import java.util.Map;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.Variant;
import org.alljoyn.ioe.controlpanelservice.ControlPanelException;
import org.alljoyn.ioe.controlpanelservice.communication.TaskManager;
import org.alljoyn.ioe.controlpanelservice.communication.interfaces.Container;
import org.alljoyn.ioe.controlpanelservice.communication.interfaces.ContainerSecured;

import android.util.Log;

/**
 * The class is a signal handler that is responsible to receive signals of UIContainer interface. <br>
 *  Signals: <br>
 *  - MetadataChanged
 */
public class ContainerWidgetSignalHandler implements Container, ContainerSecured {
	private static final String TAG = "cpan" + ContainerWidgetSignalHandler.class.getSimpleName();
	
	
	/**
	 * Container widget to be notified about signal receiving
	 */
	private ContainerWidget containerWidget;
	
	/**
	 * Constructor
	 * @param containerWidget
	 */
	public ContainerWidgetSignalHandler(ContainerWidget containerWidget) {
		this.containerWidget = containerWidget;
	}

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.Container#getVersion()
	 */
	@Override
	public short getVersion() throws BusException {
		return 0;
	}

	@Override
	public int getStates() throws BusException {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public Map<Short, Variant> getOptParams() throws BusException {
		// TODO Auto-generated method stub
		return null;
	}

	/**
	 * Signal handler
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.Container#MetadataChanged()
	 */
	@Override
	public void MetadataChanged() throws BusException {
		
		String msg = "Device: '" + containerWidget.device.getDeviceId() + 
                "', ContainerWidget: '" + containerWidget.objectPath + "', received METADATA_CHANGED signal";
		
		Log.d(TAG, msg);
		
		final ControlPanelEventsListener eventsListener = containerWidget.controlPanel.getEventsListener();
		try {
			containerWidget.refreshProperties();
		} catch (ControlPanelException cpe) {
			msg += ", but failed to refresh the Container properties";
			Log.e(TAG, msg);
			eventsListener.errorOccurred(containerWidget.controlPanel, msg);
			return;
		}
		
		//Delegate to the listener on a separate thread
		TaskManager.getInstance().execute( new Runnable() {
			@Override
			public void run() {
				eventsListener.metadataChanged(containerWidget.controlPanel, containerWidget);
			}
		});
	}//MetadataChanged

}
