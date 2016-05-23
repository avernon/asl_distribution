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
import org.allseen.lsf.TransitionEffectV2;

public class TransitionEffectV2Test extends TestCase {
    private static final NativeLibraryLoader LIBS = NativeLibraryLoader.LIBS;

    private TransitionEffectV2 TransitionEffectV2;

    @Override
    protected void setUp() throws Exception
    {
        TransitionEffectV2 = new TransitionEffectV2();

        super.setUp();
    }

    @Override
    protected void tearDown() throws Exception
    {
        TransitionEffectV2 = null;

        super.tearDown();
    }

    public void testBasicSet()
    {
        int transitionPeriod = 100;
        LampState lampState = new LampState();
        String presetID = "PresetID-1";
        int brightness = 3;

        lampState.setBrightness(brightness);

        TransitionEffectV2.setLampState(lampState);
        TransitionEffectV2.setPresetID(presetID);
        TransitionEffectV2.setTransitionPeriod(transitionPeriod);

        assertTrue(TransitionEffectV2.getLampState().getBrightness() == brightness);
        assertTrue(TransitionEffectV2.getPresetID().equals(presetID));
        assertTrue(TransitionEffectV2.getTransitionPeriod()== transitionPeriod);

    }
}
