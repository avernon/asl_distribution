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
package org.alljoyn.devmodules.api;

import java.util.ArrayList;
import java.util.Vector;
import java.util.concurrent.CountDownLatch;

import org.alljoyn.bus.BusAttachment;
import org.alljoyn.bus.SessionOpts;
import org.alljoyn.bus.SessionPortListener;
import org.alljoyn.bus.Status;
import org.alljoyn.devmodules.sessionmanager.SessionManager;
import org.alljoyn.devmodules.groups.GroupSessionManager;
import org.alljoyn.devmodules.interfaces.AllJoynContainerInterface;
import org.alljoyn.devmodules.interfaces.ModuleAPIInterface;
import org.alljoyn.devmodules.loader.ContainerLoader;

import android.util.Log;

public class ModuleAPIManager implements AllJoynContainerInterface {
	static 
    {
        System.loadLibrary("alljoyn_java");
    }
	
	private static final String TAG = "ModuleAPIManager";
	
	private SessionManager sessionManager;
	private static final String SERVICE_NAME = "org.alljoyn.api.devmodules";
	private static final short SERVICE_PORT = 24;
	private static final String SESSION_NAME = "api";
	private static final String OBJECT_PATH_PREFIX = "/devmodulesapi/";
	private int mSessionId;
	
	public Vector<ModuleAPIInterface> moduleList = new Vector<ModuleAPIInterface>();
	
	//public static CallbackInterface callbackInterface;
	
	private static ModuleAPIManager instance;
	
	public ModuleAPIManager() {
		
	}
	
	public static ModuleAPIManager getInstance(String apiServiceId) {
		if(instance == null) {
			instance = new ModuleAPIManager();
		    instance.sessionManager = new SessionManager(SERVICE_NAME, true);
		    //instance.sessionManager.setDebug(true);
		    
		    instance.sessionManager.registerBusObject(new CoreAPIObject(), OBJECT_PATH_PREFIX+CoreAPIObject.OBJECT_PATH);

		    ContainerLoader.LoadAPIImpl(instance);
		    
		    Log.d(TAG, "Added objects to vector, now going to register their busObjects");
		    for(ModuleAPIInterface module:instance.moduleList) {
		    	Log.d(TAG, "module: "+module.getBusObject());
		    	instance.sessionManager.registerBusObject(module.getBusObject(), OBJECT_PATH_PREFIX+module.getBusObjectPath());
		    	Log.d(TAG, "callback : "+module.getCallbackBusObject());
		    	Log.d(TAG, "callback : "+module.getCallbackBusObjectPath());
		    	instance.sessionManager.registerBusObject(module.getCallbackBusObject(), module.getCallbackBusObjectPath());
		    }
		    Log.d(TAG, "ConnectBus...");
		    instance.sessionManager.connectBus();
		    
		    instance.sessionManager.createSession(SESSION_NAME+"._"+instance.sessionManager.getBusAttachment().getGlobalGUIDString()+"._"+apiServiceId, SERVICE_PORT, new SessionPortListener() {
		    	public boolean acceptSessionJoiner(short sessionPort, String joiner, SessionOpts sessionOpts) {
	                Log.d(TAG, "SessionPortListener.acceptSessionJoiner(" + sessionPort + ", " + joiner + ", " + sessionOpts.toString() + ")");
	        		if (sessionPort == SERVICE_PORT) {
	        			return true;
	        		}
	        		return false;
	            }
	            
	            public void sessionJoined(short sessionPort, int id, String joiner) {
	            	Log.d(TAG, "User " + joiner + " joined., id=" + id);
	            	//TODO:Change this to signal emitter!!!!
//	            	callbackInterface = instance.sessionManager.getBusAttachment().getProxyBusObject(joiner, 
//	            			CallbackInterface.OBJECT_PATH,
//	    					id,
//	    					new Class<?>[] { CallbackInterface.class }).getInterface(CallbackInterface.class);
	            	//Setup the callbacks for each module
	            	for(ModuleAPIInterface module:instance.moduleList) {
	            		module.connectCallbackObject(id, joiner);
	            	}
	            }
		    }, new SessionOpts(SessionOpts.TRAFFIC_MESSAGES, true, SessionOpts.PROXIMITY_PHYSICAL, SessionOpts.TRANSPORT_LOCAL));
		    Log.i(TAG, "Did this advertise????");
		}
		return instance;
	}

	public String getUniqueID() {
		return null;
	}

	public SessionManager getSessionManager() {
		return instance.sessionManager;
	}
	
	public int getGroupSessionId(String groupName) throws Exception {
		throw new Exception("Not Supported");
	}

	public BusAttachment getBusAttachment() {
		return instance.sessionManager.getBusAttachment();
	}

	public Status createSession(String sessionName, short sessionPort,
			SessionPortListener sessionPortListener, SessionOpts sessionOpts) {
		return instance.sessionManager.createSession(sessionName, sessionPort, sessionPortListener, sessionOpts);
	}

	public ArrayList<String> getParticipants(String uID) {
		return null;
	}

	public String whoIsBusId(String sender) {
		// TODO Auto-generated method stub
		return null;
	}
}
