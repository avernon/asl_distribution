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

import java.util.HashMap;

import org.alljoyn.cops.filetransfer.data.FileDescriptor;

import android.test.AndroidTestCase;

public class FileDescriptorTest extends AndroidTestCase
{
	public void testEquals()
	{
		FileDescriptor descriptor1 = new FileDescriptor();
		descriptor1.fileID = new byte[20];
		descriptor1.filename = "foo";
		descriptor1.owner = "bar";
		descriptor1.relativePath = "somePath";
		descriptor1.sharedPath = "someOtherPath";
		descriptor1.size = 1337;
		
		FileDescriptor descriptor2 = new FileDescriptor();
		descriptor2.fileID = descriptor1.fileID;
		descriptor2.filename = descriptor1.filename;
		descriptor2.owner = descriptor1.owner;
		descriptor2.relativePath = descriptor1.relativePath;
		descriptor2.sharedPath = descriptor1.sharedPath;
		descriptor2.size = descriptor1.size;
		
		boolean equals = descriptor1.equals(descriptor2);
		
		assertTrue(equals);
	}
	
	public void testHash()
	{
		FileDescriptor descriptor1 = new FileDescriptor();
		descriptor1.fileID = new byte[20];
		descriptor1.filename = "foo";
		descriptor1.owner = "bar";
		descriptor1.relativePath = "somePath";
		descriptor1.sharedPath = "someOtherPath";
		descriptor1.size = 1337;
		
		FileDescriptor descriptor2 = new FileDescriptor();
		descriptor2.fileID = descriptor1.fileID;
		descriptor2.filename = descriptor1.filename;
		descriptor2.owner = descriptor1.owner;
		descriptor2.relativePath = descriptor1.relativePath;
		descriptor2.sharedPath = descriptor1.sharedPath;
		descriptor2.size = descriptor1.size;
		
		HashMap<FileDescriptor, Integer> hashMap = new HashMap<FileDescriptor, Integer>();
		hashMap.put(descriptor1, 9001);
		hashMap.put(descriptor2, 9002);
		
		assertSame(hashMap.size(), 1);		
	}
}
