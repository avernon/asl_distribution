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

package org.alljoyn.services.common;

import java.util.Map;

/**
 * A generic Property store definition. Needs to be implemented per platform.
 * The application creates this store and passes it to the About and Config
 * services that use it for Announcements and for Get/Set data support.
 * The application is responsible for the persistence of this store.
 * @deprecated see org.alljoyn.bus.AboutDataListener
 */
@Deprecated
public interface PropertyStore {

    /**
     * Classifies the properties by purpose: for announcement, for get-about, for get-config
     */
    enum Filter {
        /**
         * Properties that should be announced
         */
        ANNOUNCE,

        /**
         * Read only properties that should be retrieved by 'About' requests
         */
        READ,

        /**
         * Read-Write properties that are available through the 'Config' interface
         */
        WRITE,   //!< WRITE    Property that has  WRITE  enabled -- Config
    }

    /**
     * Get all the properties that are stored for the given language
     * @deprecated see org.alljoyn.bus.AboutDataListener
     * @param languageTag IETF language tag
     * @param filter classifies the properties to get: for announcement,
     *               for get-about, for get-config
     * @param dataMap the map to fill
     * @throws PropertyStoreException if language is not supported.
     */
    @Deprecated
    void readAll(String languageTag, Filter filter, Map<String, Object> dataMap) throws PropertyStoreException;

    /**
     * Update a property value for a given language.
     * @deprecated see org.alljoyn.bus.AboutDataListener
     * @param key the property name
     * @param languageTag the language in which this property should be set
     * @param newValue the property value
     * @throws PropertyStoreException if language isn't supported, key not found, or illegal value
     */
    @Deprecated
    void update(String key, String languageTag, Object newValue) throws PropertyStoreException;

    /**
     * Reset a property for a given language
     * @deprecated see org.alljoyn.bus.AboutDataListener
     * @param key the property name
     * @param languageTag the language in which this property should be set
     * @throws PropertyStoreException if language isn't supported, or key not found
     */
    @Deprecated
    void reset(String key, String languageTag) throws PropertyStoreException;

    /**
     * Reset all the properties in the store
     * @deprecated see org.alljoyn.bus.AboutDataListener
     * @throws PropertyStoreException indicating failure to reset all the properties in the store
     */
    @Deprecated
    void resetAll() throws PropertyStoreException;

}
