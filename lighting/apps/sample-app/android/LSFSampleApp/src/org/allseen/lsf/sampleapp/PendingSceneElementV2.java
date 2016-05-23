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
package org.allseen.lsf.sampleapp;

import java.util.ArrayList;
import java.util.Collection;
import java.util.UUID;

import org.allseen.lsf.sdk.LampCapabilities;
import org.allseen.lsf.sdk.LightingDirector;
import org.allseen.lsf.sdk.Preset;
import org.allseen.lsf.sdk.PulseEffect;
import org.allseen.lsf.sdk.SceneElement;
import org.allseen.lsf.sdk.ColorAverager;
import org.allseen.lsf.sdk.TransitionEffect;

import android.util.Log;

public class PendingSceneElementV2 extends PendingLightingItem {
    public static String LOCAL_ID_PREFIX = "_";

    public Collection<String> groups;
    public Collection<String> lamps;

    public LampCapabilities capability;
    public ColorAverager colorTempAverager;

    public int minColorTemp;
    public int maxColorTemp;
    public boolean hasEffects;

    public PendingPresetEffect pendingPresetEffect;
    public PendingTransitionEffectV2 pendingTransitionEffect;
    public PendingPulseEffectV2 pendingPulseEffect;

    public static boolean isLocalID(String sceneElementID) {
        return sceneElementID.startsWith(LOCAL_ID_PREFIX);
    }

    public PendingSceneElementV2() {
        this((SceneElement)null);
    }

    public PendingSceneElementV2(SceneElement sceneElement) {
        super.init(sceneElement);

        groups = sceneElement != null ? sceneElement.getGroupIDs() : new ArrayList<String>();
        lamps = sceneElement != null ? sceneElement.getLampIDs() : new ArrayList<String>();

        capability = new LampCapabilities();
        colorTempAverager = new ColorAverager();

        //TODO-FIX
        minColorTemp = -1;
        maxColorTemp = -1;
        hasEffects = false;

        String effectID = sceneElement != null ? sceneElement.getEffectID() : null;

        if (effectID != null) {
            LightingDirector director = LightingDirector.get();
            Preset preset = director.getPreset(effectID);

            if (preset == null) {
                TransitionEffect transitionEffect = director.getTransitionEffect(effectID);

                if (transitionEffect == null) {
                    PulseEffect pulseEffect = director.getPulseEffect(effectID);

                    if (pulseEffect == null) {
                        Log.e(SampleAppActivity.TAG, "Unknown effect with ID " + effectID);
                    } else {
                        pendingPresetEffect = null;
                        pendingTransitionEffect = null;
                        pendingPulseEffect = new PendingPulseEffectV2(pulseEffect);
                    }
                } else {
                    pendingPresetEffect = null;
                    pendingTransitionEffect = new PendingTransitionEffectV2(transitionEffect);
                    pendingPulseEffect = null;
                }
            } else {
                pendingPresetEffect = new PendingPresetEffect(preset);
                pendingTransitionEffect = null;
                pendingPulseEffect = null;
            }
        }
    }

    public PendingSceneElementV2(PendingSceneElementV2 pendingSceneElement) {
        super.init(pendingSceneElement.id, pendingSceneElement.name);

        groups = new ArrayList<String>(pendingSceneElement.groups);
        lamps = new ArrayList<String>(pendingSceneElement.lamps);

        capability = new LampCapabilities(pendingSceneElement.capability);
        colorTempAverager = new ColorAverager();//TODO-CHK Should this be initialized?

        minColorTemp = pendingSceneElement.minColorTemp;
        maxColorTemp = pendingSceneElement.maxColorTemp;
        hasEffects = pendingSceneElement.hasEffects;

        if (pendingSceneElement.pendingPresetEffect != null) {
            pendingPresetEffect = new PendingPresetEffect(pendingSceneElement.pendingPresetEffect);
        } else if (pendingSceneElement.pendingTransitionEffect != null) {
            pendingTransitionEffect = new PendingTransitionEffectV2(pendingSceneElement.pendingTransitionEffect);
        } else if (pendingSceneElement.pendingPulseEffect != null) {
            pendingPulseEffect = new PendingPulseEffectV2(pendingSceneElement.pendingPulseEffect);
        } else {
            Log.e(SampleAppActivity.TAG, "No effect in scene element " + id);
        }

    }

    @Override
    protected String ensureValidID(String pendingID) {
        if (pendingID == null || pendingID.isEmpty()) {
            pendingID = LOCAL_ID_PREFIX + UUID.randomUUID().toString();
        }

        return pendingID;
    }

    public boolean isAddMode() {
        return isLocalID(id);
    }
}
