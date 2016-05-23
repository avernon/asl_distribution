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
package org.alljoyn.dashboard.ui.application;

import java.util.Iterator;

import org.alljoyn.ns.Notification;
import org.alljoyn.dashboard.R;
import org.alljoyn.dashboard.logic.NotificationsManagerImpl;
import org.alljoyn.dashboard.logic.Interface.Device;
import org.alljoyn.dashboard.logic.Interface.NotificationWrapper;
import org.alljoyn.dashboard.logic.Interface.NotificationWrapper.ReadStatus;
import org.alljoyn.dashboard.ui.util.UIUtil;

import android.annotation.TargetApi;
import android.app.Notification.Builder;
import android.app.Notification.InboxStyle;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.media.AudioManager;
import android.net.Uri;
import android.os.Build;
import android.preference.PreferenceManager;
import android.util.Log;

public class NativeNotificationHandler
{
    private static final String TAG = "DASHBOARD_NativeNotificationHandler";

    private static int NOTIF_ID = 1;
    private static int LAST_CLEARED_NOTIF_ID = NOTIF_ID;

    // intent fired when user selects native notification
    public static final String NOTIFICATION_CLEARED_ACTION = "NOTIFICATION_CLEARED";

    public static void clearNativeNotificationBar(Context context) {
        try	{
            for (int id = LAST_CLEARED_NOTIF_ID; id <= NOTIF_ID; id++) {
                ((NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE)).cancel(id);
            }
            LAST_CLEARED_NOTIF_ID = NOTIF_ID;
        }
        catch (Exception e) {
            Log.e(TAG, "Error calling context.getSystemService(Context.NOTIFICATION_SERVICE)).cancel",e);
        }
    }

    @TargetApi(Build.VERSION_CODES.JELLY_BEAN)
    public static void display(Context context, Notification dbNotification, long time, Intent launchIntent)
    {
        final Device device = UIUtil.getDevice(dbNotification.getAppId());
        final String notificationTitle = (device != null) ? device.getFriendlyName() : dbNotification.getDeviceName();
        final String notificationBody = UIUtil.getNotificationTextAsString(dbNotification);
        final String tickerText = notificationTitle + ": " + notificationBody;
        final String shortTickerText = tickerText.length() > 160 ? tickerText.substring(0, 160) + context.getString(R.string.ellipsis) : tickerText;
        final int nativeNotificationIcon = R.drawable.app_logo_title;

        // set the intent to launch when notification is clicked
        final PendingIntent pendingIntent = PendingIntent.getActivity(context, 0, launchIntent, PendingIntent.FLAG_UPDATE_CURRENT);

        // init the notification based on OS version
        android.app.Notification nativeNotification;
        if (android.os.Build.VERSION.SDK_INT >= 16)
        {
            final int numUncleared = NotificationsManagerImpl.getInstance().getUnclearedNotificationsCount();
            Builder notifBuilder = new Builder(context)
            .setContentIntent(pendingIntent)
            .setTicker(shortTickerText)
            .setWhen(time)
            .setSmallIcon(nativeNotificationIcon);

            final InboxStyle inboxStyle = new InboxStyle(notifBuilder);

            if (numUncleared > 1)
            {
                String message = numUncleared + " new notifications";

                inboxStyle.setBigContentTitle(message);
                notifBuilder.setContentTitle(message);

                NotificationWrapper nw;
                Device nextDevice;
                String nextTitle, nextBody, nextText;
                final Iterator<NotificationWrapper> iter = NotificationsManagerImpl.getInstance().getNotificationList().iterator();
                while (iter.hasNext())
                {
                    nw = iter.next();
                    if (nw.getReadStatus() == ReadStatus.NEW)
                    {
                        nextDevice = UIUtil.getDevice(nw.getNotification().getAppId());
                        nextTitle = (nextDevice != null) ? nextDevice.getFriendlyName() : nw.getNotification().getDeviceName();
                        nextBody = UIUtil.getNotificationTextAsString(nw.getNotification());
                        nextText = nextTitle + ": " + nextBody;

                        inboxStyle.addLine(nextText);
                    }
                }
            }
            else
            {
                notifBuilder.setContentTitle(notificationTitle)
                .setContentText(notificationBody);
                inboxStyle.setBigContentTitle(notificationTitle);
                inboxStyle.addLine(notificationBody);
            }

            nativeNotification = inboxStyle.build();
        }
        else if (android.os.Build.VERSION.SDK_INT >= 11)
        {
            nativeNotification = new android.app.Notification.Builder(context)
            .setContentTitle(notificationTitle)
            .setContentText(notificationBody)
            .setContentIntent(pendingIntent)
            .setTicker(shortTickerText)
            .setWhen(time)
            .setSmallIcon(nativeNotificationIcon)
            .getNotification();

            NOTIF_ID++;
        }
        else
        {
            nativeNotification = new android.app.Notification(nativeNotificationIcon, shortTickerText, time);
            nativeNotification.setLatestEventInfo(context, notificationTitle, notificationBody, pendingIntent);

            NOTIF_ID++;
        }

        // set sound and vibrate settings
        Log.d(TAG, "set sound and vibrate settings.");
        int notificationType = 0;
        final SharedPreferences pref = PreferenceManager.getDefaultSharedPreferences(context);
        final boolean shouldVibrate = pref.getBoolean(context.getString(R.string.settings_vibrate_key), true);

        final AudioManager audioManager = (AudioManager) context.getSystemService(Context.AUDIO_SERVICE);
        if (shouldVibrate && audioManager.getRingerMode() != AudioManager.RINGER_MODE_SILENT)
        {
            notificationType |= android.app.Notification.DEFAULT_VIBRATE;
        }

        final String notificationUri = pref.getString(context.getString(R.string.settings_ringtone_key), null);
        if (notificationUri != null)
        {
            nativeNotification.sound = Uri.parse(notificationUri);
        }
        else
        {
            notificationType |= android.app.Notification.DEFAULT_SOUND;
        }
        nativeNotification.defaults = notificationType;

        // cancel notification when clicked
        nativeNotification.flags |= android.app.Notification.FLAG_AUTO_CANCEL;

        final Intent deleteIntent = new Intent(context, NotificationsManagerImpl.class);
        deleteIntent.setAction(NOTIFICATION_CLEARED_ACTION);
        nativeNotification.deleteIntent = PendingIntent.getBroadcast(context, 0, deleteIntent, 0);

        // generate notification
        Log.d(TAG, "generate notification.");
        ((NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE)).notify(NOTIF_ID, nativeNotification);
    }


}
