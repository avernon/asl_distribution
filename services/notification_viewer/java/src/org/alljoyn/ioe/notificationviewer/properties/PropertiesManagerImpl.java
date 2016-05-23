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

package org.alljoyn.ioe.notificationviewer.properties;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Properties;

import org.alljoyn.ioe.notificationviewer.Constants;

import android.os.Environment;

public class PropertiesManagerImpl implements PropertiesManager {

    private final static String PROPERTIES_FILEPATH = Environment.getExternalStorageDirectory().getAbsolutePath() + Constants.ALLJOYN_DIR + Constants.PROPERTIES_FILENAME;
    private final static String KEY_NOTIF_POPUP_TIMEOUT_IN_MS = "notif_popup_timeout_in_ms";
    private final static String KEY_NOTIF_FULLSCREEN_ALERT_TIMEOUT_IN_MS = "notif_fullscreen_alert_timeout_in_ms";
    
    private final static String DEFAULT_VALUE_NOTIF_POPUP_TIMEOUT_IN_MS = "45000";
    private final static String DEFAULT_VALUE_NOTIF_FULLSCREEN_ALERT_TIMEOUT_IN_MS = "10000";
    
    private Properties properties;
    
    @Override
    public void init() {
        properties = new Properties();
        File f = new File(PROPERTIES_FILEPATH);
        if (false == f.isFile()) {
            FileOutputStream out = null;
            try {
                properties.put(KEY_NOTIF_POPUP_TIMEOUT_IN_MS, DEFAULT_VALUE_NOTIF_POPUP_TIMEOUT_IN_MS);
                properties.put(KEY_NOTIF_FULLSCREEN_ALERT_TIMEOUT_IN_MS, DEFAULT_VALUE_NOTIF_FULLSCREEN_ALERT_TIMEOUT_IN_MS);
                
                File parentDir = f.getParentFile();
                if (null != parentDir && false == parentDir.isDirectory()) {
                    parentDir.mkdirs();
                }
                out = new FileOutputStream(PROPERTIES_FILEPATH);
                properties.store(out, null);
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            } finally {
                if (null != out) {
                    try {
                        out.close();
                    } catch (IOException e) {
                    }
                }
            }
        }
        else {
            FileInputStream in = null;
            try {
                in = new FileInputStream(PROPERTIES_FILEPATH);
                properties.load(in);
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            } finally {
                if (null != in) {
                    try {
                        in.close();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }
        }
    }

    @Override
    public int getNotificationPopupTimeoutInMs() {
        int retval = Integer.parseInt(DEFAULT_VALUE_NOTIF_POPUP_TIMEOUT_IN_MS);
        String valueNotifPopupTimeoutInSeconds = (String) properties.get(KEY_NOTIF_POPUP_TIMEOUT_IN_MS);
        if (null != valueNotifPopupTimeoutInSeconds) {
            try {
                retval = Integer.parseInt(valueNotifPopupTimeoutInSeconds);
            }
            catch (NumberFormatException nfe) {
                nfe.printStackTrace();
            }
        }
        return retval;
    }

    @Override
    public int getNotificationFullscreenAlertTimeoutInMs() {
        int retval = Integer.parseInt(DEFAULT_VALUE_NOTIF_FULLSCREEN_ALERT_TIMEOUT_IN_MS);
        String valueNotifPopupTimeoutInSeconds = (String) properties.get(KEY_NOTIF_FULLSCREEN_ALERT_TIMEOUT_IN_MS);
        if (null != valueNotifPopupTimeoutInSeconds) {
            try {
                retval = Integer.parseInt(valueNotifPopupTimeoutInSeconds);
            }
            catch (NumberFormatException nfe) {
                nfe.printStackTrace();
            }
        }
        return retval;
    }

}
