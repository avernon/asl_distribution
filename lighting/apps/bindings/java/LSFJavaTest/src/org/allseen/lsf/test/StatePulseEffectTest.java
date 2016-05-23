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
import org.allseen.lsf.StatePulseEffect;

public class StatePulseEffectTest extends TestCase {
    private static final NativeLibraryLoader LIBS = NativeLibraryLoader.LIBS;

    private StatePulseEffect statePulseEffect;

    @Override
    protected void setUp() throws Exception
    {
        statePulseEffect = new StatePulseEffect();

        super.setUp();
    }

    @Override
    protected void tearDown() throws Exception
    {
        statePulseEffect = null;

        super.tearDown();
    }

    public void testBasicSet()
    {
        String[] lampIDs = new String[] { "F", "G", "H" };
        String[] lampGroupIDs = new String[] { "A", "B", "C", "D", "E" };
        int pulsePeriod = 1000;
        int pulseDuration = 2000;
        int pulseCount = 3;
        int fromBrightness = 1;
        int toBrightness = 2;
        LampState fromLampState = new LampState();
        LampState toLampState = new LampState();

        fromLampState.setBrightness(fromBrightness);
        toLampState.setBrightness(toBrightness);

        statePulseEffect.setLamps(lampIDs);
        statePulseEffect.setLampGroups(lampGroupIDs);
        statePulseEffect.setPulsePeriod(pulsePeriod);
        statePulseEffect.setPulseDuration(pulseDuration);
        statePulseEffect.setPulseCount(pulseCount);
        statePulseEffect.setFromLampState(fromLampState);
        statePulseEffect.setToLampState(toLampState);

        assertTrue(Arrays.deepEquals(statePulseEffect.getLamps(), lampIDs));
        assertTrue(Arrays.deepEquals(statePulseEffect.getLampGroups(), lampGroupIDs));
        assertTrue(statePulseEffect.getPulsePeriod() == pulsePeriod);
        assertTrue(statePulseEffect.getPulseDuration() == pulseDuration);
        assertTrue(statePulseEffect.getPulseCount() == pulseCount);
        assertTrue(statePulseEffect.getFromLampState().getBrightness() == fromBrightness);
        assertTrue(statePulseEffect.getToLampState().getBrightness() == toBrightness);
    }
}
