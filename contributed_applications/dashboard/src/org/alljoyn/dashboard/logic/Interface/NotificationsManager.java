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
package org.alljoyn.dashboard.logic.Interface;

import java.util.ArrayList;
import java.util.UUID;


public interface NotificationsManager
{

    public int getUnclearedNotificationsCount();

    public int getUnreadNotificationsCount();

    public int getUnreadNotificationsCount(UUID m_deviceId);

    //	public void removeNotificationsForDevice(UUID deviceID);

    public void markAllNotificationsAsCleared();

    public void markAllNotificationsAsRead();

    public void markAllNotificationsAsRead(UUID deviceId);

    public ArrayList<NotificationWrapper> getNotificationList();

    public ArrayList<NotificationWrapper> getNotificationList(UUID m_deviceId);
    /**
     * Starts receiver functionality
     */
    public void startReceiver();

    /**
     * Unregister transportConsumerChannel BusObject and SignalHandler
     */
    public void stopReceiver();

    public NotificationWrapper getNotificationByMessageID(int messageID);

}
