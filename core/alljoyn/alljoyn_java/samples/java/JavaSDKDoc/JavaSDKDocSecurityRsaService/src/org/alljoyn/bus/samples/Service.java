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
package org.alljoyn.bus.samples;

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

import org.alljoyn.bus.AuthListener;
import org.alljoyn.bus.BusAttachment;
import org.alljoyn.bus.BusException;
import org.alljoyn.bus.BusListener;
import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.Mutable;
import org.alljoyn.bus.SessionOpts;
import org.alljoyn.bus.SessionPortListener;
import org.alljoyn.bus.Status;

public class Service {
    static { 
        System.loadLibrary("alljoyn_java");
    }

    private static final short CONTACT_PORT=42;

    static boolean sessionEstablished = false;
    static int sessionId;

    public static class SecureService implements SecureInterface, BusObject {
        public String Ping(String inStr) throws BusException {
            System.out.println("Ping : " + inStr);
            System.out.println("Reply : " + inStr);
            return inStr;
        }
    }

    private static class MyBusListener extends BusListener {
        public void nameOwnerChanged(String busName, String previousOwner, String newOwner){
            if ("com.my.well.known.name".equals(busName)) {
                System.out.println("BusAttachement.nameOwnerChanged(" + busName + ", " + previousOwner + ", " + newOwner);
            }
        }
    }

    /* The RSA Key eXchange listener uses X.509 certificates to authenticate. */
    private static class RsaKeyXListener implements AuthListener {
        public boolean requested(String mechanism, String peerName, int count,
                String userName, AuthRequest[] requests) {
            System.out.println(String.format("AuthListener.requested(%s, %s, %d, %s, %s);", 
                    mechanism ,
                    peerName,
                    count,
                    userName,
                    AuthRequestsToString(requests)));

            /* Collect the requests we're interested in to simplify processing below. */
            PasswordRequest passwordRequest = null;
            CertificateRequest certificateRequest = null;
            VerifyRequest verifyRequest = null;

            for (AuthRequest request : requests) {
                if (request instanceof PasswordRequest) {
                    passwordRequest = (PasswordRequest) request;
                } else if (request instanceof CertificateRequest) {
                    certificateRequest = (CertificateRequest) request;
                } else if (request instanceof VerifyRequest) {
                    verifyRequest = (VerifyRequest) request;
                }
            }

            if (verifyRequest != null) {
                /* Verify a certificate chain supplied by the peer. */
                return true;
            } else if (certificateRequest != null) {
                /* 
                 * The engine is asking us for our certificate chain.  
                 *
                 * If we return true and do not supply the certificate chain, then the engine will
                 * create a self-signed certificate for us.  It will ask for the passphrase to use
                 * for the private key via a PasswordRequest. 
                 */
                return true;
            } else if (passwordRequest != null) {
                /*
                 * A password request under the ALLJOYN_RSA_KEYX mechanism is for the passphrase of the
                 * private key.
                 *
                 * PasswordRequest.isNewPassword() indicates if the engine has created a private key
                 * for us (as part of creating a self-signed certificate).  Otherwise it is
                 * expecting the passphrase for the existing private key.
                 */
                if (count <= 3) {
                    /*
                     * Request the passphrase of our private key via the UI.  We need to wait
                     * here for the user to enter the passphrase before we can return.  The
                     * latch takes care of the synchronization for us.
                     */
                    if(passwordRequest.isNewPassword()){
                        System.out.print("Enter password to generate new " +
                        "private key and certificate : ");
                    } else {
                        System.out.print("Please enter the private key password : ");
                    }
                    Scanner in = new Scanner(System.in);
                    String password = in.nextLine();
                    passwordRequest.setPassword(password.toCharArray());
                    return true;
                }
            }
            return false;
        }

        public void completed(String mechanism, String peerName, boolean authenticated) {
            if (!authenticated) {
                System.out.println("Authentication failed.");
            } else {
                System.out.println("Authentication successful.");
            }
        }

