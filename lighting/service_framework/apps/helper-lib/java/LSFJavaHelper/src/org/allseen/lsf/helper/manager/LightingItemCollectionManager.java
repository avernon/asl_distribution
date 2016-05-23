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

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.allseen.lsf.ResponseCode;
import org.allseen.lsf.helper.listener.LightingItemErrorEvent;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public abstract class LightingItemCollectionManager<ADAPTER, LISTENER, MODEL> extends LightingItemListenerManager<LISTENER> {

    protected final Map<String, ADAPTER> itemAdapters = new HashMap<String, ADAPTER>();
    protected final List<LISTENER> itemListeners = new ArrayList<LISTENER>();

    public LightingItemCollectionManager(LightingSystemManager director) {
        super(director);
    }

    public boolean hasID(String itemID) {
        return itemAdapters.containsKey(itemID);
    }

    protected Collection<String> getIDCollection() {
        return itemAdapters.keySet();
    }

    public Iterator<String> getIDIterator() {
        return getIDCollection().iterator();
    }

    public String[] getIDArray() {
        return getIDArray(new String[size()]);
    }

    public String[] getIDArray(String[] itemIDs) {
        return getIDCollection().toArray(itemIDs);
    }

    public int size() {
        return itemAdapters.size();
    }

    protected ADAPTER getAdapter(String itemID) {
        return itemAdapters.get(itemID);
    }

    protected ADAPTER removeAdapter(String itemID) {
        ADAPTER item = itemAdapters.remove(itemID);

        sendRemovedEvent(item);

        return item;
    }

    protected Collection<ADAPTER> getAdapters() {
        return itemAdapters.values();
    }

    @Override
    public void addListener(LISTENER listener) {
        super.addListener(listener);

        sendChangedEvent(listener, itemAdapters.values().iterator(), size());
    }

    public void sendChangedEvent(String itemID) {
        sendChangedEvent(Arrays.asList(getAdapter(itemID)).iterator(), 1);
    }

    protected void sendChangedEvent(Iterator<ADAPTER> items, int count) {
        for (LISTENER listener : itemListeners) {
            sendChangedEvent(listener, items, count);
        }
    }

    public void sendRemovedEvent(ADAPTER item) {
        sendRemovedEvent(Arrays.asList(item).iterator(), 1);
    }

    protected void sendRemovedEvent(Iterator<ADAPTER> items, int count) {
        for (LISTENER listener : itemListeners) {
            sendChangedEvent(listener, items, count);
        }
    }

    public void sendErrorEvent(String name, ResponseCode responseCode) {
        sendErrorEvent(name, responseCode, null);
    }

    public void sendErrorEvent(String name, ResponseCode responseCode, String itemID) {
        sendErrorEvent(new LightingItemErrorEvent(name, responseCode, itemID));
    }

    public void sendErrorEvent(LightingItemErrorEvent errorEvent) {
        for (LISTENER listener : itemListeners) {
            sendErrorEvent(listener, errorEvent);
        }
    }

    protected abstract void sendChangedEvent(LISTENER listener, Iterator<ADAPTER> items, int count);
    protected abstract void sendRemovedEvent(LISTENER listener, Iterator<ADAPTER> items, int count);
    protected abstract void sendErrorEvent(LISTENER listener, LightingItemErrorEvent errorEvent);

    public abstract MODEL getModel(String itemID);
}
