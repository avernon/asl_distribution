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

import org.alljoyn.bus.BusAttachment;
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

    public static class SampleService implements SampleInterface, BusObject {

        /** Do not use per-object synchronization since we want Pi() to execute concurrently */
        public void preDispatch() {
        }

        /** Do not use per-object synchronization since we want Pi() to execute concurrently */
        public void postDispatch() {
        }

        /**
         * This method is thread safe, but we mark it synchronized just to
         * illustrate how one would mix and match concurrent and serialized
         * methods.
         */
        public synchronized String Ping(String str) {
            return str;
        }

        /**
         * This method is thread safe, but we mark it synchronized just to
         * illustrate how one would mix and match concurrent and serialized
         * methods.
         */
        public synchronized String Concatenate(String arg1, String arg2) {
            return arg1+arg2;
        }

        /**
         * This method is thread safe, but we mark it synchronized just to
         * illustrate how one would mix and match concurrent and serialized
         * methods.
         */
        public synchronized int Fibonacci(int arg1) {
            int a=0,b=1;

            for (int i=0;i<arg1;i++) {
                a=a+b;
                b=a-b;
            }
            return a;
        }
        
        /**
         * A long running calculation used to illustrate how AllJoyn methods are
         * in fact dispatched concurrently.  By passing a very large <iterations>
         * count, this very slowly converging Gregory-Liebniz series can take
         * many seconds to complete.
         *
         * Note that this method must be thread-safe and the object and method not
         * synchronized/serialized for concurrent method execution to be achieved.
         */
        public double Pi(int iterations) {
            double piOverFour = 0.0;
            double sign = 1.0;
            for (int k = 0; k < iterations; ++k) {
                /*
                 * (-1)^k
                 * --------
                 * (2k + 1)
                 */
                double term = 1.0/(2.0 * k + 1);
                term *= sign;
                piOverFour += term;
                sign = -sign;
            }
            
            return piOverFour * 4.0;
        }
    }

    private static class MyBusListener extends BusListener {
        public void nameOwnerChanged(String busName, String previousOwner, String newOwner) {
            if ("com.my.well.known.name".equals(busName)) {
                System.out.println("BusAttachement.nameOwnerChanged(" + busName + ", " + previousOwner + ", " + newOwner);
            }
        }
    }

    public static void main(String[] args) {

        BusAttachment mBus;
        mBus = new BusAttachment("AppName", BusAttachment.RemoteMessage.Receive);

        Status status;

        SampleService mySampleService = new SampleService();

        status = mBus.registerBusObject(mySampleService, "/myService");
        if (status != Status.OK) {            
            return;
        }
        System.out.println("BusAttachment.registerBusObject successful");

        BusListener listener = new MyBusListener();
        mBus.registerBusListener(listener);

        status = mBus.connect();
        if (status != Status.OK) {

            return;
        }
        System.out.println("BusAttachment.connect successful on " + System.getProperty("org.alljoyn.bus.address"));        

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
