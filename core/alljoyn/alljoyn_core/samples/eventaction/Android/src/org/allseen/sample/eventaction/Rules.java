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
package org.allseen.sample.eventaction;

import java.util.Vector;

import org.allseen.sample.event.tester.ActionDescription;
import org.allseen.sample.event.tester.EventDescription;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

public class Rules {
	private EventDescription event;
	private Vector<ActionDescription> actions = new Vector<ActionDescription>();
	
	public Rules() {}
	
	public Rules(EventDescription event) {
		this.event = event;
	}
	
	public EventDescription getEvent() {
		return event;
	}
	
	public Vector<ActionDescription> getActions() {
		return actions;
	}
	
	public void addAction(ActionDescription action) {
		actions.add(action);
	}
	
	public void removeAction(ActionDescription action) {
		actions.remove(action);
	}

	public void removeAllActions() {
		actions.clear();
	}
	
	public String toString() {
		JSONObject json = new JSONObject();
		try{
			json.put("event", event.toString());
			JSONArray array = new JSONArray();
			for(ActionDescription a : this.actions) {
				array.put(a.toString());
			}
			json.put("actions", array);
		}catch(Exception e) {
			e.printStackTrace();
		}
		return json.toString();
	}
	
	public void createFromString(String s) {
		try {
			JSONObject json = new JSONObject(s);
			event = new EventDescription();
			event.createFromString((String)json.get("event"));
			JSONArray array = json.getJSONArray("actions");
			for(int i = 0; i < array.length(); i++) {
				ActionDescription a = new ActionDescription();
				a.createFromString(array.getString(i));
				actions.add(a);
			}
		} catch (JSONException e) {
			e.printStackTrace();
		}
		
	}

}
