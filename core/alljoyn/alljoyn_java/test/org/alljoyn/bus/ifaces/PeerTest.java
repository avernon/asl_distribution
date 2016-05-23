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
import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.ProxyBusObject;
import org.alljoyn.bus.Status;
import org.alljoyn.bus.ifaces.DBusProxyObj;
import org.alljoyn.bus.ifaces.Peer;

import junit.framework.TestCase;

public class PeerTest extends TestCase {
    public PeerTest(String name) {
        super(name);
    }

    static {
        System.loadLibrary("alljoyn_java");
    }

    public class Service implements BusObject {
    }

    private BusAttachment bus;

    private Service service;

    private Peer peer;

    public void setUp() throws Exception {
        bus = new BusAttachment(getClass().getName());
        Status status = bus.connect();
        assertEquals(Status.OK, status);

        service = new Service();
        status = bus.registerBusObject(service, "/testobject");
        assertEquals(Status.OK, status);

        DBusProxyObj control = bus.getDBusProxyObj();
        DBusProxyObj.RequestNameResult res = control.RequestName("org.alljoyn.bus.ifaces.PeerTest",
                                                                DBusProxyObj.REQUEST_NAME_NO_FLAGS);
        assertEquals(DBusProxyObj.RequestNameResult.PrimaryOwner, res);

        ProxyBusObject remoteObj = bus.getProxyBusObject("org.alljoyn.bus.ifaces.PeerTest",
                                                         "/testobject", BusAttachment.SESSION_ID_ANY,
                                                         new Class<?>[] { Peer.class });
        peer = remoteObj.getInterface(Peer.class);
    }

    public void tearDown() throws Exception {
        peer = null;

        DBusProxyObj control = bus.getDBusProxyObj();
        DBusProxyObj.ReleaseNameResult res = control.ReleaseName("org.alljoyn.bus.ifaces.PeerTest");
        assertEquals(DBusProxyObj.ReleaseNameResult.Released, res);

        bus.unregisterBusObject(service);
        service = null;

        bus.disconnect();
        bus = null;
    }

    public void testPing() throws Exception {
        peer.Ping();
    }

    public void testGetMachineId() throws Exception {
        String id = peer.GetMachineId();
        // the id is a guid of type c2634fd9823215edf03157f2acf07611 and is not
        //known till runtime. for that.
        // reason we are only checking it is not an empty string.
        assertFalse(id.equals(""));
        assertTrue(id.length() > 4);
    }
}
