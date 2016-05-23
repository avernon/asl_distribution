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
package org.allseen.lsf;

import org.allseen.lsf.sdk.ControllerClientStatus;
import org.allseen.lsf.sdk.TrackingID;

public class SceneElementManager extends BaseNativeClassWrapper {
    public static final int MAX_SCENE_ELEMENTS = 100;

    public SceneElementManager(ControllerClient controller, SceneElementManagerCallback callback) {
        createNativeObject(controller, callback);
    }

    public native ControllerClientStatus getAllSceneElementIDs();
    public native ControllerClientStatus getSceneElementName(String sceneElementID, String language);
    public native ControllerClientStatus setSceneElementName(String sceneElementID, String sceneElementName, String language);
    public native ControllerClientStatus createSceneElement(TrackingID trackingID, SceneElement sceneElement, String sceneElementName, String language);
    public native ControllerClientStatus updateSceneElement(String sceneElementID, SceneElement sceneElement);
    public native ControllerClientStatus deleteSceneElement(String sceneElementID);
    public native ControllerClientStatus getSceneElement(String sceneElementID);
    public native ControllerClientStatus applySceneElement(String sceneElementID);
    public native ControllerClientStatus getSceneElementDataSet(String sceneElementID, String language);

    protected native void createNativeObject(ControllerClient controller, SceneElementManagerCallback callback);

    @Override
    protected native void destroyNativeObject();
}
