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

package org.alljoyn.ns;

/**
 * Notification message types
 */
public enum NotificationMessageType {
	EMERGENCY ((short)0), 
	WARNING((short)1), 
	INFO((short)2);
	
	/**
	 * Type Id
	 */
	private short typeId;
	
	/**
	 * Constructor
	 * @param typeId
	 */
	private NotificationMessageType(short typeId) {
		this.typeId = typeId;
	}
	
	/**
	 * @return Returns type id
	 */
	public short getTypeId() {
		return typeId;
	}
	
	/**
	 * Search for message type with the given Id.
	 * If not found returns NULL
	 * @param msgTypeId type id
	 * @return Notification message type
	 */
	public static NotificationMessageType getMsgTypeById(short msgTypeId) {
		NotificationMessageType retType = null;
		for (NotificationMessageType type : NotificationMessageType.values()) {
			if ( msgTypeId == type.getTypeId() ) {
				retType = type;
				break;
			}
		}
		return retType;
	}//getMsgTypeById
}
