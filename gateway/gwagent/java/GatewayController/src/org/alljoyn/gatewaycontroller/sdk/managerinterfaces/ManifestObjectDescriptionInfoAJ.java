/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

package org.alljoyn.gatewaycontroller.sdk.managerinterfaces;

import org.alljoyn.bus.annotation.Position;

/**
 * Manifest object description with a full information
 */
public class ManifestObjectDescriptionInfoAJ {

    /**
     * Object path with full name
     */
    public static class ObjectPathInfoAJ {

        /**
         * Object path
         */
        @Position(0)
        public String objectPath;

        /**
         * Whether this object path is a prefix
         */
        @Position(1)
        public boolean isPrefix;

        /**
         * Object path friendly name
         */
        @Position(2)
        public String objectPathFriendlyName;
    }

    /**
     * Interfaces with the full name
     */
    public static class InterfaceInfoAJ {

        /**
         * Interface name
         */
        @Position(0)
        public String interfaceName;

        /**
         * Interface friendly name
         */
        @Position(1)
        public String friendlyName;

        /**
         * Whether the interface is secured
         */
        @Position(2)
        public boolean isSecured;
    }

    // =======================================//

    /**
     * Object path
     */
    @Position(0)
    public ObjectPathInfoAJ objPathInfo;

    /**
     * Interfaces
     */
    @Position(1)
    public InterfaceInfoAJ[] interfaces;
}
