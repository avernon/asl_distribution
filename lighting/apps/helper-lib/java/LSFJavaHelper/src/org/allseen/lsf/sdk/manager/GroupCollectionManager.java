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
package org.allseen.lsf.sdk.manager;

import java.util.Collection;
import java.util.Iterator;

import org.allseen.lsf.sdk.TrackingID;
import org.allseen.lsf.sdk.factory.GroupFactory;
import org.allseen.lsf.sdk.listener.GroupCollectionListener;
import org.allseen.lsf.sdk.model.GroupDataModel;
import org.allseen.lsf.sdk.model.GroupsFlattener;
import org.allseen.lsf.sdk.model.LightingItemFilter;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class GroupCollectionManager<GROUP, ERROR> extends LightingItemCollectionManager<GROUP, GroupCollectionListener<? super GROUP, ? super ERROR>, GroupDataModel, ERROR> {

    protected final GroupFactory<GROUP, ERROR> factory;
    protected final GroupsFlattener<GROUP> groupsFlattener;

    public GroupCollectionManager(LightingSystemManager<?, GROUP, ?, ?, ?, ?, ?, ?, ?, ?, ?> manager, GroupFactory<GROUP, ERROR> factory) {
        super(manager, factory);

        this.factory = factory;
        this.groupsFlattener = new GroupsFlattener<GROUP>(factory);
    }

    public GROUP addGroup(String groupID) {
        return addGroup(groupID, factory.createGroup(groupID));
    }

    public GROUP addGroup(String groupID, GROUP group) {
        return itemAdapters.put(groupID, group);
    }

    public GROUP getGroup(String groupID) {
        return getAdapter(groupID);
    }

    public GROUP[] getGroups() {
        return getAdapters().toArray(factory.createGroups(size()));
    }

    public GROUP[] getGroups(LightingItemFilter<GROUP> filter) {
        Collection<GROUP> filteredGroups = getGroupCollection(filter);
        return filteredGroups.toArray(factory.createGroups(filteredGroups.size()));
    }

    public Collection<GROUP> getGroupCollection(LightingItemFilter<GROUP> filter) {
        return getAdapters(filter);
    }

    public Iterator<GROUP> getGroupIterator() {
        return getAdapters().iterator();
    }

    public void flattenGroups() {
        groupsFlattener.flattenGroups(itemAdapters);
    }

    public void flattenGroup(GROUP group) {
        groupsFlattener.flattenGroup(itemAdapters, group);
    }

    public Collection<GROUP> removeGroups() {
        return removeAllAdapters();
    }

    public GROUP removeGroup(String groupID) {
        return removeAdapter(groupID);
    }

    @Override
    protected void sendInitializedEvent(GroupCollectionListener<? super GROUP, ? super ERROR> listener, GROUP group, TrackingID trackingID) {
        listener.onGroupInitialized(trackingID, group);
    }

    @Override
    protected void sendChangedEvent(GroupCollectionListener<? super GROUP, ? super ERROR> listener, GROUP group) {
        listener.onGroupChanged(group);
    }

    @Override
    protected void sendRemovedEvent(GroupCollectionListener<? super GROUP, ? super ERROR> listener, GROUP group) {
        listener.onGroupRemoved(group);
    }

    @Override
    protected void sendErrorEvent(GroupCollectionListener<? super GROUP, ? super ERROR> listener, ERROR error) {
        listener.onGroupError(error);
    }

    @Override
    public GroupDataModel getModel(String groupID) {
        return getModel(getAdapter(groupID));
    }

    @Override
    public GroupDataModel getModel(GROUP group) {
        return group != null ? factory.findGroupDataModel(group) : null;
    }
}
