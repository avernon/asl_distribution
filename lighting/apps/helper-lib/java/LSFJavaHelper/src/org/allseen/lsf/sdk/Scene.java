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
package org.allseen.lsf.sdk;

import java.util.ArrayList;
import java.util.Collection;

import org.allseen.lsf.sdk.manager.AllJoynManager;

/**
 * Abstract base class that represents generic Scene operations that can be performed. Generic scenes
 * can be applied, renamed, and deleted.
 */
public abstract class Scene extends SceneItem {

    /**
     * Applies the current Scene in the Lighting system.
     */
    @Override
    public void apply() {
        String errorContext = "Scene.apply() error";

        postErrorIfFailure(errorContext,
                AllJoynManager.sceneManager.applyScene(this.getId()));
    }

    /**
     * Renames the current Scene using the provided name.
     *
     * @param sceneName The new name for the Scene
     */
    @Override
    public void rename(String sceneName) {
        String errorContext = "Scene.rename() error";

        if (postInvalidArgIfNull(errorContext, sceneName)) {
            postErrorIfFailure(errorContext,
                    AllJoynManager.sceneManager.setSceneName(this.getId(), sceneName, LightingDirector.get().getDefaultLanguage()));
        }
    }

    /**
     * Permanently deletes the current Scene from the lighting controller.
     * <p>
     * <b>Note: You cannot delete a scene that is used by a master scene. The dependency
     * must be deleted first.</b>
     */
    @Override
    public void delete() {
        AllJoynManager.sceneManager.deleteScene(this.getId());
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    @Override
    protected Collection<LightingItem> getDependentCollection() {
        LightingDirector director = LightingDirector.get();
        Collection<LightingItem> dependents = new ArrayList<LightingItem>();

        dependents.addAll(director.getMasterSceneCollectionManager().getMasterScenesCollection(new HasComponentFilter<MasterScene>(Scene.this)));

        return dependents;
    }
}
