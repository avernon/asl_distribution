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
import org.allseen.lsf.sdk.factory.MasterSceneFactory;
import org.allseen.lsf.sdk.listener.MasterSceneCollectionListener;
import org.allseen.lsf.sdk.model.LightingItemFilter;
import org.allseen.lsf.sdk.model.MasterSceneDataModel;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class MasterSceneCollectionManager<MASTERSCENE, ERROR> extends LightingItemCollectionManager<MASTERSCENE, MasterSceneCollectionListener<? super MASTERSCENE, ? super ERROR>, MasterSceneDataModel, ERROR> {

    protected final MasterSceneFactory<MASTERSCENE, ERROR> factory;

    public MasterSceneCollectionManager(LightingSystemManager<?, ?, ?, ?, ?, ?, ?, ?, MASTERSCENE, ?, ?> manager, MasterSceneFactory<MASTERSCENE, ERROR> factory) {
        super(manager, factory);

        this.factory = factory;
    }

    public MASTERSCENE addMasterScene(String masterSceneID) {
        return addMasterScene(masterSceneID, factory.createMasterScene(masterSceneID));
    }

    public MASTERSCENE addMasterScene(String masterSceneID, MASTERSCENE scene) {
        return itemAdapters.put(masterSceneID, scene);
    }

    public MASTERSCENE getMasterScene(String masterSceneID) {
        return getAdapter(masterSceneID);
    }

    public MASTERSCENE[] getMasterScenes() {
        return getAdapters().toArray(factory.createMasterScenes(size()));
    }

    public MASTERSCENE[] getMasterScenes(LightingItemFilter<MASTERSCENE> filter) {
        Collection<MASTERSCENE> filteredMasterScenes = getMasterScenesCollection(filter);
        return filteredMasterScenes.toArray(factory.createMasterScenes(filteredMasterScenes.size()));
    }

    public Collection<MASTERSCENE> getMasterScenesCollection(LightingItemFilter<MASTERSCENE> filter) {
        return getAdapters(filter);
    }

    public Iterator<MASTERSCENE> getMasterSceneIterator() {
        return getAdapters().iterator();
    }

    public Collection<MASTERSCENE> removeMasterScenes() {
        return removeAllAdapters();
    }

    public MASTERSCENE removeMasterScene(String masterSceneID) {
        return removeAdapter(masterSceneID);
    }

    @Override
    protected void sendInitializedEvent(MasterSceneCollectionListener<? super MASTERSCENE, ? super ERROR> listener, MASTERSCENE masterScene, TrackingID trackingID) {
        listener.onMasterSceneInitialized(trackingID, masterScene);
    }

    @Override
    protected void sendChangedEvent(MasterSceneCollectionListener<? super MASTERSCENE, ? super ERROR> listener, MASTERSCENE masterScene) {
        listener.onMasterSceneChanged(masterScene);
    }

    @Override
    protected void sendRemovedEvent(MasterSceneCollectionListener<? super MASTERSCENE, ? super ERROR> listener, MASTERSCENE masterScene) {
        listener.onMasterSceneRemoved(masterScene);
    }

    @Override
    protected void sendErrorEvent(MasterSceneCollectionListener<? super MASTERSCENE, ? super ERROR> listener, ERROR error) {
        listener.onMasterSceneError(error);
    }

    @Override
    public MasterSceneDataModel getModel(String masterSceneID) {
        return getModel(getAdapter(masterSceneID));
    }

    @Override
    public MasterSceneDataModel getModel(MASTERSCENE masterScene) {
        return masterScene != null ? factory.findMasterSceneDataModel(masterScene) : null;
    }
}
