/******************************************************************************
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
 ******************************************************************************/

package org.alljoyn.bus;

import org.alljoyn.bus.annotation.BusAnnotation;
import org.alljoyn.bus.annotation.BusAnnotations;
import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusSignal;
import org.alljoyn.bus.annotation.BusProperty;

@BusInterface(name="org.alljoyn.bus.InterfaceWithAnnotations")
@BusAnnotations({@BusAnnotation(name="org.freedesktop.DBus.Deprecated", value="true")})
public interface InterfaceWithAnnotations {

    @BusMethod(name="Ping", signature="s", replySignature="s")
    @BusAnnotations({@BusAnnotation(name="name", value="value"), @BusAnnotation(name="name2", value="value2")})
    public String ping(String inStr) throws BusException;

    @BusMethod(name="Pong", signature="s", replySignature="s")
    public String pong(String inStr) throws BusException;


    @BusMethod(name="Pong2", signature="s")
    @BusAnnotations({@BusAnnotation(name="org.freedesktop.DBus.Deprecated", value="true"),
        @BusAnnotation(name="org.freedesktop.DBus.Method.NoReply", value="true")})
    public void pong2(String inStr) throws BusException;


    @BusSignal(name="Signal")
    @BusAnnotations({@BusAnnotation(name="org.freedesktop.DBus.Deprecated", value="true")})
    public void signal() throws BusException;


    @BusProperty
    @BusAnnotations({@BusAnnotation(name="org.freedesktop.DBus.Property.EmitsChangedSignal", value="true")})
    public String getProp1() throws BusException;

    @BusProperty
    @BusAnnotations({@BusAnnotation(name="org.freedesktop.DBus.Property.EmitsChangedSignal", value="true")})
    public void setProp1(String s) throws BusException;


    @BusProperty
    @BusAnnotations({@BusAnnotation(name="org.freedesktop.DBus.Property.EmitsChangedSignal", value="invalidates")})
    public String getProp2() throws BusException;

    @BusProperty
    @BusAnnotations({@BusAnnotation(name="org.freedesktop.DBus.Property.EmitsChangedSignal", value="invalidates")})
    public void setProp2(String s) throws BusException;
}