        private String AuthRequestsToString(AuthListener.AuthRequest[] requests) {
            String str;
            str = "[";
            for (AuthListener.AuthRequest request : requests) {
                if (request instanceof AuthListener.CertificateRequest) {
                    str += "CertificateRequest ";
                }
                if (request instanceof AuthListener.LogonEntryRequest) {
                    str += "LogonEntryRequest ";
                }
                if (request instanceof AuthListener.PrivateKeyRequest) {
                    str += "PrivateKeyRequest ";
                }
                if (request instanceof AuthListener.UserNameRequest) {
                    str += "UserNameRequest ";
                }
                if (request instanceof AuthListener.PasswordRequest) {
                    str += "PasswordRequest ";
                }
                if (request instanceof AuthListener.VerifyRequest) {
                    str += "VerifyRequest ";
                }
            }
            str += "]";
            return str;
        }
    }

    public static void main(String[] args) {

        BusAttachment mBus;
        mBus = new BusAttachment("RsaKeyXService", BusAttachment.RemoteMessage.Receive);

        Status status;

        SecureService mySecureService = new SecureService();

        status = mBus.registerBusObject(mySecureService, "/testRsaSecurity");
        if (status != Status.OK) {
            return;
        }
        System.out.println("BusAttachment.registerBusObject successful");

        BusListener listener = new MyBusListener();
        mBus.registerBusListener(listener);

        RsaKeyXListener authListener = new RsaKeyXListener();
        status = mBus.registerAuthListener("ALLJOYN_RSA_KEYX", authListener);
        if (status != Status.OK) {
            return;
        }
        System.out.println("BusAttachment.registerAuthListener successful");

        status = mBus.connect();
        if (status != Status.OK) {
            return;
        }
        System.out.println("BusAttachment.connect successful");        

        int flags = 0; //do not use any request name flags
        status = mBus.requestName("com.my.well.known.name", flags);
        if (status != Status.OK) {
            return;
        }
        System.out.println("BusAttachment.request 'com.my.well.known.name' successful");

        status = mBus.advertiseName("com.my.well.known.name", SessionOpts.TRANSPORT_ANY);
        if (status != Status.OK) {
            System.out.println("Status = " + status);
            mBus.releaseName("com.my.well.known.name");
            return;
        }
        System.out.println("BusAttachment.advertiseName 'com.my.well.known.name' successful");



        Mutable.ShortValue contactPort = new Mutable.ShortValue(CONTACT_PORT);

        SessionOpts sessionOpts = new SessionOpts();
        sessionOpts.traffic = SessionOpts.TRAFFIC_MESSAGES;
        sessionOpts.isMultipoint = false;
        sessionOpts.proximity = SessionOpts.PROXIMITY_ANY;
        sessionOpts.transports = SessionOpts.TRANSPORT_ANY;

        status = mBus.bindSessionPort(contactPort, sessionOpts, 
                new SessionPortListener() {
            public boolean acceptSessionJoiner(short sessionPort, String joiner, SessionOpts sessionOpts) {
                System.out.println("SessionPortListener.acceptSessionJoiner called");
                if (sessionPort == CONTACT_PORT) {
                    return true;
                } else {
                    return false;
                }
            }
            public void sessionJoined(short sessionPort, int id, String joiner) {
                System.out.println(String.format("SessionPortListener.sessionJoined(%d, %d, %s)", sessionPort, id, joiner));
                sessionId = id;
                sessionEstablished = true;
            }
        });
        if (status != Status.OK) {
            return;
        }
        System.out.println("BusAttachment.bindSessionPort successful");

        while (!sessionEstablished) {
            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
                System.out.println("Thead Exception caught");
                e.printStackTrace();
            }
        }

        System.out.println("BusAttachment session established");

        while (true) {
            try {
                Thread.sleep(10000);
            } catch (InterruptedException e) {
                System.out.println("Thead Exception caught");
                e.printStackTrace();
            }
        }
    }
}
