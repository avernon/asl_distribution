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

public class MasterSceneManagerCallback extends DefaultNativeClassWrapper {

    public MasterSceneManagerCallback() {
        createNativeObject();
    }


    public void getAllMasterSceneIDsReplyCB(ResponseCode responseCode, String[] masterSceneIDs)                                         { }
    public void getMasterSceneNameReplyCB(ResponseCode responseCode, String masterSceneID, String language, String masterSceneName)     { }
    public void setMasterSceneNameReplyCB(ResponseCode responseCode, String masterSceneID, String language)                             { }
    public void masterScenesNameChangedCB(String[] masterSceneIDs)                                                                      { }
    public void createMasterSceneReplyCB(ResponseCode responseCode, String masterSceneID)                                               { }
    public void masterScenesCreatedCB(String[] masterSceneIDs)                                                                          { }
    public void getMasterSceneReplyCB(ResponseCode responseCode, String masterSceneID, MasterScene masterScene)                         { }
    public void deleteMasterSceneReplyCB(ResponseCode responseCode, String masterSceneID)                                               { }
    public void masterScenesDeletedCB(String[] masterSceneIDs)                                                                          { }
    public void updateMasterSceneReplyCB(ResponseCode responseCode, String masterSceneID)                                               { }
    public void masterScenesUpdatedCB(String[] masterSceneIDs)                                                                          { }
    public void applyMasterSceneReplyCB(ResponseCode responseCode, String masterSceneID)                                                { }
    public void masterScenesAppliedCB(String[] masterSceneIDs)                                                                          { }
    public void createMasterSceneWithTrackingReplyCB(ResponseCode responseCode, String masterSceneID, long trackingID)                  { }

    // @Override
    @Override
    protected native void createNativeObject();

    // @Override
    @Override
    protected native void destroyNativeObject();
}
