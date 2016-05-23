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

import org.allseen.lsf.sdk.ResponseCode;

public class SceneElementManagerCallback extends DefaultNativeClassWrapper {

    public SceneElementManagerCallback() {
        createNativeObject();
    }

    public void getAllSceneElementIDsReplyCB(ResponseCode responseCode, String[] sceneElementIDs)                                       { }
    public void getSceneElementNameReplyCB(ResponseCode responseCode, String sceneElementID, String language, String sceneElementName)  { }
    public void setSceneElementNameReplyCB(ResponseCode responseCode, String sceneElementID, String language)                           { }
    public void sceneElementsNameChangedCB(String[] sceneElementIDs)                                                                    { }
    public void createSceneElementReplyCB(ResponseCode responseCode, String sceneElementID, long trackingID)                            { }
    public void sceneElementsCreatedCB(String[] sceneElementIDs)                                                                        { }
    public void updateSceneElementReplyCB(ResponseCode responseCode, String sceneElementID)                                             { }
    public void sceneElementsUpdatedCB(String[] sceneElementIDs)                                                                        { }
    public void deleteSceneElementReplyCB(ResponseCode responseCode, String sceneElementID)                                             { }
    public void sceneElementsDeletedCB(String[] sceneElementIDs)                                                                        { }
    public void getSceneElementReplyCB(ResponseCode responseCode, String sceneElementID, SceneElement sceneElement)                     { }
    public void applySceneElementReplyCB(ResponseCode responseCode, String sceneElementID)                                              { }
    public void sceneElementsAppliedCB(String[] sceneElementIDs)                                                                        { }

    @Override
    protected native void createNativeObject();

    @Override
    protected native void destroyNativeObject();
}
