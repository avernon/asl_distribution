/**
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

import org.alljoyn.bus.BusAttachment;
import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.Status;

import junit.framework.TestCase;

public class BusObjectTest extends TestCase {
    public BusObjectTest(String name) {
        super(name);
    }

    static {
        System.loadLibrary("alljoyn_java");
    }

    private BusAttachment bus;

    public void setUp() throws Exception {
        bus = null;
    }

    public void tearDown() throws Exception {
        if (bus != null) {
            bus.disconnect();
            bus = null;
        }
    }

    public class Service implements BusObject,
                                    BusObjectListener {

        public boolean registered;

        public Service() {
            registered = false;
        }

        public void registered() { registered = true; }

        public void unregistered() { registered = false; }
    }

    public void testObjectRegistered() throws Exception {
        bus = new BusAttachment(getClass().getName());

        Service service = new Service();
        Status status = bus.registerBusObject(service, "/service");
        assertEquals(Status.OK, status);
        Thread.sleep(100);
        assertFalse(service.registered);

        status = bus.connect();
        assertEquals(Status.OK, status);
        Thread.sleep(100);
        assertTrue(service.registered);

        bus.unregisterBusObject(service);
        Thread.sleep(100);
        assertFalse(service.registered);
    }
}
