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
package org.allseen.lsf.sdk.model;

/**
 * <b>WARNING: This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK</b>.
 */
public class TransitionEffectDataModelV2 extends ColorItemDataModel {
    public static final char TAG_PREFIX_TRANSITION = 'E';

    public static String defaultName = "<Loading transition effect info...>";
    public static long defaultDuration = 5000;

    protected boolean durationInitialized;

    private String presetID;
    private long duration;

    public TransitionEffectDataModelV2() {
        this(null);
    }

    public TransitionEffectDataModelV2(String transitionEffectID) {
        this(transitionEffectID, null);
    }

    public TransitionEffectDataModelV2(String transitionEffectID, String transitionEffectName) {
        super(transitionEffectID, TAG_PREFIX_TRANSITION, transitionEffectName != null ? transitionEffectName : defaultName);

        setCapability(LampCapabilities.allCapabilities);

        duration = defaultDuration;
        presetID = null;

        durationInitialized = false;
    }

    public String getPresetID() {
        return presetID;
    }

    public void setPresetID(String transtionEffectPresetID) {
        presetID = transtionEffectPresetID;
        // preset/state share same flag since only one field should be set
        stateInitialized = true;
    }

    public long getDuration() {
        return duration;
    }

    public void setDuration(long transitionEffectDuration) {
        duration = transitionEffectDuration;
        durationInitialized = true;
    }

    public boolean containsPreset(String presetID) {
        return presetID.equals(this.presetID);
    }

    @Override
    public boolean isInitialized() {
        return super.isInitialized() && stateInitialized && durationInitialized;
    }
}
