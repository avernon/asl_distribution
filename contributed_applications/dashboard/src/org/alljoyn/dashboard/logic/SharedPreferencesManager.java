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

import java.util.Map;
import java.util.Set;
import java.util.UUID;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.util.Log;

public class SharedPreferencesManager
{
    private static SharedPreferences devicesSp;
    private static String DEVICES = "devices";


    public static final String keyValueSeparator = "=";
    public static final String pairsSeparator = ";";
    // Device constants
    public static final String deviceSsid         = "SSID";
    public static final String deviceId           = "ID";
    public static final String deviceFriendlyName = "friendlyName";
    public static final String devicePassword     = "password";
    public static final String deviceOnboardedNet ="onboardedNetworkSSID";
    public static final String deviceIconUrl ="iconUrl";


    private final static String  TAG = "DASHBOARD_SharedPreferencesManager";

    public static void init(Context c)
    {
        devicesSp = c.getSharedPreferences(DEVICES, Context.MODE_PRIVATE);
    }

    public static void saveDevice(UUID m_uniqueId, String deviceDescription)
    {
        if (m_uniqueId == null || deviceDescription == null) {
            return;
        }
        Log.d(TAG, "save device to preferencese, id = " + m_uniqueId + " device description = " + deviceDescription);
        if (devicesSp == null)
        {
            Log.e(TAG, "devicesSp == null");
            return;
        }
        Editor e = devicesSp.edit();

        e.putString(m_uniqueId.toString(), deviceDescription);
        e.commit();
    }

    public static void removeDevice(UUID m_uniqueId)
    {
        Log.d(TAG, "remove device from preferencese, id = " + m_uniqueId);
        if (devicesSp == null)
        {
            Log.e(TAG, "devicesSp == null");
            return;
        }
        Editor e = devicesSp.edit();

        e.remove(m_uniqueId.toString());
        e.commit();
    }

    public static void updateDevice(UUID m_uniqueId, String deviceNewDescription)
    {
        Log.d(TAG, "update device in preferencese, id = " + m_uniqueId + " device new  description = " + deviceNewDescription);
        if (devicesSp == null)
        {
            Log.e(TAG, "devicesSp == null");
            return;
        }
        Editor e = devicesSp.edit();

        e.remove(m_uniqueId.toString());
        e.putString(m_uniqueId.toString(), deviceNewDescription);

        e.commit();
    }

    public static Map<String, String> getAllDevices()
    {
        if (devicesSp == null) {
            return null;
        }
        Map<String, String> allDevices = (Map<String, String>) devicesSp.getAll();
        if(allDevices != null) {
            StringBuilder s = new StringBuilder();
            Set<String> keys = allDevices.keySet();
            for (String key : keys) {
                s.append('{').append("id=").append(key).append(':').append(allDevices.get(key)).append('}');
            }
            Log.d(TAG, "getAllDevices: " + s.toString());
        }
        return allDevices;
    }
}
