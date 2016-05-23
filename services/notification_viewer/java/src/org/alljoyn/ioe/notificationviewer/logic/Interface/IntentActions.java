/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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
 ******************************************************************************/

package org.alljoyn.ioe.notificationviewer.logic.Interface;

public class IntentActions {

    // FOR INTENTS
    public static final String ACTION_REFRESH = "org.alljoyn.ioe.android.new_data_action";

    public static final String ACTION_DEVICE_FOUND = "org.alljoyn.ioe.device_found";
    public static final String ACTION_DEVICE_LOST = "org.alljoyn.ioe.device_lost";
    public static final String ACTION_NEW_NOTIFICATION_ARRIVED = "org.alljoyn.ioe.new_notification_arrived";
    public static final String ACTION_NEW_NOTIFICATION_REMOVED = "org.alljoyn.ioe.new_notification_removed";

    public static final String ACTION_TVNOTIFICATION_VIEWER_ICON_AVAILABLE = "org.alljoyn.ioe.notificationviewer.device_icon_available";
    public static final String EXTRA_APP_ID = "appId";
    public static final String EXTRA_IS_NOTIFICATION_WITH_IMAGE = "isNotificationWithImage";
    public static final String EXTRA_VIEW_ID = "viewId";

    public static final String ACTION_SESSION_LOST_WITH_DEVICE = "org.alljoyn.ioe.session_lost_with_device";

    public static final String ACTION_DEVICE_STATUS_CHANGED = "org.alljoyn.ioe.device_status_state";
}
