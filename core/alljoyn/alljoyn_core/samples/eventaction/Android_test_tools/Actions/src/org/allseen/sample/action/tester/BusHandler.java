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

package org.allseen.sample.action.tester;

import java.util.HashMap;
import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.preference.PreferenceManager;
import android.util.Log;

public class BusHandler extends Handler {
	public static final String TAG = "BusHandler";
		
	private Context mContext;
	private EventActionListener listener;
	private SharedPreferences mPrefs; 
	private static final String PREFS_KEY = "engine_rules";

    /* These are the messages sent to the BusHandler from the UI/Application thread. */
    public static final int INITIALIZE = 0;
    public static final int INTROSPECT = 2;
    public static final int CALL_ACTION = 3;
    public static final int SHUTDOWN = 100;
    
    private HashMap<String,Device> remoteInfo = new HashMap<String, Device>();
    
    /*
     * Native JNI methods
     */
    static {
        System.loadLibrary("gnustl_shared");
        System.loadLibrary("MyAllJoynCode");
    }

	 /** Initialize AllJoyn in JNI(C++) */
    private native void initialize(String packageName);
    
    /** Perform introspection with description in JNI(C++) */
    private native String doIntrospection(String sessionName, String path, int sessionId);
    
    private native void introspectionDone(int sessionId);

    /** Save and enable a rule */
    private native void callAction(
								//action
								  String jAUniqueName, String jAPath,
								  String jAIface, String jAMember, String jASig);
    
    /** clear out the saved rules in local memory and persistent memory */
    private native void deleteAllRules();
    
    /** Clean up and shutdown AllJoyn in JNI(C++) */
    private native void shutdown();

    /**
     * Constructor
     */
    public BusHandler(Looper looper, Context context, EventActionListener listener) {
        super(looper);
        this.mContext = context;
        this.listener = listener;
        this.mPrefs = PreferenceManager.getDefaultSharedPreferences(context);
    }
    
    /**
     * Callback from jni code invoked via an About Annouce callback
     * @param sessionName	name of the remote application
     * @param sessionId		sessionId that was set
     * @param friendlyName	name to display in the UI
     */
	public void foundActionApplication(String sessionName, int sessionId, String friendlyName) {
		Log.d(TAG, "Found device with friendly name: "+friendlyName);
		Message msg = this.obtainMessage(INTROSPECT);
		Bundle data = new Bundle();
		data.putString("name", sessionName);
		data.putString("friendly", friendlyName);
		msg.setData(data);
		msg.arg1 = sessionId;
		this.sendMessage(msg);
	}

    /**
     * Callback from jni code invoked when a device goes away
     * @param sessionId		sessionId that was lost
     */
	public void lostActionApplication(int sessionId) {
		Log.d(TAG, "Lost applicatoin with session id: "+sessionId);
		listener.onActionLost(sessionId);
	}
	
	/**
	 * Helper method to send an Add Rule request to the message Handler
	 */
	public void callAction(Bundle b) {
		Message msg = this.obtainMessage(CALL_ACTION);
		msg.setData(b);
		msg.arg1 = 1;
		this.sendMessage(msg);
	}
    

	/**
	 * Helper method to start the introspection process on a remote AllJoyn Appliction
	 */
    public void introspect(String sessionName, int sessionId, String path, DescriptionParser node) {
    	try{
        	String xml = doIntrospection(sessionName, path, sessionId);
        	if(xml == null) {
        		/** The device must not support the new org.allseen.Introspectable interface */
        		return;
        	}
        	Log.d(TAG, "path: "+path+"\n"+xml);
	    	node.parse(xml);

	    	/*
	    	 * Parsing complete, collect the actions and assing them into the remoteInfo object
	    	 */
	    	Device info = remoteInfo.get(sessionName);
	    	for(Description eai : node.getActions()) {
		    	info.addAction((ActionDescription)eai);
	    	}
	    	/*
	    	 * Introspect then parse the children paths
	    	 */
	    	for(DescriptionParser in : node.getChidren()) {
	    		/*
	    		 * Recursively call and process the child nodes looking for actions and events
	    		 */
	    		introspect(sessionName, sessionId, in.getPath(), in);
	    	}
	    	
	    	/*
	    	 * If the root node then parsing complete, inform listener of events/actions found
	    	 */
	    	if(node.getPath().equals("/")) { //root node, recursive parsing complete 
	    		if(info.getActions().size() > 0) { //We have actions so inform as such to the UI
	    			listener.onActionsFound(info);
	    			introspectionDone(sessionId);
	    		}
	    	}
    	}catch(Exception e) {
    		e.printStackTrace();
    	}
    }
    

	/**
	 * Helper method used by Handler to call into JNI to save the rule.
	 */
    private void doCallAction(Bundle b) {
    	callAction(
				//action
				b.getString("aUniqueName"),
				b.getString("aPath"),
				b.getString("aIface"),
				b.getString("aMember"),
				b.getString("aSig"));
    }
    
	/**
	 * Handles the messages so that the UI thread is not blocked
	 */
    @Override
    public void handleMessage(Message msg) {
        switch (msg.what) {
        /* Connect to the bus and start our service. */
        case INITIALIZE:
        { 
        	initialize(mContext.getPackageName());
        	break;
        }
        case INTROSPECT:
        {
        	try{
	        	String sessionName = msg.getData().getString("name");
	        	Device device = new Device(sessionName, msg.arg1, msg.getData().getString("friendly"), "/");
	        	remoteInfo.put(sessionName, device);
	        	introspect(device.getSessionName(),
	        			device.getSessionId(),
	        			device.getPath(),
	        			new DescriptionParser(device.getPath())
	        			);
        	} catch( Exception e ) {
        		e.printStackTrace();
        	}
        	break;
        }
        case CALL_ACTION:
        {
        	try{
        		doCallAction(msg.getData());
        	} catch( Exception e ) {
        		e.printStackTrace();
        	}
        	break;
        }
        /* Release all resources acquired in connect. */
        case SHUTDOWN: {
            shutdown();
            break;   
        }

        default:
            break;
        }
    }
    
    
}
