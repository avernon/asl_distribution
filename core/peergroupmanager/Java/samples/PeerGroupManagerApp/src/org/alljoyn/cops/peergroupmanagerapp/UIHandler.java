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

package org.alljoyn.cops.peergroupmanagerapp;

import org.alljoyn.bus.Status;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.widget.Toast;

public class UIHandler extends Handler {
    
    private static final String TAG = "GroupManagerApp";

    /* UI Handler Codes */
    public static final int TOAST_MSG = 0;
    public static final int TOGGLE_DISCOVERY_BUTTONS = 1;
    public static final int UPDATE_GROUP_LIST_SPINNER = 2;
    
    private MainActivity mActivity;
    
    public UIHandler (MainActivity activity) {
        mActivity = activity;
    }
    
    @Override
    public void handleMessage(Message msg) {
        switch (msg.what) {
        case TOAST_MSG:
            Toast.makeText(mActivity.getApplicationContext(), (String) msg.obj, Toast.LENGTH_LONG).show();
            break;
        case UPDATE_GROUP_LIST_SPINNER:
            Bundle data = msg.getData();
            mActivity.updateGroupListSpinner(data.getStringArray("availableGroupList"), 
            		data.getStringArray("hostedGroupList"), 
            		data.getStringArray("joinedGroupList"), 
            		data.getStringArray("lockedGroupList"));
            break;
        default:
            break;
        }
    }
    
    public void logInfo(String msg) {
        Log.i(TAG, msg);
    }
    
    public void logStatus(String msg, Status status) {
        String log = String.format("%s: %s", msg, status);
        if (status == Status.OK) {
            Log.i(TAG, log);
        } else {
            Message toastMsg = obtainMessage(TOAST_MSG, log);
            sendMessage(toastMsg);
            Log.e(TAG, log);
        }
    }

    public void logError(String msg) {
        Message toastMsg = obtainMessage(TOAST_MSG, msg);
        sendMessage(toastMsg);
        Log.e(TAG, msg);
    }

    public void logException(String msg, Exception ex) {
        String log = String.format("%s: %s", msg, ex);
        Message toastMsg = obtainMessage(TOAST_MSG, log);
        sendMessage(toastMsg);
        Log.e(TAG, log, ex);
    }
}
