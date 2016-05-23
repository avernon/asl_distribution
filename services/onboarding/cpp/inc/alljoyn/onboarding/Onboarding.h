/******************************************************************************
 * Copyright (c) 2013, AllSeen Alliance. All rights reserved.
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

#ifndef _ONBOARDING_H
#define _ONBOARDING_H

#include <qcc/platform.h>
#include <qcc/String.h>

#define MAX_SSID_SIZE 32
#define MIN_PSK_SIZE 8
#define MAX_PSK_SIZE 64

namespace ajn {
namespace services {

/**
 * Enumerator for validation error: VALIDATED = 0, UNREACHABLE, UNSUPPORTEDPROTOCOL, UNAUTHORIZED, ERRORMESSAGE
 */
typedef enum {
    VALIDATED = 0,    //!< VALIDATED WIFI configuration was successful
    UNREACHABLE = 1, //!< UNREACHABLE   WIFI not found
    UNSUPPORTEDPROTOCOL = 2, //!< UNSUPPORTEDPROTOCOL using incorrect authentication type
    UNAUTHORIZED = 3, //!< UNAUTHORIZED pass phrase not correct
    ERRORMESSAGE = 4, //!< ERRORMESSAGE  general error message
} OBValidationState;

/**
 * Enumerator for authentication type namely: Any = -1, OPEN = 0, WEP, WPA, WPA2, WPS
 */
typedef enum {
    WPA2_AUTO = -3,                            //!< WPA2_AUTO authentication
    WPA_AUTO = -2,                           //!< WPA_AUTO authentication
    ANY = -1,                           //!< ANY authentication
    OPEN = 0,                          //!< OPEN authentication
    WEP = 1,                           //!< WEP authentication
    WPA_TKIP = 2,                           //!< WPA_TKIP authentication
    WPA_CCMP = 3,                           //!< WPA_CCMP authentication
    WPA2_TKIP = 4,                            //!<WPA2_TKIP authentication
    WPA2_CCMP = 5,                        //!<WPA2_CCMP authentication
    WPS = 6,                          //!<WPS authentication


} OBAuthType;

/**
 * Enum for concurrency availability
 */
typedef enum {
    CONCURRENCY_MIN = 1,
    CONCURRENCY_NONE = 1,
    CONCURRENCY_AVAIL = 2,
    CONCURRENCY_MAX = 2
} OBConcurrency;

/**
 * Structure to hold Scan info
 */
typedef struct {
    /**
     * AP SSID
     */
    qcc::String SSID;
    /**
     *  AP authentication type
     */
    OBAuthType authType;
} OBScanInfo;

/**
 * Enumerator for state of onboarding namely: NOT_CONFIGURED, CONFIGURED_NOT_VALIDATED, CONFIGURED_VALIDATING, CONFIGURED_VALIDATED, CONFIGURED_ERROR, CONFIGURED_RETRY
 */
typedef enum {
    NOT_CONFIGURED = 0, //!< NOT_CONFIGURED blank configuration
    CONFIGURED_NOT_VALIDATED, //!< CONFIGURED_NOT_VALIDATED configuration has been set but didn't validated it.
    CONFIGURED_VALIDATING, //!< CONFIGURED_VALIDATING configuration has been set in checking state.
    CONFIGURED_VALIDATED, //!< CONFIGURED_VALIDATED configuration has been set and validated.
    CONFIGURED_ERROR, //!< CONFIGURED_ERROR configuration has been set and there was an error.
    CONFIGURED_RETRY, //!< CONFIGURED_RETRY configuration has been set and there was an error in retry mode.
} OBState;

/**
 *	Structure to hold the WIFI details
 */
typedef struct {
    /**
     *	SSID is the WIFI's SSID
     */
    qcc::String SSID;
    /**
     *  state is current state
     */
    OBState state;
    /**
     *  WIFI authentication type
     */
    OBAuthType authType;
    /**
     * WIFI passcode
     */
    qcc::String passcode;
} OBInfo;


/**
 * Structure to hold the Last error received from the WIFI connection
 */
typedef struct {
    /**
     *	last validated state.
     */
    short validationState;
    /**
     *  error message
     */
    qcc::String message;
}OBLastError;

inline bool isValidWEPKey(qcc::String key)
{
    size_t size = key.size();
    return (size == 5  ||  // 40-bit ascii
            size == 10 ||  // 40 bit hex
            size == 13 ||  // 104 bit ascii
            size == 26 ||  // 104 bit hex
            size == 16 ||  // 152 bit ascii
            size == 32 ||  // 152-bit hex
            size == 29 ||  // 256-bit ascii
            size == 64);   // 256-bit hex
}

inline bool isValidWPAKey(qcc::String key)
{
    return key.size() >= MIN_PSK_SIZE && key.size() <= MAX_PSK_SIZE;
}

}
}

#endif
