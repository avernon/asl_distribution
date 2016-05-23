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

public class LocalDebugList {


	private static final String TAG = "DebugList";

	// Arrays for holding the data
	private static DebugMessageList mDebugList ;


	private static LocalDebugList _instance; // the singleton version

	private LocalDebugList() { 
		// private to control usage
		checkSetup();
	} 


	// prevent instantiation via an explicit clone() call
	public Object clone() throws CloneNotSupportedException {
		throw new CloneNotSupportedException();
	}

	// method to return reference to internal data
	public static synchronized LocalDebugList getInstance() {
		if (_instance == null) {
			_instance = new LocalDebugList();
			checkSetup();
		}
		return _instance;
	}

	// check that list has been set up. If not, create them
	private static void checkSetup(){
		if (mDebugList==null)
		{
			mDebugList = new DebugMessageList();	
			mDebugList.clear();
		}
	}

	// clear lists
	public static synchronized void clear (){
		mDebugList.clear();
	}

	// add a profile to the list
	public static synchronized void add (int level, String message){

		checkSetup();

		DebugMessageDescriptor dd = new DebugMessageDescriptor();
		dd.level = level;
		dd.message = message;
		mDebugList.add(dd);

	}

	// get the last item in the list
	public static synchronized DebugMessageDescriptor get (){
		checkSetup();
		if (!mDebugList.isEmpty()){
			return mDebugList.get(mDebugList.size());
		} else {
			return null;
		}
	}


	// get the number of messages stored
	public static synchronized int size(){
		checkSetup();
		return mDebugList.size();
	}


	// return list of profiles
	public static synchronized DebugMessageDescriptor[] getAll() {
		checkSetup();
		if (!mDebugList.isEmpty()){
			return mDebugList.getAll();
		} else {
			return new DebugMessageDescriptor[0];
		}

	}


} // DebugList
