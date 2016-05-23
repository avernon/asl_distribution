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
import org.alljoyn.bus.ProxyBusObject;
import org.alljoyn.bus.Status;
import org.alljoyn.bus.Variant;
import org.alljoyn.bus.ifaces.Properties;

import java.util.Map;

import junit.framework.TestCase;

public class PropsTestSecure extends TestCase {

    static {
        System.loadLibrary("alljoyn_java");
    }

    public PropsTestSecure(String name) {
        super(name);
    }

    public class SecureService implements PropsInterfaceSecure, BusObject {

        private String stringProperty = "Hello";

        private int intProperty = 6;

        public String getStringProp() { return stringProperty; }

        public void setStringProp(String stringProperty) { this.stringProperty = stringProperty; }

        public int getIntProp() { return intProperty; }

        public void setIntProp(int intProperty) { this.intProperty = intProperty; }
    }

    public class Service implements PropsInterface, BusObject {

        private String stringProperty = "Hello";

        private int intProperty = 6;

        public String getStringProp() { return stringProperty; }

        public void setStringProp(String stringProperty) { this.stringProperty = stringProperty; }

        public int getIntProp() { return intProperty; }

        public void setIntProp(int intProperty) { this.intProperty = intProperty; }

        public String ping(String str) throws BusException {
            return str;
        }
    }

    BusAttachment serviceBus;
    BusAttachment clientBus;
    SrpAuthListener serviceAuthListener;
    SrpAuthListener clientAuthListener;

    private TestKeyStoreListener serviceKeyStoreListener;
    private TestKeyStoreListener clientKeyStoreListener;

    static private String INTERFACE_NAME = "org.alljoyn.bus.PropsInterfaceSecure";
    static private String UNSECURE_INTERFACE_NAME = "org.alljoyn.bus.PropsInterface";
    static private String OBJECT_PATH    = "/org/alljoyn/test/secureproperties";

    /*
     * In memory keystore listener
     */
    public class TestKeyStoreListener implements KeyStoreListener {
        private byte[] keys;
        public boolean saveKeys;
        public byte[] getKeys() { return keys; }
        public char[] getPassword() { return "password".toCharArray(); }
        public void putKeys(byte[] keys) {
            if (saveKeys) {
                this.keys = keys;
            }
        }
    }

    /*
     * SRP Key Exchange Authlistener
     */
    public class SrpAuthListener implements AuthListener {
        public boolean requestPasswordFlag;
        public boolean completedFlag;

        public SrpAuthListener() {
            requestPasswordFlag = false;
            completedFlag = false;
        }

        public boolean requested(String mechanism, String authPeer, int count, String userName,
                AuthRequest[] requests) {
            assertTrue("ALLJOYN_SRP_KEYX".equals(mechanism));
            for(AuthRequest request : requests){
                if(request instanceof PasswordRequest) {
                    ((PasswordRequest) request).setPassword("123456".toCharArray());
                    requestPasswordFlag = true;
                }
            }
            return true;
        }

        public void completed(String mechanism, String authPeer, boolean authenticated) {
            assertTrue("ALLJOYN_SRP_KEYX".equals(mechanism));
            assertTrue(authenticated);
            completedFlag = authenticated;
        }
    }

    public void setUp() throws Exception {
        serviceBus = new BusAttachment(getClass().getName());
        serviceKeyStoreListener = new TestKeyStoreListener();
        serviceBus.registerKeyStoreListener(serviceKeyStoreListener);

        serviceAuthListener = new SrpAuthListener();
        assertEquals(Status.OK, serviceBus.registerAuthListener("ALLJOYN_SRP_KEYX", serviceAuthListener));
        assertEquals(Status.OK, serviceBus.connect());
        serviceBus.clearKeyStore();

        clientBus = new BusAttachment(getClass().getName());
        clientKeyStoreListener = new TestKeyStoreListener();
        clientBus.registerKeyStoreListener(clientKeyStoreListener);

        clientAuthListener = new SrpAuthListener();
        assertEquals(Status.OK, clientBus.registerAuthListener("ALLJOYN_SRP_KEYX", clientAuthListener));
        assertEquals(Status.OK, clientBus.connect());
        clientBus.clearKeyStore();
    }

    public void tearDown() throws Exception {
        if (serviceBus != null) {
            serviceBus.disconnect();
            serviceBus.release();
            serviceBus = null;
        }

        if (clientBus != null) {
            clientBus.disconnect();
            clientBus.release();
            clientBus = null;
        }
    }

