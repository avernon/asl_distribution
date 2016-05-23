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

import java.util.ArrayDeque;
import java.util.Collection;
import java.util.Iterator;
import java.util.Queue;

import org.allseen.lsf.helper.facade.Lamp;
import org.allseen.lsf.helper.listener.LampCollectionListener;
import org.allseen.lsf.helper.listener.LightingItemErrorEvent;
import org.allseen.lsf.helper.model.LampDataModel;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class LampCollectionManager extends LightingItemCollectionManager<Lamp, LampCollectionListener, LampDataModel> {

    protected final Queue<String> lampIDs = new ArrayDeque<String>();

    public LampCollectionManager(LightingSystemManager director) {
        super(director);
    }

    @Override
    protected Collection<String> getIDCollection() {
        // Overridden for efficiency
        return lampIDs;
    }

    public Lamp addLamp(String lampID) {
        return addLamp(lampID, new Lamp(lampID));
    }

    public Lamp addLamp(String lampID, Lamp lamp) {
        itemAdapters.put(lampID, lamp);
        lampIDs.add(lampID);

        return lamp;
    }

    public Lamp getLamp(String lampID) {
        return getAdapter(lampID);
    }

    public Lamp[] getLamps() {
        return getAdapters().toArray(new Lamp[size()]);
    }

    public Iterator<Lamp> getLampIterator() {
        return getAdapters().iterator();
    }

    public Lamp removeLamp(String lampID) {
        lampIDs.remove(lampID);

        return removeAdapter(lampID);
    }

    @Override
    protected void sendChangedEvent(LampCollectionListener listener, Iterator<Lamp> lamps, int count) {
        listener.onLampsChanged(lamps, count);
    }

    @Override
    protected void sendRemovedEvent(LampCollectionListener listener, Iterator<Lamp> lamps, int count) {
        listener.onLampsRemoved(lamps, count);
    }

    @Override
    protected void sendErrorEvent(LampCollectionListener listener, LightingItemErrorEvent errorEvent) {
        listener.onLampError(errorEvent);
    }

    @Override
    public LampDataModel getModel(String lampID) {
        Lamp lamp = getAdapter(lampID);

        return lamp != null ? lamp.getLampDataModel() : null;
    }
}
