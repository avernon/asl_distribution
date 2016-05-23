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

import java.util.Collections;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import org.allseen.lsf.helper.facade.Group;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class GroupsFlattener {
    public Set<String> groupIDSet;
    public Set<String> lampIDSet;
    int duplicates;

    public GroupsFlattener() {
        super();
    }

    public void flattenGroups(Map<String, Group> groups) {
        for (Group group : groups.values()) {
            GroupDataModel groupModel = group.getGroupDataModel();

            groupIDSet = new HashSet<String>();
            lampIDSet = new HashSet<String>();
            duplicates = 0;

            flattenGroups(groups, groupModel);
            flattenLamps(groups);

            groupModel.setGroups(groupIDSet);
            groupModel.setLamps(lampIDSet);
            groupModel.duplicates = duplicates;
        }
    }

    public void flattenGroups(Map<String, Group> groups, GroupDataModel parentModel) {
        if (!groupIDSet.contains(parentModel.id)) {
            groupIDSet.add(parentModel.id);

            for (String childGroupID : parentModel.members.getLampGroups()) {
                Group childGroup = groups.get(childGroupID);
                GroupDataModel childModel = childGroup != null ? childGroup.getGroupDataModel() : null;

                if (childModel != null) {
                    flattenGroups(groups, childModel);
                }
            }
        } else {
            duplicates++;
        }
    }

    public void flattenLamps(Map<String, Group> groups) {
        for (String groupID : groupIDSet) {
            Group group = groups.get(groupID);
            GroupDataModel groupModel = group != null ? group.getGroupDataModel() : null;

            if (groupModel != null) {
                Collections.addAll(lampIDSet, groupModel.members.getLamps());
            }
        }
    }
}
