/******************************************************************************
 * Copyright (c) 2013, AllSeen Alliance. All rights reserved.
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
package org.alljoyn.config.transport;

import java.util.Map;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.Variant;
import org.alljoyn.bus.annotation.BusAnnotation;
import org.alljoyn.bus.annotation.BusAnnotations;
import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusProperty;
import org.alljoyn.bus.annotation.Secure;

/**
 * Definition of the Config BusInterface 
 */
@BusInterface (name = ConfigTransport.INTERFACE_NAME)
@Secure
public interface ConfigTransport extends BusObject
{
    public static final String INTERFACE_NAME = "org.alljoyn.Config";
	public final static String OBJ_PATH = "/Config";

	/**
	 * Get the writable properties of the device.
	 * @param languageTag IETF language tags specified by  RFC 5646
	 * @return Return all the updatable configuration fields based on the language tag.  See The list of known configuration fields for more details. 
	 * If language tag is not specified (i.e. ""), configuration fields based on device's language preference are returned.
	 * @throws BusException
	 */
    @BusMethod(signature = "s", replySignature="a{sv}")
    public Map<String, Variant> GetConfigurations(String languageTag) throws BusException;
    
    /**
     * Update the configuration data with the given map.  Only the fields listed in the map will be updated.  
     * @param configuration
     * @throws BusException
     */
    @BusMethod(signature="sa{sv}")
    public void  UpdateConfigurations (String languageTag, Map<String,Variant> configuration) throws BusException;

    
    @BusMethod(signature="sas")
    public void  ResetConfigurations (String language, String[] fieldsToRemove) throws BusException;


    /**
     * @return Interface version
     * @throws BusException
     */
    @BusProperty(signature="q")
    public short getVersion() throws BusException;
    
    /**
     * Change the pass phrase.  If this feature is not allowed by the OEM, 
     * the AllJoyn error code org.alljoyn.Error.FeatureNotAvailable will be returned.
     * @param daemonRealm
     * @param passphrase
     * @throws BusException
     */
    @BusMethod(signature="say")
    public void SetPasscode(String daemonRealm, byte[] newPasscode) throws BusException;

    /**
     * Direct the device to disconnect from the personal AP, clear all previously configured data, 
     * and start the soft AP mode.  Some device may not support this feature.  In such a case, 
     * the AllJoyn error code org.alljoyn.Error.FeatureNotAvailable will be returned in the AllJoyn response.
     * @throws BusException
     */
    @BusMethod
    @BusAnnotations({@BusAnnotation(name="org.freedesktop.DBus.Method.NoReply", value="true")})
    public void FactoryReset() throws BusException;

    /**
     * This method restarts or power cycles the device.
     * @throws BusException
     */
    @BusMethod
    @BusAnnotations({@BusAnnotation(name="org.freedesktop.DBus.Method.NoReply", value="true")})
    public void Restart() throws BusException;

    
}
