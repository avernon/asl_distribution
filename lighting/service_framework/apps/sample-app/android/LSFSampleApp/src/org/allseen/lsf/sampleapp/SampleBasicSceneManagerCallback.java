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
package org.allseen.lsf.sampleapp;

import org.allseen.lsf.ResponseCode;
import org.allseen.lsf.Scene;
import org.allseen.lsf.SceneManagerCallback;

import android.os.Handler;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.util.Log;

public class SampleBasicSceneManagerCallback extends SceneManagerCallback {
    protected SampleAppActivity activity;
    protected FragmentManager fragmentManager;
    protected Handler handler;

    public SampleBasicSceneManagerCallback(SampleAppActivity activity, FragmentManager fragmentManager, Handler handler) {
        super();

        this.activity = activity;
        this.fragmentManager = fragmentManager;
        this.handler = handler;
    }

    @Override
    public void getAllSceneIDsReplyCB(ResponseCode responseCode, String[] sceneIDs) {
        if (!responseCode.equals(ResponseCode.OK)) {
            activity.showErrorResponseCode(responseCode, "getAllSceneIDsReplyCB");
        }

        Log.d(SampleAppActivity.TAG, "getAllSceneIDsReplyCB()");

        for (final String sceneID : sceneIDs) {
            postProcessBasicSceneID(sceneID);
        }
    }

    @Override
    public void getSceneNameReplyCB(ResponseCode responseCode, String sceneID, String language, String sceneName) {
        if (!responseCode.equals(ResponseCode.OK)) {
            activity.showErrorResponseCode(responseCode, "getSceneNameReplyCB");
        }

        Log.d(SampleAppActivity.TAG, "getSceneNameReplyCB(): " + sceneName);
        postUpdateSceneName(sceneID, sceneName);
    }

    @Override
    public void setSceneNameReplyCB(ResponseCode responseCode, String sceneID, String language) {
        if (!responseCode.equals(ResponseCode.OK)) {
            activity.showErrorResponseCode(responseCode, "setSceneNameReplyCB");
        }

        Log.d(SampleAppActivity.TAG, "setSceneNameReplyCB(): " + sceneID);
        AllJoynManager.sceneManager.getSceneName(sceneID, SampleAppActivity.LANGUAGE);
    }

