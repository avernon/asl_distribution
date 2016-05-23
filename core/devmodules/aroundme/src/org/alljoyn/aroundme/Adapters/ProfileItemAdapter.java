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
package org.alljoyn.aroundme.Adapters;


import java.util.ArrayList;
import java.util.HashMap;

import org.alljoyn.aroundme.R;
import org.alljoyn.aroundme.R.id;
import org.alljoyn.aroundme.R.layout;



import android.content.Context;


import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import android.widget.BaseAdapter;

import android.widget.TextView;
import android.widget.Toast;

// List Management for profile fields
// Note that this is *not* a singleton list, so can be created multiple times




//Adapter to deal with formatted strings
public class ProfileItemAdapter extends BaseAdapter { 
	
	private static final String TAG = "ProfileItemAdapter";

	// Arrays for holding the data
	private ArrayList<String> mFieldList ; 
	private ArrayList<String> mValueList ; 

	// Context of the current Activity
	private Context mContext; 
	


	public ProfileItemAdapter(Context c) { 
		mContext = c; 
		mFieldList = new ArrayList<String>(); 
		mValueList = new ArrayList<String>(); 
	} 


	private ProfileItemAdapter() { 
		// no implementation, just private to make sure Context is supplied
	} 


	public int getCount() { 
		return mFieldList.size(); 
	} 

	public Object getItem(int position) { 
		return position; 
	} 

	public long getItemId(int position) { 
		return position; 
	} 

	public synchronized void add (String key, String value) {
		mFieldList.add(key);
		mValueList.add(value);
		update();
	}
	
	public synchronized void clear(){
		mFieldList.clear();
		mValueList.clear();
		update();
	}
	

	// return the View to be displayed
	public View getView(int position, View convertView, ViewGroup parent) { 

		// Inflate a view template
		if (convertView == null) {
			LayoutInflater inflater = (LayoutInflater)mContext.getSystemService (Context.LAYOUT_INFLATER_SERVICE);
			convertView = inflater.inflate(R.layout.profileitem, parent, false);
		}

		// get the display views
		TextView fieldView = (TextView) convertView.findViewById(R.id.pfield);
		TextView valueView = (TextView) convertView.findViewById(R.id.ptext);

		fieldView.setText(mFieldList.get(position)+": "); 
		valueView.setText(mValueList.get(position));

		return convertView;

	} 



	public void update() {
		
		if (mContext != null) {
			notifyDataSetChanged(); // force re-display of list
		}
	}

} // ProfileItemAdapter
