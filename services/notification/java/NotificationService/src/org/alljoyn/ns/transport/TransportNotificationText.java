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

package org.alljoyn.ns.transport;

import org.alljoyn.bus.annotation.Position;
import org.alljoyn.ns.NotificationText;

/* 
 * The utility class used to wrap NotificationText object into format of TransportNotificationText that 
 * is sent over AJ network
 */
public class TransportNotificationText {
	
	/**
	 * Text language
	 */
	@Position(0)
	public String language;
	
	/**
	 * Message text
	 */
	@Position(1)
	public String text;

	/**
	 * Constructor
	 */
	public TransportNotificationText() {}
	
	/**
	 * Constructor
	 * @param language
	 * @param text
	 */
	public TransportNotificationText(String language, String text) {
		this.language = language;
		this.text     = text;
	}

	/**
	 * Creates object of TransportNotificationText from NotificationText object
	 * @param notifText reference to NotificationText object
	 * @return TransportNotificationText
	 */
	public static TransportNotificationText buildInstance(NotificationText notifText) {
		TransportNotificationText trNotTxt = new TransportNotificationText(notifText.getLanguage(),
		     															   notifText.getText()
		);
		return trNotTxt;
	}//buildInstance

}
