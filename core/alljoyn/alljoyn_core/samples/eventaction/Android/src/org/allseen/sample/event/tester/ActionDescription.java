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

package org.allseen.sample.event.tester;

/*
 * Place holder for the case where an Action needs to have its own set of extended values.
 * Allows ability to store an array for Descriptions and use instanceOf to determine type.
 */
public class ActionDescription extends Description {
	private String friendlyName;

	public String getFriendlyName() {
		return friendlyName;
	}

	public void setFriendlyName(String friendlyName) {
		this.friendlyName = friendlyName;
	}
	
	public String toString() {
		String ret = "";
		ret += this.getDescription()+",";
		ret += this.getSessionName()+",";
		ret += this.getPath()+",";
		ret += this.getIface()+",";
		ret += this.getMemberName()+",";
		ret += this.getSignature()+",";
		ret += this.getFriendlyName();
		
		return ret;
	}
	
	public void createFromString(String s) {
		String elements[] = s.split("\\,");
		this.setDescription(elements[0]);
		this.setSessionName(elements[1]);
		this.setPath(elements[2]);
		this.setIface(elements[3]);
		this.setMemberName(elements[4]);
		this.setSignature(elements[5]);
		this.setFriendlyName(elements[6]);
	}
}
