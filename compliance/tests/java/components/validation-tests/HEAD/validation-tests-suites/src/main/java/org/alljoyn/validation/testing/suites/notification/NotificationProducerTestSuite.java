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
package org.alljoyn.validation.testing.suites.notification;

import java.util.UUID;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.TimeUnit;

import org.alljoyn.about.client.AboutClient;
import org.alljoyn.services.android.utils.AndroidLogger;
import org.alljoyn.validation.framework.AppUnderTestDetails;
import org.alljoyn.validation.framework.UserInputDetails;
import org.alljoyn.validation.framework.annotation.ValidationSuite;
import org.alljoyn.validation.framework.annotation.ValidationTest;
import org.alljoyn.validation.framework.utils.introspection.BusIntrospector;
import org.alljoyn.validation.testing.utils.BaseTestSuite;
import org.alljoyn.validation.testing.utils.about.AboutAnnouncementDetails;
import org.alljoyn.validation.testing.utils.log.Logger;
import org.alljoyn.validation.testing.utils.log.LoggerFactory;
import org.alljoyn.validation.testing.utils.notification.NotificationValidator;
import org.alljoyn.validation.testing.utils.notification.NotificationValidator.NotificationValidationExceptionHandler;
import org.alljoyn.validation.testing.utils.services.ServiceHelper;

@ValidationSuite(name = "Notification-v1")
public class NotificationProducerTestSuite extends BaseTestSuite
{
    private static final String BUS_APPLICATION_NAME = "NotificationProducerTestSuite";

    protected static final String TAG = "NotfProdTestSuite";
    private static final Logger logger = LoggerFactory.getLogger(TAG);

    private static final long TIMEOUT_FOR_SHUTDOWN_IN_SECONDS = 1;

    private UserInputDetails userInputDetails = null;
    private AboutAnnouncementDetails deviceAboutAnnouncement;

    private volatile Thread waitingforUserInputThread;
    private volatile Exception notificationAssertionFailure = null;

    private ServiceHelper serviceHelper;

    private NotificationValidator notificationValidator;

    private AboutClient aboutClient;

    private ExecutorService executorService;

    private AppUnderTestDetails appUnderTestDetails;
    private UUID dutAppId;
    private String dutDeviceId;

    @Override
    protected void setUp() throws Exception
    {
        super.setUp();

        logger.debug("test setUp started");

        appUnderTestDetails = getValidationTestContext().getAppUnderTestDetails();
        dutDeviceId = appUnderTestDetails.getDeviceId();
        logger.debug(String.format("Running NotificationProducer test case against Device ID: %s", dutDeviceId));
        dutAppId = appUnderTestDetails.getAppId();
        logger.debug(String.format("Running NotificationProducer test case against App ID: %s", dutAppId));

        waitingforUserInputThread = Thread.currentThread();

        executorService = getExecutorService();

        try
        {
            serviceHelper = getServiceHelper();

            serviceHelper.initialize(BUS_APPLICATION_NAME, dutDeviceId, dutAppId);

            notificationValidator = getNotificationValidator();
            serviceHelper.initNotificationReceiver(notificationValidator);

            deviceAboutAnnouncement = serviceHelper.waitForNextDeviceAnnouncement(determineAboutAnnouncementTimeout(), TimeUnit.SECONDS);
            if (deviceAboutAnnouncement == null)
            {
                throw new Exception("Timed out waiting for About announcement");
            }

            aboutClient = serviceHelper.connectAboutClient(deviceAboutAnnouncement);

            logger.debug("test setUp done");
        }
        catch (Exception e)
        {
            logger.error("Exception in setup method", e);
            releaseResources();
            throw e;
        }
    }

    protected NotificationValidator getNotificationValidator()
    {
        return new NotificationValidator(getValidationTestContext());
    }

    protected ServiceHelper getServiceHelper()
    {
        return new ServiceHelper(new AndroidLogger());
    }

    protected ExecutorService getExecutorService()
    {
        return java.util.concurrent.Executors.newSingleThreadExecutor();
    }

    @ValidationTest(name = "Notification-v1-01")
    public void testNotificationsReceived() throws Exception
    {
        logger.debug("Starting testNotificationReceived method");
        userInputDetails = new UserInputDetails("Notification Producer Test",
                "Please initiate the sending of notifications from the DUT and click Continue when all notifications that you want to test have been sent", "Continue");

        BusIntrospector busIntrospector = serviceHelper.getBusIntrospector(aboutClient);
        notificationValidator.initializeForDevice(deviceAboutAnnouncement, busIntrospector, new NotificationValidationExceptionHandler()
        {

            @Override
            public void onNotificationValidationException(Exception exception)
            {
                logger.debug("Notificiation failed validation checks", exception);
                notificationAssertionFailure = exception;
                waitingforUserInputThread.interrupt();
            }
        });

        executorService.submit(notificationValidator);

        try
        {
            logger.debug("Waiting for user input");
            getValidationTestContext().waitForUserInput(userInputDetails);
        }
        catch (InterruptedException e)
        {
            if (notificationAssertionFailure != null)
            {
                Thread.interrupted();
                throw notificationAssertionFailure;
            }
            throw e;
        }
        logger.debug(String.format("Received: %d notifications", notificationValidator.getNumberOfNotificationsReceived()));
        assertTrue("No notifications received!", notificationValidator.getNumberOfNotificationsReceived() > 0);
    }

    @Override
    protected void tearDown() throws Exception
    {
        super.tearDown();

        logger.debug("test tearDown started");

        releaseResources();

        logger.debug("test tearDown done");
    }

    private void releaseResources() throws Exception
    {

        InterruptedException exception = null;
        executorService.shutdownNow();
        try
        {
            logger.debug("Waiting for thread to shutdown");
            executorService.awaitTermination(TIMEOUT_FOR_SHUTDOWN_IN_SECONDS, TimeUnit.SECONDS);
        }
        catch (InterruptedException e)
        {
            exception = e;
        }

        disconnectFromAboutClient();
        releaseServiceHelper();
        if (exception != null)
        {
            logger.warn("Interrupted while waiting for a thread to exit", exception);
            throw new Exception("Interrupted while waiting for thread to exit", exception);
        }
    }

    private void releaseServiceHelper()
    {
        if (serviceHelper != null)
        {
            serviceHelper.release();
            serviceHelper = null;
        }
    }

    private void disconnectFromAboutClient()
    {
        if (aboutClient != null)
        {
            aboutClient.disconnect();
            aboutClient = null;
        }
    }
}
