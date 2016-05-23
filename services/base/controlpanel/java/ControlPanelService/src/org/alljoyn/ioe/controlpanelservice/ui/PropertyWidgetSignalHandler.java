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

import java.util.Map;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.Variant;
import org.alljoyn.ioe.controlpanelservice.ControlPanelException;
import org.alljoyn.ioe.controlpanelservice.communication.TaskManager;
import org.alljoyn.ioe.controlpanelservice.communication.interfaces.PropertyControl;
import org.alljoyn.ioe.controlpanelservice.communication.interfaces.PropertyControlSecured;

import android.util.Log;

/**
 * The class is a signal handler that is responsible to receive signals of PropertyControl interface. <br>
 *  Signals: <br>
 *  - ValueChanged    <br>
 *  - MetadataChanged
 */
public class PropertyWidgetSignalHandler implements PropertyControlSecured, PropertyControl {
	private static final String TAG = "cpan" + PropertyWidgetSignalHandler.class.getSimpleName();

	
	/**
	 * Property widget to be notified about signal receiving
	 */
	private PropertyWidget propertyWidget;

	/**
	 * @param propertyWidget
	 */
	public PropertyWidgetSignalHandler(PropertyWidget propertyWidget) {
		this.propertyWidget = propertyWidget;
	}

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.PropertyControl#getVersion()
	 */
	@Override
	public short getVersion() throws BusException {
		return 0;
	}

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.PropertyControl#getValue()
	 */
	@Override
	public Variant getValue() throws BusException {
		return null;
	}

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.PropertyControl#setValue(org.alljoyn.bus.Variant)
	 */
	@Override
	public void setValue(Variant value) throws BusException {
	}


	@Override
	public int getStates() throws BusException {
		return 0;
	}

	@Override
	public Map<Short, Variant> getOptParams() throws BusException {
		return null;
	}
	

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.PropertyControl#ValueChanged(org.alljoyn.bus.Variant)
	 */
	@Override
	public void ValueChanged(Variant value) throws BusException {
		
	    ControlPanelEventsListener eventsListener = propertyWidget.controlPanel.getEventsListener();
	    
	    String msg = "Device: '" + propertyWidget.device.getDeviceId() +
                "', PropertyWidget: '" + propertyWidget.objectPath + "', received VALUE_CHANGED signal";
    
	    Log.d(TAG, msg);
	    
	    try {
			Object unmarshVal = propertyWidget.unmarshalCurrentValue(value);
			Log.d(TAG, "The new property: '" + propertyWidget.objectPath + "' value is: '" + unmarshVal +  "'");
			eventsListener.valueChanged(propertyWidget.controlPanel, propertyWidget, unmarshVal);
		} catch (ControlPanelException cpe) {
			msg += ", but failed to unmarshal the received data, Error: '" + cpe.getMessage() + "'";
			Log.e(TAG, msg);
			eventsListener.errorOccurred(propertyWidget.controlPanel, msg);
		}
	}//ValueChanged

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.PropertyControl#MetadataChanged()
	 */
	@Override
	public void MetadataChanged() throws BusException {
        
        String msg = "Device: '" + propertyWidget.device.getDeviceId() +
                "', PropertyWidget: '" + propertyWidget.objectPath + "', received METADATA_CHANGED signal";

        Log.d(TAG, msg);
        
        final ControlPanelEventsListener eventsListener = propertyWidget.controlPanel.getEventsListener();
        
        try {
        	propertyWidget.refreshProperties();
        }
        catch(ControlPanelException cpe) {
        	 msg += ", but failed to refresh the widget properties";
        	 Log.e(TAG, msg);
             eventsListener.errorOccurred(propertyWidget.controlPanel, msg);
             return;
        }
        
        //Delegate to the listener on a separate thread
        TaskManager.getInstance().execute( new Runnable() {
			@Override
			public void run() {
				eventsListener.metadataChanged(propertyWidget.controlPanel, propertyWidget);
			}
		});
	}//MetadataChanged
	
}
