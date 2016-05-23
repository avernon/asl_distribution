/*
 * Copyright AllSeen Alliance. All rights reserved.
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

import org.allseen.lsf.LampGroup;
import org.allseen.lsf.LampState;
import org.allseen.lsf.MasterScene;
import org.allseen.lsf.PulseEffectV2;
import org.allseen.lsf.SceneElement;
import org.allseen.lsf.SceneWithSceneElements;
import org.allseen.lsf.TransitionEffectV2;

public class LightingItemUtil {
    public static final String[] NO_ITEM_IDS = new String[0];

    public static LampState createLampStateFromView(boolean powerOn, int viewHue, int viewSaturation, int viewBrightness, int viewColorTemp) {
        LampState lampState = new LampState();
        lampState.setOnOff(powerOn);
        ColorStateConverter.convertViewToModel(viewHue, viewSaturation, viewBrightness, viewColorTemp, lampState);

        return lampState;
    }


    public static LampGroup createLampGroup(String[] lampIds, String[] groupIds) {
        LampGroup lampGroup = new LampGroup();

        if ((lampIds != null) && (groupIds != null)) {
            lampGroup.setLamps(lampIds);
            lampGroup.setLampGroups(groupIds);
        }

        return lampGroup;
    }

    public static TransitionEffectV2 createTransitionEffect(boolean powerOn, int[] colorHsvt, long duration) {
        return createTransitionEffect(createLampStateFromView(powerOn, colorHsvt[0], colorHsvt[1], colorHsvt[2], colorHsvt[3]), duration);
    }

    public static TransitionEffectV2 createTransitionEffect(LampState lampState, long duration) {
        TransitionEffectV2 transitionEffect = null;

        if ((lampState != null) && (duration >= 0)) {
            transitionEffect = new TransitionEffectV2();
            transitionEffect.setLampState(lampState);
            transitionEffect.setTransitionPeriod(duration);
        }

        return transitionEffect;
    }

    public static TransitionEffectV2 createTransitionEffect(PresetDataModel presetModel, long duration) {
        TransitionEffectV2 transitionEffect = null;

        if ((presetModel != null) && (duration >= 0)) {
            transitionEffect = new TransitionEffectV2();
            transitionEffect.setPresetID(presetModel.id);
            transitionEffect.setTransitionPeriod(duration);
        }

        return transitionEffect;
    }

    public static PulseEffectV2 createPulseEffect(boolean fromPowerOn, int[] fromColorHsvt, boolean toPowerOn, int[] toColorHsvt, long period, long duration, long count) {
        return createPulseEffect(
                createLampStateFromView(fromPowerOn, fromColorHsvt[0], fromColorHsvt[1], fromColorHsvt[2], fromColorHsvt[3]),
                createLampStateFromView(toPowerOn, toColorHsvt[0], toColorHsvt[1], toColorHsvt[2], toColorHsvt[3]),
                period, duration, count);
    }

    public static PulseEffectV2 createPulseEffect(LampState fromState, LampState toState, long period, long duration, long count) {
        PulseEffectV2 pulseEffect = null;

        if (fromState != null && toState != null && period > 0 && duration > 0 && count > 0) {
            pulseEffect = new PulseEffectV2();
            pulseEffect.setFromLampState(fromState);
            pulseEffect.setToLampState(toState);

            pulseEffect.setPulsePeriod(period);
            pulseEffect.setPulseDuration(duration);
            pulseEffect.setNumPulses(count);
        }

        return pulseEffect;
    }

    public static PulseEffectV2 createPulseEffect(PresetDataModel fromPresetModel, PresetDataModel toPresetModel, long period, long duration, long count) {
        PulseEffectV2 pulseEffect = null;

        if (fromPresetModel != null && toPresetModel != null && period > 0 && duration > 0 && count > 0) {
            pulseEffect = new PulseEffectV2();
            pulseEffect.setFromPresetID(fromPresetModel.id);
            pulseEffect.setToPresetID(toPresetModel.id);

            pulseEffect.setPulsePeriod(period);
            pulseEffect.setPulseDuration(duration);
            pulseEffect.setNumPulses(count);
        }

        return pulseEffect;
    }

    public static SceneElement createSceneElement(String effectId, LampGroup groupMembers) {
        return groupMembers != null ? createSceneElement(effectId, groupMembers.getLamps(), groupMembers.getLampGroups()) : null;
    }

    public static SceneElement createSceneElement(String effectId, String[] lampIds, String[] lampGroupIds) {
        SceneElement sceneElement = null;

        if (effectId != null && lampIds != null && lampGroupIds != null) {
            sceneElement = new SceneElement();
            sceneElement.setEffectID(effectId);
            sceneElement.setLamps(lampIds);
            sceneElement.setLampGroups(lampGroupIds);
        }

        return sceneElement;
    }

    public static MasterScene createMasterScene(String[] sceneIds) {
        MasterScene masterScene = null;

        if (sceneIds != null) {
            masterScene = new MasterScene();
            masterScene.setScenes(sceneIds);
        }

        return masterScene;
    }

    public static SceneWithSceneElements createSceneWithSceneElements(String[] sceneElementIds) {
        SceneWithSceneElements sceneWithElements = null;

        if (sceneElementIds != null) {
            sceneWithElements = new SceneWithSceneElements();
            sceneWithElements.setSceneElements(sceneElementIds);
        }

        return sceneWithElements;
    }
}
