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
package org.allseen.lsf.sdk.model;

import org.allseen.lsf.SceneWithSceneElements;

public class SceneDataModelV2 extends LightingItemDataModel {
    public static final char TAG_PREFIX_SCENE_WITH_ELEMENTS = 'S';

    public static String defaultName = "<Loading scene info ...>";

    private SceneWithSceneElements sceneWithSceneElements;

    protected boolean sceneWithSceneElementsInitialized;

    public SceneDataModelV2() {
        this((String)null);
    }

    public SceneDataModelV2(String sceneID) {
        this(sceneID, null);
    }

    public SceneDataModelV2(String sceneID, String sceneName) {
        super(sceneID, TAG_PREFIX_SCENE_WITH_ELEMENTS, sceneName != null ? sceneName : defaultName);

        sceneWithSceneElements = null;
        sceneWithSceneElementsInitialized = false;
    }

    public SceneDataModelV2(SceneDataModelV2 other) {
        super(other);

        sceneWithSceneElements = other.sceneWithSceneElements;

        sceneWithSceneElementsInitialized = other.sceneWithSceneElementsInitialized;
    }

    public String[] getSceneElementIDs() {
        return sceneWithSceneElements != null ? sceneWithSceneElements.getSceneElements() : LightingItemUtil.NO_ITEM_IDS;
    }

    public SceneWithSceneElements getSceneWithSceneElements() {
        return sceneWithSceneElements;
    }

    public void setSceneWithSceneElements(SceneWithSceneElements scene) {
        sceneWithSceneElements = scene;
        sceneWithSceneElementsInitialized = true;
    }

    public boolean containsSceneElement(String sceneElementID) {
        String[] childIDs = sceneWithSceneElements.getSceneElements();

        for (String childID : childIDs) {
            if (childID.equals(sceneElementID)) {
                return true;
            }
        }

        return false;
    }

    @Override
    public boolean isInitialized() {
        return super.isInitialized() && sceneWithSceneElementsInitialized;
    }
}
