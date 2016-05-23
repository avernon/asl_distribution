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

package org.alljoyn.bus.samples.rawservice;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.annotation.BusMethod;

/**
 * The BusInterface annotation is used to tell the code that this interface is an AllJoyn interface.
 *
 * The 'name' value is used to specify by which name this interface will be known.  If the name is
 * not given the fully qualified name of the Java interface is be used.  In most instances its best
 * to assign an interface name since it helps promote code reuse.
 */
@BusInterface(name = "org.alljoyn.bus.samples.raw.RawInterface")
public interface RawInterface {

    /**
     * Ask the service to arrange a raw reliable session that can be used to
     * transfer a "file" and return a contact port over which this session
     * can be joined.
     *
     * @return an integer session port with which the raw session may be
     * joined
     *
     * @throws BusException
     */
    @BusMethod
    short RequestRawSession() throws BusException;
}
