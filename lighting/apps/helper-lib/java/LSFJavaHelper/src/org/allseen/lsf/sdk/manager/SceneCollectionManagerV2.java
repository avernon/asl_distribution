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
import org.allseen.lsf.sdk.factory.SceneV2Factory;
import org.allseen.lsf.sdk.listener.SceneCollectionListener;
import org.allseen.lsf.sdk.model.LightingItemFilter;
import org.allseen.lsf.sdk.model.SceneDataModelV2;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class SceneCollectionManagerV2<SCENEV2, ERROR> extends SceneCollectionManager<SCENEV2, SceneDataModelV2, ERROR> { //extends LightingItemCollectionManager<SCENEV2, SceneCollectionListener<? super SCENEV2, ? super ERROR>, SceneDataModelV2, ERROR> {

    protected final SceneV2Factory<SCENEV2, ERROR> factory;

    public SceneCollectionManagerV2(LightingSystemManager<?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?> manager, SceneV2Factory<SCENEV2, ERROR> factory) {
        super(manager, factory);

        this.factory = factory;
    }

    @Override
    public SCENEV2 addScene(String sceneID) {
        return addScene(sceneID, factory.createSceneV2(sceneID));
    }

    public SCENEV2 addScene(String sceneID, SCENEV2 scene) {
        return itemAdapters.put(sceneID, scene);
    }

    public SCENEV2 getScene(String sceneID) {
        return getAdapter(sceneID);
    }

    public SCENEV2[] getScenes() {
        return getAdapters().toArray(factory.createScenesV2(size()));
    }

    public SCENEV2[] getScenes(LightingItemFilter<SCENEV2> filter) {
        Collection<SCENEV2> filteredScenes = getScenesCollection(filter);
        return filteredScenes.toArray(factory.createScenesV2(filteredScenes.size()));
    }

    public Collection<SCENEV2> getScenesCollection(LightingItemFilter<SCENEV2> filter) {
        return getAdapters(filter);
    }

    public Iterator<SCENEV2> getSceneIterator() {
        return getAdapters().iterator();
    }

    public Collection<SCENEV2> removeScenes() {
        return removeAllAdapters();
    }

    @Override
    public SCENEV2 removeScene(String sceneID) {
        return removeAdapter(sceneID);
    }

    @Override
    protected void sendInitializedEvent(SceneCollectionListener<? super SCENEV2, ? super ERROR> listener, SCENEV2 scene, TrackingID trackingID) {
        listener.onSceneInitialized(trackingID, scene);
    }

    @Override
    protected void sendChangedEvent(SceneCollectionListener<? super SCENEV2, ? super ERROR> listener, SCENEV2 scene) {
        listener.onSceneChanged(scene);
    }

    @Override
    protected void sendRemovedEvent(SceneCollectionListener<? super SCENEV2, ? super ERROR> listener, SCENEV2 scene) {
        listener.onSceneRemoved(scene);
    }

    @Override
    protected void sendErrorEvent(SceneCollectionListener<? super SCENEV2, ? super ERROR> listener, ERROR error) {
        listener.onSceneError(error);
    }

    @Override
    public SceneDataModelV2 getModel(String sceneID) {
        return getModel(getAdapter(sceneID));
    }

    @Override
    public SceneDataModelV2 getModel(SCENEV2 scene) {
        return scene != null ? factory.findSceneDataModelV2(scene) : null;
    }
}
