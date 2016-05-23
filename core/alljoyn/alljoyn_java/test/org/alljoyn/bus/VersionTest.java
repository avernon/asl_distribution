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
package org.alljoyn.bus;

import junit.framework.TestCase;

import org.alljoyn.bus.Version;

public class VersionTest  extends TestCase {
    static {
        System.loadLibrary("alljoyn_java");
    }

    // Since the version can change there are only a few things we can check
    // without creating complex parsing code.
    // 1. check that the code does not crash when the method is called
    // 2. make sure the value returned is a reasonable. If its a string make
    //    sure its not empty if its a number make sure its not negative.
    public void testGetVersion() {
        assertFalse(Version.get().isEmpty());
    }
    
    public void testGetBuildInfo() {
        assertFalse(Version.getBuildInfo().isEmpty());
    }
    
    public void testGetNumericVersion() {
        assertTrue(Version.getNumeric() >= 0);
    }
}
