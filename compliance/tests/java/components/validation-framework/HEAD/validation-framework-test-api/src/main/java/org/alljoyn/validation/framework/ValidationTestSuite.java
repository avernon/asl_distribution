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
 * This interface provides method to determine applicable
 * {@link ValidationTestGroup}.
 * 
 */
public interface ValidationTestSuite
{
    /**
     * This method provides a list of {@code ValidationTestGroup} that are
     * applicable for the test suite based on About announcements.
     * 
     * For example, for a device which contains multiple applications, the list
     * would contain a {@code ValidationTestGroup} for About interface of each
     * application and {@code ValidationTestGroup} for any other service like
     * Config.
     * 
     * @param allJoynAnnouncedDevice
     *            the object containing device id and About announcements for
     *            the device
     * @return List of {@code ValidationTestGroup} that are applicable for the
     *         test suite based on About announcements
     */
    List<ValidationTestGroup> getApplicableTests(AllJoynAnnouncedDevice allJoynAnnouncedDevice);
}