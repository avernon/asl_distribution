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
package org.allseen.lsf.test;

import java.util.Arrays;

import junit.framework.TestCase;

import org.allseen.lsf.LampState;
import org.allseen.lsf.NativeLibraryLoader;
import org.allseen.lsf.PresetPulseEffect;
import org.allseen.lsf.PresetTransitionEffect;
import org.allseen.lsf.Scene;
import org.allseen.lsf.StatePulseEffect;
import org.allseen.lsf.StateTransitionEffect;

public class SceneTest extends TestCase {
    private static final NativeLibraryLoader LIBS = NativeLibraryLoader.LIBS;

    private static final String[] lampIDs1 = new String[] { "F1", "G1", "H1" };
    private static final String[] lampIDs2 = new String[] { "F2", "G2", "H2" };
    private static final String[] lampGroupIDs1 = new String[] { "A1", "B1", "C1", "D1", "E1" };
    private static final String[] lampGroupIDs2 = new String[] { "A2", "B2", "C2", "D2", "E2" };
    private static final String presetID1 = "PresetID-1";
    private static final String presetID2 = "PresetID-2";
    private static final String presetID3 = "PresetID-3";
    private static final String presetID4 = "PresetID-4";
    private static final int pulsePeriod = 1000;
    private static final int pulseDuration = 2000;
    private static final int pulseCount = 3;
    private static final int transitionPeriod = 3000;
    private static final int brightness1 = 123;
    private static final int brightness2 = 456;

    private LampState lampState1;
    private LampState lampState2;
    private PresetPulseEffect presetPulseEffect;
    private PresetTransitionEffect presetTransitionEffect;
    private StatePulseEffect statePulseEffect;
    private StateTransitionEffect stateTransitionEffect;

    private Scene scene;

    @Override
    protected void setUp() throws Exception
    {
        lampState1 = new LampState();
        lampState1.setBrightness(brightness1);

        lampState2 = new LampState();
        lampState2.setBrightness(brightness2);

        presetPulseEffect = new PresetPulseEffect();
        presetPulseEffect.setLamps(lampIDs1);
        presetPulseEffect.setLampGroups(lampGroupIDs1);
        presetPulseEffect.setFromPreset(presetID1);
        presetPulseEffect.setToPreset(presetID2);
        presetPulseEffect.setPulsePeriod(pulsePeriod);
        presetPulseEffect.setPulseDuration(pulseDuration);
        presetPulseEffect.setPulseCount(pulseCount);

        presetTransitionEffect = new PresetTransitionEffect();
        presetTransitionEffect.setLamps(lampIDs2);
        presetTransitionEffect.setLampGroups(lampGroupIDs2);
        presetTransitionEffect.setPresetID(presetID3);
        presetTransitionEffect.setTransitionPeriod(transitionPeriod);

        statePulseEffect = new StatePulseEffect();
        statePulseEffect.setLamps(lampIDs1);
        statePulseEffect.setLampGroups(lampGroupIDs2);
        statePulseEffect.setFromLampState(lampState1);
        statePulseEffect.setToLampState(lampState2);
        statePulseEffect.setPulsePeriod(pulsePeriod);
        statePulseEffect.setPulseDuration(pulseDuration);
        statePulseEffect.setPulseCount(pulseCount);

        stateTransitionEffect = new StateTransitionEffect();
        stateTransitionEffect.setTransitionPeriod(transitionPeriod);

        scene = new Scene();

        super.setUp();
    }

    @Override
    protected void tearDown() throws Exception
    {
        presetPulseEffect = null;
        presetTransitionEffect = null;
        statePulseEffect = null;
        stateTransitionEffect = null;

        super.tearDown();
    }

    public void testBasicSet()
    {
        scene.setPresetPulseEffects(new PresetPulseEffect[] {presetPulseEffect});
        scene.setPresetTransitionEffects(new PresetTransitionEffect[] {presetTransitionEffect});
        scene.setStatePulseEffects(new StatePulseEffect[] {statePulseEffect});
        scene.setStateTransitionEffects(new StateTransitionEffect[] {stateTransitionEffect});

        PresetPulseEffect[] presetPulseEffects = scene.getPresetPulseEffects();
        assertTrue(Arrays.deepEquals(presetPulseEffects[0].getLamps(), lampIDs1));
        assertTrue(Arrays.deepEquals(presetPulseEffects[0].getLampGroups(), lampGroupIDs1));
        assertTrue(presetPulseEffects[0].getFromPreset().equals(presetID1));
        assertTrue(presetPulseEffects[0].getToPreset().equals(presetID2));
        assertTrue(presetPulseEffects[0].getPulsePeriod() == pulsePeriod);
        assertTrue(presetPulseEffects[0].getPulseDuration() == pulseDuration);
        assertTrue(presetPulseEffects[0].getPulseCount() == pulseCount);

        PresetTransitionEffect[] presetTransitionEffects = scene.getPresetTransitionEffects();
        assertTrue(Arrays.deepEquals(presetTransitionEffects[0].getLamps(), lampIDs2));
        assertTrue(Arrays.deepEquals(presetTransitionEffects[0].getLampGroups(), lampGroupIDs2));
        assertTrue(presetTransitionEffects[0].getPresetID().equals(presetID3));
        assertTrue(presetTransitionEffects[0].getTransitionPeriod() == transitionPeriod);

        StatePulseEffect[] statePulseEffects = scene.getStatePulseEffects();
        assertTrue(Arrays.deepEquals(statePulseEffects[0].getLamps(), lampIDs1));
        assertTrue(Arrays.deepEquals(statePulseEffects[0].getLampGroups(), lampGroupIDs2));
        assertTrue(statePulseEffects[0].getFromLampState().getBrightness() == brightness1);
        assertTrue(statePulseEffects[0].getToLampState().getBrightness() == brightness2);
        assertTrue(statePulseEffects[0].getPulsePeriod() == pulsePeriod);
        assertTrue(statePulseEffects[0].getPulseDuration() == pulseDuration);
        assertTrue(statePulseEffects[0].getPulseCount() == pulseCount);

        StateTransitionEffect[] stateTransitionEffects = scene.getStateTransitionEffects();
        assertTrue(stateTransitionEffects[0].getLamps().length == 0);
        assertTrue(stateTransitionEffects[0].getLampGroups().length == 0);
        assertTrue(stateTransitionEffects[0].getTransitionPeriod() == transitionPeriod);
    }
}
