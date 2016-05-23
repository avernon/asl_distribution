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
package org.alljoyn.aroundme.Debug.ServiceBrowser;


import org.alljoyn.aroundme.R;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;


/*
 * Simple  application that will display the details of an Interface
 */
public class AJInterface extends Activity {


	private TextView mTitleView ;
	private TextView mDescriptionView ;
	private String   mInterfaceName ;
	private String   mDescription ;
    private ArrayAdapter<String> mListViewAdapter;

	
	
	private static final String TAG = "AJInterface";
	@Override
	public void onCreate(Bundle savedInstanceState) {
		
		super.onCreate(savedInstanceState);

		// layout the UI
		setContentView(R.layout.ajinterface);

		//TODO: split up interface description into methods, signals and properties, display separately
		
		// get the title views
		mTitleView        = (TextView) findViewById(R.id.interfaceTitle);
		mDescriptionView  = (TextView) findViewById(R.id.interfaceDescription);
	
		//get the name and description of the interface
		Intent myIntent = getIntent();
		mInterfaceName = myIntent.getStringExtra(BrowserConstants.BROWSER_PREFIX+".name");
		mDescription   = myIntent.getStringExtra(BrowserConstants.BROWSER_PREFIX+".description");
		
		//set the text views to the retrieved items
		mTitleView.setText(mInterfaceName);
		mDescriptionView.setVerticalScrollBarEnabled(true);
		mDescriptionView.setText(mDescription);
		
	} // onCreate

	
	@Override
	protected void onDestroy() {
		super.onDestroy();
		finish();
	} //onDestroy

} // AJInterface
