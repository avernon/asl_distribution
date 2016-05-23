package org.alljoyn.ioe.controlpaneladapter;
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

import org.alljoyn.ioe.controlpanelservice.ControlPanelException;
import org.alljoyn.ioe.controlpanelservice.ui.ActionWidget;
import org.alljoyn.ioe.controlpanelservice.ui.AlertDialogWidget.DialogButton;

import android.os.AsyncTask;
import android.util.Log;

/**
 * A Utility class that has 2 functions:
 * 1. Executing an action on the remote device, in a background process, to free the UI thread.
 * 2. Notifying the caller about the result. 
 */
abstract class ExecuteActionAsyncTask extends AsyncTask<Object, Void, ControlPanelException> {

	private final static String TAG = "cpapp" + ExecuteActionAsyncTask.class.getSimpleName();

	@Override
	/**
	 * This background processor assumes params[0] to be a ActionWidget or DialogButton.
	 */
	protected ControlPanelException doInBackground(Object... params) {
		try {
			if (params[0] instanceof ActionWidget) {
				ActionWidget actionWidget 	= (ActionWidget) params[0];
				Log.d(TAG, String.format("Executing action '%s'", actionWidget.getLabel()));
				actionWidget.exec();
				Log.d(TAG, "Action executed");
			} else if (params[0] instanceof DialogButton) {
				DialogButton dialogButton 	= (DialogButton) params[0];
				Log.d(TAG, String.format("Executing action '%s'", dialogButton.getLabel()));
				dialogButton.exec();
				Log.d(TAG, "Action executed");
			}				
		} catch (ControlPanelException e) {
			Log.e(TAG, "Failed executing the action, error in calling remote object: '" + e.getMessage() + "'");
			return e;
		}
		return null; // No exception...ok!
	}

	
	@Override
	/**
	 * Exception means failure. Otherwise - success.  
	 */
    protected void onPostExecute(ControlPanelException e) {
		if (e != null) {
			onFailure(e);
		} else {
			onSuccess();
		}
	}

	/**
	 * Notify the caller about an exception.  
	 */
    abstract protected void onFailure(ControlPanelException e);
	/**
	 * Notify the caller about success.  
	 */
    abstract protected void onSuccess();
	
}
