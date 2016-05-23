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
 * RichNotificationAudioUrl. Creates object of the RichNotificationAudioUrl class
 */
public class RichAudioUrl {

	/**
	 * Reference to language string <br>
	 * The language must comply IETF standard 
	 */
	private String language;
	
	/**
	 * RichNotification Audio Url
	 */
	private String url;
	
	/**
	 * Constructor
	 */
	public RichAudioUrl() {}
	
	/**
	 * Constructor
	 * @param language - The language must comply IETF standard 
	 * @param url - rich notification audio url
	 * @throws NotificationServiceException Thrown if language is null url is null or empty
	 */
	public RichAudioUrl(String language, String url) throws NotificationServiceException {
		setLanguage(language);
		setUrl(url);
	}

	/**
	 * @return String Returns audio url language. The language must comply IETF standard 
	 */
	public String getLanguage() {
		return language;
	}
	
	/**
	 * Set the language
	 * @param language The language must comply IETF standard 
	 * @throws NotificationServiceException Thrown if language is null
	 */
	public void setLanguage(String language) throws NotificationServiceException {
		if (language == null || language.length() == 0 ) {
			throw new NotificationServiceException("Language is undefined");
		}
		this.language = language;
	}//setLanguage
	
	/**
	 * @return the rich notification audio url
	 */
	public String getUrl(){
		return url;
	}
	
	/**
	 * Set the notification url
	 * @param url the notification url
	 * @throws NotificationServiceException Thrown if url is null or is empty
	 */
	public void setUrl(String url) throws NotificationServiceException {
		if ( url == null || url.length() == 0 ) {
			throw new NotificationServiceException("audio url is undefined");
		}
		this.url = url;
	}//setUrl

	
	/**
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		return "RichAudioUrl [language= '" + language + "', url='" + url + "']";
	}
	
}//RichNotificationAudioUrl

