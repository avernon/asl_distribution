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

import org.allseen.lsf.helper.facade.Scene;
import org.allseen.lsf.helper.listener.LightingItemErrorEvent;
import org.allseen.lsf.helper.listener.SceneCollectionListener;
import org.allseen.lsf.helper.model.SceneDataModel;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class SceneCollectionManager extends LightingItemCollectionManager<Scene, SceneCollectionListener, SceneDataModel> {

    public SceneCollectionManager(LightingSystemManager director) {
        super(director);
    }

    public Scene addScene(String sceneID) {
        return addScene(sceneID, new Scene(sceneID));
    }

    public Scene addScene(String sceneID, Scene scene) {
        return itemAdapters.put(sceneID, scene);
    }

    public Scene getScene(String sceneID) {
        return getAdapter(sceneID);
    }

    public Scene[] getScenes() {
        return getAdapters().toArray(new Scene[size()]);
    }

    public Iterator<Scene> getPresetIterator() {
        return getAdapters().iterator();
    }

    public Scene removeScene(String sceneID) {
        return removeAdapter(sceneID);
    }

    @Override
    protected void sendChangedEvent(SceneCollectionListener listener, Iterator<Scene> scenes, int count) {
        listener.onScenesChanged(scenes, count);
    }

    @Override
    protected void sendRemovedEvent(SceneCollectionListener listener, Iterator<Scene> scenes, int count) {
        listener.onScenesRemoved(scenes, count);
    }

    @Override
    protected void sendErrorEvent(SceneCollectionListener listener, LightingItemErrorEvent errorEvent) {
        listener.onSceneError(errorEvent);
    }

    @Override
    public SceneDataModel getModel(String sceneID) {
        Scene scene = getAdapter(sceneID);

        return scene != null ? scene.getSceneDataModel() : null;
    }
}
