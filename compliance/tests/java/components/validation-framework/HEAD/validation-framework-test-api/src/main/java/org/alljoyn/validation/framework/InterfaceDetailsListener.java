/*******************************************************************************
 *  Copyright AllSeen Alliance. All rights reserved.
 *
 *     Contributed by Qualcomm Connected Experiences, Inc.,
 *     with authorization from the AllSeen Alliance, Inc.
 *     
 *     Licensed under the Apache License, Version 2.0 (the "License");
 *     you may not use this file except in compliance with the License.
 *     You may obtain a copy of the License at
 *     
 *         http://www.apache.org/licenses/LICENSE-2.0
 *     
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *     See the License for the specific language governing permissions and
 *     limitations under the License.
 *     
 *     Pursuant to Section 1 of the License, the work of authorship constituting
 *     a Work and any Contribution incorporated in the Work shall mean only that
 *     Contributor's code submissions authored by that Contributor.  Any rights
 *     granted under the License are conditioned upon acceptance of these
 *     clarifications.
 *******************************************************************************/
package org.alljoyn.validation.framework;

import java.util.List;

/**
 * This interface defines a method to store details of the interface that is
 * tested. This is meant for enabling the feeding into some kind of test report.
 * 
 * This is NOT currently being used by the test framework.
 * 
 */
public interface InterfaceDetailsListener
{
    /**
     * This method handles the adding of interface details during test
     * execution.
     * 
     * @param interfaceName
     *            name of the interface tested, e.g. {@code org.alljoyn.About}
     * @param version
     *            version of the interface tested
     * @param objectPath
     *            path on the Alljoyn bus where the interface was found, e.g.
     *            {@code /About}
     * @param details
     *            any custom details to be noted
     * @param attributes
     *            the attributes of the interface tested
     */
    void addInterfaceDetails(String interfaceName, short version, String objectPath, String details, List<InterfaceAttribute> attributes);
}