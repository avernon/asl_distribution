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

package org.alljoyn.cops.filetransfer.test;

import java.util.ArrayList;

import org.alljoyn.cops.filetransfer.Dispatcher;
import org.alljoyn.cops.filetransfer.FileSystemAbstraction;
import org.alljoyn.cops.filetransfer.OfferManager;
import org.alljoyn.cops.filetransfer.PermissionsManager;
import org.alljoyn.cops.filetransfer.Transmitter;
import org.alljoyn.cops.filetransfer.data.Action;
import org.alljoyn.cops.filetransfer.data.FileDescriptor;
import org.alljoyn.cops.filetransfer.data.StatusCode;
import org.alljoyn.cops.filetransfer.listener.OfferReceivedListener;
import org.alljoyn.cops.filetransfer.utility.Logger;

import android.test.AndroidTestCase;

public class OfferManagerTest extends AndroidTestCase
{
	private OfferManager offerManager;
	private MockFileSystemAbstraction mockFSA;
	private MockPermissionsManager mockPermissionsManager;
	private MockTransmitter mockTransmitter;
	private MockDispatcher mockDispatcher;
	
	
	protected void setUp() throws Exception
	{		
		mockFSA = new MockFileSystemAbstraction();
		mockPermissionsManager = new MockPermissionsManager();
		mockTransmitter = new MockTransmitter();
		mockDispatcher = new MockDispatcher(mockTransmitter);		
		offerManager = new OfferManager(mockDispatcher, "bar", mockPermissionsManager, mockFSA);		
	}

	protected void tearDown() throws Exception
	{
		super.tearDown();
	}
	
	public void testIsOfferPending() throws InterruptedException
	{
		final FileDescriptor descriptor = getDummyFileDescriptor();		
		mockTransmitter.setResult(StatusCode.OFFER_ACCEPTED);	
		
		new Thread(new Runnable()
		{
			@Override
			public void run()
			{
				try
				{
					Thread.sleep(500);
				} catch (InterruptedException e)
				{
					Logger.log(e.toString());
				}
				Logger.log("check 1");
				assertTrue(offerManager.isOfferPending(descriptor.fileID));				
			}			
		}).start();		
		
		offerManager.offerFile(descriptor.owner, descriptor.sharedPath, 1000);		
		
		Thread.sleep(1500);		
		Logger.log("check 2");
		assertFalse(offerManager.isOfferPending(descriptor.fileID));
	}	

	public void testHandleOfferFile()
	{
		FileDescriptor file = getDummyFileDescriptor();
		
		//no listener - refuse offer
		int response = offerManager.handleOffer(file, file.owner);
		assertSame(StatusCode.OFFER_REJECTED, response);
		
		//listener refuses offer
		offerManager.setOfferReceivedListener(new OfferReceivedListener()
		{
			public boolean acceptOfferedFile(FileDescriptor file, String peer)
			{
				return false;
			}
		});
		
		response = offerManager.handleOffer(file, file.owner);
		assertSame(StatusCode.OFFER_REJECTED, response);
		
		//listener accepts offer
		offerManager.setOfferReceivedListener(new OfferReceivedListener()
		{
			public boolean acceptOfferedFile(FileDescriptor file, String peer)
			{
				return true;
			}
		});
		
		response = offerManager.handleOffer(file, file.owner);
		assertSame(StatusCode.OFFER_ACCEPTED, response);
	}
	
	public void testOfferFileAccepted()
	{
		final FileDescriptor descriptor = getDummyFileDescriptor();
		
		mockTransmitter.setResult(StatusCode.OFFER_ACCEPTED);
		
		Thread offerResponseThread = new Thread()
		{
			@Override
			public void run()
			{
				try
				{
					Thread.sleep(500);
				} catch (InterruptedException e) {	}
				
				offerManager.handleFileRequest(descriptor.fileID, 0, 100, descriptor.owner, 100);
			}			
		};
		
		offerResponseThread.start();
		int status = offerManager.offerFile(descriptor.owner, descriptor.sharedPath, 1000);
		
		assertEquals(StatusCode.OK, status);
	}
	
	public void testOfferFileRejected()
	{
		final FileDescriptor descriptor = getDummyFileDescriptor();
		
		mockTransmitter.setResult(StatusCode.OFFER_REJECTED);
		
		int status = offerManager.offerFile(descriptor.owner, descriptor.sharedPath, 1000);
		
		assertEquals(StatusCode.OFFER_REJECTED, status);		
	}
	
	public void testOfferFileTimeout()
	{
		final FileDescriptor descriptor = getDummyFileDescriptor();
		
		mockTransmitter.setResult(StatusCode.OFFER_ACCEPTED);
		
		int status = offerManager.offerFile(descriptor.owner, descriptor.sharedPath, 1000);
		
		assertEquals(StatusCode.OFFER_TIMEOUT, status);		
	}
	
	private FileDescriptor getDummyFileDescriptor()
	{
		FileDescriptor descriptor = new FileDescriptor();
		descriptor.fileID = new byte[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
		descriptor.filename = "foo";
		descriptor.owner = "bar";
		descriptor.relativePath = "";
		descriptor.sharedPath = "";
		descriptor.size = 100;
		
		return descriptor;
	}
	
	private class MockTransmitter extends Transmitter
	{	
		private int result = StatusCode.INVALID;
		
		public MockTransmitter()
		{
			super(null, null, 0);
		}
		
		public void setResult(int newResult)
		{
			result = newResult;			
		}

		@Override
		public int transmit(Action action)
		{
			return result;			
		}
	}
	
	private class MockDispatcher extends Dispatcher
	{
		public MockDispatcher(Transmitter transmitter)
		{
			super(transmitter);
		}			
	}
	
	private class MockPermissionsManager extends PermissionsManager
	{
		
	}
	
	private class MockFileSystemAbstraction extends FileSystemAbstraction
	{
		@Override
		public FileDescriptor[] getFileInfo(ArrayList<String> pathList,
				ArrayList<String> failedPaths, String localBusId)
		{
			return new FileDescriptor[] { getDummyFileDescriptor() };
		}	
	}
}
