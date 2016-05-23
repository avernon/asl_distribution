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

package org.alljoyn.ioe.notificationviewer.logic;

import java.security.MessageDigest;
import java.util.ArrayList;
import java.util.Set;

import org.alljoyn.services.common.utils.GenericLogger;

import android.content.Context;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.util.Log;

public class Util {
    private static final String TAG = "Util";
    public static SharedPreferences pref;

    private static final GenericLogger m_logger = new GenericLogger() {
        @Override
        public void debug(String TAG, String msg) {
            Log.d(TAG, msg);
        }

        @Override
        public void info(String TAG, String msg) {
            // To change body of implemented methods use File | Settings | File Templates.
            Log.i(TAG, msg);
        }

        @Override
        public void warn(String TAG, String msg) {
            // To change body of implemented methods use File | Settings | File Templates.
            Log.w(TAG, msg);
        }

        @Override
        public void error(String TAG, String msg) {
            // To change body of implemented methods use File | Settings | File Templates.
            Log.e(TAG, msg);
        }

        @Override
        public void fatal(String TAG, String msg) {
            // To change body of implemented methods use File | Settings | File Templates.
            Log.wtf(TAG, msg);
        }
    };

    public static void saveDevices(ArrayList<DeviceImpl> devices) {

    }

    public static ArrayList<DeviceImpl> uploadDevices() {
        return null;
    }

    public static GenericLogger getGenericLogger() {
        return m_logger;
    }

    public static String calcMD5FromString(String input) {
        if (input == null || input.length() == 0) {
            return null;
        }
        try {
            MessageDigest hashEngine = MessageDigest.getInstance("MD5");
            hashEngine.update(input.getBytes("iso-8859-1"), 0, input.length());
            return convertToHex(hashEngine.digest());
        } catch (Exception e) {
            return null;
        }
    }

    public static final String convertToHex(byte[] data) {
        if (data == null || data.length == 0) {
            return null;
        }
        StringBuilder r = new StringBuilder(data.length * 2);
        for (byte b : data) {
            r.append(HEX_CODE[(b >> 4) & 0xF]);
            r.append(HEX_CODE[(b & 0xF)]);
        }
        String hexadecimalString = r.toString();

        return hexadecimalString;
    }

    public static String convertHexToString(String hex) {

        m_logger.debug(TAG, "convertHexToString: " + hex);
        if (hex == null || hex.length() % 2 != 0)
            return "";

        StringBuilder sb = new StringBuilder();

        // split into two characters
        for (int i = 0; i < hex.length() - 1; i += 2) {

            // grab the hex in pairs
            String output = hex.substring(i, (i + 2));
            // convert hex to decimal
            int decimal = Integer.parseInt(output, 16);
            // convert the decimal to character
            sb.append((char) decimal);
        }
        m_logger.debug(TAG, "convertHexToString: " + sb.toString());
        return sb.toString();
    }

    /**
     * A utility for conversion of password to hexa array
     */
    private static final char[] HEX_CODE = "0123456789ABCDEF".toCharArray();

    public static String bundleToString(Bundle bundle) {
        if (bundle == null)
            return "";
        Set<String> keys = bundle.keySet();
        if (keys == null || keys.size() == 0)
            return "";
        StringBuilder s = new StringBuilder();
        for (String key : keys) {
            s.append("  " + key + " = " + bundle.get(key));
        }
        return s.toString();
    }

    public static String getDensityName(Context context) {
        float density = context.getResources().getDisplayMetrics().density;
        if (density >= 4.0) {
            return "xxxhdpi";
        }
        if (density >= 3.0) {
            return "xxhdpi";
        }
        if (density >= 2.0) {
            return "xhdpi";
        }
        if (density >= 1.5) {
            return "hdpi";
        }
        if (density >= 1.0) {
            return "mdpi";
        }
        return "ldpi";
    }
}
