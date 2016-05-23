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
package org.allseen.lsf.helper.model;

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

    public GroupDataModel() {
        this((String)null);
    }

    public GroupDataModel(String groupID) {
        this(groupID, null);
    }

    public GroupDataModel(String groupID, String groupName) {
        super(groupID, TAG_PREFIX_GROUP, groupName != null ? groupName : defaultName);

        members = new LampGroup();
    }

    public GroupDataModel(GroupDataModel other) {
        super(other);

        this.members = new LampGroup(other.members);
        this.lamps = new HashSet<String>(other.lamps);
        this.groups = new HashSet<String>(other.groups);
        this.duplicates = other.duplicates;
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

    public Set<String> getLamps() {
        return lamps;
    }

    public Set<String> getGroups() {
        return groups;
    }
}
