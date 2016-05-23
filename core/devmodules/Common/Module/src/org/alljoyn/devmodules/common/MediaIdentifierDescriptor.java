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
package org.alljoyn.devmodules.common;

import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.ArrayList;


import org.alljoyn.bus.annotation.Position;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.content.ContentResolver;
import android.content.ContentUris;
import android.content.res.AssetFileDescriptor;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.provider.ContactsContract;
import android.provider.ContactsContract.Contacts;
import android.provider.MediaStore;
import android.util.Log;


/*
 * Class to hold Media Identifier in save-able format
 * The data can be stored/retrieved as a String in JSON format, or accessed via get/set methods for specific fields
 */


/*
 * The structure is equivalent to an array of MediaIntifier instances
 * MediaIdentifier includes the following fields
 * 
 * service        file path on the hosting device
 * thumbpath   Location of Thumbnail/icon path, if any
 * name        (file) name, without path
 * type        MIME type
 * size        size in bytes
 * title       Descriptive title
 * userid      User name/id of the source
 * mediatype   Media type (see MediaQueryConstants)
 * localpath   Path where file is stored on local device (not remote/source device)
 * 
 */
public class MediaIdentifierDescriptor  {

	private static final String TAG = "MediaIdentifierDescriptor";

	private String          _string ;
	private MediaIdentifier _mi;
	private JSONObject      _object ;

	public MediaIdentifierDescriptor () {
		_string = "";
		_object = new JSONObject();
		_mi     = new MediaIdentifier();
	}


	// Convert structure to a JSON-encoded String
	public synchronized String toString(){
		/***
		// Build the JSON object then dump to String

		JSONObject jobj = new JSONObject();
		try{
			// Build the JSONObject from the MediaIdentifer
			jobj.put("path",      _mi.path);
			jobj.put("thumbpath", _mi.thumbpath);
			jobj.put("name",      _mi.name);
			jobj.put("type",      _mi.type);
			jobj.put("size",      _mi.size);
			jobj.put("title",     _mi.title);
			jobj.put("userid",    _mi.userid);
			jobj.put("mediatype", _mi.mediatype);
			jobj.put("localpath", _mi.localpath);
			jobj.put("timestamp", _mi.timestamp);
		} catch (JSONException e) {
			Log.e(TAG, "Error converting to String: "+e.toString());
		}
		***/

		_string = _object.toString();
		return _string;
	}


	// Methods to get/set data (thread safe)

	// Build the object based on a JSON-encoded String (the opposite of toString())
	public synchronized void setString(String contents){
		try{
			_string = contents;
			// Extract the Media Identifier
			//MediaIdentifier mi = new MediaIdentifier();
			//JSONObject jobj = new JSONObject(contents);
			_object = new JSONObject(contents);
			_mi.path      = _object.getString("path"); 
			_mi.thumbpath = _object.getString("thumbpath"); 
			_mi.name      = _object.getString("name"); 
			_mi.type      = _object.getString("type"); 
			_mi.size      = _object.getInt   ("size"); 
			_mi.title     = _object.getString("title"); 
			_mi.userid    = _object.getString("userid"); 
			_mi.mediatype = _object.getString("mediatype"); 
			_mi.localpath = _object.getString("localpath"); 
			_mi.timestamp = _object.getLong  ("timestamp"); 
		}catch(Exception e){
			Log.e(TAG, "setString(): Error loading Descriptor");
		}
	}


	// return the entire list as a TansactionList class
	public synchronized MediaIdentifier get (){ 
		return _mi;
	}


	// add a MediaIdentifier to the list
	public synchronized void add (MediaIdentifier mi){ 	
		_mi = mi;
		
		try{
			// Build the JSONObject from the MediaIdentifer
			_object.put("path",      _mi.path);
			_object.put("thumbpath", _mi.thumbpath);
			_object.put("name",      _mi.name);
			_object.put("type",      _mi.type);
			_object.put("size",      _mi.size);
			_object.put("title",     _mi.title);
			_object.put("userid",    _mi.userid);
			_object.put("mediatype", _mi.mediatype);
			_object.put("localpath", _mi.localpath);
			_object.put("timestamp", _mi.timestamp);
			
			_string = _object.toString();

		} catch (JSONException e) {
			Log.e(TAG, "Error converting to JSON: "+e.toString());
		}

	}
} // ProfileDescriptor
