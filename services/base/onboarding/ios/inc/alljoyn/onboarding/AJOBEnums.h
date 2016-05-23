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

/**
 * Enumerator for validation error: VALIDATED = 0, UNREACHABLE, UNSUPPORTEDPROTOCOL, UNAUTHORIZED, ERRORMESSAGE
 */
typedef NS_ENUM (NSInteger, AJOBValidationState){
    /***
     * WIFI configuration was successful
     */
    VALIDATED = 0,
    /***
     * WIFI not found
     */
    UNREACHABLE = 1,
    /***
     * using incorrect authentication type
     */
    UNSUPPORTEDPROTOCOL = 2,
    /***
     * pass phrase not correct
     */
    UNAUTHORIZED = 3,
    /***
     * general error message
     */
    ERRORMESSAGE = 4,
};

/**
 * Enumerator for authentication type
 */
typedef NS_ENUM (NSInteger, AJOBAuthType) {
    /***
     * WPA2_AUTO authentication
     */
    WPA2_AUTO = -3,
    /***
     * WPA2_AUTO authentication
     */
    WPA_AUTO = -2,
    /***
     * WPA2_AUTO authentication
     */
    ANY = -1,
    /***
     * WPA2_AUTO authentication
     */
    OPEN = 0,
    /***
     * WPA2_AUTO authentication
     */
    WEP = 1,
    /***
     * WPA2_AUTO authentication
     */
    WPA_TKIP = 2,
    /***
     * WPA2_AUTO authentication
     */
    WPA_CCMP = 3,
    /***
     * WPA2_AUTO authentication
     */
    WPA2_TKIP = 4,
    /***
     * WPA2_AUTO authentication
     */
    WPA2_CCMP = 5,
    /***
     * WPA2_AUTO authentication
     */
    WPS = 6,
};

/**
 * NS_ENUM for concurrency availability
 */
typedef NS_ENUM (NSInteger, AJOBConcurrency) {
    /***
     * CONCURRENCY_MIN
     */
    CONCURRENCY_MIN = 1,
    /***
     * CONCURRENCY_NONE
     */
    CONCURRENCY_NONE = 1,
    /***
     * CONCURRENCY_AVAIL
     */
    CONCURRENCY_AVAIL = 2,
    /***
     * CONCURRENCY_MAX
     */
    CONCURRENCY_MAX = 2
};

/**
 * Enumerator for state of onboarding namely: NOT_CONFIGURED, CONFIGURED_NOT_VALIDATED, CONFIGURED_VALIDATING, CONFIGURED_VALIDATED, CONFIGURED_ERROR, CONFIGURED_RETRY
 */
typedef NS_ENUM (NSInteger, AJOBState) {
    /***
     * NOT_CONFIGURED blank configuration
     */
    NOT_CONFIGURED = 0,
    /***
     * CONFIGURED_NOT_VALIDATED configuration has been set but didn't validated it.
     */
    CONFIGURED_NOT_VALIDATED,
    /***
     * CONFIGURED_VALIDATING configuration has been set in checking state.
     */
    CONFIGURED_VALIDATING,
    /***
     * CONFIGURED_VALIDATED configuration has been set and validated.
     */
    CONFIGURED_VALIDATED,
    /***
     * CONFIGURED_ERROR configuration has been set and there was an error.
     */
    CONFIGURED_ERROR,
    /***
     * CONFIGURED_RETRY configuration has been set and there was an error in retry mode.
     */
    CONFIGURED_RETRY,
} ;