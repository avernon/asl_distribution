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

/**
 * About keys as defined by HLD
 *
 * @deprecated please see org.alljoyn.bus.AboutKeys class
 */
@Deprecated
public interface AboutKeys {
    /**
     * Required. If Config service exists on the device, About instance
     * populates the DeviceId as per Config service; If there is no Config on
     * the device, it is set using the platform specific means
     */
    public final static String ABOUT_DEVICE_ID = "DeviceId";

    /**
     * Required. If Config service exists on the device, About instance
     * populates the value as DeviceName in Config; If there is no Config, it is
     * set by platform specific means and reflected in About
     */
    public final static String ABOUT_DEVICE_NAME = "DeviceName";

    /**
     * Required. The globally unique id for the application
     */
    public final static String ABOUT_APP_ID = "AppId";

    /**
     * Required. This field specifies the Application Name. It is assigned by
     * the App Manufacturer
     */
    public final static String ABOUT_APP_NAME = "AppName";

    /**
     * Required. The manufacturer's name of the application.
     */
    public final static String ABOUT_MANUFACTURER = "Manufacturer";

    /**
     * Required. Detailed description
     */
    public final static String ABOUT_DESCRIPTION = "Description";

    /**
     * Required. The default language supported by the device. IETF language
     * tags specified by RFC 5646. It is populated by Config service when
     * present else it is specified by device specific means
     */
    public final static String ABOUT_DEFAULT_LANGUAGE = "DefaultLanguage";

    /**
     * Required. The software version for the OEM software.
     */
    public final static String ABOUT_SOFTWARE_VERSION = "SoftwareVersion";

    /**
     * Required. The current version of the AllJoyn SDK utilized by the
     * application.
     */
    public final static String ABOUT_AJ_SOFTWARE_VERSION = "AJSoftwareVersion";

    /**
     * Required. The application model number.
     */
    public final static String ABOUT_MODEL_NUMBER = "ModelNumber";

    /**
     * Optional. The date of manufacture using format YYYY-MM-DD (known as XML
     * DateTime Format)
     */
    public final static String ABOUT_DATE_OF_MANUFACTURE = "DateOfManufacture";

    /**
     * Optional. The device hardware version
     */
    public final static String ABOUT_HARDWARE_VERSION = "HardwareVersion";

    /**
     * Optional. The support URL to be populated by device OEM
     */
    public final static String ABOUT_SUPPORT_URL = "SupportUrl"; 

    /**
     * Required. This field returns the list of supported languages by the
     * device.
     */
    public final static String ABOUT_SUPPORTED_LANGUAGES = "SupportedLanguages";

}
