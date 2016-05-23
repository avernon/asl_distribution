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
package org.alljoyn.bus.samples.simpleclient.test;


import org.alljoyn.bus.samples.simpleclient.*;

import android.test.ActivityInstrumentationTestCase2;
import android.view.KeyEvent;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.ListView;

public class TestSimpleClient extends ActivityInstrumentationTestCase2<Client> 
{
	private Client clientActivity;
	private ListView listOfMessages;
	private ArrayAdapter<String> listAdapter;
	private EditText textEditor;
	
	private final String pingMsg1 = "C L I E N T";
	private final String replyMsg1 = "Reply:  client";
	private final String pingMsg2 = "S U P E R L O N G M E S S A G E";
	private final String replyMsg2 = "Reply:  superlongmessage";
	
	public TestSimpleClient() 
	{
		super("org.alljoyn.bus.samples.simpleclient", Client.class);
	}

	public void setUp() throws Exception 
	{
		super.setUp();
		
		clientActivity = this.getActivity();
		
		listOfMessages = (ListView)clientActivity.findViewById(org.alljoyn.bus.samples.simpleclient.R.id.ListView);
		listAdapter = (ArrayAdapter<String>) listOfMessages.getAdapter();
		textEditor = (EditText)clientActivity.findViewById(org.alljoyn.bus.samples.simpleclient.R.id.EditText);
	}
	
	@Override
	public  void tearDown() throws Exception 
	{
	 	super.tearDown();
	}
	
	private void waitDiscoveryComplete()
	{
  		/* Wait 30 second for discovery complete */
  	   	try {
  			Thread.sleep(30000);
  		} catch (InterruptedException e) {
  			assertTrue("sleep timeout!", false);
  		}		
	}
	
	private void waitReplyBack()
	{
  		/* Wait 10 second for reply back */
  	   	try {
  			Thread.sleep(10000);
  		} catch (InterruptedException e) {
  			assertTrue("sleep timeout!", false);
  		}		
	}

	private void checkListView()
	{
		int msgCount = listAdapter.getCount();
			
		assertEquals("Reply not received!", 4, msgCount);
		
		assertEquals("1st reply missing!", replyMsg1, listAdapter.getItem(1));
		
		assertEquals("2nd reply missing!", replyMsg2, listAdapter.getItem(3));
	}
	
	public void testClientPing()
	{
		waitDiscoveryComplete();
		
		// text editor should focus after discovery and joinSession complete
		assertTrue("Discovery or joinSession fail!", textEditor.isInputMethodTarget());
		
		this.sendKeys(pingMsg1);
		
  		/* Wait 100ms for discovery complete */
  	   	try {
  			Thread.sleep(100);
  		} catch (InterruptedException e) {
  			assertTrue("sleep timeout!", false);
  		}		
  	   	
		this.sendKeys(KeyEvent.KEYCODE_ENTER);
		
		// Wait till reply back from service
		waitReplyBack();
		
		this.sendKeys(pingMsg2);
		
  		/* Wait 100ms for discovery complete */
  	   	try {
  			Thread.sleep(100);
  		} catch (InterruptedException e) {
  			assertTrue("sleep timeout!", false);
  		}		
  	   	
		this.sendKeys(KeyEvent.KEYCODE_ENTER);
		
		// Wait till reply back from service
		waitReplyBack();
		
		// Check reply from service
		checkListView();
	}

}
