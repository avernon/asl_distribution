/******************************************************************************
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
 ******************************************************************************/

package org.alljoyn.about;

import static org.junit.Assert.*;

import org.alljoyn.about.AboutKeys;
import org.junit.Test;

public class AboutKeysTest {
    @Test
    public void testKeys() {
        assertEquals("AppId", AboutKeys.ABOUT_APP_ID);
        assertEquals("DefaultLanguage", AboutKeys.ABOUT_DEFAULT_LANGUAGE);
        assertEquals("DeviceName", AboutKeys.ABOUT_DEVICE_NAME);
        assertEquals("DeviceId", AboutKeys.ABOUT_DEVICE_ID);
        assertEquals("AppName", AboutKeys.ABOUT_APP_NAME);
        assertEquals("Manufacturer", AboutKeys.ABOUT_MANUFACTURER);
        assertEquals("ModelNumber", AboutKeys.ABOUT_MODEL_NUMBER);
        assertEquals("SupportedLanguages", AboutKeys.ABOUT_SUPPORTED_LANGUAGES);
        assertEquals("Description", AboutKeys.ABOUT_DESCRIPTION);
        assertEquals("DateOfManufacture", AboutKeys.ABOUT_DATE_OF_MANUFACTURE);
        assertEquals("SoftwareVersion", AboutKeys.ABOUT_SOFTWARE_VERSION);
        assertEquals("AJSoftwareVersion", AboutKeys.ABOUT_AJ_SOFTWARE_VERSION);
        assertEquals("HardwareVersion", AboutKeys.ABOUT_HARDWARE_VERSION);
        assertEquals("SupportUrl", AboutKeys.ABOUT_SUPPORT_URL);
    }

    @Test
    public void testImplementAboutKeys(){
        class AboutKeysImpl implements AboutKeys {
            public final static String ABOUT_CUSTOM_KEY = "CustomKey";
        }

        assertEquals("AppId", AboutKeysImpl.ABOUT_APP_ID);
        assertEquals("DefaultLanguage", AboutKeysImpl.ABOUT_DEFAULT_LANGUAGE);
        assertEquals("DeviceName", AboutKeysImpl.ABOUT_DEVICE_NAME);
        assertEquals("DeviceId", AboutKeysImpl.ABOUT_DEVICE_ID);
        assertEquals("AppName", AboutKeysImpl.ABOUT_APP_NAME);
        assertEquals("Manufacturer", AboutKeysImpl.ABOUT_MANUFACTURER);
        assertEquals("ModelNumber", AboutKeysImpl.ABOUT_MODEL_NUMBER);
        assertEquals("SupportedLanguages", AboutKeysImpl.ABOUT_SUPPORTED_LANGUAGES);
        assertEquals("Description", AboutKeysImpl.ABOUT_DESCRIPTION);
        assertEquals("DateOfManufacture", AboutKeysImpl.ABOUT_DATE_OF_MANUFACTURE);
        assertEquals("SoftwareVersion", AboutKeysImpl.ABOUT_SOFTWARE_VERSION);
        assertEquals("AJSoftwareVersion", AboutKeysImpl.ABOUT_AJ_SOFTWARE_VERSION);
        assertEquals("HardwareVersion", AboutKeysImpl.ABOUT_HARDWARE_VERSION);
        assertEquals("SupportUrl", AboutKeysImpl.ABOUT_SUPPORT_URL);
        assertEquals("CustomKey", AboutKeysImpl.ABOUT_CUSTOM_KEY);
    }

}
