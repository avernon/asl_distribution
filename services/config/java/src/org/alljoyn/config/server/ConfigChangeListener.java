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

package org.alljoyn.config.server;

import java.util.Map;

import org.alljoyn.bus.Variant;

/**
 * A listener to configuration changes that were triggered by remote clients. 
 */
public interface ConfigChangeListener
{
	/**	
	 * A callback that informs the listener that the configuration has changed for a specific language
	 * @param newConfiguration
	 * @param languageTag the language for which fields were updated
	 */
	public void onConfigChanged(Map<String, Variant> newConfiguration, String languageTag);
	
	/**
	 * A callback that informs the listener that some configuration fields were removed for a specific language
	 * @param language the language for which fields were removed
	 * @param fieldNames the fields that were removed
	 */
	public void onResetConfiguration(String language, String[] fieldNames);
}
