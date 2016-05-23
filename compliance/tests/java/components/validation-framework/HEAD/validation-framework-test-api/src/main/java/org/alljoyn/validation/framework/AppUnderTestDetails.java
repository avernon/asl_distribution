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

import java.util.UUID;

/**
 * This class contains information about the device/app being tested.
 * 
 */
public class AppUnderTestDetails
{
    private String deviceId;
    private UUID appId;

    /**
     * @param appId
     *            the globally unique identifier for the application given by
     *            its About interface’s AppId metadata field
     * @param deviceId
     *            the Device identifier set by platform-specific means found in
     *            About interface’s DeviceId metadata field
     */
    public AppUnderTestDetails(UUID appId, String deviceId)
    {
        this.appId = appId;
        this.deviceId = deviceId;
    }

    /**
     * @return the Device identifier set by platform-specific means found in
     *         About interface’s DeviceId metadata field
     */
    public String getDeviceId()
    {
        return deviceId;
    }

    /**
     * @return the globally unique identifier for the application given by its
     *         About interface’s AppId metadata field
     */
    public UUID getAppId()
    {
        return appId;
    }
}