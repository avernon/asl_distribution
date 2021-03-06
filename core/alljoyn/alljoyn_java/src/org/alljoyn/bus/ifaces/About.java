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

/**
 *
 */
package org.alljoyn.bus.ifaces;

import java.util.Map;

import org.alljoyn.bus.AboutObjectDescription;
import org.alljoyn.bus.BusException;
import org.alljoyn.bus.Variant;
import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusProperty;
import org.alljoyn.bus.annotation.BusSignal;

/**
 * Definition of the About BusInterface
 */
@BusInterface (name = About.INTERFACE_NAME)
public interface About
{
    public static final String INTERFACE_NAME = "org.alljoyn.About";
    public final static String OBJ_PATH       = "/About";
    public static final short VERSION = 1;
    /**
     * @return the version of the protocol
     * @throws BusException indicating failure to read Version property
     */
    @BusProperty(signature="q")
    public short getVersion() throws BusException;


    /**
     *
     * @param languageTag IETF language tags specified by  RFC 5646
     * @return all the configuration fields based on the language tag.
     *         See The list of known configuration fields in About interface for
     *         more details.
     * @throws BusException indicating failure to calling the remote GetAboutData method
     */
    @BusMethod(name = "GetAboutData", signature = "s", replySignature="a{sv}")
    public Map<String, Variant> getAboutData(String languageTag) throws BusException;

    /**
     * Return the array of object paths and the list of all interfaces available
     * at the given object path.
     * @return the array of object paths and the list of all interfaces available
     *         at the given object path.
     * @throws BusException indicating failure when calling the remote GetObjectDescription method
     */
    @BusMethod(name = "GetObjectDescription", replySignature="a(oas)")
    public AboutObjectDescription[] getObjectDescription() throws BusException;

    /**
     * This signal is used to announce the list of all interfaces available at
     * the given object path.
     * @param version The interface version is added since it might help with the
     * decision to connect back.
     * @param port The global gateway port for the services for this application
     * @param objectDescriptions Descriptions of the BusObjects that make up the service. "a(sas)"
     * @param serviceMetadata Service specific key/value pairs. (Service implementers
     *                        are free to populate this dictionary with any key/value
     *                        pairs that are meaningful to the service and its
     *                        potential consumers) "a{sv}"
     */
    @BusSignal (name = "Announce", signature="qqa(oas)a{sv}")
    public void announce(short version, short port, AboutObjectDescription[] objectDescriptions, Map<String,Variant> serviceMetadata);
}
