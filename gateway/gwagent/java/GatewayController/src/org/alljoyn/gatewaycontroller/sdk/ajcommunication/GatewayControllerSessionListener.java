/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

package org.alljoyn.gatewaycontroller.sdk.ajcommunication;

import org.alljoyn.bus.SessionListener;
import org.alljoyn.gatewaycontroller.sdk.ajcommunication.CommunicationUtil.SessionResult;

import android.util.Log;

/**
 * This class is responsible for handling session related events from the
 * AllJoyn system. Extend this class to receive the events of: <br>
 * - sessionJoined <br>
 * - sessioLost <br>
 * 
 * The events are called on the AllJoyn thread, so avoid blocking them with long
 * running tasks.
 */
public class GatewayControllerSessionListener extends SessionListener {
    private static final String TAG = "gwc" + GatewayControllerSessionListener.class.getSimpleName();

    /**
     * Receives sessionLost event. Avoid blocking this thread with long running
     * tasks.
     * 
     * @param sessionId
     *            The id of the lost session
     * @param reason
     *            The reason of the lost session
     * @see org.alljoyn.bus.SessionListener#sessionLost(int, int)
     */
    @Override
    public void sessionLost(int sessionId, int reason) {
        Log.d(TAG, "Received SESSION_LOST for SID: '" + sessionId + "', reason: '" + reason + "'");
    }

    /**
     * Receives result of joining session asynchronously. Avoid blocking this
     * thread with long running tasks.
     * 
     * @param result
     */
    public void sessionJoined(SessionResult result) {
        Log.d(TAG, "SESSION_JOINED: '" + result + "'");
    }

}
