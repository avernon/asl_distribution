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
import org.alljoyn.bus.BusException;
import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.Status;
import org.alljoyn.bus.ifaces.DBusProxyObj;

import junit.framework.TestCase;

public class InterfaceDescriptionTest extends TestCase {
    public InterfaceDescriptionTest(String name) {
        super(name);
    }

    static {
        System.loadLibrary("alljoyn_java");
    }

    public class Service implements SimpleInterface,
                                    BusObject {
        public String ping(String inStr) throws BusException { return inStr; }
    }

    public class ServiceC implements SimpleInterfaceC,
                                     BusObject {
        public String ping(String inStr) throws BusException { return inStr; }
        public String pong(String inStr) throws BusException { return inStr; }
    }

    private BusAttachment bus;

    public void setUp() throws Exception {
        bus = new BusAttachment(getClass().getName());

        Status status = bus.connect();
        assertEquals(Status.OK, status);

        DBusProxyObj control = bus.getDBusProxyObj();
        DBusProxyObj.RequestNameResult res = control.RequestName("org.alljoyn.bus.InterfaceDescriptionTest",
                                                                 DBusProxyObj.REQUEST_NAME_NO_FLAGS);
        assertEquals(DBusProxyObj.RequestNameResult.PrimaryOwner, res);
    }

    public void tearDown() throws Exception {
        DBusProxyObj control = bus.getDBusProxyObj();
        DBusProxyObj.ReleaseNameResult res = control.ReleaseName("org.alljoyn.bus.InterfaceDescriptionTest");
        assertEquals(DBusProxyObj.ReleaseNameResult.Released, res);

        bus.disconnect();
        bus = null;
    }

    public void testDifferentSignature() throws Exception {
        Service service = new Service();
        Status status = bus.registerBusObject(service, "/service");
        assertEquals(Status.OK, status);

        boolean thrown = false;
        try {
            SimpleInterfaceB proxy = bus.getProxyBusObject("org.alljoyn.bus.InterfaceDescriptionTest",
                "/service",
                BusAttachment.SESSION_ID_ANY,
                new Class<?>[] { SimpleInterfaceB.class }).getInterface(SimpleInterfaceB.class);
            proxy.ping(1);
        } catch (BusException ex) {
            thrown = true;
        }
        assertTrue(thrown);

        bus.unregisterBusObject(service);
    }

    public void testProxyInterfaceSubset() throws Exception {
        ServiceC service = new ServiceC();
        Status status = bus.registerBusObject(service, "/service");
        assertEquals(Status.OK, status);

        boolean thrown = false;
        try {
            SimpleInterface proxy = bus.getProxyBusObject("org.alljoyn.bus.InterfaceDescriptionTest", "/service",
                BusAttachment.SESSION_ID_ANY,
                new Class<?>[] { SimpleInterface.class }).getInterface(SimpleInterface.class);
            proxy.ping("str");
        } catch (BusException ex) {
            thrown = true;
        }
        assertTrue(thrown);

        bus.unregisterBusObject(service);
    }

    public void testProxyInterfaceSuperset() throws Exception {
        Service service = new Service();
        Status status = bus.registerBusObject(service, "/service");
        assertEquals(Status.OK, status);

        boolean thrown = false;
        try {
            SimpleInterfaceC proxy = bus.getProxyBusObject("org.alljoyn.bus.InterfaceDescriptionTest",
                "/service",
                BusAttachment.SESSION_ID_ANY,
                new Class<?>[] { SimpleInterfaceC.class }).getInterface(SimpleInterfaceC.class);
            proxy.ping("str");
        } catch (BusException ex) {
            thrown = true;
        }
        assertTrue(thrown);

        bus.unregisterBusObject(service);
    }
}
