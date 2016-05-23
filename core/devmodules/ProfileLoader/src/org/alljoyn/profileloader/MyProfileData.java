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

package org.alljoyn.profileloader;

import org.alljoyn.devmodules.api.profilemanager.ProfileManagerAPI;
import org.alljoyn.devmodules.common.ProfileDescriptor;
import org.alljoyn.storage.ProfileCache;


import android.util.Log;


/*
 * Class to hold profile data of the current user
 * This is a Singleton class, i.e. can be accessed from different scopes.
 * It is also thread safe, which is why all variables are accessed via a method
 */
public class MyProfileData  {

	private static final String  TAG = "MyProfileData";

	private static ProfileDescriptor _profile;

	// prevent class from being instantiated via new constructor
	private MyProfileData (){
		// do nothing
	}

	// prevent instantiation via an explicit clone() call
	public Object clone() throws CloneNotSupportedException {
		throw new CloneNotSupportedException();
	}

	// method to return reference to internal data
	public static synchronized ProfileDescriptor getProfile() {
		if (_profile == null) {
			try {
				_profile = ProfileManagerAPI.GetMyProfile();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		return _profile;
	}

	// method to determine whether the profile has been set up or not
	public static synchronized boolean isSet() {
		if (_profile.getField(ProfileDescriptor.ProfileFields.NAME_DISPLAY).length()>0){
			return true;
		} else {
			return false;
		}
	}

	// clear/reset the current profile data
	public static synchronized void clear(){

	}

	// Methods to get/set data (thread safe)
	// Note that we should not return null values for AllJoyn methods (how can you send a null value)
	// so the 'checkXYZ' functions make sure that a non-null value is returned

	public static synchronized String getSvcName (){ 
		return _profile.getField("profileid"); 
	}

	public static synchronized void setProfile (ProfileDescriptor profile){ 
		Log.d(TAG, "My Profile set to:\n"+profile.getJSONString());
		_profile = profile; 
		// Also save the profile to storage
		ProfileCache.saveProfile(getSvcName(), _profile);
	}



} // MyProfileData
