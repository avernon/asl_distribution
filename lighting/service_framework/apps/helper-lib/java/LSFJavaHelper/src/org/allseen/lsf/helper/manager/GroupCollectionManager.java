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
package org.allseen.lsf.helper.manager;

import java.util.Iterator;

import org.allseen.lsf.helper.facade.Group;
import org.allseen.lsf.helper.listener.GroupCollectionListener;
import org.allseen.lsf.helper.listener.LightingItemErrorEvent;
import org.allseen.lsf.helper.model.GroupDataModel;
import org.allseen.lsf.helper.model.GroupsFlattener;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class GroupCollectionManager extends LightingItemCollectionManager<Group, GroupCollectionListener, GroupDataModel> {

    protected GroupsFlattener groupsFlattener = new GroupsFlattener();

    public GroupCollectionManager(LightingSystemManager director) {
        super(director);
    }

    public Group addGroup(String groupID) {
        return addGroup(groupID, new Group(groupID));
    }

    public Group addGroup(String groupID, Group group) {
        return itemAdapters.put(groupID, group);
    }

    public Group getGroup(String groupID) {
        return getAdapter(groupID);
    }

    public Group[] getGroups() {
        return getAdapters().toArray(new Group[size()]);
    }

    public Iterator<Group> getGroupIterator() {
        return getAdapters().iterator();
    }

    public void flattenGroups() {
        groupsFlattener.flattenGroups(itemAdapters);
    }

    public Group removeGroup(String groupID) {
        return removeAdapter(groupID);
    }

    @Override
    protected void sendChangedEvent(GroupCollectionListener listener, Iterator<Group> groups, int count) {
        listener.onGroupsChanged(groups, count);
    }

    @Override
    protected void sendRemovedEvent(GroupCollectionListener listener, Iterator<Group> groups, int count) {
        listener.onGroupsRemoved(groups, count);
    }

    @Override
    protected void sendErrorEvent(GroupCollectionListener listener, LightingItemErrorEvent errorEvent) {
        listener.onGroupError(errorEvent);
    }

    @Override
    public GroupDataModel getModel(String groupID) {
        Group group = getAdapter(groupID);

        return group != null ? group.getGroupDataModel() : null;
    }
}
