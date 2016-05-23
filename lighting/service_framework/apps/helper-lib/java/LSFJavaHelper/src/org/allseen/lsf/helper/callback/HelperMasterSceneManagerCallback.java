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
package org.allseen.lsf.helper.callback;

import org.allseen.lsf.MasterScene;
import org.allseen.lsf.MasterSceneManagerCallback;
import org.allseen.lsf.ResponseCode;
import org.allseen.lsf.helper.manager.AllJoynManager;
import org.allseen.lsf.helper.manager.LightingSystemManager;
import org.allseen.lsf.helper.model.MasterSceneDataModel;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class HelperMasterSceneManagerCallback extends MasterSceneManagerCallback {
    protected LightingSystemManager director;

    public HelperMasterSceneManagerCallback(LightingSystemManager director) {
        super();

        this.director = director;
    }

    @Override
    public void getAllMasterSceneIDsReplyCB(ResponseCode responseCode, String[] masterSceneIDs) {
        if (!responseCode.equals(ResponseCode.OK)) {
            director.getMasterSceneCollectionManager().sendErrorEvent("getAllMasterSceneIDsReplyCB", responseCode);
        }

        for (final String masterSceneID : masterSceneIDs) {
            postProcessMasterSceneID(masterSceneID);
        }
    }

    @Override
    public void getMasterSceneNameReplyCB(ResponseCode responseCode, String masterSceneID, String language, String masterSceneName) {
        if (!responseCode.equals(ResponseCode.OK)) {
            director.getMasterSceneCollectionManager().sendErrorEvent("getMasterSceneNameReplyCB", responseCode, masterSceneID);
        }

        postUpdateMasterSceneName(masterSceneID, masterSceneName);
    }

    @Override
    public void setMasterSceneNameReplyCB(ResponseCode responseCode, String masterSceneID, String language) {
        if (!responseCode.equals(ResponseCode.OK)) {
            director.getMasterSceneCollectionManager().sendErrorEvent("setMasterSceneNameReplyCB", responseCode, masterSceneID);
        }

        AllJoynManager.masterSceneManager.getMasterSceneName(masterSceneID, LightingSystemManager.LANGUAGE);
    }

    @Override
    public void masterScenesNameChangedCB(final String[] masterSceneIDs) {
        director.getHandler().post(new Runnable() {
            @Override
            public void run() {
                boolean containsNewIDs = false;

                for (final String masterSceneID : masterSceneIDs) {
                    if (director.getMasterSceneCollectionManager().hasID(masterSceneID)) {
                        AllJoynManager.masterSceneManager.getMasterSceneName(masterSceneID, LightingSystemManager.LANGUAGE);
                    } else {
                        containsNewIDs = true;
                    }
                }

                if (containsNewIDs) {
                    AllJoynManager.masterSceneManager.getAllMasterSceneIDs();
                }
            }
        });
    }

    @Override
    public void createMasterSceneReplyCB(ResponseCode responseCode, String masterSceneID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            director.getMasterSceneCollectionManager().sendErrorEvent("createMasterSceneReplyCB", responseCode, masterSceneID);
        }

        postProcessMasterSceneID(masterSceneID);
    }

    @Override
    public void masterScenesCreatedCB(String[] masterSceneIDs) {
        AllJoynManager.masterSceneManager.getAllMasterSceneIDs();
    }

    @Override
    public void updateMasterSceneReplyCB(ResponseCode responseCode, String masterSceneID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            director.getMasterSceneCollectionManager().sendErrorEvent("updateMasterSceneReplyCB", responseCode, masterSceneID);
        }
    }

    @Override
    public void masterScenesUpdatedCB(String[] masterSceneIDs) {
        for (String masterSceneID : masterSceneIDs) {
            AllJoynManager.masterSceneManager.getMasterScene(masterSceneID);
        }
    }

    @Override
    public void deleteMasterSceneReplyCB(ResponseCode responseCode, String masterSceneID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            director.getMasterSceneCollectionManager().sendErrorEvent("deleteMasterSceneReplyCB", responseCode, masterSceneID);
        }
    }

    @Override
    public void masterScenesDeletedCB(String[] masterSceneIDs) {
        postDeleteMasterScenes(masterSceneIDs);
    }

    @Override
    public void getMasterSceneReplyCB(ResponseCode responseCode, String masterSceneID, MasterScene masterScene) {
        if (!responseCode.equals(ResponseCode.OK)) {
            director.getMasterSceneCollectionManager().sendErrorEvent("getMasterSceneReplyCB", responseCode, masterSceneID);
        }

        postUpdateMasterScene(masterSceneID, masterScene);
    }

    @Override
    public void applyMasterSceneReplyCB(ResponseCode responseCode, String masterSceneID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            director.getMasterSceneCollectionManager().sendErrorEvent("applyMasterSceneReplyCB", responseCode, masterSceneID);
        }

        //TODO-CHK Do we need to do anything here?
    }

    @Override
    public void masterScenesAppliedCB(String[] masterSceneIDs) {
        //TODO-CHK Do we need to do anything here?
    }

    protected void postProcessMasterSceneID(final String masterSceneID) {
        director.getHandler().post(new Runnable() {
            @Override
            public void run() {
                if (!director.getMasterSceneCollectionManager().hasID(masterSceneID)) {
                    postUpdateMasterSceneID(masterSceneID);
                    AllJoynManager.masterSceneManager.getMasterSceneName(masterSceneID, LightingSystemManager.LANGUAGE);
                    AllJoynManager.masterSceneManager.getMasterScene(masterSceneID);
                }
            }
        });
    }

    protected void postUpdateMasterSceneID(final String masterSceneID) {
        director.getHandler().post(new Runnable() {
            @Override
            public void run() {
                if (!director.getMasterSceneCollectionManager().hasID(masterSceneID)) {
                    director.getMasterSceneCollectionManager().addMasterScene(masterSceneID);
                }
            }
        });

        postSendMasterSceneChanged(masterSceneID);
    }

    protected void postUpdateMasterScene(final String masterSceneID, final MasterScene masterScene) {
        director.getHandler().post(new Runnable() {
            @Override
            public void run() {
                MasterSceneDataModel masterSceneModel = director.getMasterSceneCollectionManager().getModel(masterSceneID);

                if (masterSceneModel != null) {
                    masterSceneModel.masterScene = masterScene;
                }
            }
        });

        postSendMasterSceneChanged(masterSceneID);
    }

    protected void postUpdateMasterSceneName(final String masterSceneID, final String masterSceneName) {
        director.getHandler().post(new Runnable() {
            @Override
            public void run() {
                MasterSceneDataModel masterSceneModel = director.getMasterSceneCollectionManager().getModel(masterSceneID);

                if (masterSceneModel != null) {
                    masterSceneModel.setName(masterSceneName);
                }
            }
        });

        postSendMasterSceneChanged(masterSceneID);
    }

    protected void postDeleteMasterScenes(final String[] masterSceneIDs) {
        director.getHandler().post(new Runnable() {
            @Override
            public void run() {
                for (String masterSceneID : masterSceneIDs) {
                    director.getMasterSceneCollectionManager().removeMasterScene(masterSceneID);
                }
            }
        });
    }

    protected void postSendMasterSceneChanged(final String masterSceneID) {
        director.getHandler().post(new Runnable() {
            @Override
            public void run() {
                director.getMasterSceneCollectionManager().sendChangedEvent(masterSceneID);
            }
        });
    }
}
