/*
 * Copyright AllSeen Alliance. All rights reserved.
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
import org.allseen.lsf.sdk.factory.SceneElementFactory;
import org.allseen.lsf.sdk.listener.SceneElementCollectionListener;
import org.allseen.lsf.sdk.model.LightingItemFilter;
import org.allseen.lsf.sdk.model.SceneElementDataModelV2;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class SceneElementCollectionManager<SCENEELEMENT, ERROR> extends LightingItemCollectionManager<SCENEELEMENT, SceneElementCollectionListener<? super SCENEELEMENT, ? super ERROR>, SceneElementDataModelV2, ERROR> {

    protected final SceneElementFactory<SCENEELEMENT, ERROR> factory;

    public SceneElementCollectionManager(LightingSystemManager<?, ?, ?, ?, ?, SCENEELEMENT, ?, ?, ?, ?, ?> manager, SceneElementFactory<SCENEELEMENT, ERROR> factory) {
        super(manager, factory);

        this.factory = factory;
    }

    public SCENEELEMENT addSceneElement(String sceneElementID) {
        return addSceneElement(sceneElementID, factory.createSceneElement(sceneElementID));
    }

    public SCENEELEMENT addSceneElement(String sceneElementID, SCENEELEMENT sceneElement) {
        return itemAdapters.put(sceneElementID, sceneElement);
    }

    public SCENEELEMENT getSceneElement(String sceneElementID) {
        return getAdapter(sceneElementID);
    }

    public SCENEELEMENT[] getSceneElements() {
        return getAdapters().toArray(factory.createSceneElements(size()));
    }

    public SCENEELEMENT[] getSceneElements(LightingItemFilter<SCENEELEMENT> filter) {
        Collection<SCENEELEMENT> filteredSceneElements = getSceneElementsCollection(filter);
        return filteredSceneElements.toArray(factory.createSceneElements(filteredSceneElements.size()));
    }

    public Collection<SCENEELEMENT> getSceneElementsCollection(LightingItemFilter<SCENEELEMENT> filter) {
        return getAdapters(filter);
    }

    public Iterator<SCENEELEMENT> getSceneElementIterator() {
        return getAdapters().iterator();
    }

    public Collection<SCENEELEMENT> removeSceneElements() {
        return removeAllAdapters();
    }

    public SCENEELEMENT removeSceneElement(String sceneElementId) {
        return removeAdapter(sceneElementId);
    }

    @Override
    protected void sendInitializedEvent(SceneElementCollectionListener<? super SCENEELEMENT, ? super ERROR> listener, SCENEELEMENT sceneElement, TrackingID trackingID) {
        listener.onSceneElementInitialized(trackingID, sceneElement);
    }

    @Override
    protected void sendChangedEvent(SceneElementCollectionListener<? super SCENEELEMENT, ? super ERROR> listener, SCENEELEMENT sceneElement) {
        listener.onSceneElementChanged(sceneElement);
    }

    @Override
    protected void sendRemovedEvent(SceneElementCollectionListener<? super SCENEELEMENT, ? super ERROR> listener, SCENEELEMENT sceneElement) {
        listener.onSceneElementRemoved(sceneElement);
    }

    @Override
    protected void sendErrorEvent(SceneElementCollectionListener<? super SCENEELEMENT, ? super ERROR> listener, ERROR error) {
        listener.onSceneElementError(error);
    }

    @Override
    public SceneElementDataModelV2 getModel(String sceneElementId) {
        return getModel(getAdapter(sceneElementId));
    }

    @Override
    public SceneElementDataModelV2 getModel(SCENEELEMENT sceneElement) {
        return sceneElement != null ? factory.findSceneElementDataModel(sceneElement) : null;
    }
}
