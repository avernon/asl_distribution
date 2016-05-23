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

import org.allseen.lsf.LampState;
import org.allseen.lsf.PresetManagerCallback;
import org.allseen.lsf.sdk.ResponseCode;
import org.allseen.lsf.sdk.TrackingID;
import org.allseen.lsf.sdk.manager.AllJoynManager;
import org.allseen.lsf.sdk.manager.LightingSystemManager;
import org.allseen.lsf.sdk.model.PresetDataModel;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class HelperPresetManagerCallback<PRESET> extends PresetManagerCallback {
    protected LightingSystemManager<?, ?, PRESET, ?, ?, ?, ?, ?, ?, ?, ?> manager;
    protected Map<String, TrackingID> creationTrackingIDs;

    public HelperPresetManagerCallback(LightingSystemManager<?, ?, PRESET, ?, ?, ?, ?, ?, ?, ?, ?> manager) {
        super();

        this.manager = manager;
        this.creationTrackingIDs = new HashMap<String, TrackingID>();
    }

    @Override
    public void getPresetReplyCB(ResponseCode responseCode, String presetID, LampState preset) {
        if (!responseCode.equals(ResponseCode.OK)) {
            manager.getPresetCollectionManager().sendErrorEvent("getPresetReplyCB", responseCode, presetID);
        }

        postUpdatePreset(presetID, preset);
    }

    @Override
    public void getAllPresetIDsReplyCB(ResponseCode responseCode, String[] presetIDs) {
        if (!responseCode.equals(ResponseCode.OK)) {
            manager.getPresetCollectionManager().sendErrorEvent("getAllPresetIDsReplyCB", responseCode);
        }

        for (final String presetID : presetIDs) {
            postProcessPresetID(presetID);
        }
    }

    @Override
    public void getPresetNameReplyCB(ResponseCode responseCode, String presetID, String language, String presetName) {
        if (!responseCode.equals(ResponseCode.OK)) {
            manager.getPresetCollectionManager().sendErrorEvent("getPresetNameReplyCB", responseCode, presetID);
        }

        postUpdatePresetName(presetID, presetName);
    }

    @Override
    public void setPresetNameReplyCB(ResponseCode responseCode, String presetID, String language) {
        if (!responseCode.equals(ResponseCode.OK)) {
            manager.getPresetCollectionManager().sendErrorEvent("setPresetNameReplyCB", responseCode, presetID);
        }

        // Currently nothing to do
    }

    @Override
    public void presetsNameChangedCB(final String[] presetIDs) {
        manager.getQueue().post(new Runnable() {
            @Override
            public void run() {
                boolean containsNewIDs = false;

                for (final String presetID : presetIDs) {
                    if (manager.getPresetCollectionManager().hasID(presetID)) {
                        AllJoynManager.presetManager.getPresetName(presetID, LightingSystemManager.LANGUAGE);
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
            manager.getPresetCollectionManager().sendErrorEvent("createPresetReplyCB", responseCode, presetID);
        }

        // Currently nothing to do
    }

    @Override
    public void createPresetWithTrackingReplyCB(ResponseCode responseCode, String presetID, long trackingID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            manager.getPresetCollectionManager().sendErrorEvent("createPresetWithTrackingReplyCB", responseCode, presetID, new TrackingID(trackingID));
        } else {
            creationTrackingIDs.put(presetID, new TrackingID(trackingID));
        }
    }

    @Override
    public void presetsCreatedCB(String[] presetIDs) {
        AllJoynManager.presetManager.getAllPresetIDs();
    }

    @Override
    public void updatePresetReplyCB(ResponseCode responseCode, String presetID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            manager.getPresetCollectionManager().sendErrorEvent("updatePresetReplyCB", responseCode, presetID);
        }

        // Currently nothing to do
    }

    @Override
    public void presetsUpdatedCB(String[] presetIDs) {
        for (String presetID : presetIDs) {
            AllJoynManager.presetManager.getPreset(presetID);
        }
    }

    @Override
    public void deletePresetReplyCB(ResponseCode responseCode, String presetID) {
        if (!responseCode.equals(ResponseCode.OK)) {
            manager.getPresetCollectionManager().sendErrorEvent("deletePresetReplyCB", responseCode, presetID);
        }

        // Currently nothing to do
    }

    @Override
    public void presetsDeletedCB(String[] presetIDs) {
        postDeletePresets(presetIDs);
    }

    @Override
    public void getDefaultLampStateReplyCB(ResponseCode responseCode, LampState defaultLampState) {
        if (!responseCode.equals(ResponseCode.OK)) {
            manager.getPresetCollectionManager().sendErrorEvent("getDefaultLampStateReplyCB", responseCode);
        }

        // Currently nothing to do
    }

    @Override
    public void setDefaultLampStateReplyCB(ResponseCode responseCode) {
        if (!responseCode.equals(ResponseCode.OK)) {
            manager.getPresetCollectionManager().sendErrorEvent("setDefaultLampStateReplyCB", responseCode);
        }

        // Currently nothing to do
    }

    @Override
    public void defaultLampStateChangedCB() {
        // Currently nothing to do
    }

    protected void postProcessPresetID(final String presetID) {
        manager.getQueue().post(new Runnable() {
            @Override
            public void run() {
                if (!manager.getPresetCollectionManager().hasID(presetID)) {
                    postUpdatePresetID(presetID);
                    AllJoynManager.presetManager.getPresetName(presetID, LightingSystemManager.LANGUAGE);
                    AllJoynManager.presetManager.getPreset(presetID);
                }
            }
        });
    }

    protected void postUpdatePresetID(final String presetID) {
        manager.getQueue().post(new Runnable() {
            @Override
            public void run() {
                if (!manager.getPresetCollectionManager().hasID(presetID)) {
                    manager.getPresetCollectionManager().addPreset(presetID);
                }
            }
        });

        postSendPresetChanged(presetID);
    }

    protected void postUpdatePresetName(final String presetID, final String presetName) {
        manager.getQueue().post(new Runnable() {
            @Override
            public void run() {
                PresetDataModel presetModel = manager.getPresetCollectionManager().getModel(presetID);

                if (presetModel != null) {
                    boolean wasInitialized = presetModel.isInitialized();
                    presetModel.setName(presetName);
                    if (wasInitialized != presetModel.isInitialized()) {
                        postSendPresetInitialized(presetID);
                    }
                }
            }
        });

        postSendPresetChanged(presetID);
    }

    protected void postUpdatePreset(final String presetID, final LampState preset) {
        manager.getQueue().post(new Runnable() {
            @Override
            public void run() {
                PresetDataModel presetModel = manager.getPresetCollectionManager().getModel(presetID);

                if (presetModel != null) {
                    boolean wasInitialized = presetModel.isInitialized();
                    presetModel.setState(preset);
                    if (wasInitialized != presetModel.isInitialized()) {
                        postSendPresetInitialized(presetID);
                    }
                }
            }
        });

        postSendPresetChanged(presetID);
    }

    protected void postDeletePresets(final String[] presetIDs) {
        manager.getQueue().post(new Runnable() {
            @Override
            public void run() {
                for (String presetID : presetIDs) {
                    manager.getPresetCollectionManager().removePreset(presetID);
                }
            }
        });
    }

    protected void postSendPresetChanged(final String presetID) {
        manager.getQueue().post(new Runnable() {
            @Override
            public void run() {
                manager.getPresetCollectionManager().sendChangedEvent(presetID);
            }
        });
    }

    protected void postSendPresetInitialized(final String presetID) {
        manager.getQueue().post(new Runnable() {
            @Override
            public void run() {
                manager.getPresetCollectionManager().sendInitializedEvent(presetID, creationTrackingIDs.remove(presetID));
            }
        });
    }
}
