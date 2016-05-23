/*
 * Copyright (c) AllSeen Alliance. All rights reserved.
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
import org.allseen.lsf.sdk.factory.SceneV1Factory;
import org.allseen.lsf.sdk.listener.SceneCollectionListener;
import org.allseen.lsf.sdk.model.LightingItemFilter;
import org.allseen.lsf.sdk.model.SceneDataModel;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class SceneCollectionManagerV1<SCENEV1, ERROR> extends SceneCollectionManager<SCENEV1, SceneDataModel, ERROR> { //LightingItemCollectionManager<SCENEV1, SceneCollectionListener<? super SCENEV1, ? super ERROR>, SceneDataModel, ERROR> {

    protected final SceneV1Factory<SCENEV1, ERROR> factory;

    public SceneCollectionManagerV1(LightingSystemManager<?, ?, ?, ?, ?, ?, SCENEV1, ?, ?, ?, ?> manager, SceneV1Factory<SCENEV1, ERROR> factory) {
        super(manager, factory);

        this.factory = factory;
    }

    @Override
    public SCENEV1 addScene(String sceneID) {
        return addScene(sceneID, factory.createSceneV1(sceneID));
    }

    public SCENEV1 addScene(String sceneID, SCENEV1 scene) {
        return itemAdapters.put(sceneID, scene);
    }

    public SCENEV1 getScene(String sceneID) {
        return getAdapter(sceneID);
    }

    public SCENEV1[] getScenes() {
        return getAdapters().toArray(factory.createScenesV1(size()));
    }

    public SCENEV1[] getScenes(LightingItemFilter<SCENEV1> filter) {
        Collection<SCENEV1> filteredScenes = getScenesCollection(filter);
        return filteredScenes.toArray(factory.createScenesV1(filteredScenes.size()));
    }

    public Collection<SCENEV1> getScenesCollection(LightingItemFilter<SCENEV1> filter) {
        return getAdapters(filter);
    }

    public Iterator<SCENEV1> getSceneIterator() {
        return getAdapters().iterator();
    }

    public Collection<SCENEV1> removeScenes() {
        return removeAllAdapters();
    }

    @Override
    public SCENEV1 removeScene(String sceneID) {
        return removeAdapter(sceneID);
    }

    @Override
    protected void sendInitializedEvent(SceneCollectionListener<? super SCENEV1, ? super ERROR> listener, SCENEV1 scene, TrackingID trackingID) {
        listener.onSceneInitialized(trackingID, scene);
    }

    @Override
    protected void sendChangedEvent(SceneCollectionListener<? super SCENEV1, ? super ERROR> listener, SCENEV1 scene) {
        listener.onSceneChanged(scene);
    }

    @Override
    protected void sendRemovedEvent(SceneCollectionListener<? super SCENEV1, ? super ERROR> listener, SCENEV1 scene) {
        listener.onSceneRemoved(scene);
    }

    @Override
    protected void sendErrorEvent(SceneCollectionListener<? super SCENEV1, ? super ERROR> listener, ERROR error) {
        listener.onSceneError(error);
    }

    @Override
    public SceneDataModel getModel(String sceneID) {
        return getModel(getAdapter(sceneID));
    }

    @Override
    public SceneDataModel getModel(SCENEV1 scene) {
        return scene != null ? factory.findSceneDataModelV1(scene) : null;
    }
}
