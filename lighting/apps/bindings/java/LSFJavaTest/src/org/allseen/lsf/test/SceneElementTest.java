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

import org.allseen.lsf.NativeLibraryLoader;
import org.allseen.lsf.SceneElement;

public class SceneElementTest extends TestCase {
    private static final NativeLibraryLoader LIBS = NativeLibraryLoader.LIBS;

    private SceneElement SceneElement;

    @Override
    protected void setUp() throws Exception
    {
        SceneElement = new SceneElement();

        super.setUp();
    }

    @Override
    protected void tearDown() throws Exception
    {
        SceneElement = null;

        super.tearDown();
    }

    public void testBasicSet()
    {
        String[] lampIDs = new String[] { "F", "G", "H" };
        String[] lampGroupIDs = new String[] { "A", "B", "C", "D", "E" };
        String effectID = "effectID-1";

        SceneElement.setLamps(lampIDs);
        SceneElement.setLampGroups(lampGroupIDs);
        SceneElement.setEffectID(effectID);

        assertTrue(Arrays.deepEquals(SceneElement.getLamps(), lampIDs));
        assertTrue(Arrays.deepEquals(SceneElement.getLampGroups(), lampGroupIDs));
        assertTrue(SceneElement.getEffectID().equals(effectID));

    }
}
