/*
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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
 */
package org.allseen.lsf.sdk.model;

import java.util.HashSet;
import java.util.Set;

import org.allseen.lsf.LampGroup;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class GroupDataModel extends ColorItemDataModel {
    public static final char TAG_PREFIX_GROUP = 'G';

    public static String defaultName = "<Loading group info...>";

    public LampGroup members;
    private Set<String> lamps;
    private Set<String> groups;
    public int duplicates;
    public int viewColorTempMin;
    public int viewColorTempMax;

    public GroupDataModel() {
        this((String)null);
    }

    public GroupDataModel(String groupID) {
        this(groupID, null);
    }

    public GroupDataModel(String groupID, String groupName) {
        this(groupID, TAG_PREFIX_GROUP, groupName);
    }

    public GroupDataModel(String groupID, char prefix, String groupName) {
        super(groupID, prefix, groupName != null ? groupName : defaultName);

        members = new LampGroup();

        viewColorTempMin = ColorStateConverter.VIEW_COLORTEMP_MIN;
        viewColorTempMax = ColorStateConverter.VIEW_COLORTEMP_MAX;
    }

    public GroupDataModel(GroupDataModel other) {
        super(other);

        this.members = new LampGroup(other.members);
        this.lamps = new HashSet<String>(other.lamps);
        this.groups = new HashSet<String>(other.groups);
        this.duplicates = other.duplicates;
        this.viewColorTempMax = other.viewColorTempMax;
        this.viewColorTempMin = other.viewColorTempMin;
    }

    public void setLamps(Set<String> lamps) {
        this.lamps = lamps;
        // capability data is now dirty
        capability = new LampCapabilities();
    }

    public void setGroups(Set<String> groups) {
        this.groups = groups;
        // capability data is now dirty
        capability = new LampCapabilities();
    }

    public void setMembers(LampGroup members) {
        this.members = members;
        // a group's state is initialized when its LampGroup container is set
        stateInitialized = true;
    }

    public Set<String> getLamps() {
        return lamps;
    }

    public Set<String> getGroups() {
        return groups;
    }

    public LampGroup getMembers() {
        return this.members;
    }

    // Only checks immediate child lamps. To see if the lamp is in a descendent (child, grandchild,
    // great-grandchild, etc.) group, you can use getLamps().contains(lampID);
    public boolean containsLamp(String lampID) {
        String[] childIDs = members.getLamps();

        for (String childID : childIDs) {
            if (childID.equals(lampID)) {
                return true;
            }
        }

        return false;
    }

    // Only checks immediate child groups. To see if the group is a descendent (child, grandchild,
    // great-grandchild, etc.) you can use getGroups().contains(groupID);
    public boolean containsGroup(String groupID) {
        String[] childIDs = members.getLampGroups();

        for (String childID : childIDs) {
            if (childID.equals(groupID)) {
                return true;
            }
        }

        return false;
    }

    @Override
    public boolean isInitialized() {
        return super.isInitialized();
    }
}
