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
package org.alljoyn.whiteboard.activity;


import java.util.HashMap;

import org.alljoyn.devmodules.common.WhiteboardLineInfo;
import org.alljoyn.devmodules.util.Utility;
import org.alljoyn.whiteboard.api.WhiteboardAPI;
import org.alljoyn.whiteboard.api.WhiteboardListener;

import android.support.v4.app.Fragment;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.LinearLayout;

public class UIFragment extends Fragment {

	private final String TAG = "Whiteboard_UIFragment";

	private DrawCanvasView canvas;
	private LinearLayout drawContainer;
	
	private String mGroupId = "";
	private boolean mDisplayed = false;
	
	private WhiteboardListener mWhiteboardListener = new WhiteboardListener(){

		@Override
		public void onWhiteboardServiceAvailable(String service) {
			
		}

		@Override
		public void onWhiteboardServiceLost(String service) {
			
		}

		@Override
		public void onRemoteDraw(WhiteboardLineInfo lineInfo) {
			draw(lineInfo);
		}
		
		@Override
		public void onRemoteGroupDraw(String group, WhiteboardLineInfo lineInfo) {
			if(mGroupId.equals(group)) {
				draw(lineInfo);
			}
			else {
				System.out.println("Group: "+group+ ", myGroup: "+mGroupId);
			}
		}

		@Override
		public void onClear() {
			clear();
		}
		
		@Override
		public void onGroupClear(String group) {
			if(mGroupId.equals(group))
				clear();
		}

	};
	
	/**
	 * Mandatory empty constructor for the fragment manager to instantiate the
	 * fragment (e.g. upon screen orientation changes).
	 */
	public UIFragment() {
	}

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		if (!mDisplayed){
			mDisplayed = true;
			Bundle args = getArguments();

			if (args!=null){
				if (args.containsKey("group")) {
					mGroupId = args.getString("group");
					Log.v(TAG, "Whiteboard UI active for group: "+mGroupId);
				}
			} else {
				Log.e(TAG, "No group specified!!!");
			}

		}
	}
	
	@Override
	public void onDestroy() {
		super.onDestroy();
		WhiteboardAPI.UnregisterListener(mWhiteboardListener);
	}
	
	@Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
		View view = inflater.inflate(Utility.getResourseIdByName(getActivity().getPackageName(),"layout","whiteboard_uifragment"), container, false);
		Button clear = (Button)view.findViewById(Utility.getResourseIdByName(getActivity().getPackageName(),"id","btn_clear"));
		clear.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				canvas.clearDrawingLines();
			}
		});
		Button clearAll = (Button)view.findViewById(Utility.getResourseIdByName(getActivity().getPackageName(),"id","btn_clear_all"));
		clearAll.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				canvas.clearDrawingLines();
				try {
					WhiteboardAPI.Clear(mGroupId,"");
				} catch (Exception e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		});
        
		canvas = new DrawCanvasView(getActivity().getApplicationContext());
		canvas.setBackgroundColor(Color.WHITE);
		canvas.setGroupId(mGroupId);
		drawContainer = (LinearLayout)view.findViewById(Utility.getResourseIdByName(getActivity().getPackageName(), "id", "draw_container"));
		drawContainer.setBackgroundColor(getResources().getColor(android.R.color.transparent));
		drawContainer.addView(canvas);
		
		WhiteboardAPI.RegisterListener(mWhiteboardListener);
		
        return view;
    }
	
	public void draw(WhiteboardLineInfo line) {
		canvas.drawLine(line);
	}
	
	public void clear() {
		canvas.doClearLines();
	}
	
	public void setGroupId(String mGroupId) {
		this.mGroupId = mGroupId;
		canvas.setGroupId(mGroupId);
	}
}
