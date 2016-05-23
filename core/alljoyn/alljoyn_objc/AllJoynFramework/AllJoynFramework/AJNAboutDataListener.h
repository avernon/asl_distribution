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
 * Protocol implemented by AllJoyn apps and called by AllJoyn to fetch
 * the about data provided by the user
 */
@protocol AJNAboutDataListener <NSObject>

@required

/**
 * Creating the dictionary that is returned when a user calls
 * org.alljoyn.About.GetAboutData. The returned MsgArg must contain the
 * AboutData dictionary for the Language specified.
 *
 * The Dictionary will contain the signature key value pairs where the key is a string 
 * value a AJNMessageArgument. The value should not be a variant since the bindings 
 * currently do not support variants. Instead providing an exact type for the message 
 * argument would work
 *
 * TODO add more documentation for the Key/Value pair requirements here.
 *
 * @param[out] aboutData the dictionary containing all of the AboutData fields for
 *                    the specified language.  If language is not specified the default
 *                    language will be returned
 * @param[in] language IETF language tags specified by RFC 5646 if the string
 *                     is NULL or an empty string the MsgArg for the default
 *                     language will be returned
 *
 * @return ER_OK on successful
 */
- (QStatus)getAboutDataForLanguage:(NSString *)language usingDictionary:(NSMutableDictionary **)aboutData;


/**
 * Return a dictionary pointer containing dictionary containing the AboutData that
 * is announced with the org.alljoyn.About.announce signal.
 * This will always be the default language and will only contain the fields
 * that are announced.
 *
 * The fields required to be part of the announced data are:
 *  - AppId
 *  - DefaultLanguage
 *  - DeviceName
 *  - DeviceId
 *  - AppName
 *  - Manufacture
 *  - ModelNumber
 *
 * If you require other fields or need the localized AboutData
 *   The org.alljoyn.About.GetAboutData method can be used.
 *
 *
 * @param[out] aboutData a dictionary with the a{sv} that contains the Announce
 *                    data.
 * @return ER_OK if successful
 */
- (QStatus)getDefaultAnnounceData:(NSMutableDictionary **)aboutData;


@end