    public void testgetProp() throws Exception {
        /* Register the service */
        SecureService service = new SecureService();
        Status status = serviceBus.registerBusObject(service, OBJECT_PATH);
        if (Status.OK != status) {
            throw new BusException("BusAttachment.registerBusObject() failed: " + status.toString());
        }

        /* Get a remote object */
        ProxyBusObject proxy = clientBus.getProxyBusObject(serviceBus.getUniqueName(),
                                                         OBJECT_PATH,
                                                         BusAttachment.SESSION_ID_ANY,
                                                         new Class<?>[] { PropsInterfaceSecure.class });
        PropsInterfaceSecure iface = proxy.getInterface(PropsInterfaceSecure.class);

        /* Get a property */
        assertEquals("Hello", iface.getStringProp());

        assertTrue(serviceAuthListener.requestPasswordFlag);
        assertTrue(clientAuthListener.requestPasswordFlag);
        assertTrue(serviceAuthListener.completedFlag);
        assertTrue(clientAuthListener.completedFlag);
   }

    public void testsetProp() throws Exception {
        /* Register the service */
        SecureService service = new SecureService();
        Status status = serviceBus.registerBusObject(service, OBJECT_PATH);
        if (Status.OK != status) {
            throw new BusException("BusAttachment.registerBusObject() failed: " + status.toString());
        }

        /* Get a remote object */
        ProxyBusObject proxy = clientBus.getProxyBusObject(serviceBus.getUniqueName(),
                                                         OBJECT_PATH,
                                                         BusAttachment.SESSION_ID_ANY,
                                                         new Class<?>[] { PropsInterfaceSecure.class,
                                                                          Properties.class });
        PropsInterfaceSecure iface = proxy.getInterface(PropsInterfaceSecure.class);

        /* Get a property */
        assertEquals("Hello", iface.getStringProp());

        /* Set a property */
        iface.setStringProp("MyNewValue");

        /* Get all of the properties of the interface */
        assertEquals("MyNewValue", iface.getStringProp());

        assertTrue(serviceAuthListener.requestPasswordFlag);
        assertTrue(clientAuthListener.requestPasswordFlag);
        assertTrue(serviceAuthListener.completedFlag);
        assertTrue(clientAuthListener.completedFlag);
   }

    public void testgetAllProp() throws Exception {
        /* Register the service */
        SecureService service = new SecureService();
        Status status = serviceBus.registerBusObject(service, OBJECT_PATH);
        if (Status.OK != status) {
            throw new BusException("BusAttachment.registerBusObject() failed: " + status.toString());
        }

        /* Get a remote object */
        ProxyBusObject proxy = clientBus.getProxyBusObject(serviceBus.getUniqueName(),
                                                         OBJECT_PATH,
                                                         BusAttachment.SESSION_ID_ANY,
                                                         new Class<?>[] { PropsInterfaceSecure.class,
                                                                          Properties.class }, true);

        /* Use the org.freedesktop.DBus.Properties interface to get all the properties */
        Properties properties = proxy.getInterface(Properties.class);
        Map<String, Variant> map = properties.GetAll(INTERFACE_NAME);
        assertEquals("Hello", map.get("StringProp").getObject(String.class));
        assertEquals(6, (int)map.get("IntProp").getObject(Integer.class));

        assertTrue(serviceAuthListener.requestPasswordFlag);
        assertTrue(clientAuthListener.requestPasswordFlag);
        assertTrue(serviceAuthListener.completedFlag);
        assertTrue(clientAuthListener.completedFlag);
   }

    public void testgetProperty() throws Exception {
        /* Register the service */
        SecureService service = new SecureService();
        Status status = serviceBus.registerBusObject(service, OBJECT_PATH);
        if (Status.OK != status) {
            throw new BusException("BusAttachment.registerBusObject() failed: " + status.toString());
        }

        /* Get a remote object */
        ProxyBusObject proxy = clientBus.getProxyBusObject(serviceBus.getUniqueName(),
                                                         OBJECT_PATH,
                                                         BusAttachment.SESSION_ID_ANY,
                                                         new Class<?>[] { PropsInterfaceSecure.class });

        /* Get a property */
        assertEquals("Hello", proxy.getProperty(PropsInterfaceSecure.class, "StringProp").getObject(String.class));

        assertTrue(serviceAuthListener.requestPasswordFlag);
        assertTrue(clientAuthListener.requestPasswordFlag);
        assertTrue(serviceAuthListener.completedFlag);
        assertTrue(clientAuthListener.completedFlag);
   }

