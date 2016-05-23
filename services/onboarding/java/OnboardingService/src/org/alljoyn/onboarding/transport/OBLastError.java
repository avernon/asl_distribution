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

/**
 * A class that represents the last onboarding error: The last error code and error message
 */
public class OBLastError {

	/** 
	 * The error code of the last validation
	 * 0 - Validated
	 * 1 - Unreachable
	 * 2 - Unsupported_protocol
	 * 3 - Unauthorized
	 * 4 - Error_message
	 */
    @Position(0) public short m_errorCode;
    
    /** 
     * The error message of the last validation
     * Error_message is the error message received from the underlying Wifi layer. 
     */
    @Position(1) public String m_errorMsg;
	
    public OBLastError()
    {
    }
    
    /**
     * Get the last validation error code
     * @return the last error code
	 * 0 - Validated
	 * 1 - Unreachable
	 * 2 - Unsupported_protocol
	 * 3 - Unauthorized
	 * 4 - Error_message
     */
	public short getErrorCode()
	{
		return m_errorCode;
	}

	/**
	 * Set the last validation error code
	 * @param errorCode
	 */
	public void setErrorCode(short errorCode)
	{
		m_errorCode = errorCode;
	}

	/**
	 * Get the last validation error message
	 * @return the error message received from the underlying Wifi layer.
	 */
	public String getErrorMessage()
	{
		return m_errorMsg;
	}

	/**
	 * Set the last validation error message
	 * @param errorMsg
	 */
	public void setErrorMessage(String errorMsg)
	{
		m_errorMsg = errorMsg;
	}
	
}
