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
import org.alljoyn.ioe.controlpanelservice.communication.interfaces.ActionControl;
import org.alljoyn.ioe.controlpanelservice.communication.interfaces.ActionControlSecured;

import android.util.Log;

/**
 * The class is a signal handler that is responsible to receive signals of ActionControl interface. <br>
 *  Signals: <br>
 *  - MetadataChanged
 */
public class ActionWidgetSignalHandler implements ActionControl, ActionControlSecured {
	private static final String TAG = "cpan" + ActionWidgetSignalHandler.class.getSimpleName();

    /**
     * Container widget to be notified about signal receiving
     */
    private ActionWidget actionWidget;
	
	/**
	 * Constructor
	 * @param actionWidget
	 */
	public ActionWidgetSignalHandler(ActionWidget actionWidget) {
		this.actionWidget = actionWidget;
	}

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.ActionControl#getVersion()
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
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.ActionControl#Exec()
	 */
	@Override
	public void Exec() {
	}

	/**
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.ActionControl#MetadataChanged()
	 */
	@Override
	public void MetadataChanged() {
       
        String msg = "Device: '" + actionWidget.device.getDeviceId() +
                "', ActionWidget: '" + actionWidget.objectPath + "', received METADATA_CHANGED signal";
        
        Log.d(TAG, msg);
        
        final ControlPanelEventsListener eventsListener = actionWidget.controlPanel.getEventsListener();
        try{
        	actionWidget.refreshProperties();
        }
        catch(ControlPanelException cpe) {
            msg += ", but failed to refresh the ActionWidget properties";
            Log.e(TAG, msg);
            eventsListener.errorOccurred(actionWidget.controlPanel, msg);
            return;
        }

        //Delegate to the listener on a separate thread
        TaskManager.getInstance().execute( new Runnable() {
			@Override
			public void run() {
				eventsListener.metadataChanged(actionWidget.controlPanel, actionWidget);
			}
		});
	}//MetadataChanged

}
