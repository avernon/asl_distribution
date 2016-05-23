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

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.annotation.BusMethod;

/**
 * The org.allseen.Introspectable interface provides introspection xml
 * that contains description elements that document the object and it's various sub-elements.
 */
@BusInterface(name = "org.allseen.Introspectable")
public interface AllSeenIntrospectable {

   /**
     * Gets the description languages that are supported for the object.
     *
     * @return array of supported language names.
     * @throws BusException indicating failure when calling GetDescriptionLanguages method
     */
    @BusMethod
    String[] GetDescriptionLanguages() throws BusException;

    /**
     * Gets the introspect with description for the object.
     * @param language to return in the description.
     * @return introspect with description.
     * @throws BusException indicating failure when calling IntrospectWithDescription method
     */
    @BusMethod
    String IntrospectWithDescription(String language) throws BusException;
}
