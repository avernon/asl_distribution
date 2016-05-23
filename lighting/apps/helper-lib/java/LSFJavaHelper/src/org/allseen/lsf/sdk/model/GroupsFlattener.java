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

import java.util.Collections;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import org.allseen.lsf.sdk.factory.GroupFactory;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class GroupsFlattener<GROUP> {
    protected final GroupFactory<GROUP, ?> factory;

    protected Set<String> groupIDSet;
    protected Set<String> lampIDSet;
    protected int duplicates;

    public GroupsFlattener(GroupFactory<GROUP, ?> factory) {
        super();

        this.factory = factory;
    }

    public void flattenGroups(Map<String, GROUP> groups) {
        for (GROUP group : groups.values()) {
            flattenGroup(groups, group);
        }
    }

    public void flattenGroup(Map<String, GROUP> groups, GROUP group) {
        GroupDataModel groupModel = factory.findGroupDataModel(group);

        groupIDSet = new HashSet<String>();
        lampIDSet = new HashSet<String>();
        duplicates = 0;

        walkGroups(groups, groupModel);
        walkLamps(groups);

        groupModel.setGroups(groupIDSet);
        groupModel.setLamps(lampIDSet);
        groupModel.duplicates = duplicates;
    }

    protected void walkGroups(Map<String, GROUP> groups, GroupDataModel parentModel) {
        if (!groupIDSet.contains(parentModel.id)) {
            groupIDSet.add(parentModel.id);

            for (String childGroupID : parentModel.members.getLampGroups()) {
                GROUP childGroup = groups.get(childGroupID);
                GroupDataModel childModel = childGroup != null ? factory.findGroupDataModel(childGroup) : null;

                if (childModel != null) {
                    walkGroups(groups, childModel);
                }
            }
        } else {
            duplicates++;
        }
    }

    protected void walkLamps(Map<String, GROUP> groups) {
        for (String groupID : groupIDSet) {
            GROUP group = groups.get(groupID);
            GroupDataModel groupModel = group != null ? factory.findGroupDataModel(group) : null;

            if (groupModel != null) {
                Collections.addAll(lampIDSet, groupModel.members.getLamps());
            }
        }
    }
}
