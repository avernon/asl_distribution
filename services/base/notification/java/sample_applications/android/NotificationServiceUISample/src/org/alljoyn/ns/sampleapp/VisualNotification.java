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

package org.alljoyn.ns.sampleapp;

import org.alljoyn.ns.Notification;
import org.alljoyn.ns.NotificationText;

/**
 * Handled the received {@link Notification} object
 */
public class VisualNotification {
	
	/**
	 * The received {@link Notification} 
	 */
	private Notification notification;
	
	/**
	 * Marker whether the {@link Notification} has been selected
	 */
	private boolean isChecked;
	
	/**
	 * The counter is incremented when a {@link VisualNotification} object gets isChecked state
	 * as TRUE and it's decremented when it's FALSE
	 */
	private static int checkedCounter;
	
	/**
	 * The language the user preferred to view the {@link NotificationText}
	 */
	private String userPreferredLang;
	
	/**
	 * The text to be presented to the user in the userPreferredLang
	 */
	private String userPreferredText;
	
	/**
	 * Gets TRUE when the {@link VisualNotification} is dismissed
	 */
	private volatile boolean isDismissed;
	
	/**
	 * Constructor
	 * @param notification The received notification
	 */
	public VisualNotification(Notification notification, String userPreferredLang) {
		this.notification      = notification;
		this.userPreferredLang = userPreferredLang;
	}

	/**
	 * @return {@link Notification}
	 */
	public Notification getNotification() {
		return notification;
	}//getNotification

	/**
	 * @return Marker whether the {@link Notification} has been checked
	 */
	public boolean isChecked() {
		return isChecked;
	}

	/**
	 * @param isChecked Sets the {@link VisualNotification} checked state <br>
	 * The state of the isChecked influences the static checkedCounter variable. <br>
	 * If isChecked is TRUE the checkedCounter is incremented by one otherwise it's decremented
	 */
	public void setChecked(boolean isChecked) {
		this.isChecked = isChecked;
		
		if ( isChecked ) {
			++checkedCounter;
		}
		else if ( checkedCounter > 0 ){
			--checkedCounter;
		}
	}//setChecked

	/**
	 * @return The current checkedCounter value
	 */
	public static int getCheckedCounter() {
		return checkedCounter;
	}//getCheckedCounter

	/**
	 * @return The language string, the user preferred to see the {@link NotificationText}
	 */
	public String getUserPreferredLang() {
		return userPreferredLang;
	}

	/**
	 * @return The text to be presented to the user, when this {@link VisualNotification} is rendered
	 */
	public String getUserPreferredText() {
		return userPreferredText;
	}

	/**
	 * @param userPreferredText The text to be presented to the user, when this {@link VisualNotification} is rendered
	 */
	public void setUserPreferredText(String userPreferredText) {
		this.userPreferredText = userPreferredText;
	}
	
	/**
	 * @return Whether the Notification is dismissed
	 */
	public boolean isDismissed() {
		return isDismissed;
	}

	/**
	 * @param isDismissed Whether the Notification is dismissed
	 */
	public void setDismissed(boolean isDismissed) {
		this.isDismissed = isDismissed;
	}
	
		
}
