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

import org.allseen.lsf.helper.facade.MasterScene;
import org.allseen.lsf.helper.listener.LightingItemErrorEvent;
import org.allseen.lsf.helper.listener.MasterSceneCollectionListener;
import org.allseen.lsf.helper.model.MasterSceneDataModel;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class MasterSceneCollectionManager extends LightingItemCollectionManager<MasterScene, MasterSceneCollectionListener, MasterSceneDataModel> {

    public MasterSceneCollectionManager(LightingSystemManager director) {
        super(director);
    }

    public MasterScene addMasterScene(String masterSceneID) {
        return addMasterScene(masterSceneID, new MasterScene(masterSceneID));
    }

    public MasterScene addMasterScene(String masterSceneID, MasterScene scene) {
        return itemAdapters.put(masterSceneID, scene);
    }

    public MasterScene getMasterScene(String masterSceneID) {
        return getAdapter(masterSceneID);
    }

    public MasterScene[] getMasterScenes() {
        return getAdapters().toArray(new MasterScene[size()]);
    }

    public Iterator<MasterScene> getMasterSceneIterator() {
        return getAdapters().iterator();
    }

    public MasterScene removeMasterScene(String masterSceneID) {
        return removeAdapter(masterSceneID);
    }

    @Override
    protected void sendChangedEvent(MasterSceneCollectionListener listener, Iterator<MasterScene> masterScenes, int count) {
        listener.onMasterScenesChanged(masterScenes, count);
    }

    @Override
    protected void sendRemovedEvent(MasterSceneCollectionListener listener, Iterator<MasterScene> masterScenes, int count) {
        listener.onMasterScenesRemoved(masterScenes, count);
    }

    @Override
    protected void sendErrorEvent(MasterSceneCollectionListener listener, LightingItemErrorEvent errorEvent) {
        listener.onMasterSceneError(errorEvent);
    }

    @Override
    public MasterSceneDataModel getModel(String masterSceneID) {
        MasterScene scene = getAdapter(masterSceneID);

        return scene != null ? scene.getMasterSceneDataModel() : null;
    }
}