    @Override
    public void scenesNameChangedCB(final String[] sceneIDs) {
        handler.post(new Runnable() {
            @Override
            public void run() {
                boolean containsNewIDs = false;

                for (final String sceneID : sceneIDs) {
                    if (activity.basicSceneModels.containsKey(sceneID)) {
                        Log.d(SampleAppActivity.TAG, "scenesNameChangedCB(): " + sceneID);
                        AllJoynManager.sceneManager.getSceneName(sceneID, SampleAppActivity.LANGUAGE);
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
            activity.showErrorResponseCode(responseCode, "createSceneReplyCB");
        }

        Log.d(SampleAppActivity.TAG, "createSceneReplyCB(): " + sceneID);
        postProcessBasicSceneID(sceneID);
    }

    @Override
    public void scenesCreatedCB(String[] sceneIDs) {
        AllJoynManager.sceneManager.getAllSceneIDs();
    }

    @Override
    public void updateSceneReplyCB(ResponseCode responseCode, String sceneID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            activity.showErrorResponseCode(responseCode, "updateSceneReplyCB");
        }

        Log.d(SampleAppActivity.TAG, "updateSceneReplyCB(): " + sceneID);
    }

    @Override
    public void scenesUpdatedCB(String[] sceneIDs) {
        Log.d(SampleAppActivity.TAG, "scenesUpdatedCB(): " + sceneIDs.length);
        for (String sceneID : sceneIDs) {
            Log.d(SampleAppActivity.TAG, "scenesUpdatedCB()" + sceneID);
            AllJoynManager.sceneManager.getScene(sceneID);
        }
    }

    @Override
    public void deleteSceneReplyCB(ResponseCode responseCode, String sceneID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            activity.showErrorResponseCode(responseCode, "deleteSceneReplyCB");
        }

        Log.d(SampleAppActivity.TAG, "deleteSceneReplyCB(): " + sceneID);
    }

    @Override
    public void scenesDeletedCB(String[] sceneIDs) {
        Log.d(SampleAppActivity.TAG, "scenesDeletedCB(): " + sceneIDs.length);
        postDeleteScenes(sceneIDs);
    }

    @Override
    public void getSceneReplyCB(ResponseCode responseCode, String sceneID, Scene scene) {
        if (!responseCode.equals(ResponseCode.OK)) {
            activity.showErrorResponseCode(responseCode, "getSceneReplyCB");
        }

        Log.d(SampleAppActivity.TAG, "getSceneReplyCB(): " + sceneID + ": " +  scene);
        postUpdateBasicScene(sceneID, scene);
    }

    @Override
    public void applySceneReplyCB(ResponseCode responseCode, String sceneID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            activity.showErrorResponseCode(responseCode, "applySceneReplyCB");
        }

        Log.d(SampleAppActivity.TAG, "applySceneReplyCB(): " + sceneID);
        //TODO-CHK Do we need to do anything here?
    }

    @Override
    public void scenesAppliedCB(String[] sceneIDs) {
        Log.d(SampleAppActivity.TAG, "scenesAppliedCB(): " + sceneIDs.length);
        //TODO-CHK Do we need to do anything here?
    }

    protected void postProcessBasicSceneID(final String sceneID) {
        Log.d(SampleAppActivity.TAG, "postProcessSceneID(): " + sceneID);
        handler.post(new Runnable() {
            @Override
            public void run() {
                if (!activity.basicSceneModels.containsKey(sceneID)) {
                    Log.d(SampleAppActivity.TAG, "new scene: " + sceneID);
                    postUpdateBasicSceneID(sceneID);
                    AllJoynManager.sceneManager.getSceneName(sceneID, SampleAppActivity.LANGUAGE);
                    AllJoynManager.sceneManager.getScene(sceneID);
                }
            }
        });
    }

    protected void postUpdateBasicSceneID(final String sceneID) {
        Log.d(SampleAppActivity.TAG, "postUpdateSceneID(): " + sceneID);
        handler.post(new Runnable() {
            @Override
            public void run() {
                BasicSceneDataModel sceneModel = activity.basicSceneModels.get(sceneID);

                if (sceneModel == null) {
                    sceneModel = new BasicSceneDataModel(sceneID);
                    activity.basicSceneModels.put(sceneID, sceneModel);
                }
            }
        });

        postUpdateBasicSceneDisplay(sceneID);
    }

    protected void postUpdateBasicScene(final String sceneID, final Scene scene) {
        Log.d(SampleAppActivity.TAG, "postUpdateBasicScene " + sceneID + ": " +  scene);
        handler.post(new Runnable() {
            @Override
            public void run() {
                BasicSceneDataModel basicSceneModel = activity.basicSceneModels.get(sceneID);

                if (basicSceneModel != null) {
                    basicSceneModel.fromScene(scene);
                }
            }
        });

        postUpdateBasicSceneDisplay(sceneID);
    }

    protected void postUpdateSceneName(final String sceneID, final String sceneName) {
        Log.d(SampleAppActivity.TAG, "postUpdateSceneName() " + sceneID + ", " +  sceneName);
        handler.post(new Runnable() {
            @Override
            public void run() {
                BasicSceneDataModel basicSceneModel = activity.basicSceneModels.get(sceneID);

                if (basicSceneModel != null) {
                    basicSceneModel.setName(sceneName);
                }
            }
        });

        postUpdateBasicSceneDisplay(sceneID);
    }

    protected void postDeleteScenes(final String[] sceneIDs) {
        Log.d(SampleAppActivity.TAG, "Removing deleted scenes");
        handler.post(new Runnable() {
            @Override
            public void run() {
                Fragment pageFragment = fragmentManager.findFragmentByTag(ScenesPageFragment.TAG);
                FragmentManager childManager = pageFragment != null ? pageFragment.getChildFragmentManager() : null;
                ScenesTableFragment tableFragment = childManager != null ? (ScenesTableFragment)childManager.findFragmentByTag(PageFrameParentFragment.CHILD_TAG_TABLE) : null;
                BasicSceneInfoFragment infoFragment = childManager != null ? (BasicSceneInfoFragment)childManager.findFragmentByTag(PageFrameParentFragment.CHILD_TAG_INFO) : null;

                for (String sceneID : sceneIDs) {
                    String name = activity.basicSceneModels.get(sceneID).getName();
                    activity.basicSceneModels.remove(sceneID);

                    if (tableFragment != null) {
                        tableFragment.removeElement(sceneID);
                    }

                    if ((infoFragment != null) && (infoFragment.key.equals(sceneID))) {
                        activity.createLostConnectionErrorDialog(name);
                    }
                }
            }
        });
    }

    protected void postUpdateBasicSceneDisplay(final String sceneID) {
        handler.post(new Runnable() {
            @Override
            public void run() {
                refreshScene(sceneID);
            }
        });
    }

    public void refreshScene(String sceneID) {
        ScenesPageFragment scenesPageFragment = (ScenesPageFragment)fragmentManager.findFragmentByTag(ScenesPageFragment.TAG);

        if (scenesPageFragment != null) {
            ScenesTableFragment basicSceneTableFragment = (ScenesTableFragment)scenesPageFragment.getChildFragmentManager().findFragmentByTag(PageFrameParentFragment.CHILD_TAG_TABLE);

            if (basicSceneTableFragment != null && sceneID != null) {
                basicSceneTableFragment.addElement(sceneID);
            }

            if (!scenesPageFragment.isMasterMode()) {
                BasicSceneInfoFragment basicSceneInfoFragment = (BasicSceneInfoFragment)scenesPageFragment.getChildFragmentManager().findFragmentByTag(PageFrameParentFragment.CHILD_TAG_INFO);

                if (basicSceneInfoFragment != null) {
                    basicSceneInfoFragment.updateInfoFields();
                }
            }
        }
    }
}
