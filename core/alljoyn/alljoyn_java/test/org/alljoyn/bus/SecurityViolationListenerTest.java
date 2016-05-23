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
import org.alljoyn.bus.ifaces.DBusProxyObj;

import junit.framework.TestCase;

public class SecurityViolationListenerTest extends TestCase {
    static {
        System.loadLibrary("alljoyn_java");
    }

    private BusAttachment bus;
    private BusAttachment serviceBus;
    private SecureService service;
    private SimpleInterface proxy;

    public class SecureService implements SecureInterface, BusObject {
        public String ping(String str) { return str; }
    }

    public class BusAuthListener implements AuthListener {
        public boolean requested(String mechanism, String authPeer, int count, String userName,
                                 AuthRequest[] requests) {
            for (AuthRequest request : requests) {
                if (request instanceof PasswordRequest) {
                    ((PasswordRequest) request).setPassword("123456".toCharArray());
                } else if (request instanceof ExpirationRequest) {
                } else {
                    return false;
                }
            }
            return true;
        }

        public void completed(String mechanism, String authPeer, boolean authenticated) {}
    }

    public SecurityViolationListenerTest(String name) {
        super(name);
    }

    public void setUp() throws Exception {
        serviceBus = new BusAttachment(getClass().getName());
        serviceBus.registerKeyStoreListener(new NullKeyStoreListener());
        assertEquals(Status.OK, serviceBus.registerAuthListener("ALLJOYN_SRP_KEYX", new BusAuthListener()));
        service = new SecureService();
        assertEquals(Status.OK, serviceBus.registerBusObject(service, "/secure"));
        assertEquals(Status.OK, serviceBus.connect());
        DBusProxyObj control = serviceBus.getDBusProxyObj();
        assertEquals(DBusProxyObj.RequestNameResult.PrimaryOwner,
                     control.RequestName("org.alljoyn.bus.BusAttachmentTest",
                                         DBusProxyObj.REQUEST_NAME_NO_FLAGS));

        bus = new BusAttachment(getClass().getName());
        assertEquals(Status.OK, bus.connect());
        ProxyBusObject proxyObj = bus.getProxyBusObject("org.alljoyn.bus.BusAttachmentTest",
                                                        "/secure",
                                                        BusAttachment.SESSION_ID_ANY,
                                                        new Class<?>[] { SimpleInterface.class });
        proxy = proxyObj.getInterface(SimpleInterface.class);
    }

    public void tearDown() throws Exception {
        proxy = null;
        bus.disconnect();
        bus = null;

        DBusProxyObj control = serviceBus.getDBusProxyObj();
        assertEquals(DBusProxyObj.ReleaseNameResult.Released,
                     control.ReleaseName("org.alljoyn.bus.BusAttachmentTest"));
        serviceBus.disconnect();
        serviceBus.unregisterBusObject(service);
        serviceBus = null;
    }

    private int violation;

    /* ALLJOYN-74 */
    public void testSecurityViolation() throws Exception {
        violation = 0;
        serviceBus.registerSecurityViolationListener(new SecurityViolationListener() {
                public void violated(Status status) {
                    ++violation;
                    MessageContext ctx = bus.getMessageContext();
                    assertEquals(false, ctx.isUnreliable);
                    assertEquals("/secure", ctx.objectPath);
                    assertEquals("org.alljoyn.bus.SimpleInterface", ctx.interfaceName);
                    assertEquals("Ping", ctx.memberName);
                    assertEquals("s", ctx.signature);
                    assertEquals("", ctx.authMechanism);
                }
            });
        boolean thrown = false;
        try {
            proxy.ping("hello");
        } catch (ErrorReplyBusException ex) {
            thrown = true;
        }
        assertTrue(thrown);
        assertEquals(1, violation);
    }
}
