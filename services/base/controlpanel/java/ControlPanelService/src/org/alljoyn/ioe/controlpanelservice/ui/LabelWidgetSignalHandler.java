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
import org.alljoyn.ioe.controlpanelservice.communication.interfaces.Label;

import android.util.Log;

public class LabelWidgetSignalHandler implements Label {
    private static final String TAG = "cpan" + LabelWidgetSignalHandler.class.getSimpleName();
    
    /**
     * Container widget to be notified about signal receiving
     */
    private LabelWidget labelWidget;

    /**
     * Constructor
     * @param labelWidget
     */
    public LabelWidgetSignalHandler(LabelWidget labelWidget) {
        this.labelWidget = labelWidget;
    }

	@Override
	public short getVersion() throws BusException {
		// TODO Auto-generated method stub
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
	
	@Override
	public String getLabel() throws BusException {
		// TODO Auto-generated method stub
		return null;
	}
	
	/**
	 * @see org.alljoyn.ioe.controlpanelservice.communication.interfaces.Label#MetadataChanged()
	 */
	@Override
	public void MetadataChanged() throws BusException {
        
        String msg = "Device: '" + labelWidget.device.getDeviceId() +
                "', labelWidget: '" + labelWidget.objectPath + "', received METADATA_CHANGED signal";

        Log.d(TAG, msg);

        final ControlPanelEventsListener eventsListener = labelWidget.controlPanel.getEventsListener();
        try {
            labelWidget.refreshProperties();
        } catch (ControlPanelException cpe) {
            msg += ", but failed to refresh the LabelWidget properties";
            Log.e(TAG, msg);
            eventsListener.errorOccurred(labelWidget.controlPanel, msg);
            return;
        }

        //Delegate to the listener on a separate thread
        TaskManager.getInstance().execute( new Runnable() {
			@Override
			public void run() {
				eventsListener.metadataChanged(labelWidget.controlPanel, labelWidget);
			}
		});
	}//MetadataChanged

}
