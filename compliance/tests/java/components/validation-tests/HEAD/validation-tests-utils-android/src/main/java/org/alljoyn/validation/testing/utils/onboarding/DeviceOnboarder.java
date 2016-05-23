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
package org.alljoyn.validation.testing.utils.onboarding;

import org.alljoyn.validation.framework.AboutAnnouncement;

public interface DeviceOnboarder
{

    public static enum OffboardingState
    {
        WAITING_ANNOUNCEMENT_AND_CONNECTING, CALLING_OFFBOARD;
    }

    public interface OffboardingProgressListener
    {
        void onStateChanged(OffboardingState state);

        void onFinished(boolean successful, String errorMessage);
    }

    public static enum OnboardingState
    {
        CONNECTING_TO_SOFT_AP, WAITING_ANNOUNCEMENT_AND_CONNECTING, CALLING_CONFIGURE_WIFI, WAITING_DISCONNECT, CONNECTING_TO_PERSONAL_AP, WAITING_ANNOUNCEMENT_ON_PERSONAL_AP;
    }

    public interface OnboardingProgressListener
    {
        void onStateChanged(OnboardingState state);

        void onFinished(boolean successful, String errorMessage);
    }

    public interface OnboardingOperation
    {
        boolean isDone();

        void cancel();

        String getDeviceId();

        String getDeviceName();
    }

    public interface OffboardingOperation
    {
        boolean isDone();

        void cancel();
    }

    OffboardingOperation offboardDevice(AboutAnnouncement aboutAnnouncement, WifiNetworkConfig personalAPConfig, OffboardingProgressListener listener);

    OnboardingOperation onboardDevice(WifiNetworkConfig softAPConfig, WifiNetworkConfig personalAPConfig, OnboardingProgressListener listener);

}
