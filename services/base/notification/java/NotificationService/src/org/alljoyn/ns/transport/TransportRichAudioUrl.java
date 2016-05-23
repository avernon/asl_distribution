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

package org.alljoyn.ns.transport;

import org.alljoyn.bus.annotation.Position;
import org.alljoyn.ns.RichAudioUrl;

/* 
 * The utility class used to wrap RichAudioUrl object into format of TransportRichAudioUrl that 
 * is sent over AJ network
 */
public class TransportRichAudioUrl {
	
	/**
	 * Url language
	 */
	@Position(0)
	public String language;
	
	/**
	 * Message url
	 */
	@Position(1)
	public String url;

	/**
	 * Constructor
	 */
	public TransportRichAudioUrl() {}
	
	/**
	 * Constructor
	 * @param language
	 * @param url
	 */
	public TransportRichAudioUrl(String language, String url) {
		this.language = language;
		this.url      = url;
	}

	/**
	 * Creates object of TransportRichAudioUrl from RichAudioUrl object
	 * @param richAudioUrl reference to TransportRichAudioUrl object
	 * @return TransportRichAudioUrl
	 */
	public static TransportRichAudioUrl buildInstance(RichAudioUrl richAudioUrl) {
		return new TransportRichAudioUrl(richAudioUrl.getLanguage(),
		     							 richAudioUrl.getUrl()
		);		
	}//buildInstance

}
