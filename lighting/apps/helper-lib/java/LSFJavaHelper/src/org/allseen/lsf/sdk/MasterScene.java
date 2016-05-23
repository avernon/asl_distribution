/* Copyright (c) AllSeen Alliance. All rights reserved.
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

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

import org.allseen.lsf.sdk.manager.AllJoynManager;
import org.allseen.lsf.sdk.model.LightingItemDataModel;
import org.allseen.lsf.sdk.model.LightingItemUtil;
import org.allseen.lsf.sdk.model.MasterSceneDataModel;

/**
 * This class represents a MasterScene definition in the lighting controller. This class
 * provides an interface to perform MasterScene operations. Supported operations include
 * adding and removing scene members, renaming, applying and deleting the MasterScene.
 * Master scenes contain an array of scenes and allow them to be applied simultaneously.
 * Master scenes are considered fully initialized when the name and array of scenes have
 * been received. Master scenes are still operational and can still be applied even in the
 * uninitialized state.
 * <p>
 * <b>Note: This class is not meant to be instantiated directly. MasterScenes should be retrieved
 * from the LightingDirector using the {@link LightingDirector#getMasterScenes()} method.</b>
 * <p>
 * <b>Note: This class does not support MasterScene creation. See {@link LightingDirector#createMasterScene(Scene[], String)}.</b>
 */
public class MasterScene extends SceneItem {
    /**
     * Specifies the default name of the MasterScene.
     *
     * @param defaultName Default name of the MasterScene
     */
    public static void setDefaultName(String defaultName) {
        if (defaultName != null) {
            MasterSceneDataModel.defaultName = defaultName;
        }
    }

    protected MasterSceneDataModel masterModel;

    /**
     * Constructs a MasterScene using the specified ID.
     * <p>
     * <b>WARNING: This method is intended to be used internally. Client software should not instantiate
     * MasterScenes directly, but should instead get them from the {@link LightingDirector} using the
     * {@link LightingDirector#getMasterScenes()} method.</b>
     *
     * @param masterSceneID The ID of the master scene
     */
    protected MasterScene(String masterSceneID) {
        super();

        masterModel = new MasterSceneDataModel(masterSceneID);
    }

    /**
     * Applies the current Master Scene in the Lighting System.
     */
    @Override
    public void apply() {
        String errorContext = "MasterScene.apply() error";

        postErrorIfFailure(errorContext,
                AllJoynManager.masterSceneManager.applyMasterScene(masterModel.id));
    }

    /**
     * Modifies the current MasterScene with the provided array of Scenes.
     *
     * @param scenes The array of new Scenes
     */
    public void modify(Scene[] scenes) {
        String errorContext = "MasterScene.modify() error";

        if (postInvalidArgIfNull(errorContext, scenes)) {
            String[] sceneIds = new String[scenes.length];
            for (int i = 0; i < scenes.length; i++) {
                sceneIds[i] = scenes[i].getId();
            }

            postErrorIfFailure(errorContext,
                    AllJoynManager.masterSceneManager.updateMasterScene(masterModel.id, LightingItemUtil.createMasterScene(sceneIds)));
        }
    }

    /**
     * Adds a scene to the current MasterScene.
     *
     * @param scene The Scene to be added
     */
    public void add(Scene scene) {
        String errorContext = "MasterScene.add() error";

        if (postInvalidArgIfNull(errorContext, scene)) {
            Set<String> sceneIds = new HashSet<String>(Arrays.asList(masterModel.getMasterScene().getScenes()));
            // only update this master scene if it does not already contains the scene to add
            if (sceneIds.add(scene.getId())) {
                postErrorIfFailure(errorContext,
                        AllJoynManager.masterSceneManager.updateMasterScene(masterModel.id, LightingItemUtil.createMasterScene(
                                sceneIds.toArray(new String[sceneIds.size()]))));
            }
        }
    }

    /**
     * Removes a Scene from the current MasterScene
     *
     * @param scene The Scene to be removed
     */
    public void remove(Scene scene) {
        String errorContext = "MasterScene.remove() error";

        if (postInvalidArgIfNull(errorContext, scene)) {
            Set<String> sceneIds = new HashSet<String>(Arrays.asList(masterModel.getMasterScene().getScenes()));
            // only update this master scene if it contains the scene to remove
            if (sceneIds.remove(scene.getId())) {
                postErrorIfFailure(errorContext,
                        AllJoynManager.masterSceneManager.updateMasterScene(masterModel.id, LightingItemUtil.createMasterScene(
                                sceneIds.toArray(new String[sceneIds.size()]))));
            }
        }
    }

    /**
     * Permanently deletes the current MasterScene from the lighting controller.
     */
    @Override
    public void delete() {
        String errorContext = "MasterScene.delete() error";

        postErrorIfFailure(errorContext,
                AllJoynManager.masterSceneManager.deleteMasterScene(masterModel.id));
    }

    /**
     * Renames the current MasterScene using the provided name.
     *
     * @param masterSceneName The new name for the MasterScene
     */
    @Override
    public void rename(String masterSceneName) {
        String errorContext = "MasterScene.rename() error";

        if (postInvalidArgIfNull(errorContext, masterSceneName)) {
            postErrorIfFailure(errorContext,
                    AllJoynManager.masterSceneManager.setMasterSceneName(masterModel.id, masterSceneName, LightingDirector.get().getDefaultLanguage()));
        }
    }

    /**
     * Returns all the scene IDs associated with the MasterScene.
     *
     * @return Array of scene IDs of the Scenes in the Master Scene
     */
    public String[] getSceneIDs() {
        return masterModel.getMasterScene().getScenes();
    }

    /**
     * Returns all the Scenes associated with the MasterScene.
     *
     * @return Array of Scenes in the Master Scene
     */
    public Scene[] getScenes() {
        //TODO-CHK Do we need to insert null "placeholders"?
        return LightingDirector.get().getScenes(Arrays.asList(getSceneIDs()));
    }

    /**
     * Tests to see if the current MasterScene contains the provided Lighting item.
     *
     * @param item Lighting item to be confirmed present in the MasterScene
     *
     * @return Returns true if the MasterScene contains Lighting item, false otherwise
     */
    @Override
    public boolean hasComponent(LightingItem item) {
        String errorContext = "MasterScene.hasComponent() error";
        return postInvalidArgIfNull(errorContext, item) ? hasScene(item.getId()) : false;
    }

    /**
     * Tests to see if the current MasterScene contains the provided Scene.
     *
     * @param scene Scene to be confirmed present in the MasterScene
     *
     * @return Returns true if the MasterScene contains Scene, false otherwise
     */
    public boolean hasScene(Scene scene) {
        String errorContext = "MasterScene.hasScene() error";
        return postInvalidArgIfNull(errorContext, scene) ? hasScene(scene.getId()) : false;
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    protected boolean hasScene(String sceneID) {
        return masterModel.containsBasicScene(sceneID);
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    @Override
    protected LightingItemDataModel getItemDataModel() {
        return getMasterSceneDataModel();
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    protected MasterSceneDataModel getMasterSceneDataModel() {
        return masterModel;
    }

    /**
     * <b>WARNING: This method is not intended to be used by clients, and may change or be
     * removed in subsequent releases of the SDK.</b>
     */
    @Override
    protected void postError(final String name, final ResponseCode status) {
        LightingDirector.get().getLightingSystemManager().getQueue().post(new Runnable() {
            @Override
            public void run() {
                LightingDirector.get().getMasterSceneCollectionManager().sendErrorEvent(name, status, getId());
            }
        });
    }
}
