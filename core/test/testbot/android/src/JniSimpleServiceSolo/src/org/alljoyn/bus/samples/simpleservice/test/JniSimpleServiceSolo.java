/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
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
package org.alljoyn.bus.samples.simpleservice.test;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

import org.alljoyn.bus.samples.simpleservice.*;
import com.robotium.solo.Solo;
import android.test.ActivityInstrumentationTestCase2;
import android.util.Log;

public class JniSimpleServiceSolo extends ActivityInstrumentationTestCase2<Service>
{
	private static final String TAG = "JniSimpleServiceTest";
	private Solo solo;
	
	private static final String ADVERTISE_DIALOG_TITLE = "Advertised Name";
	private static final String DIALOG_MISSING = "Advertise dialog missing!";
	
	//2 seconds for service to complete advertise
	private static final Integer SERVICE_WAIT_ADVERTISE = 2000;
	
	// 30 seconds for client to connect and send message
	private static final Integer CLIENT_ARRIVE_IN_MS = 30000;
	
	private static final String STOP_BUTTON_DISABLED = "Stop button should be enabled after Start!";
	
	private static final String DEFAULT_WELL_NAME = "simple.service";
	private static final String DEFAULT_CLIENT_MSG = "jni client message";
	private static final String CLIENT_MSG_MISSING = "Client message missing!";
	
	// android setting file path
	private static final String SETTING_PATH = "/data/local/tmp";
	private static final String SETTING_FILE = "/alljoyn.setting";
	
	private static final String NAME_KEY = "WELL_KNOWN_NAME";
	private String mNameValue = DEFAULT_WELL_NAME;
	
	private static final String CLIENT_MESSAGE_KEY = "CLIENT_MSG";
	private String mClientMsgValue = DEFAULT_CLIENT_MSG;
	
	public JniSimpleServiceSolo() {
		super(Service.class);

	}

	@Override
	public void setUp() throws Exception {
		//This is where the solo object is created.
		solo = new Solo(getInstrumentation(), getActivity());
		
		getSettingsFromFile();
	}

	@Override
	public void tearDown() throws Exception {
		//finishOpenedActivities() will finish all the activities that have been opened during the test execution.
		solo.finishOpenedActivities();

	}

	// Read setting from file system
	private boolean getSettingsFromFile()
	{
		boolean readOK = false;
		String name = null;
		String value = null;
		
		
		try
		{
			FileReader input = new FileReader(SETTING_PATH + SETTING_FILE);
			BufferedReader bufRead = new BufferedReader(input);
			String myLine = null;

			while ( (myLine = bufRead.readLine()) != null)
			{    
				String[] nameValuePairs = myLine.split("=");
				// check to make sure you have valid data
				name = nameValuePairs[0];
				value = nameValuePairs[1];
				Log.d(TAG, "Name/value from file : " + name + "/" + value);
				
				if (name.equalsIgnoreCase(NAME_KEY) && value != null)
				{
					mNameValue = value;
					// If well known name is set, the file is ok
					readOK = true;
				}
				else if (name.equalsIgnoreCase(CLIENT_MESSAGE_KEY) && value != null)
				{
					mClientMsgValue = value;
				}
			}
			
			bufRead = null;
			input = null;
			
		} catch (FileNotFoundException e)
		{
			Log.w(TAG, "Setting file not found : " + SETTING_PATH + SETTING_FILE);
		} catch (IOException e) {
			Log.e(TAG, "Read from setting file failed!");
		}
		
		return readOK;
	}
	
	private void advertise() throws Exception
	{

		// make sure dialog is displayed
		try {
			Thread.sleep(10);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		// Make sure advertise dialog displayed
		assertTrue(DIALOG_MISSING, solo.searchText(ADVERTISE_DIALOG_TITLE));
		
		
		// Enter well known name
		solo.clearEditText(0);
		Log.d(TAG, "Well known name entered: " + mNameValue);
		
		solo.typeText(0, mNameValue);
		
		// Click Start button
		solo.clickOnButton("Start");
		
		// wait for advertise to complete to join
		try {
			Thread.sleep(SERVICE_WAIT_ADVERTISE);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		// Make sure Stop button is enabled 
		assertTrue(STOP_BUTTON_DISABLED, solo.getButton(1).isEnabled());
			
	}
	
	private void waitForClientMsg() throws Exception
	{
		// wait for advertise to complete to join
		try {
			Thread.sleep(CLIENT_ARRIVE_IN_MS);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	private void quitMenu() throws Exception
	{
		// wait for advertise to complete to join
		try {
			Thread.sleep(100);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		solo.clickOnMenuItem("Quit");
	}
	
	public void testClientMsgArrived() throws Exception
	{
		advertise();
		
		waitForClientMsg();
	
		quitMenu();
		

	}	
}
