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

import java.util.concurrent.Callable;
import java.util.concurrent.FutureTask;

import org.alljoyn.onboarding.OnboardingService;
import org.alljoyn.validation.testing.utils.about.AboutAnnouncementDetails;
import org.alljoyn.validation.testing.utils.onboarding.DeviceOnboarder.OnboardingOperation;
import org.alljoyn.validation.testing.utils.onboarding.DeviceOnboarder.OnboardingProgressListener;
import org.alljoyn.validation.testing.utils.onboarding.DeviceOnboarder.OnboardingState;

import android.content.Context;

public class DeviceOnboarderTask implements Callable<Object>
{
    protected static final String TAG = "DeviceOnboarderTask";
    private OnboardingHelper onboardingHelper;
    private OnboardingProgressListener listener;
    private WifiNetworkConfig personalAPConfig;
    protected static final short OBS_CONFIGURE_WIFI_RETURN_NO_CHANNEL_SWITCHING = 1;
    private String deviceId = null;
    private String deviceName = null;
    private Context context;

    public DeviceOnboarderTask(Context context, WifiNetworkConfig softAPConfig, WifiNetworkConfig personalAPConfig, OnboardingProgressListener listener)
    {
        this.personalAPConfig = personalAPConfig;
        this.listener = listener;

        this.context = context;
        onboardingHelper = getOnboardingHelper(context);
        onboardingHelper.setPersonalAPConfig(personalAPConfig);
        onboardingHelper.setSoftAPConfig(softAPConfig);
    }

    protected OnboardingHelper getOnboardingHelper(Context context)
    {
        return new OnboardingHelper(context);
    }

    @Override
    public Object call() throws Exception
    {
        AboutAnnouncementDetails aboutAnnouncementDetails = null;
        try
        {
            listener.onStateChanged(OnboardingState.CONNECTING_TO_SOFT_AP);

            String keyStorePath = context.getFileStreamPath("alljoyn_keystore").getAbsolutePath();
            onboardingHelper.initialize(keyStorePath, null, null);

            onboardingHelper.connectToDUTOnSoftAP();

            listener.onStateChanged(OnboardingState.WAITING_ANNOUNCEMENT_AND_CONNECTING);
            onboardingHelper.waitForAboutAnnouncementAndThenConnect();

            listener.onStateChanged(OnboardingState.CALLING_CONFIGURE_WIFI);
            short configureWiFiRetval = onboardingHelper.callConfigureWiFi(personalAPConfig);

            if (configureWiFiRetval != OBS_CONFIGURE_WIFI_RETURN_NO_CHANNEL_SWITCHING)
            {
                throw new Exception("Unsupported configuration. ConfigureWifi method call did not return 1");
            }

            listener.onStateChanged(OnboardingState.WAITING_DISCONNECT);
            onboardingHelper.callConnectWiFiAndWaitForSoftAPDisconnect();

            listener.onStateChanged(OnboardingState.CONNECTING_TO_PERSONAL_AP);
            onboardingHelper.connectToPersonalAP();

            listener.onStateChanged(OnboardingState.WAITING_ANNOUNCEMENT_ON_PERSONAL_AP);
            aboutAnnouncementDetails = onboardingHelper.waitForAboutAnnouncementAndThenConnect();

            short currentState = onboardingHelper.retrieveStateProperty();
            short expectedState = OnboardingService.OnboardingState.PERSONAL_AP_CONFIGURED_VALIDATED.getStateId();
            if (currentState != expectedState)
            {
                throw new Exception(String.format("Onboarding State property is %d and does not match the expected value of PERSONAL_AP_CONFIGURED_VALIDATED(%d)", currentState,
                        expectedState));
            }

            deviceId = aboutAnnouncementDetails.getDeviceId();

            deviceName = aboutAnnouncementDetails.getDeviceName();

            listener.onFinished(true, null);
        }
        catch (Exception e)
        {
            listener.onFinished(false, e.getMessage());
        }
        finally
        {
            releaseResources();
        }

        return null;
    }

    private void releaseResources()
    {
        if (onboardingHelper != null)
        {
            onboardingHelper.release();
            onboardingHelper = null;
        }
    }

    public class OnboardingOperationImpl extends FutureTask<Object> implements OnboardingOperation
    {

        public OnboardingOperationImpl(Callable<Object> callable)
        {
            super(callable);
        }

        @Override
        public void cancel()
        {
            super.cancel(true);
        }

        @Override
        public String getDeviceId()
        {
            return deviceId;
        }

        @Override
        public String getDeviceName()
        {
            return deviceName;
        }

    }

    public OnboardingOperationImpl getRunnable()
    {
        return new OnboardingOperationImpl(this);
    }
}
