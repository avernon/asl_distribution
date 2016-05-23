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
import org.alljoyn.bus.SignalEmitter;
import org.alljoyn.bus.Status;

import junit.framework.TestCase;

public class SignalEmitterTest extends TestCase {
    public SignalEmitterTest(String name) {
        super(name);
    }

    static {
        System.loadLibrary("alljoyn_java");
    }

    private int uniquifier = 0;
    private String genUniqueName(BusAttachment bus) {
        return "test.x" + bus.getGlobalGUIDString() + ".x" + uniquifier++;
    }

    private BusAttachment bus;

    public class Emitter implements EmitterInterface,
                                    BusObject {

        private SignalEmitter local;
        private SignalEmitter global;
        private SignalEmitter emitter;

        public Emitter() {
            local = new SignalEmitter(this);
            global = new SignalEmitter(this, SignalEmitter.GlobalBroadcast.On);
            emitter = local;
        }

        public void emit(String string) throws BusException {
            emitter.getInterface(EmitterInterface.class).emit(string);
        }

        public void setTimeToLive(int timeToLive) {
            local.setTimeToLive(timeToLive);
            global.setTimeToLive(timeToLive);
        }

        public void setCompressHeader(boolean compress) {
            local.setCompressHeader(compress);
            global.setCompressHeader(compress);
        }

        public void setSessionlessFlag(boolean isSessionless) {
            local.setSessionlessFlag(isSessionless);
            global.setSessionlessFlag(isSessionless);
        }

        public void setGlobalBroadcast(boolean globalBroadcast) {
            emitter = globalBroadcast ? global : local;
        }

        public MessageContext getMessageContext() {
            return local.getMessageContext();
        }

        public Status cancelSessionlessSignal(int serialNum) {
            return local.cancelSessionlessSignal(serialNum);
        }
    }

    private Emitter emitter;

    public void setUp() throws Exception {
        bus = new BusAttachment(getClass().getName());
        Status status = bus.connect();
        assertEquals(Status.OK, status);

        emitter = new Emitter();
        status = bus.registerBusObject(emitter, "/emitter");
        assertEquals(Status.OK, status);

        assertEquals(Status.OK, bus.registerSignalHandler("org.alljoyn.bus.EmitterInterface", "Emit",
                                                          this, getClass().getMethod("signalHandler",
                                                                                     String.class)));

        /* Add rule to receive non-session based signals */
        status = bus.addMatch("type='signal',interface='org.alljoyn.bus.EmitterInterface',member='Emit'");
        if (Status.OK != status) {
            throw new GameException("Cannot add rule to receive signals");
        }
    }

    public void tearDown() throws Exception {
        bus.unregisterBusObject(emitter);
        emitter = null;

        /* Remove rule to receive non-session based signals */
        Status status = bus.removeMatch("type='signal',interface='org.alljoyn.bus.EmitterInterface',member='Emit'");
        if (Status.OK != status) {
            throw new GameException("Cannot remove rule to receive signals");
        }

        bus.disconnect();
        bus = null;
    }

    public void signalHandler(String string) throws BusException {
        bus.getMessageContext();
    }

    public void testTimeToLive() throws Exception {
        emitter.setTimeToLive(1);
        emitter.emit("timeToLiveOn");

        emitter.setTimeToLive(0);
        emitter.emit("timeToLiveOff");

        // TODO: how to verify?
    }

    public void testCompressHeader() throws Exception {
        emitter.setCompressHeader(true);
        emitter.emit("compressHeaderOn1");
        emitter.emit("compressHeaderOn2");

        emitter.setCompressHeader(false);
        emitter.emit("compressHeaderOff");

        // TODO: how to verify?
    }

    public void testMessageContext() throws Exception {
        emitter.setGlobalBroadcast(false);
        emitter.setCompressHeader(false);
        emitter.setSessionlessFlag(true);
        emitter.setTimeToLive(0);
        emitter.emit("sessionless1");
        MessageContext ctx = emitter.getMessageContext();
        assertEquals("/emitter", ctx.objectPath);
        assertEquals("org.alljoyn.bus.EmitterInterface", ctx.interfaceName);
        assertEquals("Emit", ctx.memberName);
        assertEquals("", ctx.destination);
        assertEquals(bus.getUniqueName(), ctx.sender);
        assertEquals("s", ctx.signature);
    }

    public void testCancelSessionless() throws Exception {
        emitter.setCompressHeader(false);
        emitter.setSessionlessFlag(true);
        emitter.setTimeToLive(0);
        emitter.emit("sessionless2");
        int serial = emitter.getMessageContext().serial;
        Status status = emitter.cancelSessionlessSignal(serial);
        assertEquals(Status.OK, status);
        status = emitter.cancelSessionlessSignal(58585858);
        assertEquals(Status.BUS_NO_SUCH_MESSAGE, status);
    }

    public void testGlobalBroadcast() throws Exception {
        // TODO fix this text
//        /* Set up another daemon to receive the global broadcast signal. */
//        AllJoynDaemon daemon = new AllJoynDaemon();
//        AllJoynProxyObj alljoyn = bus.getAllJoynProxyObj();
//        assertEquals(AllJoynProxyObj.ConnectResult.Success, alljoyn.Connect(daemon.remoteAddress()));
//
//        System.setProperty("org.alljoyn.bus.address", daemon.address());
//        BusAttachment otherConn = new BusAttachment(getClass().getName(), BusAttachment.RemoteMessage.Receive);
//        assertEquals(Status.OK, otherConn.connect());
//        assertEquals(Status.OK, otherConn.registerSignalHandler("org.alljoyn.bus.EmitterInterface", "Emit",
//                                                                this, getClass().getMethod("signalHandler",
//                                                                                           String.class)));
//
//        /* Emit the signal from this daemon. */
//        signalsHandled = 0;
//        emitter.setGlobalBroadcast(true);
//        emitter.Emit("globalBroadcastOn");
//        emitter.setGlobalBroadcast(false);
//        emitter.Emit("globalBroadcastOff");
//        Thread.currentThread().sleep(100);
//        assertEquals(1, signalsHandled);
//
//        otherConn.unregisterSignalHandler(this, getClass().getMethod("signalHandler", String.class));
//        otherConn.disconnect();
//        alljoyn.Disconnect(daemon.remoteAddress());
//        daemon.stop();
    }

    public void testSessionCast() throws Exception {
        String AA = genUniqueName(bus);
        String BB = genUniqueName(bus);
        String CC = genUniqueName(bus);

        Participant A = new Participant(AA);
        Participant B = new Participant(BB);
        Participant C = new Participant(CC);

        A.find(BB);
        A.find(CC);
        B.find(AA);
        B.find(CC);
        C.find(AA);
        C.find(BB);
        

        /* no sessions yet */
        A.emit();
        B.emit();
        C.emit();
        Thread.sleep(1000);
        A.checkReceived(0);
        B.checkReceived(0);
        C.checkReceived(0);

        /* set up some sessions */
        B.join(A);
        C.join(A);
        C.join(B);
        A.emit();
        B.emit();
        Thread.sleep(1000);
        A.checkReceived(0);
        B.checkReceived(1);
        C.checkReceived(2);

        C.emit();
        Thread.sleep(1000);
        A.checkReceived(0);
        B.checkReceived(0);
        C.checkReceived(0);
    }
}
