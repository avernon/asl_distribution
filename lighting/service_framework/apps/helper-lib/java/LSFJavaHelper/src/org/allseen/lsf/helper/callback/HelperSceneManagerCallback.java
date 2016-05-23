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

import org.allseen.lsf.ResponseCode;
import org.allseen.lsf.Scene;
import org.allseen.lsf.SceneManagerCallback;
import org.allseen.lsf.helper.manager.AllJoynManager;
import org.allseen.lsf.helper.manager.LightingSystemManager;
import org.allseen.lsf.helper.model.SceneDataModel;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class HelperSceneManagerCallback extends SceneManagerCallback {
    protected LightingSystemManager director;

    public HelperSceneManagerCallback(LightingSystemManager director) {
        super();

        this.director = director;
    }

    @Override
    public void getAllSceneIDsReplyCB(ResponseCode responseCode, String[] sceneIDs) {
        if (!responseCode.equals(ResponseCode.OK)) {
            director.getSceneCollectionManager().sendErrorEvent("getAllSceneIDsReplyCB", responseCode, null);
        }

        for (final String sceneID : sceneIDs) {
            postProcessSceneID(sceneID);
        }
    }

    @Override
    public void getSceneNameReplyCB(ResponseCode responseCode, String sceneID, String language, String sceneName) {
        if (!responseCode.equals(ResponseCode.OK)) {
            director.getSceneCollectionManager().sendErrorEvent("getSceneNameReplyCB", responseCode, sceneID);
        }

        postUpdateSceneName(sceneID, sceneName);
    }

    @Override
    public void setSceneNameReplyCB(ResponseCode responseCode, String sceneID, String language) {
        if (!responseCode.equals(ResponseCode.OK)) {
            director.getSceneCollectionManager().sendErrorEvent("setSceneNameReplyCB", responseCode, sceneID);
        }

        AllJoynManager.sceneManager.getSceneName(sceneID, LightingSystemManager.LANGUAGE);
    }

    @Override
    public void scenesNameChangedCB(final String[] sceneIDs) {
        director.getHandler().post(new Runnable() {
            @Override
            public void run() {
                boolean containsNewIDs = false;

                for (final String sceneID : sceneIDs) {
                    if (director.getSceneCollectionManager().hasID(sceneID)) {
                        AllJoynManager.sceneManager.getSceneName(sceneID, LightingSystemManager.LANGUAGE);
                    } else {
                        containsNewIDs = true;
                    }
                }

                if (containsNewIDs) {
                    AllJoynManager.sceneManager.getAllSceneIDs();
                }
            }
        });
    }

    @Override
    public void createSceneReplyCB(ResponseCode responseCode, String sceneID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            director.getSceneCollectionManager().sendErrorEvent("createSceneReplyCB", responseCode, sceneID);
        }

        postProcessSceneID(sceneID);
    }

    @Override
    public void scenesCreatedCB(String[] sceneIDs) {
        AllJoynManager.sceneManager.getAllSceneIDs();
    }

    @Override
    public void updateSceneReplyCB(ResponseCode responseCode, String sceneID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            director.getSceneCollectionManager().sendErrorEvent("updateSceneReplyCB", responseCode, sceneID);
        }
    }

    @Override
    public void scenesUpdatedCB(String[] sceneIDs) {
        for (String sceneID : sceneIDs) {
            AllJoynManager.sceneManager.getScene(sceneID);
        }
    }

    @Override
    public void deleteSceneReplyCB(ResponseCode responseCode, String sceneID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            director.getSceneCollectionManager().sendErrorEvent("deleteSceneReplyCB", responseCode, sceneID);
        }
    }

    @Override
    public void scenesDeletedCB(String[] sceneIDs) {
        postDeleteScenes(sceneIDs);
    }

    @Override
    public void getSceneReplyCB(ResponseCode responseCode, String sceneID, Scene scene) {
        if (!responseCode.equals(ResponseCode.OK)) {
            director.getSceneCollectionManager().sendErrorEvent("getSceneReplyCB", responseCode, sceneID);
        }

        postUpdateScene(sceneID, scene);
    }

    @Override
    public void applySceneReplyCB(ResponseCode responseCode, String sceneID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            director.getSceneCollectionManager().sendErrorEvent("applySceneReplyCB", responseCode, sceneID);
        }

        //TODO-CHK Do we need to do anything here?
    }

    @Override
    public void scenesAppliedCB(String[] sceneIDs) {
        //TODO-CHK Do we need to do anything here?
    }

    protected void postProcessSceneID(final String sceneID) {
        director.getHandler().post(new Runnable() {
            @Override
            public void run() {
                if (!director.getSceneCollectionManager().hasID(sceneID)) {
                    postUpdateSceneID(sceneID);
                    AllJoynManager.sceneManager.getSceneName(sceneID, LightingSystemManager.LANGUAGE);
                    AllJoynManager.sceneManager.getScene(sceneID);
                }
            }
        });
    }

    protected void postUpdateSceneID(final String sceneID) {
        director.getHandler().post(new Runnable() {
            @Override
            public void run() {
                if (!director.getSceneCollectionManager().hasID(sceneID)) {
                    director.getSceneCollectionManager().addScene(sceneID);
                }
            }
        });

        postSendSceneChanged(sceneID);
    }

    protected void postUpdateScene(final String sceneID, final Scene scene) {
        director.getHandler().post(new Runnable() {
            @Override
            public void run() {
                SceneDataModel basicSceneModel = director.getSceneCollectionManager().getModel(sceneID);

                if (basicSceneModel != null) {
                    basicSceneModel.fromScene(scene);
                }
            }
        });

        postSendSceneChanged(sceneID);
    }

    protected void postUpdateSceneName(final String sceneID, final String sceneName) {
        director.getHandler().post(new Runnable() {
            @Override
            public void run() {
                SceneDataModel basicSceneModel = director.getSceneCollectionManager().getModel(sceneID);

                if (basicSceneModel != null) {
                    basicSceneModel.setName(sceneName);
                }
            }
        });

        postSendSceneChanged(sceneID);
    }

    protected void postDeleteScenes(final String[] sceneIDs) {
        director.getHandler().post(new Runnable() {
            @Override
            public void run() {
                for (String sceneID : sceneIDs) {
                    director.getSceneCollectionManager().removeScene(sceneID);
                }
            }
        });
    }

    protected void postSendSceneChanged(final String sceneID) {
        director.getHandler().post(new Runnable() {
            @Override
            public void run() {
                director.getSceneCollectionManager().sendChangedEvent(sceneID);
            }
        });
    }
}
