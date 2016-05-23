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

import java.util.ArrayDeque;
import java.util.Collection;
import java.util.Iterator;
import java.util.Queue;

import org.allseen.lsf.sdk.TrackingID;
import org.allseen.lsf.sdk.factory.LampFactory;
import org.allseen.lsf.sdk.listener.LampCollectionListener;
import org.allseen.lsf.sdk.model.LampDataModel;
import org.allseen.lsf.sdk.model.LightingItemFilter;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class LampCollectionManager<LAMP, ERROR> extends LightingItemCollectionManager<LAMP, LampCollectionListener<? super LAMP, ? super ERROR>, LampDataModel, ERROR> {

    protected final LampFactory<LAMP, ERROR> factory;
    protected final Queue<String> lampIDs = new ArrayDeque<String>();

    public LampCollectionManager(LightingSystemManager<LAMP, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?> manager, LampFactory<LAMP, ERROR> factory) {
        super(manager, factory);
        this.factory = factory;
    }

    @Override
    protected Collection<String> getIDCollection() {
        // Overridden for efficiency
        return lampIDs;
    }

    public LAMP addLamp(String lampID) {
        return addLamp(lampID, factory.createLamp(lampID));
    }

    public LAMP addLamp(String lampID, LAMP lamp) {
        itemAdapters.put(lampID, lamp);
        lampIDs.add(lampID);

        return lamp;
    }

    public LAMP getLamp(String lampID) {
        return getAdapter(lampID);
    }

    public LAMP[] getLamps() {
        return getAdapters().toArray(factory.createLamps(size()));
    }

    public LAMP[] getLamps(LightingItemFilter<LAMP> filter) {
        Collection<LAMP> filteredLamps = getLampsCollection(filter);
        return filteredLamps.toArray(factory.createLamps(filteredLamps.size()));
    }

    public Collection<LAMP> getLampsCollection(LightingItemFilter<LAMP> filter) {
        return getAdapters(filter);
    }

    public Iterator<LAMP> getLampIterator() {
        return getAdapters().iterator();
    }

    public Collection<LAMP> removeAllLamps() {
        return removeAllAdapters();
    }

    public LAMP removeLamp(String lampID) {
        lampIDs.remove(lampID);

        return removeAdapter(lampID);
    }

    @Override
    protected void sendInitializedEvent(LampCollectionListener<? super LAMP, ? super ERROR> listener, LAMP lamp, TrackingID trackingID) {
        listener.onLampInitialized(lamp);
    }

    @Override
    protected void sendChangedEvent(LampCollectionListener<? super LAMP, ? super ERROR> listener, LAMP lamp) {
        listener.onLampChanged(lamp);
    }

    @Override
    protected void sendRemovedEvent(LampCollectionListener<? super LAMP, ? super ERROR> listener, LAMP lamp) {
        listener.onLampRemoved(lamp);
    }

    @Override
    protected void sendErrorEvent(LampCollectionListener<? super LAMP, ? super ERROR> listener, ERROR error) {
        listener.onLampError(error);
    }

    @Override
    public LampDataModel getModel(String lampID) {
        return getModel(getAdapter(lampID));
    }

    @Override
    public LampDataModel getModel(LAMP lamp) {
        return lamp != null ? factory.findLampDataModel(lamp) : null;
    }
}
