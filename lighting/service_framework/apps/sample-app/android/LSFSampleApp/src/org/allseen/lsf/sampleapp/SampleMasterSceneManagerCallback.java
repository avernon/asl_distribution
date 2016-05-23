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

import org.allseen.lsf.MasterScene;
import org.allseen.lsf.MasterSceneManagerCallback;
import org.allseen.lsf.ResponseCode;

import android.os.Handler;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.util.Log;

public class SampleMasterSceneManagerCallback extends MasterSceneManagerCallback {
    protected SampleAppActivity activity;
    protected FragmentManager fragmentManager;
    protected Handler handler;

    public SampleMasterSceneManagerCallback(SampleAppActivity activity, FragmentManager fragmentManager, Handler handler) {
        super();

        this.activity = activity;
        this.fragmentManager = fragmentManager;
        this.handler = handler;
    }

    @Override
    public void getAllMasterSceneIDsReplyCB(ResponseCode responseCode, String[] masterSceneIDs) {
        if (!responseCode.equals(ResponseCode.OK)) {
            activity.showErrorResponseCode(responseCode, "getAllMasterSceneIDsReplyCB");
        }

        Log.d(SampleAppActivity.TAG, "getAllMasterSceneIDsReplyCB()");

        for (final String masterSceneID : masterSceneIDs) {
            postProcessMasterSceneID(masterSceneID);
        }
    }

    @Override
    public void getMasterSceneNameReplyCB(ResponseCode responseCode, String masterSceneID, String language, String masterSceneName) {
        if (!responseCode.equals(ResponseCode.OK)) {
            activity.showErrorResponseCode(responseCode, "getMasterSceneNameReplyCB");
        }

        Log.d(SampleAppActivity.TAG, "getMasterSceneNameReplyCB(): " + masterSceneName);
        postUpdateMasterSceneName(masterSceneID, masterSceneName);
    }

    @Override
    public void setMasterSceneNameReplyCB(ResponseCode responseCode, String masterSceneID, String language) {
        if (!responseCode.equals(ResponseCode.OK)) {
            activity.showErrorResponseCode(responseCode, "setMasterSceneNameReplyCB");
        }

        Log.d(SampleAppActivity.TAG, "setMasterSceneNameReplyCB(): " + masterSceneID);
        AllJoynManager.masterSceneManager.getMasterSceneName(masterSceneID, SampleAppActivity.LANGUAGE);
    }

