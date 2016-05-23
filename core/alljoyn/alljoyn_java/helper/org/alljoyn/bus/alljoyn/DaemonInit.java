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

package org.alljoyn.bus.alljoyn;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.wifi.WifiManager;
import android.os.Process;
import android.util.Log;

/**
 * This class is to ensure that AllJoyn daemon is initialized to be ready for accepting connections from clients.
 * Before invoking Connect() to BusAttachment, the application should call PrepareDaemon()/PrepareDaemonAsync()
 * if it expects to use the bundled daemon no other daemons are available. PrepareDaemon() waits until the daemon
 * initialization is done. PrepareDaemonAsync() is the async version of PrepareDaemon().
 *
 */
public class DaemonInit {

    private final static String TAG = "DaemonInit";
    private static Context sContext;

    public static BroadcastReceiver receiver;

    public static Context getContext(){
        return sContext;
    }

    /**
     * Initialize daemon service if needed.
     * First it checks whether any daemon is running; if no daemon is running, then it starts the APK daemon if it is installed;
     * If no APK daemon is installed, then starts the bundled daemon. This is a blocking call; it blocks until the daemon is ready or
     * no daemon is found. Thus only non-UI thread is allowed to call PrepareDaemon().
     * @param context The application context
     * @return true  if the daemon is ready for connection
     *         false if no daemon is available
     */
    public static boolean PrepareDaemon(Context context) {
        Log.v(TAG, "Android version : " + android.os.Build.VERSION.SDK_INT);

        sContext = context.getApplicationContext();
        Log.v(TAG, "Saved application context");

        return true;
    }

}
