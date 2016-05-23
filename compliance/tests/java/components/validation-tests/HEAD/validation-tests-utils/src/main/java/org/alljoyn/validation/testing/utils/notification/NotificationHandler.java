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
package org.alljoyn.validation.testing.utils.notification;

import java.util.UUID;
import java.util.concurrent.LinkedBlockingDeque;
import java.util.concurrent.TimeUnit;

import org.alljoyn.ns.Notification;
import org.alljoyn.ns.NotificationReceiver;
import org.alljoyn.validation.testing.utils.log.Logger;
import org.alljoyn.validation.testing.utils.log.LoggerFactory;

public class NotificationHandler implements NotificationReceiver
{
    private static final String TAG = "NotificationHandler";
    private static final Logger logger = LoggerFactory.getLogger(TAG);

    private LinkedBlockingDeque<Notification> receivedNotifications = new LinkedBlockingDeque<Notification>();

    private String senderDeviceId;
    private UUID senderAppId;

    public void initializeForDevice(String deviceId, UUID appId)
    {
        this.senderDeviceId = deviceId;
        this.senderAppId = appId;
    }

    @Override
    public void receive(Notification notification)
    {
        UUID appId = notification.getAppId();
        String deviceId = notification.getDeviceId();

        if (senderDeviceId.equals(deviceId) && senderAppId.equals(appId))
        {
            logger.debug(String.format("Received notification from DUT with messageId: %d", notification.getMessageId()));
            receivedNotifications.add(notification);
        }
        else
        {
            logger.debug(String.format("Ignoring notification received from: deviceId: %s; appId: %s", deviceId, appId));
        }
    }

    @Override
    public void dismiss(int arg0, UUID arg1)
    {
    }

    public Notification getReceivedNotification() throws InterruptedException
    {
        return receivedNotifications.take();
    }

    public Notification getReceivedNotification(long timeout, TimeUnit unit) throws InterruptedException
    {
        return receivedNotifications.poll(timeout, unit);
    }

    public void clearReceivedNotifications() throws InterruptedException
    {
        receivedNotifications.clear();
    }
}