    @Override
    public void masterScenesNameChangedCB(final String[] masterSceneIDs) {
        handler.post(new Runnable() {
            @Override
            public void run() {
                boolean containsNewIDs = false;

                for (final String masterSceneID : masterSceneIDs) {
                    if (activity.masterSceneModels.containsKey(masterSceneID)) {
                        Log.d(SampleAppActivity.TAG, "masterScenesNameChangedCB(): " + masterSceneID);
                        AllJoynManager.masterSceneManager.getMasterSceneName(masterSceneID, SampleAppActivity.LANGUAGE);
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
            activity.showErrorResponseCode(responseCode, "createMasterSceneReplyCB");
        }

        Log.d(SampleAppActivity.TAG, "createMasterSceneReplyCB(): " + masterSceneID);
        postProcessMasterSceneID(masterSceneID);
    }

    @Override
    public void masterScenesCreatedCB(String[] masterSceneIDs) {
        AllJoynManager.masterSceneManager.getAllMasterSceneIDs();
    }

    @Override
    public void updateMasterSceneReplyCB(ResponseCode responseCode, String masterSceneID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            activity.showErrorResponseCode(responseCode, "updateMasterSceneReplyCB");
        }

        Log.d(SampleAppActivity.TAG, "updateMasterSceneReplyCB(): " + masterSceneID);
    }

    @Override
    public void masterScenesUpdatedCB(String[] masterSceneIDs) {
        Log.d(SampleAppActivity.TAG, "masterScenesUpdatedCB(): " + masterSceneIDs.length);
        for (String masterSceneID : masterSceneIDs) {
            Log.d(SampleAppActivity.TAG, "masterScenesUpdatedCB()" + masterSceneID);
            AllJoynManager.masterSceneManager.getMasterScene(masterSceneID);
        }
    }

    @Override
    public void deleteMasterSceneReplyCB(ResponseCode responseCode, String masterSceneID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            activity.showErrorResponseCode(responseCode, "deleteMasterSceneReplyCB");
        }

        Log.d(SampleAppActivity.TAG, "deleteMasterSceneReplyCB(): " + masterSceneID);
    }

    @Override
    public void masterScenesDeletedCB(String[] masterSceneIDs) {
        Log.d(SampleAppActivity.TAG, "masterScenesDeletedCB(): " + masterSceneIDs.length);
        postDeleteMasterScenes(masterSceneIDs);
    }

    @Override
    public void getMasterSceneReplyCB(ResponseCode responseCode, String masterSceneID, MasterScene masterScene) {
        if (!responseCode.equals(ResponseCode.OK)) {
            activity.showErrorResponseCode(responseCode, "getMasterSceneReplyCB");
        }

        Log.d(SampleAppActivity.TAG, "getMasterSceneReplyCB(): " + masterSceneID + ": " +  masterScene);
        postUpdateMasterScene(masterSceneID, masterScene);
    }

    @Override
    public void applyMasterSceneReplyCB(ResponseCode responseCode, String masterSceneID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            activity.showErrorResponseCode(responseCode, "applyMasterSceneReplyCB");
        }

        Log.d(SampleAppActivity.TAG, "applyMasterSceneReplyCB(): " + masterSceneID);
        //TODO-CHK Do we need to do anything here?
    }

    @Override
    public void masterScenesAppliedCB(String[] masterSceneIDs) {
        Log.d(SampleAppActivity.TAG, "masterScenesAppliedCB(): " + masterSceneIDs.length);
        //TODO-CHK Do we need to do anything here?
    }

    protected void postProcessMasterSceneID(final String masterSceneID) {
        Log.d(SampleAppActivity.TAG, "postProcessMasterSceneID(): " + masterSceneID);
        handler.post(new Runnable() {
            @Override
            public void run() {
                if (!activity.masterSceneModels.containsKey(masterSceneID)) {
                    Log.d(SampleAppActivity.TAG, "new master scene: " + masterSceneID);
                    postUpdateMasterSceneID(masterSceneID);
                    AllJoynManager.masterSceneManager.getMasterSceneName(masterSceneID, SampleAppActivity.LANGUAGE);
                    AllJoynManager.masterSceneManager.getMasterScene(masterSceneID);
                }
            }
        });
    }

    protected void postUpdateMasterSceneID(final String masterSceneID) {
        Log.d(SampleAppActivity.TAG, "postUpdateMasterSceneID(): " + masterSceneID);
        handler.post(new Runnable() {
            @Override
            public void run() {
                MasterSceneDataModel masterSceneModel = activity.masterSceneModels.get(masterSceneID);

                if (masterSceneModel == null) {
                    masterSceneModel = new MasterSceneDataModel(masterSceneID);
                    activity.masterSceneModels.put(masterSceneID, masterSceneModel);
                }
            }
        });

        postUpdateMasterSceneDisplay(masterSceneID);
    }

    protected void postUpdateMasterScene(final String masterSceneID, final MasterScene masterScene) {
        Log.d(SampleAppActivity.TAG, "postUpdateMasterScene " + masterSceneID + ": " +  masterScene);
        handler.post(new Runnable() {
            @Override
            public void run() {
                MasterSceneDataModel masterSceneModel = activity.masterSceneModels.get(masterSceneID);

                if (masterSceneModel != null) {
                    masterSceneModel.masterScene = masterScene;
                }
            }
        });

        postUpdateMasterSceneDisplay(masterSceneID);
    }

    protected void postUpdateMasterSceneName(final String masterSceneID, final String masterSceneName) {
        Log.d(SampleAppActivity.TAG, "postUpdateMasterSceneName() " + masterSceneID + ", " +  masterSceneName);
        handler.post(new Runnable() {
            @Override
            public void run() {
                MasterSceneDataModel masterSceneModel = activity.masterSceneModels.get(masterSceneID);

                if (masterSceneModel != null) {
                    masterSceneModel.setName(masterSceneName);
                }
            }
        });

        postUpdateMasterSceneDisplay(masterSceneID);
    }

    protected void postDeleteMasterScenes(final String[] masterSceneIDs) {
        Log.d(SampleAppActivity.TAG, "Removing deleted master scenes");
        handler.post(new Runnable() {
            @Override
            public void run() {
                Fragment pageFragment = fragmentManager.findFragmentByTag(ScenesPageFragment.TAG);
                FragmentManager childManager = pageFragment != null ? pageFragment.getChildFragmentManager() : null;
                ScenesTableFragment tableFragment = childManager != null ? (ScenesTableFragment)childManager.findFragmentByTag(PageFrameParentFragment.CHILD_TAG_TABLE) : null;
                MasterSceneInfoFragment infoFragment = childManager != null ? (MasterSceneInfoFragment)childManager.findFragmentByTag(PageFrameParentFragment.CHILD_TAG_INFO) : null;

                for (String masterSceneID : masterSceneIDs) {
                    String name = activity.masterSceneModels.get(masterSceneID).getName();
                    activity.masterSceneModels.remove(masterSceneID);

                    if (tableFragment != null) {
                        tableFragment.removeElement(masterSceneID);
                    }

                    if ((infoFragment != null) && (infoFragment.key.equals(masterSceneID))) {
                        activity.createLostConnectionErrorDialog(name);
                    }
                }
            }
        });
    }

    protected void postUpdateMasterSceneDisplay(final String masterSceneID) {
        handler.post(new Runnable() {
            @Override
            public void run() {
                ScenesPageFragment scenesPageFragment = (ScenesPageFragment)fragmentManager.findFragmentByTag(ScenesPageFragment.TAG);

                if (scenesPageFragment != null) {
                    ScenesTableFragment scenesTableFragment = (ScenesTableFragment)scenesPageFragment.getChildFragmentManager().findFragmentByTag(PageFrameParentFragment.CHILD_TAG_TABLE);

                    if (scenesTableFragment != null) {
                        scenesTableFragment.addElement(masterSceneID);
                    }

                    if (scenesPageFragment.isMasterMode()) {
                        MasterSceneInfoFragment masterSceneInfoFragment = (MasterSceneInfoFragment)scenesPageFragment.getChildFragmentManager().findFragmentByTag(PageFrameParentFragment.CHILD_TAG_INFO);

                        if (masterSceneInfoFragment != null) {
                            masterSceneInfoFragment.updateInfoFields();
                        }
                    }
                }
            }
        });
    }
}
