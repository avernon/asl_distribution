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

package org.alljoyn.about.client;

import java.util.Map;

import org.alljoyn.about.AboutKeys;
import org.alljoyn.bus.BusException;
import org.alljoyn.bus.BusObject;
import org.alljoyn.services.common.BusObjectDescription;
import org.alljoyn.services.common.ClientBase;

/**
 * An interface for retrieval of remote IoE device's About data.
 * Encapsulates the AboutTransport BusInterface
 * @deprecated see org.alljoyn.bus.AboutProxy
 */
@Deprecated
public interface AboutClient extends ClientBase
{
    /**
     * Get the language that is used for Announcements.
     * @deprecated see org.alljoyn.bus.AboutProxy
     * @return a String representing the language. IETF language tags specified by  RFC 5646.
     * @throws BusException indicating failure getting the default language
     */
    @Deprecated
    public String getDefaultLanguage() throws BusException;

    /**
     * Get the languages that are supported by the device.
     * @deprecated see org.alljoyn.bus.AboutProxy
     * @return a String array of languages. IETF language tags specified by  RFC 5646.
     * @throws BusException indicating failure getting the list of languages supported by the device
     */
    @Deprecated
    public String[] getLanguages() throws BusException;

    /**
     * Return all the configuration fields based on the language tag.
     * @deprecated see org.alljoyn.bus.AboutProxy
     * @param languageTag IETF language tags specified by  RFC 5646
     * @return All the configuration fields based on the language tag. 
     *         If language tag is not specified (i.e. ""), fields based on device's
     *         default language are returned
     * @throws BusException indicating failure getting the AboutData for the specified language
     * @see AboutKeys
     */
    @Deprecated
    public Map <String, Object> getAbout(String languageTag) throws BusException;

    /**
     * Returns the Bus Interfaces and Bus Objects supported by the device.
     * @deprecated see org.alljoyn.bus.AboutProxy
     * @return the array of object paths and the list of all interfaces available
     *         at the given object path.
     * @throws BusException indicating failure to get the BusObjectDescriptions
     */
    @Deprecated
    public BusObjectDescription[] getBusObjectDescriptions() throws BusException;
}
