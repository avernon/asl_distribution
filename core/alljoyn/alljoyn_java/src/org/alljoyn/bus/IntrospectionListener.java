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
 * Implemented by a user-defined {@link BusObject} that is interested in
 * customizing the D-Bus introspection XML presented to remote nodes.
 *
 * Listener objects are the Java objects that handle notification events and are
 * called from AllJoyn in the context of one of its threads.  All listener
 * objects are expected to be multithread safe (MT-Safe) between construction
 * and destruction.  That is, every thread executing in a listener object's
 * methods 1) gets a unique copy of all temporary data (it is re-entrant); and
 * 2) all shared data -- the object instance's member variables or any globals
 * must contain no read-modify-write access patterns (okay to write or read,
 * just never to read-modify-write).  If such access patterns are required, it
 * is the responsibility of the client to, for example, add the synchronized
 * keyword when overriding one of the listener methods or provide some other
 * serialization mechanism in order to preserve MT-Safe operation.
 *
 * This rule extends to other objects accessed during processing of
 * notifications.  For example, it is a programming error to allow a notifiation
 * method to update a collection in another object without serializing access
 * to the collection.
 *
 * The important consideration in this case is that as soon as one sets up a
 * listener object to receive notifications from AllJoyn, one is implicitly
 * dealing with multithreaded code.
 *
 * Since listener objects generally run in the context of the AllJoyn thread
 * which manages reception of events, If a blocking AllJoyn call is made in
 * the context of a notification, the necessary and sufficient conditions for
 * deadlock are established.
 *
 * The important consideration in this case is that when one receives a
 * notification from AllJoyn, that notification is executing in the context of
 * an AllJoyn thread.  If one makes a blocking call back into AllJoyn on that
 * thread, a deadlock cycle is likely, and if this happens your bus attachment
 * receive thread will deadlock (with itself).  The deadlock is typically broken
 * after a bus timeout eventually happens.
 */
public interface IntrospectionListener {

    /**
     * Returns a description of the object in the D-Bus introspection XML
     * format.  Note that the DTD description and the root element are not
     * generated.
     *
     * Any implementation of this function must be multithread safe.  See the
     * class documentation for details.
     *
     * @param deep include XML for all decendents rather than stopping at direct
     *             children
     * @param indent number of characters to indent the XML
     * @return the description of the object in D-Bus introspection XML format
     */
    String generateIntrospection(boolean deep, int indent);
}

