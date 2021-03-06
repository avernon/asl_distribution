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

import org.alljoyn.aroundme.R;
import org.alljoyn.aroundme.R.id;
import org.alljoyn.aroundme.R.layout;



import android.content.Context;
import android.graphics.Color;


import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import android.widget.BaseAdapter;

import android.widget.TextView;
import android.widget.Toast;

// List Management for debug data




//Adapter to deal with formatted strings
public class DebugAdapter extends BaseAdapter { 
	
	private static final String TAG = "DebugAdapter";

	// Arrays for holding the data
	private static ArrayList<TextHolder> mMsgList = new ArrayList<TextHolder>(); 

	// Context of the current Activity
	private static Context mContext; 
	
	private static DebugAdapter _adapter; // the singleton version
	
	private static boolean viewAttached = false;


	
	// Colour values
	//private static final int UI_COLOUR_INFO       = 0xFFFFFFFF ;


	private static final int UI_COLOUR_VERBOSE  = Color.GREEN ;
	private static final int UI_COLOUR_DEBUG    = Color.BLUE ;
	private static final int UI_COLOUR_INFO     = Color.YELLOW ;
	private static final int UI_COLOUR_WARNING  = Color.MAGENTA ;
	private static final int UI_COLOUR_ERROR    = Color.RED ;


	// convenience class for holding string and format parameters
	class TextHolder {
		public String msg;
		public int color;

		public TextHolder (String msg, int c){
			this.msg = msg;
			this.color = c;
		}


		public TextHolder (String msg, String l){
			this.msg = msg;
			this.color = getColour(l);
		}
	}
	

	// convert text debug level to colour ("e" = error, "w" = warning, otherwise info)
	private int getColour(String l){
		if ((l==null) || (l.length()!=1)) {
			return UI_COLOUR_INFO;	
		} else if ("d".equals(l)) {
			return UI_COLOUR_DEBUG;
		} else if ("e".equals(l)) {
			return UI_COLOUR_ERROR;
		} else if ("i".equals(l)) {
			return UI_COLOUR_INFO;
		} else if ("w".equals(l)) {
			return UI_COLOUR_WARNING;
		} else if ("v".equals(l)) {
			return UI_COLOUR_VERBOSE;
		} else {
			return UI_COLOUR_INFO;
		}
		
	}

	public DebugAdapter(Context c) { 
		mContext = c; 
	} 


	private DebugAdapter() { 
		// no implementation, just private to control usage
	} 

	
	// prevent instantiation via an explicit clone() call
	public Object clone() throws CloneNotSupportedException {
		throw new CloneNotSupportedException();
	}

	// method to return reference to internal data
	public static synchronized DebugAdapter getAdapter() {
		if (_adapter == null) {
			_adapter = new DebugAdapter();
		}
		return _adapter;
	}

	public static synchronized void setContext (Context context){
		mContext = context;
		viewAttached = true;
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

	public static synchronized void add (TextHolder th) {
		if (_adapter == null) {
			_adapter = new DebugAdapter();
		}
		mMsgList.add(th);
		update();
		if (th.color != UI_COLOUR_INFO){
            Toast.makeText(mContext, (String) th.msg, Toast.LENGTH_LONG).show();
		}
	}

	public static synchronized void add (String msg) {
		if (_adapter == null) {
			_adapter = new DebugAdapter();
		}
		TextHolder th = _adapter.new TextHolder (msg, "i");
		mMsgList.add(th);
	}

	public static synchronized void add (String msg, String lvl) {
		if (_adapter == null) {
			_adapter = new DebugAdapter();
		}
		TextHolder th = _adapter.new TextHolder (msg, lvl);
		mMsgList.add(th);
	}
	
	public static synchronized void clear(){
		mMsgList.clear();
		update();
	}
	

	// return the View to be displayed
	public View getView(int position, View convertView, ViewGroup parent) { 

		// Inflate a view template
		if (convertView == null) {
			LayoutInflater inflater = (LayoutInflater)mContext.getSystemService (Context.LAYOUT_INFLATER_SERVICE);
			convertView = inflater.inflate(R.layout.simpleitem, parent, false);
		}

		// get the display views
		TextView txtView = (TextView) convertView.findViewById(R.id.itemText);

		txtView.setText(mMsgList.get(position).msg); 
		txtView.setTextColor(mMsgList.get(position).color);

		return convertView;

	} 



	public static void update() {
		if (_adapter == null) {
			_adapter = new DebugAdapter();
		}
		
		if (mContext != null) {
			_adapter.notifyDataSetChanged(); // force re-display of list
		}
	}

} // DebugAdapter
