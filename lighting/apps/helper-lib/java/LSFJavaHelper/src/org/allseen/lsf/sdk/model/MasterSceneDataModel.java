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
package org.allseen.lsf.sdk.model;

import org.allseen.lsf.MasterScene;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class MasterSceneDataModel extends LightingItemDataModel {
    public static final char TAG_PREFIX_MASTER_SCENE = 'S';

    public static String defaultName = "<Loading master scene info...>";

    protected boolean masterSceneInitialized;

    public MasterScene masterScene;

    public MasterSceneDataModel() {
        this(null, null);
    }

    public MasterSceneDataModel(String masterSceneID) {
        this(masterSceneID, null);
    }

    public MasterSceneDataModel(String masterSceneID, String masterSceneName) {
        super(masterSceneID, TAG_PREFIX_MASTER_SCENE, masterSceneName != null ? masterSceneName : defaultName);

        masterScene = new MasterScene();
        masterSceneInitialized = false;
    }

    public MasterSceneDataModel(MasterSceneDataModel other) {
        super(other);

        this.masterScene = new MasterScene(other.masterScene);
        this.masterSceneInitialized = other.masterSceneInitialized;
    }

    public MasterScene getMasterScene() {
        return masterScene;
    }

    public void setMasterScene(MasterScene masterScene) {
        this.masterScene = masterScene;
        masterSceneInitialized = true;
    }

    public boolean containsBasicScene(String basicSceneID) {
        String[] childIDs = masterScene.getScenes();

        for (String childID : childIDs) {
            if (childID.equals(basicSceneID)) {
                return true;
            }
        }

        return false;
    }

    @Override
    public boolean isInitialized() {
        return super.isInitialized() && masterSceneInitialized;
    }
}
