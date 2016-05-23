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
package org.allseen.lsf.sampleapp;

import java.util.ArrayList;
import java.util.List;

import org.allseen.lsf.sdk.LightingDirector;
import org.allseen.lsf.sdk.SceneElement;
import org.allseen.lsf.sdk.SceneV2;

import android.util.Log;

public class PendingSceneV2 extends PendingLightingItem {
    public List<PendingSceneElementV2> deleted = new ArrayList<PendingSceneElementV2>();
    public List<PendingSceneElementV2> current = new ArrayList<PendingSceneElementV2>();

    public PendingSceneV2() {
        this.init((SceneV2)null);
    }

    public PendingSceneV2(SceneV2 scene) {
        super.init(scene);

        if (scene != null) {
            LightingDirector director = LightingDirector.get();

            for (String sceneElementID : scene.getSceneElementIDs()) {
                SceneElement sceneElement = director.getSceneElement(sceneElementID);
                PendingSceneElementV2 pendingSceneElement = new PendingSceneElementV2(sceneElement);

                current.add(pendingSceneElement);
            }
        }
    }

    public boolean isAddMode() {
        return id == null || id.isEmpty();
    }

    public void doDeleteSceneElement(String sceneElementID) {
        int index = -1;

        for (int i = 0; index < 0 && i < current.size(); i++) {
            if (sceneElementID.equals(current.get(i).id)) {
                index = i;
            }
        }

        if (index >=0) {
            PendingSceneElementV2 deletedSceneElement = current.remove(index);

            if (!PendingSceneElementV2.isLocalID(sceneElementID)) {
                deleted.add(deletedSceneElement);
            }
        } else {
            Log.w(SampleAppActivity.TAG, "Could not delete scene element ID " + sceneElementID);
        }
    }
}