    public void testsetProperty() throws Exception {
        /* Register the service */
        SecureService service = new SecureService();
        Status status = serviceBus.registerBusObject(service, OBJECT_PATH);
        if (Status.OK != status) {
            throw new BusException("BusAttachment.registerBusObject() failed: " + status.toString());
        }

        /* Get a remote object */
        ProxyBusObject proxy = clientBus.getProxyBusObject(serviceBus.getUniqueName(),
                                                         OBJECT_PATH,
                                                         BusAttachment.SESSION_ID_ANY,
                                                         new Class<?>[] { PropsInterfaceSecure.class,
                                                                          Properties.class });

        /* Get a property */
        assertEquals("Hello", proxy.getProperty(PropsInterfaceSecure.class, "StringProp").getObject(String.class));

        /* Set a property */
        proxy.setProperty(PropsInterfaceSecure.class, "StringProp", new Variant("MyNewValue"));

        /* Get all of the properties of the interface */
        assertEquals("MyNewValue", proxy.getProperty(PropsInterfaceSecure.class, "StringProp").getObject(String.class));

        assertTrue(serviceAuthListener.requestPasswordFlag);
        assertTrue(clientAuthListener.requestPasswordFlag);
        assertTrue(serviceAuthListener.completedFlag);
        assertTrue(clientAuthListener.completedFlag);
   }

    public void testgetAllProperties() throws Exception {
        /* Register the service */
        SecureService service = new SecureService();
        Status status = serviceBus.registerBusObject(service, OBJECT_PATH);
        if (Status.OK != status) {
            throw new BusException("BusAttachment.registerBusObject() failed: " + status.toString());
        }

        /* Get a remote object */
        ProxyBusObject proxy = clientBus.getProxyBusObject(serviceBus.getUniqueName(),
                                                         OBJECT_PATH,
                                                         BusAttachment.SESSION_ID_ANY,
                                                         new Class<?>[] { PropsInterfaceSecure.class });

        Map<String, Variant> map = proxy.getAllProperties(PropsInterfaceSecure.class);
        assertEquals("Hello", map.get("StringProp").getObject(String.class));
        assertEquals(6, (int)map.get("IntProp").getObject(Integer.class));

        assertTrue(serviceAuthListener.requestPasswordFlag);
        assertTrue(clientAuthListener.requestPasswordFlag);
        assertTrue(serviceAuthListener.completedFlag);
        assertTrue(clientAuthListener.completedFlag);
   }

    public void testgetPropUsingObjSecurity() throws Exception {
        /* Register the service */
        Service service = new Service();
        Status status = serviceBus.registerBusObject(service, OBJECT_PATH, true);
        if (Status.OK != status) {
            throw new BusException("BusAttachment.registerBusObject() failed: " + status.toString());
        }

        /* Get a remote object */
        ProxyBusObject proxy = clientBus.getProxyBusObject(serviceBus.getUniqueName(),
                                                         OBJECT_PATH,
                                                         BusAttachment.SESSION_ID_ANY,
                                                         new Class<?>[] { PropsInterface.class }, true);
        PropsInterface iface = proxy.getInterface(PropsInterface.class);

        /* Get a property */
        assertEquals("Hello", iface.getStringProp());

        assertTrue(serviceAuthListener.requestPasswordFlag);
        assertTrue(clientAuthListener.requestPasswordFlag);
        assertTrue(serviceAuthListener.completedFlag);
        assertTrue(clientAuthListener.completedFlag);
   }

    public void testsetPropUsingObjSecurity() throws Exception {
        /* Register the service */
        Service service = new Service();
        Status status = serviceBus.registerBusObject(service, OBJECT_PATH, true);
        if (Status.OK != status) {
            throw new BusException("BusAttachment.registerBusObject() failed: " + status.toString());
        }

        /* Get a remote object */
        ProxyBusObject proxy = clientBus.getProxyBusObject(serviceBus.getUniqueName(),
                                                         OBJECT_PATH,
                                                         BusAttachment.SESSION_ID_ANY,
                                                         new Class<?>[] { PropsInterface.class }, true);
        PropsInterface iface = proxy.getInterface(PropsInterface.class);

        /* Get a property */
        assertEquals("Hello", iface.getStringProp());

        /* Set a property */
        iface.setStringProp("MyNewValue");

        /* Get all of the properties of the interface */
        assertEquals("MyNewValue", iface.getStringProp());

        assertTrue(serviceAuthListener.requestPasswordFlag);
        assertTrue(clientAuthListener.requestPasswordFlag);
        assertTrue(serviceAuthListener.completedFlag);
        assertTrue(clientAuthListener.completedFlag);
   }

