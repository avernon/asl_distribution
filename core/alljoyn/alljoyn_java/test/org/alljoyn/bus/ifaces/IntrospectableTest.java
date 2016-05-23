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

package org.alljoyn.bus.ifaces;

import org.alljoyn.bus.BusAttachment;
import org.alljoyn.bus.ProxyBusObject;
import org.alljoyn.bus.Status;
import org.alljoyn.bus.ifaces.Introspectable;

import junit.framework.TestCase;

public class IntrospectableTest extends TestCase {
    public IntrospectableTest(String name) {
        super(name);
    }

    static {
        System.loadLibrary("alljoyn_java");
    }

    private BusAttachment bus;

    public void setUp() throws Exception {
        bus = new BusAttachment(getClass().getName());
        Status status = bus.connect();
        assertEquals(Status.OK, status);
    }

    public void tearDown() throws Exception {
        bus.disconnect();
        bus = null;
    }

    public void testIntrospect() throws Exception {
        ProxyBusObject remoteObj = bus.getProxyBusObject("org.freedesktop.DBus",
                                                         "/org/freedesktop/DBus",
                                                         BusAttachment.SESSION_ID_ANY,
                                                         new Class<?>[] { Introspectable.class });
        Introspectable introspectable = remoteObj.getInterface(Introspectable.class);
        String data = introspectable.Introspect();
        // This test returns the xml definition of the org.freedesktop.DBus interface
        // rather than check the xml output we are only checking that the returned
        // string is not empty and contains the tag <interface name="org.freedesktop.DBus.Introspectable">
        assertFalse(data.equals(""));
        assertTrue(data.contains("<interface name=\"org.freedesktop.DBus.Introspectable\">"));
    }
}
