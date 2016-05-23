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

import java.util.Map;
import java.util.TreeMap;
import java.util.Vector;

import junit.framework.TestCase;

import org.alljoyn.bus.ifaces.DBusProxyObj;

public class AddressBookTest extends TestCase {

    static {
        System.loadLibrary("alljoyn_java");
    }

    public AddressBookTest(String name) {
        super(name);
    }

    public class ContactService implements AddressBookInterface, BusObject {

        private Map<String, Contact> contactMap = new TreeMap<String, Contact>();

        public void setContact(Contact contact) {
            contactMap.put(contact.lastName, contact);
        }

        public Contact getContact(String lastName) throws BusException {
            Contact contact = contactMap.get(lastName);
            if (null == contact) {
                throw new BusException("No such contact");
            }
            return contact;
        }

        public Contact[] getContacts(String[] lastNames) {
            Vector<Contact> contactVec = new Vector<Contact>();
            for (String lastName: lastNames) {
                Contact c = contactMap.get(lastName);
                if (null != c) {
                    contactVec.add(c);
                }
            }
            return contactVec.toArray(new Contact[0]);
        }
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

    public void testAddressBook() throws Exception {

        /* Create a bus connection */
        BusAttachment bus = new BusAttachment(getClass().getName());
        bus.registerKeyStoreListener(new NullKeyStoreListener());

        /* Register the service */
        ContactService service = new ContactService();
        Status status = bus.registerBusObject(service, "/addressbook");
        if (Status.OK != status) {
            throw new BusException("BusAttachment.registerBusObject() failed: " + status.toString());
        }

        /* Register the authentication listener for the service */
        BusAuthListener authListener = new BusAuthListener();
        bus.registerAuthListener("ALLJOYN_SRP_KEYX", authListener);
        if (Status.OK != status) {
            throw new BusException("BusAttachment.registerAuthListener() failed with " + status.toString());
        }

        /* Connect the bus */
        status = bus.connect();
        if (Status.OK != status) {
            throw new BusException("BusAttachment.connect() failed with " + status.toString());
        }

        /* Request a well-known name */
        DBusProxyObj control = bus.getDBusProxyObj();
        DBusProxyObj.RequestNameResult res = control.RequestName("org.alljoyn.bus.addressbook",
                DBusProxyObj.REQUEST_NAME_NO_FLAGS);
        if (res != DBusProxyObj.RequestNameResult.PrimaryOwner) {
            throw new BusException("Failed to obtain well-known name");
        }

        /* Get a remote object */
        Class<?>[] ifaces = { AddressBookInterface.class };
        ProxyBusObject remoteObj = bus.getProxyBusObject("org.alljoyn.bus.addressbook",
                "/addressbook",
                BusAttachment.SESSION_ID_ANY,
                ifaces);
        AddressBookInterface proxy = remoteObj.getInterface(AddressBookInterface.class);

        /* Add a single contact */
        Contact contact = new Contact();
        contact.firstName = "first";
        contact.lastName = "last";
        contact.phoneNumberMap.put("home", "1234567");
        contact.phoneNumberMap.put("work", "7654321");
        proxy.setContact(contact);

        /* Get one or more contacts from service */
        String[] lastNames = new String[] { "last" };
        Contact[] contacts = proxy.getContacts(lastNames);

        /* Print out info on contacts */
        assertEquals("first", contacts[0].firstName);
        assertEquals("last", contacts[0].lastName);
        assertEquals("1234567", contacts[0].phoneNumberMap.get("home"));
        assertEquals("7654321", contacts[0].phoneNumberMap.get("work"));
    }
}

