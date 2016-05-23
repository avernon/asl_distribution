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

package org.alljoyn.onboarding.transport;

import org.alljoyn.bus.annotation.Position;
import org.alljoyn.onboarding.OnboardingService.AuthType;

/**
 * A struct that represents a WiFi scan result: SSID and authType.
 */
public class MyScanResult
{
	/**
	 * The personal AP SSID
	 */
    @Position(0) public String m_ssid;
    
    /**
     * The personal AP authentication type
     * -3 - wpa2_auto, onboardee should try WPA2_TKIP and WPA2_CCMP
	 * -2 - wpa_auto, onboardee should try WPA_TKIP and WPA_CCMP
	 * -1 - any, The onboardee chooses the authentication
	 * 0 - Open Personal AP is open 
	 * 1 - WEP
	 * 2 - WPA_TKIP
	 * 3 - WPA_CCMP
	 * 4 - WPA2_TKIP
	 * 5 - WPA2_CCMP
	 * 6 - WPS
     * @see {@link AuthType}
     */
    @Position(1) public short m_authType;
}
