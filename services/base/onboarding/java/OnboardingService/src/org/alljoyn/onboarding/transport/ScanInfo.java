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

package org.alljoyn.onboarding.transport;

import org.alljoyn.bus.annotation.Position;

/**
 * A class that represents a WiFi scan: an array of SSID and authType, with an age
 */
public class ScanInfo
{
	/**
	 * age reflects how long ago was the scan procedure performed by the device. The units are in minutes.
	 */
    @Position(0) public short m_age;
    
    /**
     * An array of {@link MyScanResult}. Each one represents a potential personal AP: SSID and authType.
     */
    @Position(1) public MyScanResult[] m_scanResults;
	
    public ScanInfo()
    {
    }
    
    /**
     * Get the age of the scan
     * @return age in minutes
     */
	public short getAge()
	{
		return m_age;
	}

	/**
	 * set the age of the scan
	 * @param age in minutes
	 */
	public void setAge(short age)
	{
		m_age = age;
	}

	/**
	 * Get the Scan Result
	 * @return an array of SSID,AuthType pairs
	 */
	public MyScanResult[] getScanResults()
	{
		return m_scanResults;
	}

	/**
	 * Set the scan result
	 * @param result
	 */
	public void setScanResult(MyScanResult[] result)
	{
		m_scanResults = result;
	}

}

