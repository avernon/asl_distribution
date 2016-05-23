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

package org.alljoyn.ns.sampleapp.controlpanel;

import org.alljoyn.ioe.controlpanelservice.ControlPanelException;
import org.alljoyn.ioe.controlpanelservice.ui.DeviceControlPanel;

import android.os.AsyncTask;

/**
 * Calls {@link DeviceControlPanel#getRootElement(org.alljoyn.ioe.controlpanelservice.ui.ControlPanelEventsListener)}
 */
public class RootElementRequest extends AsyncTask<DeviceControlPanel, Void, Object> {

	/**
	 * Control Panel manager
	 */
	private final ControlPanelManager manager;

	/**
	 * Constructor
	 */
	public RootElementRequest(ControlPanelManager manager) {
		super();
		this.manager = manager;
	}

	/**
	 * @see android.os.AsyncTask#doInBackground(java.lang.Object[])
	 */
	@Override
	protected Object doInBackground(DeviceControlPanel... controlPanel) {
		
		try {
			return controlPanel[0].getRootElement(manager);
		} catch (ControlPanelException cpe) {
			return cpe;
		}
	}//doInBackground

	/**
	 * @see android.os.AsyncTask#onPostExecute(java.lang.Object)
	 */
	@Override
	protected void onPostExecute(Object result) {
		manager.onReadyRootElementRequest(result);
	}//onPostExecute
	
}
