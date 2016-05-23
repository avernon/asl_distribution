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

#import "AJOBSOnboarding.h"
#import "alljoyn/about/AJNConvertUtil.h"

static NSString * const PASSCODE_FORMAT = @"%02X";

@implementation AJOBSOnboarding

+(bool)isValidWEPKey:(NSString *) key
{
    size_t size = [key length];
    return (size == 5  ||  // 40-bit ascii
            size == 10 ||  // 40 bit hex
            size == 13 ||  // 104 bit ascii
            size == 26 ||  // 104 bit hex
            size == 16 ||  // 152 bit ascii
            size == 32 ||  // 152-bit hex
            size == 29 ||  // 256-bit ascii
            size == 64);   // 256-bit hex
}

+(bool)isValidWPAKey:(NSString *) key
{
    return [key length] >= MIN_PSK_SIZE && [key length] <= MAX_PSK_SIZE;
}

+(NSString*)passcodeToHex:(NSString*) passcode
{
    const char *pass = [passcode UTF8String];
    NSMutableString *passcodeHex = [NSMutableString string];
    while (*pass) {
        [passcodeHex appendFormat:PASSCODE_FORMAT, *pass++ & BIT_MASK];
    }
    return passcodeHex;
}

+(ajn::services::OBInfo)toOBInfo:(AJOBInfo) ajOBInfo
{
    ajn::services::OBInfo obInfo;
    obInfo.SSID = [AJNConvertUtil convertNSStringToQCCString:ajOBInfo.SSID];
    obInfo.state = (ajn::services::OBState)ajOBInfo.state;
    obInfo.authType =  (ajn::services::OBAuthType)ajOBInfo.authType;
    obInfo.passcode = [AJNConvertUtil convertNSStringToQCCString:ajOBInfo.passcode];
    return obInfo;
}

+(AJOBInfo)toAJOBInfo:(ajn::services::OBInfo) obInfo
{
    AJOBInfo ajOBInfo;
    ajOBInfo.SSID = [AJNConvertUtil convertQCCStringtoNSString:obInfo.SSID];
    ajOBInfo.state = obInfo.state;
    ajOBInfo.authType = obInfo.authType;
    ajOBInfo.passcode = [AJNConvertUtil convertQCCStringtoNSString:obInfo.passcode];
    return ajOBInfo;
}

+(AJOBLastError)toAJOBLastError:(ajn::services::OBLastError) obLastError
{
    AJOBLastError ajOBLastError;
    ajOBLastError.validationState = obLastError.validationState;
    ajOBLastError.message = [AJNConvertUtil convertQCCStringtoNSString:obLastError.message];
    return ajOBLastError;
}

@end
