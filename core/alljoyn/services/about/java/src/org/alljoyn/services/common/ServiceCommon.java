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

import java.util.List;

import org.alljoyn.about.transport.AboutTransport;
import org.alljoyn.services.common.utils.GenericLogger;

/**
 * A base class for Services
 * @deprecated
 */
@Deprecated
public interface ServiceCommon
{
    /**
     * The list of BusObjects that are registered for this service, and the
     * BusInterfaces that they implement.
     * @deprecated
     * @return the list of BusObjectDescription
     * @see AboutTransport#Announce(short, short, BusObjectDescription[], java.util.Map)
     */
    @Deprecated
    public List<BusObjectDescription> getBusObjectDescriptions();

    /**
     * Set the platform specific logger
     * @deprecated
     * @param logger a Java logger utility
     */
    @Deprecated
    void setLogger(GenericLogger logger);

    /**
     * Is the service running in a client mode. Note: a service can run in both
     * modes simultaneously
     * @deprecated
     * @return true if the service is running in a client mode
     */
    @Deprecated
    boolean isClientRunning();

    /**
     * Is the service running in a server mode. Note: a service can run in both
     * modes simultaneously
     * @deprecated
     * @return true if the service is running in a server mode
     */
    @Deprecated
    boolean isServerRunning();

}
