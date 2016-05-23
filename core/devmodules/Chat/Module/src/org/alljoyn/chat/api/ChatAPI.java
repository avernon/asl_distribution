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
package org.alljoyn.chat.api;

import org.alljoyn.devmodules.APICore;

import android.util.Log;

public class ChatAPI {

	private static final String TAG = "ChatAPI";

	// prevent instantiation via an explicit clone() call
	public Object clone() throws CloneNotSupportedException {
		throw new CloneNotSupportedException();
	}

	private static ChatAPIInterface ChatInterface = null;

	// the callback object
	private static ChatCallbackObject mChatCallbackObject = null;

	/**
     * Assign a listener to be triggered when events occur from remote applications
     * 
     * @param listener		The implemented callback class that will be triggered
     */
	public static void RegisterListener(ChatListener listener) {
		setupInterface();
		mChatCallbackObject.registerListener(listener);
	}

	private static void setupInterface() {
		if (mChatCallbackObject == null) {
			mChatCallbackObject = new ChatCallbackObject();
		}

		if(ChatInterface == null) {
			ChatInterface = APICore.getInstance().getProxyBusObject("chat",
					new Class[] {ChatAPIInterface.class}).getInterface(ChatAPIInterface.class);
		}
	}

	/**
	 * Opens a chat room.
	 * Deprecated at this time, use SendGroupChat instead and leverage the UIFragment example
	 * 
	 * @param users		List of users to invite
	 * @return			The name of the chat room created
	 * @throws Exception
	 */
	public static String createChatRoom(String[] users) throws Exception {
		String room = "_";
		for(int i = 0; i < 32; i++)
			room += (char)('A'+(int)(Math.random()*26));
		CreateChatRoom(room, users);
		return room;
	}

	/**
	 * Opens a chat room named with the supplied string
 	 * Deprecated at this time, use SendGroupChat instead and leverage the UIFragment example
	 * 
	 * @param room		The name of the chat room
	 * @param users		List of the users to invite
	 * @throws Exception
	 */
	public static void CreateChatRoom(String room, String[] users) throws Exception {
		setupInterface();
		Log.i(TAG,"placing call to start chat room!!!");
		ChatInterface.createChat(room, users);
	}

	/**
	 * Send a chat message to all the users in a group
	 * 
	 * @param groupId		The group id to receive the message
	 * @param chatMsg		Message that will be sent
	 * @throws Exception
	 */
	public static void SendGroupChat(String groupId, String chatMsg) throws Exception {
		try{
			setupInterface();
			Log.i(TAG,"SendGroupChat() placing call to group send chat message!!!");
			ChatInterface.sendGroup(groupId, chatMsg, "");
		}catch(Exception e) {
			Log.e(TAG, "SendGroupChat() Error sending message. "+e.toString());
			e.printStackTrace();
		}
	}

	/**
	 * Send a chat message to a room
	 * Deprecated at this time, use SendGroupChat instead and leverage the UIFragment example
	 * 
	 * @param room			The room to receive the message
	 * @param chatMsg		Message that will be sent
	 * @throws Exception
	 */
	public static void Send(String room, String chatMsg) throws Exception {
		try{
			setupInterface();
			Log.i(TAG,"Send() placing call to signal chat message!!!");
			ChatInterface.send(room, chatMsg, "");
		}catch(Exception e) {
			Log.e(TAG, "Send() Error sending message. "+e.toString());
			e.printStackTrace();
		}
	}

	/**
	 * Stops a chat room and leaves it.
	 * Deprecated at this time, use SendGroupChat instead and leverage the UIFragment example
	 * 
	 * @param room
	 * @throws Exception
	 */
	public static void LeaveChat(String room) throws Exception {
		setupInterface();
		ChatInterface.leaveChat(room);
	}
}
