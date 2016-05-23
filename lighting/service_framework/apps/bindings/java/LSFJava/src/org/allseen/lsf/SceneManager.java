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
package org.allseen.lsf;

public class SceneManager extends BaseNativeClassWrapper {
    public SceneManager(ControllerClient controller, SceneManagerCallback callback) {
         createNativeObject(controller, callback);
    }

    public native ControllerClientStatus getAllSceneIDs();
    public native ControllerClientStatus getSceneName(String sceneID, String language);
    public native ControllerClientStatus setSceneName(String sceneID, String sceneName, String language);
    public native ControllerClientStatus createScene(Scene scene, String sceneName, String language);
    public native ControllerClientStatus updateScene(String sceneID, Scene scene);
    public native ControllerClientStatus deleteScene(String sceneID);
    public native ControllerClientStatus getScene(String sceneID);
    public native ControllerClientStatus applyScene(String sceneID);

    protected native void createNativeObject(ControllerClient controller, SceneManagerCallback callback);

    @Override
    protected native void destroyNativeObject();
}
