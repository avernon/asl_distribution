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

import org.allseen.lsf.LampState;
import org.allseen.lsf.PresetManagerCallback;
import org.allseen.lsf.ResponseCode;

import android.os.Handler;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.util.Log;

public class SamplePresetManagerCallback extends PresetManagerCallback {
    protected SampleAppActivity activity;
    protected FragmentManager fragmentManager;
    protected Handler handler;

    public SamplePresetManagerCallback(SampleAppActivity activity, FragmentManager fragmentManager, Handler handler) {
        super();

        this.activity = activity;
        this.fragmentManager = fragmentManager;
        this.handler = handler;
    }

    @Override
    public void getPresetReplyCB(ResponseCode responseCode, String presetID, LampState preset) {
        if (!responseCode.equals(ResponseCode.OK)) {
            activity.showErrorResponseCode(responseCode, "getPresetReplyCB");
        }

        Log.d(SampleAppActivity.TAG, "getPresetReplyCB(): " + presetID + ": " +  preset);
        postUpdatePreset(presetID, preset);
    }

    @Override
    public void getAllPresetIDsReplyCB(ResponseCode responseCode, String[] presetIDs) {
        if (!responseCode.equals(ResponseCode.OK)) {
            activity.showErrorResponseCode(responseCode, "getAllPresetIDsReplyCB");
        }

        Log.d(SampleAppActivity.TAG, "getAllPresetIDsReplyCB()");

        for (final String presetID : presetIDs) {
            postProcessPresetID(presetID);
        }
    }

    @Override
    public void getPresetNameReplyCB(ResponseCode responseCode, String presetID, String language, String presetName) {
        if (!responseCode.equals(ResponseCode.OK)) {
            activity.showErrorResponseCode(responseCode, "getPresetNameReplyCB");
        }

        Log.d(SampleAppActivity.TAG, "getPresetNameReplyCB(): " + presetName);
        postUpdatePresetName(presetID, presetName);
    }

    @Override
    public void setPresetNameReplyCB(ResponseCode responseCode, String presetID, String language) {
        if (!responseCode.equals(ResponseCode.OK)) {
            activity.showErrorResponseCode(responseCode, "setPresetNameReplyCB");
        }

        // Currently nothing to do
    }

    @Override
    public void presetsNameChangedCB(final String[] presetIDs) {
        handler.post(new Runnable() {
            @Override
            public void run() {
                boolean containsNewIDs = false;

                for (final String presetID : presetIDs) {
                    if (activity.presetModels.containsKey(presetID)) {
                        Log.d(SampleAppActivity.TAG, "presetsNameChangedCB(): " + presetID);
                        AllJoynManager.presetManager.getPresetName(presetID, SampleAppActivity.LANGUAGE);
                    } else {
                        containsNewIDs = true;
                    }
                }

                if (containsNewIDs) {
                    AllJoynManager.presetManager.getAllPresetIDs();
                }
            }
        });
    }

    @Override
    public void createPresetReplyCB(ResponseCode responseCode, String presetID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            activity.showErrorResponseCode(responseCode, "createPresetReplyCB");
        }

