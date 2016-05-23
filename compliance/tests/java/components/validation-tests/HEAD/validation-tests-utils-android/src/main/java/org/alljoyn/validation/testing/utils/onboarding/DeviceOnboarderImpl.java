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

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import org.alljoyn.validation.framework.AboutAnnouncement;
import org.alljoyn.validation.testing.utils.onboarding.DeviceOffboarderTask.OffboardingOperationImpl;
import org.alljoyn.validation.testing.utils.onboarding.DeviceOnboarderTask.OnboardingOperationImpl;

import android.content.Context;

public class DeviceOnboarderImpl implements DeviceOnboarder
{
    private ExecutorService executorService = Executors.newSingleThreadExecutor();
    private Context context;

    public DeviceOnboarderImpl(Context context)
    {
        this.context = context;
    }

    @Override
    public OffboardingOperation offboardDevice(AboutAnnouncement aboutAnnouncement, WifiNetworkConfig personalAPConfig, OffboardingProgressListener listener)
    {
        DeviceOffboarderTask deviceOffboarderTask = new DeviceOffboarderTask(context, aboutAnnouncement, personalAPConfig, listener);
        OffboardingOperationImpl obsOperation = deviceOffboarderTask.getRunnable();
        executorService.submit(obsOperation);
        return obsOperation;
    }

    @Override
    public OnboardingOperation onboardDevice(WifiNetworkConfig softAPConfig, WifiNetworkConfig personalAPConfig, OnboardingProgressListener listener)
    {
        DeviceOnboarderTask deviceOnboarderTask = new DeviceOnboarderTask(context, softAPConfig, personalAPConfig, listener);
        OnboardingOperationImpl obsOperation = deviceOnboarderTask.getRunnable();
        executorService.submit(obsOperation);
        return obsOperation;
    }

}
