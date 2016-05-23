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
package org.alljoyn.bus.samples.slclient.test;

import org.alljoyn.bus.samples.slclient.Client;

import android.test.ActivityInstrumentationTestCase2;
import android.view.KeyEvent;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.ListView;

public class TestSessionlessClient extends ActivityInstrumentationTestCase2<Client>
{
	private Client slClientActivity;
	
	private ListView listOfMessages;
	private ArrayAdapter<String> listAdapter;
	private EditText textEditor;
	
	private final String pingMsg1 = "S L C L I E N T";
	private final String pingMsg2 = "S U P E R L O N G M E S S A G E";
	
	public TestSessionlessClient()
	{
		super("org.alljoyn.bus.samples.slclient.Client", Client.class);
	}
	
	public void setUp() throws Exception 
	{
		super.setUp();
		
			
		slClientActivity = this.getActivity();
			
		listOfMessages = (ListView)slClientActivity.findViewById(org.alljoyn.bus.samples.slclient.R.id.ListView);
		listAdapter = (ArrayAdapter<String>) listOfMessages.getAdapter();
		textEditor = (EditText)slClientActivity.findViewById(org.alljoyn.bus.samples.slclient.R.id.EditText);
	}
		
	@Override
	public  void tearDown() throws Exception 
	{
	 	super.tearDown();
	} 
		
	private void waitSignalArrive()
	{
  		/* Wait 30 seconds for signal to reach service */
  	   	try {
  			Thread.sleep(30000);
  		} catch (InterruptedException e) {
  			assertTrue("sleep timeout!", false);
  		}		
	}
	
	public void testClientPing()
	{
		// text editor should focus
		assertTrue("Not able to enter text", textEditor.isInputMethodTarget());
		
		this.sendKeys(pingMsg1);
		
  		// Wait 100ms 
  	   	try {
  			Thread.sleep(100);
  		} catch (InterruptedException e) {
  			assertTrue("sleep timeout!", false);
  		}		
  	   	
		this.sendKeys(KeyEvent.KEYCODE_ENTER);
		
  		// Wait 100ms 
  	   	try {
  			Thread.sleep(100);
  		} catch (InterruptedException e) {
  			assertTrue("sleep timeout!", false);
  		}
		
		waitSignalArrive();
		
		this.sendKeys(pingMsg2);
		
  		// Wait 100ms 
  	   	try {
  			Thread.sleep(100);
  		} catch (InterruptedException e) {
  			assertTrue("sleep timeout!", false);
  		}		
  	   	
		this.sendKeys(KeyEvent.KEYCODE_ENTER);
		
		waitSignalArrive();
	}
}
