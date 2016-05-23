/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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

package org.alljoyn.ioe.notificationviewer.logic.Interface;

public class DeviceResponse 
{
	public enum ResponseCode
	{
		Status_OK,
		Status_ERROR,
		Status_ERROR_NO_PEER_NAME,
		Status_ERROR_CANT_ESTABLISH_SESSION
		
	}//enum
	
	private ResponseCode m_status;
	private String m_msg;
	private Throwable m_throwable;
	
	public DeviceResponse(ResponseCode status)
	{
		m_status = status;

	}
	
	public DeviceResponse(ResponseCode status, String msg)
	{
		m_status = status;
		m_msg = msg;
	}
	
	public DeviceResponse(ResponseCode status, String msg, Throwable t)
	{
		m_status = status;
		m_msg = msg;
		m_throwable = t;
	}

	public ResponseCode getStatus()
	{
		return m_status;
	}
	
	public String getMsg() 
	{
		return m_msg;
	}
}
