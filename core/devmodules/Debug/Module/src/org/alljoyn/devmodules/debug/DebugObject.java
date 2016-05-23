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
package org.alljoyn.devmodules.debug;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Vector;

import org.alljoyn.bus.*;
import org.alljoyn.bus.AuthListener.AuthRequest;
import org.alljoyn.bus.AuthListener.PasswordRequest;
import org.alljoyn.bus.AuthListener.UserNameRequest;
import org.alljoyn.bus.annotation.BusSignalHandler;
import org.json.JSONException;
import org.json.JSONObject;

import android.app.ListActivity;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.hardware.*;
import android.os.Bundle;
import android.os.Message;
import android.os.Messenger;
import android.os.RemoteException;
import android.util.Log;

public class DebugObject implements DebugInterface, BusObject {
	public void DebugMessage(String service, int level, String message) throws BusException {
		//Signal no implementation
	}
	
	public void StopLogging() {
		Log.d(this.getClass().getName(),"Temp Method");
//		DebugImpl impl = (DebugImpl)CoreLogic.getInstance().getObject(DebugConstants.OBJECT_PATH.substring(1));
//		impl.
	}
}
