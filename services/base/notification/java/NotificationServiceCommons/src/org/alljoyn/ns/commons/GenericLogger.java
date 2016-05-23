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

package org.alljoyn.ns.commons;

/**
 * Implement this interface to provide logging functionality for the Notification service
 */
public interface GenericLogger {
	/**
	 * Debug level message
	 * @param TAG Tag to be added to the message, i.e. class that writes the message 
	 * @param msg 
	 */
	public void debug(String TAG, String msg);
	
	/**
	 * Info level message
	 * @param TAG Tag to be added to the message, i.e. class that writes the message 
	 * @param msg 
	 */
	public void info(String TAG, String msg);

	/**
	 * Warn level message
	 * @param TAG Tag to be added to the message, i.e. class that writes the message 
	 * @param msg 
	 */
	public void warn(String TAG, String msg);

	/**
	 * Error level message
	 * @param TAG Tag to be added to the message, i.e. class that writes the message 
	 * @param msg 
	 */
	public void error(String TAG, String msg);
	
	/**
	 * Fatal level message
	 * @param TAG Tag to be added to the message, i.e. class that writes the message 
	 * @param msg 
	 */
	public void fatal(String TAG, String msg);
}
