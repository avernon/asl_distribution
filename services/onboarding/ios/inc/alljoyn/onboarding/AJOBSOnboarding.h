/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

#import <Foundation/Foundation.h>
#import "alljoyn/onboarding/Onboarding.h"
#import "AJOBEnums.h"

#define MAX_SSID_SIZE 32
#define MIN_PSK_SIZE 8
#define MAX_PSK_SIZE 64

#define BIT_MASK 0x00FF

/**
 * AJOBSOnboarding class
 */
@interface AJOBSOnboarding: NSObject



/**
 *	Structure to hold the WIFI details
 */
typedef struct {
    /**
     *	SSID is the WIFI's SSID
     */
    NSString *SSID;
    /**
     *  state is current state
     */
    AJOBState state;
    /**
     *  WIFI authentication type
     */
    AJOBAuthType authType;
    /**
     * WIFI passcode
     */
    NSString *passcode;
} AJOBInfo;

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
    NSString *message;
}AJOBLastError;

/**
 * Convert passcode to Hex format.
 * @param passcode passcode to be covert.
 * @return Passcode in Hex format
 */
+(NSString*)passcodeToHex:(NSString*) passcode;

/**
 * Passcode validation for WEP authentication
 * @param key The passcode key
 * @return bool
 */
+(bool)isValidWEPKey:(NSString *) key;

/**
 * Passcode validation for WPA authentication
 * @param key The passcoce key
 * @return bool
 */
+(bool)isValidWPAKey:(NSString *) key;

/**
 * Convert AJOBInfo object to OBInfo object.
 * @param ajOBInfo The AJOBInfo object.
 * @return OBInfo object.
 */
+(ajn::services::OBInfo)toOBInfo:(AJOBInfo) ajOBInfo;

/**
 * Convert OBInfo object to AJOBInfo object.
 * @param obInfo The OBInfo object.
 * @return AJOBInfo object.
 */
+(AJOBInfo)toAJOBInfo:(ajn::services::OBInfo) obInfo;

/**
 * Convert OBLastError object to AJOBLastError object.
 * @param obLastError The OBLastError object.
 * @return AJOBLastError object.
 */
+(AJOBLastError)toAJOBLastError:(ajn::services::OBLastError) obLastError;

@end
