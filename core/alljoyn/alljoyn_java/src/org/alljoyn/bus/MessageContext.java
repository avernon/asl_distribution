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

package org.alljoyn.bus;

/**
 * Contains information about a specific method call or signal
 * message.
 */
public final class MessageContext {

    /**
     * {@code true} if the message is unreliable.  Unreliable messages have a non-zero
     * time-to-live and may be silently discarded.
     */
    public boolean isUnreliable;

    /**
     * The object path for this message.  An empty string if unable to find the
     * AllJoyn object path.
     */
    public String objectPath;

    /**
     * The interface for this message.  An empty string if unable to find the
     * AllJoyn interface.
     */
    public String interfaceName;

    /**
     * The member (method/signal) name for this message.  An empty string if
     * unable to find the member name.
     */
    public String memberName;

    /**
     * The destination for this message.  An empty string if unable to find the
     * message destination.
     */
    public String destination;

    /**
     * The sender for this message.  An empty string if the message did not
     * specify a sender.
     */
    public String sender;

    /**
     * The session ID that the sender used to send the message.
     */
    public int sessionId;

    /**
     * The serial number of the message.
     */
    public int serial;

    /**
     * The signature for this message.  An empty string if unable to find the
     * AllJoyn signature.
     */
    public String signature;

    /**
     * The authentication mechanism in use for this message.
     */
    public String authMechanism;

    @SuppressWarnings("unused")
    private MessageContext(boolean isUnreliable, String objectPath, String interfaceName,
                           String memberName, String destination, String sender, int sessionId,
                           String signature, String authMechanism, int serial) {
        this.isUnreliable = isUnreliable;
        this.objectPath = objectPath;
        this.interfaceName = interfaceName;
        this.memberName = memberName;
        this.destination = destination;
        this.sender = sender;
        this.sessionId = sessionId;
        this.signature = signature;
        this.authMechanism = authMechanism;
        this.serial = serial;
    }

    public MessageContext() {
    }
}
