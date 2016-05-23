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

package org.alljoyn.ns;


/**
 * NotificationText. Creates object of the NotificationText class
 */
public class NotificationText {

	/**
	 * Reference to language string <br>
	 * The language must comply with the IETF standard 
	 */
	private String language;
	
	/**
	 * Notification text
	 */
	private String text;
	
	/**
	 * Constructor
	 */
	public NotificationText() {}
	
	/**
	 * Constructor
	 * @param language The language must comply with the IETF standard 
	 * @param text the notification text
	 * @throws NotificationServiceException Thrown if language is null text is null or empty
	 */
	public NotificationText(String language, String text) throws NotificationServiceException {
		setLanguage(language);
		setText(text);
	}

	/**
	 * @return String Returns notification language. The language must comply with the IETF standard 
	 */
	public String getLanguage() {
		return language;
	}
	
	/**
	 * Set the language
	 * @param language The language must comply with the IETF standard 
	 * @throws NotificationServiceException Thrown if language is null
	 */
	public void setLanguage(String language) throws NotificationServiceException {
		if ( language == null || language.length() == 0 ) {
			throw new NotificationServiceException("Language is undefined");
		}
		this.language = language;
	}//setLanguage
	
	/**
	 * @return the notification text
	 */
	public String getText(){
		return text;
	}
	
	/**
	 * Set the notification text
	 * @param text the notification text
	 * @throws NotificationServiceException Thrown if text is null or is empty
	 */
	public void setText(String text) throws NotificationServiceException {
		if ( text == null || text.length() == 0 ) {
			throw new NotificationServiceException("Text is undefined");
		}
		this.text = text;
	}//setText

	
	/**
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		return "NotificationText [language='" + language + "', text='" + text + "']";
	}
	
}//NotificationText
