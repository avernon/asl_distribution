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

import java.util.ArrayList;
import java.util.HashMap;


import android.content.Context;
import android.util.Log;

public class RemoteDebugList {

	private static final String TAG = "RemoteDebugList";

	// Array of Services
	private static ArrayList<String>      mServiceList           = new ArrayList<String>();

	// Hash map of debug lists, indexed by service name
	private static HashMap<String,DebugMessageList> mServiceDebugList = new HashMap<String,DebugMessageList>();


	private static RemoteDebugList _instance; // the singleton version

	private RemoteDebugList() { 
		// private to control usage
		checkSetup();
	} 


	// prevent instantiation via an explicit clone() call
	public Object clone() throws CloneNotSupportedException {
		throw new CloneNotSupportedException();
	}

	// method to return reference to internal data
	public static synchronized RemoteDebugList getInstance() {
		if (_instance == null) {
			_instance = new RemoteDebugList();
			checkSetup();
		}
		return _instance;
	}

	// check that list has been set up. If not, create them
	private static void checkSetup(){
		if (mServiceList==null){
			mServiceList = new ArrayList<String>();
			mServiceList.clear();
		}

		if (mServiceDebugList==null){
			mServiceDebugList = new HashMap<String,DebugMessageList>();
			mServiceDebugList.clear();
		}
	}

	// clear lists
	public static synchronized void clear (){
		checkSetup();
		mServiceList.clear();
		mServiceDebugList.clear();
	}

	// add a service to the list
	public static synchronized void addService (String service){
		Log.v(TAG, "addService("+service+")");
		checkSetup();

		if (!mServiceList.contains(service)){
			// add the service to the list and create a new debug list for it
			mServiceList.add(service);
			DebugMessageList msglist = new DebugMessageList();
			mServiceDebugList.put(service, msglist);
		}
	}

	// remove a service from the list
	public static synchronized void removeService (String service){
		Log.v(TAG, "removeService("+service+")");
		checkSetup();

		if (mServiceList.contains(service)){
			mServiceList.remove(service);
			mServiceDebugList.remove(service);
		}

	}

	// list the services currently known. Returns null if none found
	public static synchronized String[] getServiceList (){
		String[] services = null;

		checkSetup();

		if (!mServiceList.isEmpty()){
			services = mServiceList.toArray(new String[mServiceList.size()]);
		}
		return services;
	}

	// add a message
	public static synchronized void add (String service, DebugMessageDescriptor dmd){
		checkSetup();
		if (!mServiceList.contains(service)){
			mServiceDebugList.get(service).add(dmd);
		}
	}

	// get the last item in the list
	public static synchronized DebugMessageDescriptor get (String service){
		checkSetup();
		if (!mServiceList.contains(service)){
			return mServiceDebugList.get(service).get();
		} else {
			return null;
		}
	}

	// get the nth item in the list
	public static synchronized DebugMessageDescriptor get (String service, int n){
		checkSetup();
		if (!mServiceList.contains(service)){
			return mServiceDebugList.get(service).get(n);
		} else {
			return null;
		}
	}


	// get the number of messages stored
	public static synchronized int size(){
		checkSetup();
		return mServiceList.size();
	}


	// return entire list of messages for the specified service
	public static synchronized DebugMessageDescriptor[] getAll(String service) {
		checkSetup();
		if (!mServiceList.isEmpty()){
			return mServiceDebugList.get(service).toArray();
		} else {
			return null;
		}

	}


} // DebugList
