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

import junit.framework.TestCase;

import org.allseen.lsf.LampState;
import org.allseen.lsf.NativeLibraryLoader;
import org.allseen.lsf.PulseEffectV2;

public class PulseEffectV2Test extends TestCase {
    private static final NativeLibraryLoader LIBS = NativeLibraryLoader.LIBS;

    private PulseEffectV2 PulseEffectV2;

    @Override
    protected void setUp() throws Exception
    {
        PulseEffectV2 = new PulseEffectV2();

        super.setUp();
    }

    @Override
    protected void tearDown() throws Exception
    {
        PulseEffectV2 = null;

        super.tearDown();
    }

    public void testBasicSet()
    {
        int pulsePeriod = 1000;
        int pulseDuration = 2000;
        int numPulses = 5;
        int fromBrightness = 1;
        int toBrightness = 2;

        LampState toLampState = new LampState();
        LampState fromLampState = new LampState();

        fromLampState.setBrightness(fromBrightness);
        toLampState.setBrightness(toBrightness);

        String fromPresetID = "PresetID-1";
        String toPresetID = "PresetID-2";

        PulseEffectV2.setToLampState(toLampState);
        PulseEffectV2.setFromLampState(fromLampState);
        PulseEffectV2.setToPresetID(toPresetID);
        PulseEffectV2.setFromPresetID(fromPresetID);
        PulseEffectV2.setPulsePeriod(pulsePeriod);
        PulseEffectV2.setPulseDuration(pulseDuration);
        PulseEffectV2.setNumPulses(numPulses);

        assertTrue(PulseEffectV2.getFromLampState().getBrightness() == fromBrightness);
        assertTrue(PulseEffectV2.getToLampState().getBrightness() == toBrightness);
        assertTrue(PulseEffectV2.getToPresetID().equals(toPresetID));
        assertTrue(PulseEffectV2.getFromPresetID().equals(fromPresetID));
        assertTrue(PulseEffectV2.getPulsePeriod() == pulsePeriod);
        assertTrue(PulseEffectV2.getPulseDuration() == pulseDuration);
        assertTrue(PulseEffectV2.getNumPulses() == numPulses);

    }
}
