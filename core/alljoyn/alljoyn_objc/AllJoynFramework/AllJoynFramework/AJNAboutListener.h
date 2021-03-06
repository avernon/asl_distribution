////////////////////////////////////////////////////////////////////////////////
// Copyright AllSeen Alliance. All rights reserved.
//
//    Contributed by Qualcomm Connected Experiences, Inc.,
//    with authorization from the AllSeen Alliance, Inc.
//    
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//    
//        http://www.apache.org/licenses/LICENSE-2.0
//    
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//    
//    Pursuant to Section 1 of the License, the work of authorship constituting
//    a Work and any Contribution incorporated in the Work shall mean only that
//    Contributor's code submissions authored by that Contributor.  Any rights
//    granted under the License are conditioned upon acceptance of these
//    clarifications.
////////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>
#import "AJNSessionOptions.h"
#import "AJNMessageArgument.h"

/**
 * Protocol implemented by AllJoyn apps and called by AllJoyn to inform
 * the app of about announce related events.
 */
@protocol AJNAboutListener <NSObject>

@required
/**
 * handler for the org.alljoyn.About.Anounce sessionless signal
 *
 * The objectDescriptionArg contains an array with a signature of `a(oas)`
 * this is an array object paths with a list of interfaces found at those paths
 *
 * The aboutDataArg contains a dictionary with with AboutData fields that have
 * been announced.
 *
 * These fields are
 *  - AppId
 *  - DefaultLanguage
 *  - DeviceName
 *  - DeviceId
 *  - AppName
 *  - Manufacturer
 *  - ModelNumber
 *
 * The DeviceName is optional an may not be included in the aboutDataArg
 *
 * DeviceName, AppName, Manufacturer are localizable values. The localization
 * for these values in the aboutDataArg will always be for the language specified
 * in the DefaultLanguage field.
 *
 * @param[in] busName              well know name of the service
 * @param[in] version              version of the Announce signal from the remote About Object
 *                               About Object
 * @param[in] port                 SessionPort used by the announcer
 * @param[in] objectDescriptionArg  MsgArg the list of object paths and interfaces in the announcement
 * @param[in] aboutDataArg          MsgArg containing a dictionary of Key/Value pairs of the AboutData
 */
- (void)didReceiveAnnounceOnBus:(NSString *)busName withVersion:(uint16_t)version withSessionPort:(AJNSessionPort)port withObjectDescription:(AJNMessageArgument *)objectDescriptionArg withAboutDataArg:(AJNMessageArgument *)aboutDataArg;

@end
