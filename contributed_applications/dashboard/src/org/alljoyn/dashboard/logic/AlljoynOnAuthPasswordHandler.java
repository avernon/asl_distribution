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
package org.alljoyn.dashboard.logic;

import org.alljoyn.dashboard.logic.Interface.Device;
import org.alljoyn.dashboard.logic.Interface.IntentActions;
import org.alljoyn.dashboard.logic.Interface.IntentExtraKeys;
import org.alljoyn.dashboard.login.security.AuthPasswordHandler;

import android.os.Bundle;
import android.util.Log;

public class AlljoynOnAuthPasswordHandler implements AuthPasswordHandler {

    private final String           TAG = this.getClass().getName();

    @Override
    public char[] getPassword(String peerName) {
        Device d = ((DeviceManagerImpl)DeviceManagerImpl.getInstance()).getDeviceByServiceName(peerName);
        if (d  != null)
        {
            Log.d(TAG, "getPassword for device " + d.getFriendlyName() + " authPeer(serviceName)= " + peerName + " --> " + String.valueOf(d.getPassphrase()));
            return d.getPassphrase();
        }
        return Device.DEFAULT_PINCODE;
    }

    @Override
    public void completed(String mechanism, String authPeer, boolean authenticated) {
        Log.d(TAG, "Auth completed: mechanism = " + mechanism + " authPeer= " + authPeer + " --> " + authenticated);
        Device d = ((DeviceManagerImpl)DeviceManagerImpl.getInstance()).getDeviceByServiceName(authPeer);
        if (d  != null)
        {
            String ajOnDeviceAuthenticationResult = authenticated ?
                    IntentActions.AJ_ON_DEVICE_AUTHENTICATION_SUCCESS :
                        IntentActions.AJ_ON_DEVICE_AUTHENTICATION_ERROR;
            Bundle extra = new Bundle();
            if (d.getId() != null) {
                extra.putSerializable(IntentExtraKeys.EXTRA_DEVICE_ID, d.getId());
            }
            if (d.getAPWifiInfo() != null) {
                extra.putString(IntentExtraKeys.EXTRA_DEVICE_SSID, d.getAPWifiInfo().getSSID());
            }
            ((DeviceManagerImpl)DeviceManagerImpl.getInstance()).updateTheUi(ajOnDeviceAuthenticationResult,extra);
        }
    }
}
