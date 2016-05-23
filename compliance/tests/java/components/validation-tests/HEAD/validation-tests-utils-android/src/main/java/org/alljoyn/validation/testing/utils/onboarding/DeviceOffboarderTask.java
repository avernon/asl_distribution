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

import org.alljoyn.bus.BusException;
import org.alljoyn.validation.framework.AboutAnnouncement;
import org.alljoyn.validation.testing.utils.about.AboutAnnouncementDetails;
import org.alljoyn.validation.testing.utils.log.Logger;
import org.alljoyn.validation.testing.utils.log.LoggerFactory;
import org.alljoyn.validation.testing.utils.onboarding.DeviceOnboarder.OffboardingOperation;
import org.alljoyn.validation.testing.utils.onboarding.DeviceOnboarder.OffboardingProgressListener;
import org.alljoyn.validation.testing.utils.onboarding.DeviceOnboarder.OffboardingState;

import android.content.Context;

public class DeviceOffboarderTask implements Callable<Object>
{
    private static final String TAG = "DeviceOffboarderTask";
    private static final Logger logger = LoggerFactory.getLogger(TAG);
    private AboutAnnouncementDetails aboutAnnouncementDetails;
    private OffboardingProgressListener listener;
    private OnboardingHelper onboardingHelper;
    private String keyStorePath;

    public DeviceOffboarderTask(Context context, AboutAnnouncement aboutAnnouncement, WifiNetworkConfig personalAPConfig, OffboardingProgressListener listener)
    {
        initAboutAnnouncementDetail(aboutAnnouncement);

        this.listener = listener;

        keyStorePath = context.getFileStreamPath("alljoyn_keystore").getAbsolutePath();
        onboardingHelper = getOnboardingHelper(context);
        onboardingHelper.setPersonalAPConfig(personalAPConfig);
    }

    protected OnboardingHelper getOnboardingHelper(Context context)
    {
        return new OnboardingHelper(context);
    }

    private void releaseResources()
    {
        if (onboardingHelper != null)
        {
            onboardingHelper.release();
            onboardingHelper = null;
        }
    }

    @Override
    public Object call() throws Exception
    {
        try
        {
            listener.onStateChanged(OffboardingState.WAITING_ANNOUNCEMENT_AND_CONNECTING);
            onboardingHelper.initialize(keyStorePath, aboutAnnouncementDetails.getDeviceId(), aboutAnnouncementDetails.getAppId());

            onboardingHelper.waitForAboutAnnouncementAndThenConnect();

            listener.onStateChanged(OffboardingState.CALLING_OFFBOARD);
            onboardingHelper.callOffboard();

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

    public class OffboardingOperationImpl extends FutureTask<Object> implements OffboardingOperation
    {

        public OffboardingOperationImpl(Callable<Object> callable)
        {
            super(callable);
        }

        @Override
        public void cancel()
        {
            super.cancel(true);
        }

    }

    public OffboardingOperationImpl getRunnable()
    {
        return new OffboardingOperationImpl(this);
    }

    private void initAboutAnnouncementDetail(AboutAnnouncement aboutAnnouncement)
    {
        this.aboutAnnouncementDetails = new AboutAnnouncementDetails(aboutAnnouncement);

        try
        {
            aboutAnnouncementDetails.convertAboutMap();
        }
        catch (BusException e)
        {
            logger.warn("BusException processing AboutMap", e);
        }
    }
}