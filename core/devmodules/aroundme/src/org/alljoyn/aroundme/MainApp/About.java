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
package org.alljoyn.aroundme.MainApp;





import org.alljoyn.aroundme.R;
import org.alljoyn.aroundme.R.layout;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;



/*
 * Simple  application that will display the About dialog
 * Not really much to do except setup up the UI and handle the Quit menu option
 */
public class About extends Activity {

	private Menu                 mMenu;

	private static final String TAG = "About";
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		
		super.onCreate(savedInstanceState);

		// layout the UI
		setContentView(R.layout.about);
		
	} // onCreate

	
	@Override
	protected void onDestroy() {
		super.onDestroy();
		finish();
	} //onDestroy



} // About
