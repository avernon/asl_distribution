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
package org.alljoyn.aroundme.RemoteMedia;

import java.util.ArrayList;
import java.util.HashMap;

import org.alljoyn.aroundme.Adapters.RemoteDebugAdapter;

import android.content.Context;

// Singleton class for managing the list of debug messages for all of the remote connected debug services

public class RemoteDebugListManager {


	private static final String TAG = "RemoteDebugListManager";


	// Hash Map for holding the data - one for each connected debug service

	private static HashMap<String,RemoteDebugAdapter> mRemDebugList     = new HashMap<String,RemoteDebugAdapter>();

	private static RemoteDebugListManager          _manager;               // the singleton version

	// Context of the current Application
	private static Context mContext; 

	private RemoteDebugListManager() { 
		// no implementation, just private to control usage
	} 


	public static synchronized void setContext (Context context){
		mContext = context;
	}

	// prevent instantiation via an implicit or explicit clone() call
	public Object clone() throws CloneNotSupportedException {
		throw new CloneNotSupportedException();
	}

	// method to return reference to internal data
	public static synchronized RemoteDebugListManager getAdapter() {
		if (_manager == null) {
			_manager = new RemoteDebugListManager();
		}
		return _manager;
	}

	// methods to add and get the various types of lists

	public static synchronized void addDebugList (String service){
		if (!mRemDebugList.containsKey(service)){
			RemoteDebugAdapter rda = new RemoteDebugAdapter (mContext);
			mRemDebugList.put(service, rda);
		}
	}

	public static synchronized void removeDebugList (String service){
		if (mRemDebugList.containsKey(service)){
			mRemDebugList.remove(service);
		}
	}

	// get the adapter for a specified service
	public static synchronized RemoteDebugAdapter get(String service) {
		if (contains(service)){
			return mRemDebugList.get(service);
		} else {
			return null;
		}
	}

	// check to see whether service is present in list
	public static synchronized boolean contains(String service) {
		return (mRemDebugList.containsKey(service));
	}

	// check to see whether list is empty
	public static synchronized boolean isEmpty() {
		return (mRemDebugList.isEmpty());
	}

	// return the number of services present
	public static synchronized int size() {
		return (mRemDebugList.size());
	}


} // RemoteDebugListManager
