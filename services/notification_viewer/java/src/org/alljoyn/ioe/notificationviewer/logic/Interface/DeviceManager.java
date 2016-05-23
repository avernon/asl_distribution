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

import java.util.Collection;
import java.util.UUID;

import android.content.Context;
import android.graphics.Bitmap;

public interface DeviceManager {

    public static String ABOUT_ICON_DEFAULT_URL = "local://defaultURL";
    public static String ABOUT_ICON_LOCAL_PREFIX_URL = "local://DeviceContent/";

    public void init(Context c, String keyStorekeyStoreFileName);

    public Collection<Device> getDevices();

    public Device getDevice(UUID deviceID);

    public boolean contains(UUID deviceID);

    Device removeDevice(UUID deviceID);

    public boolean isDeviceUsingDefaultImage(UUID deviceID);

    public Bitmap getDeviceImage(UUID deviceID, boolean isNotificationWithImage, int idOfLayoutContainingIconView);

}
