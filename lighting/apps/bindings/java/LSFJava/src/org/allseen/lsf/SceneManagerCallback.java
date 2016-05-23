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

import org.allseen.lsf.sdk.ResponseCode;

public class SceneManagerCallback extends DefaultNativeClassWrapper {

    public SceneManagerCallback() {
        createNativeObject();
    }

    public void getAllSceneIDsReplyCB(ResponseCode responseCode, String[] sceneIDs)                                         { }
    public void getSceneNameReplyCB(ResponseCode responseCode, String sceneID, String language, String sceneName)           { }
    public void setSceneNameReplyCB(ResponseCode responseCode, String sceneID, String language)                             { }
    public void scenesNameChangedCB(String[] sceneIDs)                                                                      { }
    public void createSceneReplyCB(ResponseCode responseCode, String sceneID)                                               { }
    public void scenesCreatedCB(String[] sceneIDs)                                                                          { }
    public void updateSceneReplyCB(ResponseCode responseCode, String sceneID)                                               { }
    public void scenesUpdatedCB(String[] sceneIDs)                                                                          { }
    public void deleteSceneReplyCB(ResponseCode responseCode, String sceneID)                                               { }
    public void scenesDeletedCB(String[] sceneIDs)                                                                          { }
    public void getSceneReplyCB(ResponseCode responseCode, String sceneID, Scene scene)                                     { }
    public void applySceneReplyCB(ResponseCode responseCode, String sceneID)                                                { }
    public void scenesAppliedCB(String[] sceneIDs)                                                                          { }
    public void createSceneWithTrackingReplyCB(ResponseCode responseCode, String sceneID, long trackingID)                  { }
    public void createSceneWithSceneElementsReplyCB(ResponseCode responseCode, String sceneID, long trackingID)             { }
    public void updateSceneWithSceneElementsReplyCB(ResponseCode responseCode, String sceneID)                              { }
    public void getSceneWithSceneElementsReplyCB(ResponseCode responseCode, String sceneID, SceneWithSceneElements scene)   { }

    // @Override
    @Override
    protected native void createNativeObject();

    // @Override
    @Override
    protected native void destroyNativeObject();
}
