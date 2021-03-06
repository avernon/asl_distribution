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
package org.alljoyn.storage;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.FilenameFilter;

import org.alljoyn.devmodules.common.MediaTypes;


import android.os.Environment;
import android.util.Log;

// Class to handle caching of received media files in local storage
// Files are prefixed with the source user ID, so be careful processing them later
// e.g. if they are moved into the 'normal' files system

// File extensions etc are not modified, so we handle potential conflicts by using the 'unique name' 
// of the supplying service as a prefix, i.e. you can the same files form multiple users and they will be stored 
// separately
public class MediaCache extends BaseCache {

	private static final String TAG                  = "MediaCache";
	private static final String MEDIA_CACHE_DIR      = "/sdcard/.alljoyn/media/received/";
	private static boolean      mCacheReady          = false;
	
	private static String [] subdirs = { MediaTypes.APP, 
											MediaTypes.FILE, 
											MediaTypes.MUSIC,
											MediaTypes.PHOTO, 
											MediaTypes.VIDEO };
	

	// Get the directory location
	protected static String getPath(){
		return MEDIA_CACHE_DIR;
	}

	protected static String getLogTag() {
		return TAG;
	}


	 
	/////////////////////////////////////////////////////////////////////////
	// File naming conventions (up front so you see this first)
	/////////////////////////////////////////////////////////////////////////

	// We use the "userid" to store files, which is the last (unique) part of the service name
	// It is safe to specify either the full service name or just the userid, either works
	
	// return the userid from the full service name
	private static String getUserid (String service){
		String userid = service;
		if (service.contains(".")){
			userid = service.substring(service.lastIndexOf(".")+1);
		} 
		return userid;
	}


	 
	/////////////////////////////////////////////////////////////////////////
	// Generic stuff (Media-independent)
	/////////////////////////////////////////////////////////////////////////


	// Run initial checks, make sure directories are there and writeable etc.
	public static void init(){
		if(mCacheReady)
			return;
		mCacheReady = false;

		try {
			// check that storage is accessible
			if (checkStorage()){
				// make sure directory exists
				File lclpath = new File(MEDIA_CACHE_DIR);

				// Make sure the  directory exists.
				lclpath.mkdirs();
				if (lclpath.exists()){
					mCacheReady = true;
					Log.d(TAG, "Media cache directory set up: "+MEDIA_CACHE_DIR);
					
					//loop and check the subdirectories too
					for (int i=0; i<subdirs.length; i++){
						File sd = new File (MEDIA_CACHE_DIR+subdirs[i]);
						sd.mkdirs();
					}
				} else {
					Log.e(TAG, "Unkown error, cache not set up");
				}

			} else {
				Log.e(TAG, "*** External Storage not available, cannot save media queries!!! ***");
			}
		} catch (Exception e) {
			Log.e(TAG, "Error setting up media cache ("+MEDIA_CACHE_DIR+"): "+e.toString());
		}
	}//init

	
	
	/////////////////////////////////////////////////////////////////////////
	// Media-Specific
	// There are generally two versions, one with a userid, one without
	// The userid is used as a prefix to help sort out files from different sources with the same name
	/////////////////////////////////////////////////////////////////////////



	// Generate a filename based on the supplied path/name, unique userid/service and media type
	// Use this version if you need to prefix the filename. Any existing path data will be replaced
	public static String getMediaPath (String userid, String mtype, String filename){
		if (!mCacheReady) init();
		return MEDIA_CACHE_DIR + mtype + "/" + getUserid(userid) + "_" + getFilename(filename);
	}

	
	// Check to see if media is already saved
	public static boolean isPresent(String userid, String mtype, String filename){
		if (!mCacheReady) init();
		return isFilePresent(getMediaPath(userid, mtype, filename));
	}

	
	// remove entry from cache
	public static void remove (String userid, String mtype, String filename){
		if (!mCacheReady) init();
		if (mCacheReady){
			// Remove the media
			removeFile (getMediaPath(userid, mtype, filename));
		} else {
			Log.e(TAG, "remove() - Cache not set up");
		}
	}

	

}//MediaCache
