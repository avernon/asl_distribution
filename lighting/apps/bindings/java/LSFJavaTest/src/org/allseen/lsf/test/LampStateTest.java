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

public class LampStateTest extends TestCase {
    private static final NativeLibraryLoader LIBS = NativeLibraryLoader.LIBS;

    private LampState lampState;

    @Override
    protected void setUp() throws Exception
    {
        lampState = new LampState();

        super.setUp();
    }

    @Override
    protected void tearDown() throws Exception
    {
        lampState = null;

        super.tearDown();
    }

    public void testLowValues()
    {
        boolean onOff = true;
        long hue = 500;
        long saturation = 600;
        long brightness = 700;
        long colorTemp = 800;

        lampState.setOnOff(onOff);
        lampState.setHue(hue);
        lampState.setSaturation(saturation);
        lampState.setBrightness(brightness);
        lampState.setColorTemp(colorTemp);

        assertTrue(lampState.getOnOff() == onOff);
        assertTrue(lampState.getHue() == hue);
        assertTrue(lampState.getSaturation() == saturation);
        assertTrue(lampState.getBrightness() == brightness);
        assertTrue(lampState.getColorTemp() == colorTemp);
    }

    public void testHighValues()
    {
        boolean onOff = true;
        long hue = 2200000500L;
        long saturation = 2200000600L;
        long brightness = 2200000700L;
        long colorTemp = 2200000800L;

        lampState.setOnOff(onOff);
        lampState.setHue(hue);
        lampState.setSaturation(saturation);
        lampState.setBrightness(brightness);
        lampState.setColorTemp(colorTemp);

        assertTrue(lampState.getOnOff() == onOff);
        assertTrue(lampState.getHue() == hue);
        assertTrue(lampState.getSaturation() == saturation);
        assertTrue(lampState.getBrightness() == brightness);
        assertTrue(lampState.getColorTemp() == colorTemp);
    }
}
