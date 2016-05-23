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

//
// List of remote debug messages for a particular service
// Note: unlike most other adapters, there can be multiple instances of this type 
//       (because we need multiple message lists)
//       This means that access to the "correct" list has to be managed externally

import org.alljoyn.aroundme.R;
import org.alljoyn.aroundme.Debug.LogOutput.DebugMessageList;
import org.alljoyn.devmodules.common.DebugMessageDescriptor;
import android.content.Context;
import android.graphics.Color;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;


public class RemoteDebugAdapter extends BaseAdapter { 
	
	private static final String TAG = "RemoteDebugAdapter";
	
	// Arrays for holding the data
	private DebugMessageList mMsgList = new DebugMessageList(); 

	// Context of the current Activity
	private Context mContext; 
	

	// make defualt constructor private, to force provision of Context
	private RemoteDebugAdapter() { 
	} 

	public RemoteDebugAdapter(Context c) { 
		mContext = c; 
	} 


	public synchronized void setContext (Context context){
		mContext = context;
	}

	public int getCount() { 
		return mMsgList.size(); 
	} 

	public Object getItem(int position) { 
		return position; 
	} 

	public long getItemId(int position) { 
		return position; 
	} 

	public synchronized void add (DebugMessageDescriptor msg) {
		mMsgList.add(msg);
		notifyDataSetChanged(); // force re-display of list
	}

	public synchronized DebugMessageDescriptor get (int pos) {
		if (pos<mMsgList.size()){
			return mMsgList.get(pos);
		} else {
			return new DebugMessageDescriptor();
		}
	}

	
	public synchronized void clear(){
		mMsgList.clear();
		notifyDataSetChanged(); // force re-display of list
	}
	

	private static int[] mTextColor = { Color.GREEN, Color.BLUE, Color.YELLOW, Color.MAGENTA, Color.RED };
	
	// return the View to be displayed
	public View getView(int position, View convertView, ViewGroup parent) { 
		// Inflate a view template
		if (convertView == null) {
			LayoutInflater inflater = (LayoutInflater)mContext.getSystemService (Context.LAYOUT_INFLATER_SERVICE);
			convertView = inflater.inflate(R.layout.simpleitem, parent, false);
		}

		// get the display views
		TextView txtView = (TextView) convertView.findViewById(R.id.itemText);

		// Set the text to the message content
		txtView.setText(mMsgList.get(position).message); 
		
		// Set the colour based on the message level
		int colour = Color.BLACK;
		int level = mMsgList.get(position).level;
		if ((level>0) && (level<mTextColor.length))
			colour = mTextColor[level];
		txtView.setTextColor(colour);

		return convertView;
	} 


} // RemoteDebugAdapter
