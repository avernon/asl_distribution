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

package org.alljoyn.ns.sampleapp;

public enum MessageTypeEnum {
	Emergency("EMERGENCY"),
	Warning("WARNING"),
    Info("INFO");
	
	/**
	 * Internal name representation
	 */
	public final String INT_NAME;
	
	/**
	 * Constructor
	 * @param name
	 */
	private MessageTypeEnum(String name) {
		INT_NAME = name;
	}	

	/**
	 * Returns string representation of the enum
	 * @return
	 */
	public static String[] stringValues() {
		MessageTypeEnum[] enumValues = MessageTypeEnum.values();
		String[] arr = new String [ enumValues.length ];
		int i = 0;
		for (MessageTypeEnum te : enumValues ) {
			arr[i] = te.toString();
			++i;
		}
		return  arr;
	}//stringValues

}
