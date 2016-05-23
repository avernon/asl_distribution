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

import org.alljoyn.ns.Notification;

public class NotificationWrapper
{

    public enum ReadStatus
    {
        NEW,
        CLEARED,
        READ,
    }

    private ReadStatus m_readStatus;

    long m_time;
    Notification m_notification;

    public NotificationWrapper(Notification notification, long time)
    {
        m_notification = notification;
        m_readStatus = ReadStatus.NEW;
        m_time = time;
    }

    public long getTime()
    {
        return m_time;
    }

    public Notification getNotification()
    {
        return m_notification;
    }

    public void markAsCleared()
    {
        // if a notification is "read", that also implies it's cleared
        if (m_readStatus != ReadStatus.READ)
        {
            m_readStatus = ReadStatus.CLEARED;
        }
    }

    public void markAsRead()
    {
        m_readStatus = ReadStatus.READ;
    }

    public ReadStatus getReadStatus()
    {
        return m_readStatus;
    }

}
