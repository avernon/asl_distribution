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
package org.allseen.lsf.sdk.callback;

import java.util.HashMap;
import java.util.Map;

import org.allseen.lsf.Scene;
import org.allseen.lsf.SceneManagerCallback;
import org.allseen.lsf.SceneWithSceneElements;
import org.allseen.lsf.sdk.ResponseCode;
import org.allseen.lsf.sdk.TrackingID;
import org.allseen.lsf.sdk.manager.AllJoynManager;
import org.allseen.lsf.sdk.manager.LightingSystemManager;
import org.allseen.lsf.sdk.manager.SceneCollectionManager;
import org.allseen.lsf.sdk.model.LightingItemDataModel;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class HelperSceneManagerCallback<SCENEV1, SCENEV2> extends SceneManagerCallback {
    protected LightingSystemManager<?, ?, ?, ?, ?, ?, SCENEV1, SCENEV2, ?, ?, ?> manager;
    protected Map<String, TrackingID> creationTrackingIDs;

    public HelperSceneManagerCallback(LightingSystemManager<?, ?, ?, ?, ?, ?, SCENEV1, SCENEV2, ?, ?, ?> manager) {
        super();

        this.manager = manager;
        this.creationTrackingIDs = new HashMap<String, TrackingID>();
    }

    @Override
    public void getAllSceneIDsReplyCB(ResponseCode responseCode, String[] sceneIDs) {
        if (!responseCode.equals(ResponseCode.OK)) {
            getSceneCollectionManager().sendErrorEvent("getAllSceneIDsReplyCB", responseCode, null);
        }

        for (final String sceneID : sceneIDs) {
            postProcessSceneID(sceneID);
        }
    }

    @Override
    public void getSceneNameReplyCB(ResponseCode responseCode, String sceneID, String language, String sceneName) {
        if (!responseCode.equals(ResponseCode.OK)) {
            getSceneCollectionManager().sendErrorEvent("getSceneNameReplyCB", responseCode, sceneID);
        }

        postUpdateSceneName(sceneID, sceneName);
    }

    @Override
    public void setSceneNameReplyCB(ResponseCode responseCode, String sceneID, String language) {
        if (!responseCode.equals(ResponseCode.OK)) {
            getSceneCollectionManager().sendErrorEvent("setSceneNameReplyCB", responseCode, sceneID);
        }

        AllJoynManager.sceneManager.getSceneName(sceneID, LightingSystemManager.LANGUAGE);
    }

    @Override
    public void scenesNameChangedCB(final String[] sceneIDs) {
        manager.getQueue().post(new Runnable() {
            @Override
            public void run() {
                boolean containsNewIDs = false;

                for (final String sceneID : sceneIDs) {
                    if (getSceneCollectionManager().hasID(sceneID)) {
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
            getSceneCollectionManager().sendErrorEvent("createSceneReplyCB", responseCode, sceneID);
        }
    }

    @Override
    public void createSceneWithTrackingReplyCB(ResponseCode responseCode, String sceneID, long trackingID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            getSceneCollectionManager().sendErrorEvent("createSceneWithTrackingReplyCB", responseCode, sceneID, new TrackingID(trackingID));
        } else {
            creationTrackingIDs.put(sceneID, new TrackingID(trackingID));
        }
    }

    @Override
    public void createSceneWithSceneElementsReplyCB(ResponseCode responseCode, String sceneID, long trackingID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            getSceneCollectionManager().sendErrorEvent("createSceneWithSceneElementsReplyCB", responseCode, sceneID, new TrackingID(trackingID));
        } else {
            creationTrackingIDs.put(sceneID, new TrackingID(trackingID));
        }
    }

    @Override
    public void scenesCreatedCB(String[] sceneIDs) {
        AllJoynManager.sceneManager.getAllSceneIDs();
    }

    @Override
    public void updateSceneReplyCB(ResponseCode responseCode, String sceneID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            getSceneCollectionManager().sendErrorEvent("updateSceneReplyCB", responseCode, sceneID);
        }
    }

    @Override
    public void updateSceneWithSceneElementsReplyCB(ResponseCode responseCode, String sceneID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            getSceneCollectionManager().sendErrorEvent("updateSceneWithSceneElementsReplyCB", responseCode, sceneID);
        }
    }

    @Override
    public void scenesUpdatedCB(String[] sceneIDs) {
        postUpdateScenes(sceneIDs);
    }

    @Override
    public void deleteSceneReplyCB(ResponseCode responseCode, String sceneID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            getSceneCollectionManager().sendErrorEvent("deleteSceneReplyCB", responseCode, sceneID);
        }
    }

    @Override
    public void scenesDeletedCB(String[] sceneIDs) {
        postDeleteScenes(sceneIDs);
    }

    @Override
    public void getSceneReplyCB(ResponseCode responseCode, String sceneID, Scene scene) {
        if (!responseCode.equals(ResponseCode.OK)) {
            getSceneCollectionManager().sendErrorEvent("getSceneReplyCB", responseCode, sceneID);
        }

        postUpdateScene(sceneID, scene);
    }

    @Override
    public void getSceneWithSceneElementsReplyCB(ResponseCode responseCode, String sceneID, SceneWithSceneElements scene) {
        if (!responseCode.equals(ResponseCode.OK)) {
            getSceneCollectionManager().sendErrorEvent("getSceneWithSceneElementsReplyCB", responseCode, sceneID);
        }

        postUpdateScene(sceneID, scene);
    }

    @Override
    public void applySceneReplyCB(ResponseCode responseCode, String sceneID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            getSceneCollectionManager().sendErrorEvent("applySceneReplyCB", responseCode, sceneID);
        }
    }

    @Override
    public void scenesAppliedCB(String[] sceneIDs) {
        // Currently nothing to do
    }

    protected void postProcessSceneID(final String sceneID) {
        manager.getQueue().post(new Runnable() {
            @Override
            public void run() {
                if (!getSceneCollectionManager().hasID(sceneID)) {
                    postUpdateSceneID(sceneID);
                    AllJoynManager.sceneManager.getSceneName(sceneID, LightingSystemManager.LANGUAGE);

                    if (AllJoynManager.isControllerServiceLeaderV1()) {
                        AllJoynManager.sceneManager.getScene(sceneID);
                    } else {
                        AllJoynManager.sceneManager.getSceneWithSceneElements(sceneID);
                    }
                }
            }
        });
    }

    protected void postUpdateSceneID(final String sceneID) {
        manager.getQueue().post(new Runnable() {
            @Override
            public void run() {
                if (!getSceneCollectionManager().hasID(sceneID)) {
                    getSceneCollectionManager().addScene(sceneID);
                }
            }
        });

        postSendSceneChanged(sceneID);
    }

    protected void postUpdateScene(final String sceneID, final Scene scene) {
        postUpdateScene(sceneID, new Runnable() {
            @Override
            public void run() {
                manager.getSceneCollectionManagerV1().getModel(sceneID).fromScene(scene);
            }
        });
    }

    protected void postUpdateScene(final String sceneID, final SceneWithSceneElements scene) {
        postUpdateScene(sceneID, new Runnable() {
            @Override
            public void run() {
                manager.getSceneCollectionManagerV2().getModel(sceneID).setSceneWithSceneElements(scene);
            }
        });
    }

    protected void postUpdateScene(final String sceneID, final Runnable delegate) {
        manager.getQueue().post(new Runnable() {
            @Override
            public void run() {
                LightingItemDataModel itemModel = getLightingItemModel(sceneID);

                if (itemModel != null) {
                    boolean wasInitialized = itemModel.isInitialized();
                    delegate.run();
                    if (wasInitialized != itemModel.isInitialized()) {
                        postSendSceneInitialized(sceneID);
                    }
                }
            }
        });

        postSendSceneChanged(sceneID);
    }

    protected void postUpdateSceneName(final String sceneID, final String sceneName) {
        manager.getQueue().post(new Runnable() {
            @Override
            public void run() {
                LightingItemDataModel itemModel = getLightingItemModel(sceneID);

                if (itemModel != null) {
                    boolean wasInitialized = itemModel.isInitialized();
                    itemModel.setName(sceneName);
                    if (wasInitialized != itemModel.isInitialized()) {
                        postSendSceneInitialized(sceneID);
                    }
                }
            }
        });

        postSendSceneChanged(sceneID);
    }

    protected void postUpdateScenes(final String[] sceneIDs) {
        manager.getQueue().post(new Runnable() {
            @Override
            public void run() {
                for (String sceneID : sceneIDs) {
                    if (AllJoynManager.isControllerServiceLeaderV1()) {
                        AllJoynManager.sceneManager.getScene(sceneID);
                    } else {
                        AllJoynManager.sceneManager.getSceneWithSceneElements(sceneID);
                    }
                }
            }
        });
    }

    protected void postDeleteScenes(final String[] sceneIDs) {
        manager.getQueue().post(new Runnable() {
            @Override
            public void run() {
                for (String sceneID : sceneIDs) {
                    getSceneCollectionManager().removeScene(sceneID);
                }
            }
        });
    }

    protected void postSendSceneChanged(final String sceneID) {
        manager.getQueue().post(new Runnable() {
            @Override
            public void run() {
                getSceneCollectionManager().sendChangedEvent(sceneID);
            }
        });
    }

    protected void postSendSceneInitialized(final String sceneID) {
        manager.getQueue().post(new Runnable() {
            @Override
            public void run() {
                getSceneCollectionManager().sendInitializedEvent(sceneID, creationTrackingIDs.remove(sceneID));
            }
        });
    }

    protected SceneCollectionManager<?, ?, ?> getSceneCollectionManager() {
        return AllJoynManager.isControllerServiceLeaderV1() ? manager.getSceneCollectionManagerV1() : manager.getSceneCollectionManagerV2();
    }

    protected LightingItemDataModel getLightingItemModel(String itemID) {
        return AllJoynManager.isControllerServiceLeaderV1() ? manager.getSceneCollectionManagerV1().getModel(itemID) : manager.getSceneCollectionManagerV2().getModel(itemID);
    }
}