    public void testgetAllPropUsingObjSecurity() throws Exception {
        /* Register the service */
        Service service = new Service();
        Status status = serviceBus.registerBusObject(service, OBJECT_PATH, true);
        if (Status.OK != status) {
            throw new BusException("BusAttachment.registerBusObject() failed: " + status.toString());
        }

        /* Get a remote object */
        ProxyBusObject proxy = clientBus.getProxyBusObject(serviceBus.getUniqueName(),
                                                         OBJECT_PATH,
                                                         BusAttachment.SESSION_ID_ANY,
                                                         new Class<?>[] { PropsInterface.class,
                                                                          Properties.class }, true);
        proxy.getInterface(PropsInterface.class);

        /* Use the org.freedesktop.DBus.Properties interface to get all the properties */
        Properties properties = proxy.getInterface(Properties.class);
        Map<String, Variant> map = properties.GetAll(UNSECURE_INTERFACE_NAME);
        assertEquals("Hello", map.get("StringProp").getObject(String.class));
        assertEquals(6, (int)map.get("IntProp").getObject(Integer.class));

        assertTrue(serviceAuthListener.requestPasswordFlag);
        assertTrue(clientAuthListener.requestPasswordFlag);
        assertTrue(serviceAuthListener.completedFlag);
        assertTrue(clientAuthListener.completedFlag);
   }

    public void testgetPropertyUsingObjSecurity() throws Exception {
        /* Register the service */
        Service service = new Service();
        Status status = serviceBus.registerBusObject(service, OBJECT_PATH, true);
        if (Status.OK != status) {
            throw new BusException("BusAttachment.registerBusObject() failed: " + status.toString());
        }

        /* Get a remote object */
        ProxyBusObject proxy = clientBus.getProxyBusObject(serviceBus.getUniqueName(),
                                                         OBJECT_PATH,
                                                         BusAttachment.SESSION_ID_ANY,
                                                         new Class<?>[] { PropsInterface.class }, true);
        //PropsInterfaceSecure iface = proxy.getInterface(PropsInterfaceSecure.class);

        /* Get a property */
        assertEquals("Hello", proxy.getProperty(PropsInterface.class, "StringProp").getObject(String.class));

        assertTrue(serviceAuthListener.requestPasswordFlag);
        assertTrue(clientAuthListener.requestPasswordFlag);
        assertTrue(serviceAuthListener.completedFlag);
        assertTrue(clientAuthListener.completedFlag);
   }

    public void testsetPropertyUsingObjSecurity() throws Exception {
        /* Register the service */
        Service service = new Service();
        Status status = serviceBus.registerBusObject(service, OBJECT_PATH, true);
        if (Status.OK != status) {
            throw new BusException("BusAttachment.registerBusObject() failed: " + status.toString());
        }

        /* Get a remote object */
        ProxyBusObject proxy = clientBus.getProxyBusObject(serviceBus.getUniqueName(),
                                                         OBJECT_PATH,
                                                         BusAttachment.SESSION_ID_ANY,
                                                         new Class<?>[] { PropsInterface.class,
                                                                          Properties.class }, true);

        /* Get a property */
        assertEquals("Hello", proxy.getProperty(PropsInterface.class, "StringProp").getObject(String.class));

        /* Set a property */
        proxy.setProperty(PropsInterface.class, "StringProp", new Variant("MyNewValue"));

        /* Get all of the properties of the interface */
        assertEquals("MyNewValue", proxy.getProperty(PropsInterface.class, "StringProp").getObject(String.class));

        assertTrue(serviceAuthListener.requestPasswordFlag);
        assertTrue(clientAuthListener.requestPasswordFlag);
        assertTrue(serviceAuthListener.completedFlag);
        assertTrue(clientAuthListener.completedFlag);
   }

    public void testgetAllPropertiesUsingObjSecurity() throws Exception {
        /* Register the service */
        Service service = new Service();
        Status status = serviceBus.registerBusObject(service, OBJECT_PATH, true);
        if (Status.OK != status) {
            throw new BusException("BusAttachment.registerBusObject() failed: " + status.toString());
        }

        /* Get a remote object */
        ProxyBusObject proxy = clientBus.getProxyBusObject(serviceBus.getUniqueName(),
                                                         OBJECT_PATH,
                                                         BusAttachment.SESSION_ID_ANY,
                                                         new Class<?>[] { PropsInterface.class }, true);

        Map<String, Variant> map = proxy.getAllProperties(PropsInterface.class);
        assertEquals("Hello", map.get("StringProp").getObject(String.class));
        assertEquals(6, (int)map.get("IntProp").getObject(Integer.class));

        assertTrue(serviceAuthListener.requestPasswordFlag);
        assertTrue(clientAuthListener.requestPasswordFlag);
        assertTrue(serviceAuthListener.completedFlag);
        assertTrue(clientAuthListener.completedFlag);
   }
}