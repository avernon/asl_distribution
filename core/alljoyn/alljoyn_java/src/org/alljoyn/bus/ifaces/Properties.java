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

import java.util.Map;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.Variant;
import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusSignal;

/**
 * The standard org.freedesktop.DBus.Properties interface that can be
 * implemented by bus objects to expose a generic "setter/getter" inteface for
 * user-defined properties on DBus.
 */
@BusInterface(name = "org.freedesktop.DBus.Properties")
public interface Properties {

    /**
     * Gets a property that exists on a named interface of a bus object.
     *
     * @param iface the interface that the property exists on
     * @param propName the name of the property
     * @return the value of the property
     * @throws BusException if the named property doesn't exist
     */
    @BusMethod
    Variant Get(String iface, String propName) throws BusException;

    /**
     * Sets a property that exists on a named interface of a bus object.
     *
     * @param iface the interface that the property exists on
     * @param propName the name of the property
     * @param value the value for the property
     * @throws BusException if the named property doesn't exist or cannot be set
     */
    @BusMethod
    void Set(String iface, String propName, Variant value) throws BusException;

    /**
     * Gets all properties for a given interface.
     *
     * @param iface the interface
     * @return a Map of name/value associations
     * @throws BusException if request cannot be honored
     */
    @BusMethod(signature = "s", replySignature = "a{sv}")
    Map<String, Variant> GetAll(String iface) throws BusException;

    /**
     * Notifies others about changes to properties.
     *
     * @param iface the interface
     * @param changedProps a map of property names an their new values
     * @param invalidatedProps a list of property names whose values are invalidated
     * @throws BusException indicating failure sending PropertiesChanged signal
     */
    @BusSignal(signature = "sa{sv}as")
    void PropertiesChanged(String iface, Map<String, Variant> changedProps, String [] invalidatedProps) throws BusException;
}