        // Currently nothing to do
    }

    @Override
    public void presetsCreatedCB(String[] presetIDs) {
        AllJoynManager.presetManager.getAllPresetIDs();
    }

    @Override
    public void updatePresetReplyCB(ResponseCode responseCode, String presetID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            activity.showErrorResponseCode(responseCode, "updatePresetReplyCB");
        }

        // Currently nothing to do
    }

    @Override
    public void presetsUpdatedCB(String[] presetIDs) {
        Log.d(SampleAppActivity.TAG, "presetsUpdatedCB(): " + presetIDs.length);
        for (String presetID : presetIDs) {
            Log.d(SampleAppActivity.TAG, "presetsUpdatedCB()" + presetID);
            AllJoynManager.presetManager.getPreset(presetID);
        }
    }

    @Override
    public void deletePresetReplyCB(ResponseCode responseCode, String presetID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            activity.showErrorResponseCode(responseCode, "deletePresetReplyCB");
        }

        // Currently nothing to do
    }

    @Override
    public void presetsDeletedCB(String[] presetIDs) {
        Log.d(SampleAppActivity.TAG, "presetsDeletedCB(): " + presetIDs.length);
        postDeletePresets(presetIDs);
    }

    @Override
    public void getDefaultLampStateReplyCB(ResponseCode responseCode, LampState defaultLampState) {
        if (!responseCode.equals(ResponseCode.OK)) {
            activity.showErrorResponseCode(responseCode, "getDefaultLampStateReplyCB");
        }

        // Currently nothing to do
    }

    @Override
    public void setDefaultLampStateReplyCB(ResponseCode responseCode) {
        if (!responseCode.equals(ResponseCode.OK)) {
            activity.showErrorResponseCode(responseCode, "setDefaultLampStateReplyCB");
        }

        // Currently nothing to do
    }

    @Override
    public void defaultLampStateChangedCB() {
        // Currently nothing to do
    }

    protected void postProcessPresetID(final String presetID) {
        Log.d(SampleAppActivity.TAG, "postProcessPresetID(): " + presetID);
        handler.post(new Runnable() {
            @Override
            public void run() {
                if (!activity.presetModels.containsKey(presetID)) {
                    Log.d(SampleAppActivity.TAG, "new preset: " + presetID);
                    postUpdatePresetID(presetID);
                    AllJoynManager.presetManager.getPresetName(presetID, SampleAppActivity.LANGUAGE);
                    AllJoynManager.presetManager.getPreset(presetID);
                }
            }
        });
    }

    protected void postUpdatePresetID(final String presetID) {
        Log.d(SampleAppActivity.TAG, "postUpdateLampGroupID(): " + presetID);
        handler.post(new Runnable() {
            @Override
            public void run() {
                PresetDataModel presetModel = activity.presetModels.get(presetID);

                if (presetModel == null) {
                    presetModel = new PresetDataModel(presetID);
                    activity.presetModels.put(presetID, presetModel);
                }
            }
        });

        postUpdateInfoFragments();
    }

    protected void postUpdatePresetName(final String presetID, final String presetName) {
        Log.d(SampleAppActivity.TAG, "postUpdatePresetName() " + presetID + ", " +  presetName);
        handler.post(new Runnable() {
            @Override
            public void run() {
                PresetDataModel presetModel = activity.presetModels.get(presetID);

                if (presetModel != null) {
                    presetModel.setName(presetName);
                }
            }
        });

        postUpdateInfoFragments();
    }

    protected void postUpdatePreset(final String presetID, final LampState preset) {
        Log.d(SampleAppActivity.TAG, "Updating preset " + presetID + ": " +  preset);
        handler.post(new Runnable() {
            @Override
            public void run() {
                PresetDataModel presetModel = activity.presetModels.get(presetID);

                if (presetModel != null) {
                    presetModel.state = preset;
                }
            }
        });

        postUpdateInfoFragments();
    }

    protected void postDeletePresets(final String[] presetIDs) {
        Log.d(SampleAppActivity.TAG, "Removing deleted presets");
        handler.post(new Runnable() {
            @Override
            public void run() {
                for (String presetID : presetIDs) {
                    activity.presetModels.remove(presetID);

                    removePreset(LampsPageFragment.TAG, presetID);
                    removePreset(GroupsPageFragment.TAG, presetID);
                    removePreset(ScenesPageFragment.TAG, presetID);
                }
            }
        });

        postUpdateInfoFragments();
    }

    protected void postUpdateInfoFragments() {
        Log.d(SampleAppActivity.TAG, "postUpdateInfoFragments()");
        handler.post(new Runnable() {
            @Override
            public void run() {
                updateInfoFragment(LampsPageFragment.TAG, PageFrameParentFragment.CHILD_TAG_INFO);
                updateInfoFragment(GroupsPageFragment.TAG, PageFrameParentFragment.CHILD_TAG_INFO);
                updateInfoFragment(ScenesPageFragment.TAG, ScenesPageFragment.CHILD_TAG_CONSTANT_EFFECT);
                updateInfoFragment(ScenesPageFragment.TAG, ScenesPageFragment.CHILD_TAG_TRANSITION_EFFECT);
                updateInfoFragment(ScenesPageFragment.TAG, ScenesPageFragment.CHILD_TAG_PULSE_EFFECT);
            }
        });
    }

    private void removePreset(String pageFragmentTag, String presetID) {
        Fragment pageFragment = fragmentManager.findFragmentByTag(pageFragmentTag);

        if (pageFragment != null) {
            FragmentManager childManager = pageFragment.getChildFragmentManager();
            DimmableItemPresetsFragment presetFragment = (DimmableItemPresetsFragment)childManager.findFragmentByTag(PageFrameParentFragment.CHILD_TAG_PRESETS);

            removePreset(presetFragment, presetID);
        }
    }

    private void removePreset(DimmableItemPresetsFragment presetFragment, String presetID) {
        if (presetFragment != null) {
            presetFragment.removeElement(presetID);
        }
    }

    private void updateInfoFragment(String pageFragmentTag, String infoFragmentTag) {
        Fragment pageFragment = fragmentManager.findFragmentByTag(pageFragmentTag);

        if (pageFragment != null) {
            updateinfoFragment((DimmableItemInfoFragment)pageFragment.getChildFragmentManager().findFragmentByTag(infoFragmentTag));
        }
    }

    private void updateinfoFragment(DimmableItemInfoFragment infoFragment) {
        if (infoFragment != null) {
            infoFragment.updatePresetFields();
        }
    }
}
