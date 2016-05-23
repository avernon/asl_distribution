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
package org.alljoyn.devmodules;

import java.util.ArrayList;

import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.ProxyBusObject;
import org.alljoyn.devmodules.sessionmanager.SessionManager;

import android.app.Activity;
import android.util.Log;


public abstract class APICore {
	
	protected SessionManager sessionManager;
	protected static final String SERVICE_NAME = "org.alljoyn.api.devmodules";
	protected static final short SERVICE_PORT = 24;
	protected static String SESSION_NAME = "";
	protected static final String OBJECT_PATH_PREFIX = "/devmodulesapi/";
	protected int mSessionId;
	protected static APICore instance;
	public boolean isReady = false;
	
	ArrayList<Object> objectList = new ArrayList<Object>(); 
	
	public static void StartAllJoynServices(Activity i) throws Exception {
		Log.w("APICore", "StartAllJoynServices in base class. Shouldn't be here!!!");
		if(instance != null) {
			instance.StartAllJoynServices(i);
		}
	}
	
	public static void StopAllJoynServices(Activity i) {
		Log.w("APICore", "StopAllJoynServices in base class. Shouldn't be here!!!");
		if(instance != null) {
			instance.StopAllJoynServices(i);
		}
	}
	
	public static String[] GetNearbyDevices() throws Exception {
		Log.w("APICore", "GetNearbyDevices in base class. Shouldn't be here!!!");
		if(instance != null) {
			return instance.GetNearbyDevices();
		}
		return null;
	}
	
	public static void StartService(String service) throws Exception {
		Log.w("APICore", "StartService in base class. Shouldn't be here!!!");
		if(instance != null) {
			instance.StartService(service);
		}
	}
	
	public static String[] GetServices() throws Exception {
		Log.w("APICore", "GetServices in base class. Shouldn't be here!!!");
		if(instance != null) {
			return instance.GetServices();
		}
		return null;
	}
	
	public static void StartAllServices() throws Exception {
		Log.w("APICore", "StartAllServices in base class. Shouldn't be here!!!");
		if(instance != null) {
			instance.StartAllServices();
		}
	}

	//----------------
	
	public static APICore getInstance() {
		return instance;
	}
	
	protected void registerBusObject(BusObject object, String path) {
		Log.w("APICore", "registerBusObject in base class. Shouldn't be here!!!");
		if(instance != null) {
			instance.registerBusObject(object, path);
		}
	}
	
	protected void registerSignalHandler(Object object) {
		Log.w("APICore", "registerSignalHandler in base class. Shouldn't be here!!!");
		if(instance != null) {
			instance.registerSignalHandler(object);
		}
	}
	
	public ProxyBusObject getProxyBusObject(String peer, Class[] interfaces)
	{
		Log.w("APICore", "getProxyBusObject in base class. Shouldn't be here!!!");
		if(instance != null) {
			return instance.getProxyBusObject(peer, interfaces);
		}
		return null;
	}	
	
	public void EnableConcurrentCallbacks() {
	}
}

