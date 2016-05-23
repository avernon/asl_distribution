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

import java.util.ArrayList;
import org.alljoyn.aroundme.R;
import org.alljoyn.profileloader.MyProfileData;
import org.alljoyn.devmodules.common.MessageIdentifier;
import org.alljoyn.devmodules.common.ProfileDescriptor;
import org.alljoyn.devmodules.common.Utilities;
import org.alljoyn.storage.ProfileCache;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.Drawable;

import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;


public class ChatMessageAdapter extends BaseAdapter { 
	
	private static final String TAG = "ChatMessageAdapter";
	
	// Arrays for holding the data
	private ArrayList<MessageIdentifier> mMsgList = null; 

	// Context of the current Activity
	private Context mContext; 
	
	private  ProfileDescriptor  mProfile ;

	private static Drawable mDefaultThumb;

	// make default constructor private, to force provision of Context
	private ChatMessageAdapter() { 
	} 

	public ChatMessageAdapter(Context c) { 
		mContext = c; 
		mMsgList = new ArrayList<MessageIdentifier>();
		mProfile = new ProfileDescriptor();
		mDefaultThumb = mContext.getResources().getDrawable(R.drawable.ic_list_person);
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

	public synchronized void add (String room, String sender, String contents) {
		MessageIdentifier mi = new MessageIdentifier();
		mi.room      = room;
		mi.sender    = sender;
		mi.contents  = contents;
		mi.timestamp = Utilities.getTime();
		mMsgList.add(mi);
		notifyDataSetChanged(); // force re-display of list
		Log.v(TAG, "add("+room+", "+sender+", "+contents+")");
	}

	public synchronized void add (MessageIdentifier mi) {
		mMsgList.add(mi);
		notifyDataSetChanged(); // force re-display of list
	}

	public synchronized MessageIdentifier get (int pos) {
		if (pos<mMsgList.size()){
			return mMsgList.get(pos);
		} else {
			return new MessageIdentifier();
		}
	}


	public synchronized void clear(){
		mMsgList.clear();
		notifyDataSetChanged(); // force re-display of list
	}
	
	// return the View to be displayed
	public View getView(int position, View convertView, ViewGroup parent) { 
		// Inflate a view template
		if (convertView == null) {
			LayoutInflater inflater = (LayoutInflater)mContext.getSystemService (Context.LAYOUT_INFLATER_SERVICE);
			convertView = inflater.inflate(R.layout.chatitem, parent, false);
		}

		// get the display views
		ImageView vThumbnail = (ImageView)convertView.findViewById(R.id.thumbnail);
		TextView  vTimestamp = (TextView) convertView.findViewById(R.id.timestamp);
		TextView  vSender    = (TextView) convertView.findViewById(R.id.sender);
		TextView  vContents  = (TextView) convertView.findViewById(R.id.contents);

		String room = get(position).room;
		String name = get(position).sender;
		String contents = get(position).contents;

		Log.v(TAG, "Display chat ("+room+","+name+","+contents+")");
		
		// retrieve the profile from cache
		if (!ProfileCache.isPresent(ProfileCache.getProfilePath(name))){
			Log.e(TAG, "Profile not found for: "+name);
		}
		mProfile = ProfileCache.getProfile(name);
		if(mProfile == null)
			return convertView;
		String fullname = mProfile.getField(ProfileDescriptor.ProfileFields.NAME_DISPLAY);
		if (fullname.length()==0) fullname="("+name+")";
		if (room.length()>0) fullname += "("+room+")";
		
		String ts = Utilities.getTimestamp(get(position).timestamp, "hh:mm");
		
		vTimestamp.setText(ts);
		vSender.setText(fullname);
		vContents.setText(get(position).contents);

		// Process the photo
		try {
			byte[] bphoto ;
			bphoto = mProfile.getPhoto();
			if ((bphoto!=null) && (bphoto.length>0)){
				Bitmap image = BitmapFactory.decodeByteArray(bphoto, 0, bphoto.length);
				vThumbnail.setImageBitmap(image);
			} else {
				vThumbnail.setImageDrawable(mDefaultThumb);			
			}
		} catch (Exception e){
			vThumbnail.setImageDrawable(mDefaultThumb);			
		}

		return convertView;
	} 


} // ChatMessageAdapter
