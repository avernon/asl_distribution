/**
 * @file
 * This contains the AboutData class responsible for holding the org.alljoyn.About
 * interface data fields.
 */
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
#ifndef _ALLJOYN_ABOUTKEYS_H
#define _ALLJOYN_ABOUTKEYS_H

#include <alljoyn/AboutDataListener.h>
#include <alljoyn/MsgArg.h>
#include <alljoyn/Status.h>

#include <qcc/String.h>

namespace ajn {

/**
 * AboutKeys
 */
class AboutKeys {
  public:
    /**
     * @anchor AboutFields
     * @name Known AboutFields
     *
     * The known fields in the About interface
     * TODO put in a table listing the properties for all of the about fields
     */
    // @{
    static const char* APP_ID;           ///< The globally unique id for the application
    static const char* DEFAULT_LANGUAGE; ///< The default language supported by the device. IETF language tags specified by RFC 5646.
    static const char* DEVICE_NAME; ///< The name of the device
    static const char* DEVICE_ID; ///< A unique string with a value generated using platform specific means
    static const char* APP_NAME; ///< The application name assigned by the manufacture
    static const char* MANUFACTURER; ///< The manufacture's name
    static const char* MODEL_NUMBER; ///< The application model number
    static const char* SUPPORTED_LANGUAGES; ///< List of supported languages
    static const char* DESCRIPTION; ///< Detailed description provided by the application
    static const char* DATE_OF_MANUFACTURE; ///< The date of manufacture using format YYYY-MM-DD
    static const char* SOFTWARE_VERSION; ///< The software version for the OEM software
    static const char* AJ_SOFTWARE_VERSION; ///< The current version of the AllJoyn SDK utilized by the application
    static const char* HARDWARE_VERSION; ///< The device hardware version
    static const char* SUPPORT_URL; ///< The support URL provided by the OEM or software developer
    // @}
};
}
#endif //_ALLJOYN_ABOUTKEYS_H
