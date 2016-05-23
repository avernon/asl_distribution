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

import java.util.Map;
import java.util.UUID;

import org.alljoyn.about.transport.AboutTransport;
import org.alljoyn.about.transport.IconTransport;

// if the device has not been on boarded, this is the actual device (Coffee machine, toaster oven etc.)
// if the device has on boarded,this is the application that runs on the machine.
// (machine can have more than one application running on it) 
public interface Device {

    public enum IconDataRequestType {
        EMPTY("EMPTY"), SDCARD("SDCARD"), RESOURCE("RESOURCE"), DEVICE_CONTENT("DEVICE_CONTENT");

        private String brandname;

        private IconDataRequestType(String brand) {
            this.brandname = brand;
        }

        @Override
        public String toString() {
            return brandname;
        }
    }

    public enum DeviceStatus {
        AVAILABLE, UNAVAILABLE,
    }

    public static String DEVICE_TAG_LAST_ACTION = "device_tag_last_action";

    public enum DeviceAction {
        // About
        GET_ABOUT,
        // About Icon
        GET_ICON_MIME_TYPE, GET_ICON_URL, GET_ICON_SIZE,
    }

    public enum ServiceType {
        ABOUT(AboutTransport.INTERFACE_NAME), ABOUT_ICON(IconTransport.INTERFACE_NAME), NOTIFICATION("org.alljoyn.Notification");

        private String m_interface = "";

        private ServiceType(String interfaceName) {
            m_interface = interfaceName;
        }

        public String getInterface() {
            return m_interface;
        }

    }// enum

    // Tag manage
    public Object getTag(String key);

    public void setTag(String key, Object value);

    public Map<String, Object> getAllTags();

    public boolean hasTag(String key);

    public void removeTag(String key);

    public UUID getId();

    public void setDefaultLanguage(String l);

    public String getDefaultLanguage();

    public String getFriendlyName();

    public DeviceStatus getStatus();

    public void setHelpUrl(String l);

    public String getHelpURL();

    public void turnOnNotifications();

    public void turnOffNotifications();

    public boolean isNotificationOn();

    public Map<String, Object> getAbout(String language, boolean force);

    public int getIconSize();

    public DeviceResponse getIconUrl();

    public DeviceResponse getDeviceIconContent();

    public String getStoredIconUrl();

    public void setStoredIconUrl(String url);

    public String getIconMimeType();

    boolean isServiceSupported(ServiceType service);

};
