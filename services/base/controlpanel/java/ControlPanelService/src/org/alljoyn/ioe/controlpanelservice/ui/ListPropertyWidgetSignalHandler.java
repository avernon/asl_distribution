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

package org.alljoyn.ioe.controlpanelservice.ui;

import java.util.List;
import java.util.Map;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.Variant;
import org.alljoyn.ioe.controlpanelservice.ControlPanelException;
import org.alljoyn.ioe.controlpanelservice.communication.TaskManager;
import org.alljoyn.ioe.controlpanelservice.communication.interfaces.ListPropertyControl;
import org.alljoyn.ioe.controlpanelservice.communication.interfaces.ListPropertyControlSecured;
import org.alljoyn.ioe.controlpanelservice.ui.ListPropertyWidget.Record;
import org.alljoyn.ioe.controlpanelservice.ui.ajstruct.ListPropertyWidgetRecordAJ;

import android.util.Log;

/**
 * The class is a signal handler that is responsible to receive signals of ListPropertyControl interface. <br>
 *  Signals: <br>
 *  - ValueChanged    <br>
 *  - MetadataChanged
 */

public class ListPropertyWidgetSignalHandler implements ListPropertyControl, ListPropertyControlSecured {
    private static final String TAG = "cpan" + ListPropertyWidgetSignalHandler.class.getSimpleName();

    /**
     * The {@link ListPropertyWidget} to be notified about the receiving the signals
     */
    private ListPropertyWidget listPropertyWidget;
	
	/**
	 * Constructor
	 * @param listPropertyWidget
	 */
	public ListPropertyWidgetSignalHandler(ListPropertyWidget listPropertyWidget) {
		this.listPropertyWidget = listPropertyWidget;
	}

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.ListPropertyControl#getVersion()
	 */
	@Override
	public short getVersion() throws BusException {
		return 0;
	}

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.ListPropertyControl#getStates()
	 */
	@Override
	public int getStates() throws BusException {
		return 0;
	}

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.ListPropertyControl#getOptParams()
	 */
	@Override
	public Map<Short, Variant> getOptParams() throws BusException {
		return null;
	}

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.ListPropertyControl#getValue()
	 */
	@Override
	public ListPropertyWidgetRecordAJ[] getValue() throws BusException {
		return null;
	}

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.ListPropertyControl#Add()
	 */
	@Override
	public void Add() throws BusException {
	}

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.ListPropertyControl#Delete(short)
	 */
	@Override
	public void Delete(short recordId) throws BusException {
	}

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.ListPropertyControl#View(short)
	 */
	@Override
	public void View(short recordId) throws BusException {
	}

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.ListPropertyControl#Update(short)
	 */
	@Override
	public void Update(short recordId) throws BusException {
	}

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.ListPropertyControl#Confirm()
	 */
	@Override
	public void Confirm() throws BusException {
	}

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.ListPropertyControl#Cancel()
	 */
	@Override
	public void Cancel() throws BusException {
		// TODO Auto-generated method stub

	}

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.ListPropertyControl#ValueChanged()
	 */
	@Override
	public void ValueChanged() throws BusException {
		
        ControlPanelEventsListener eventsListener = listPropertyWidget.controlPanel.getEventsListener();
            
        String msg = "Device: '" + listPropertyWidget.device.getDeviceId() +
                "', ListProperty: '" + listPropertyWidget.objectPath + "', received VALUE_CHANGED signal";
    
        Log.d(TAG, msg);
       
        try {
            List<Record> records = listPropertyWidget.getValue();
            eventsListener.valueChanged(listPropertyWidget.controlPanel, listPropertyWidget, records);
        } catch (ControlPanelException cpe) {
            msg += ", but failed to read the new values, Error: '" + cpe.getMessage() + "'";
            Log.e(TAG, msg);
            eventsListener.errorOccurred(listPropertyWidget.controlPanel, msg);
        }
	}//ValueChanged

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.ListPropertyControl#MetadataChanged()
	 */
	@Override
	public void MetadataChanged() throws BusException {
        
        String msg = "Device: '" + listPropertyWidget.device.getDeviceId() +
                "', ListProperty: '" + listPropertyWidget.objectPath + "', received METADATA_CHANGED signal";

        Log.d(TAG, msg);

        final ControlPanelEventsListener eventsListener = listPropertyWidget.controlPanel.getEventsListener();

        try {
            listPropertyWidget.refreshProperties();
        }
        catch(ControlPanelException cpe) {
             msg += ", but failed to refresh the widget properties";
             Log.e(TAG, msg);
             eventsListener.errorOccurred(listPropertyWidget.controlPanel, msg);
             return;
        }

        //Delegate to the listener on a separate thread
        TaskManager.getInstance().execute( new Runnable() {
			@Override
			public void run() {
				eventsListener.metadataChanged(listPropertyWidget.controlPanel, listPropertyWidget);
			}
		});
        
	}//MetadataChanged

}
