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
package org.alljoyn.bus.samples.slservice.test;

import org.alljoyn.bus.samples.slservice.Service;

import android.test.ActivityInstrumentationTestCase2;
import android.widget.ArrayAdapter;
import android.widget.ListView;

public class TestSessionlessService extends ActivityInstrumentationTestCase2<Service>
{
	private Service slServiceActivity;
	
	private ListView listOfMessages;
	private ArrayAdapter<String> listAdapter;
	
	private final String pingMsg1 = "Ping:  slclient";
	private final String pingMsg2 = "Ping:  slclientsuperlongmessage";
	
	public TestSessionlessService() 
	{
		super("org.alljoyn.bus.samples.slservice.Service", Service.class);
	}

	public void setUp() throws Exception 
	{
		super.setUp();
		
			
		slServiceActivity = this.getActivity();
			
		listOfMessages = (ListView)slServiceActivity.findViewById(org.alljoyn.bus.samples.slservice.R.id.ListView);
		listAdapter = (ArrayAdapter<String>) listOfMessages.getAdapter();
	}
		
	@Override
	public  void tearDown() throws Exception 
	{
	 	super.tearDown();
	} 
		
	private void waitSignalsArrived()
	{
  		/* Wait 60 seconds for 2 signals to reach service */
  	   	try {
  			Thread.sleep(60000);
  		} catch (InterruptedException e) {
  			assertTrue("sleep timeout!", false);
  		}		
	}
	

	private void checkListView()
	{
		int msgCount = listAdapter.getCount();
			
		assertEquals("Pings not received!", 2, msgCount);
		
		assertEquals("1st ping missing!", pingMsg1, listAdapter.getItem(0));
		
		assertEquals("2nd ping missing!", pingMsg2, listAdapter.getItem(1));
	}
	
	public void testSignalFromClient()
	{
		waitSignalsArrived();
  	   	
		checkListView();
		
	}
}
