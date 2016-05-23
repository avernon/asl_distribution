/* Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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
package org.allseen.lsf.helper.facade;

import org.allseen.lsf.helper.manager.AllJoynManager;
import org.allseen.lsf.helper.model.LightingItemDataModel;
import org.allseen.lsf.helper.model.SceneDataModel;

/**
 * A Scene object represents a set of lamps and associated states in a lighting system, and can be
 * used to apply the states to the lamps.
 */
public final class Scene extends LightingItem {

    protected SceneDataModel sceneModel;

    /**
     * Constructs a Scene using the specified ID.
     * <p>
     * <b>WARNING: This method is intended to be used internally. Client software should not instantiate
     * Scenes directly, but should instead get them from the {@link LightingDirector} using the
     * {@link LightingDirector#getScenes()} method.</b>
     *
     * @param sceneID The ID of the scene
     */
    public Scene(String sceneID) {
        super();

        sceneModel = new SceneDataModel(sceneID);
    }

    /**
     * Sends a command to apply this Scene, which sets the appropriate state for all
     * constituent lamps.
     */
    public void apply() {
        AllJoynManager.sceneManager.applyScene(sceneModel.id);
    }

    @Override
    protected LightingItemDataModel getItemDataModel() {
        return getSceneDataModel();
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    public SceneDataModel getSceneDataModel() {
        return sceneModel;
    }
}
