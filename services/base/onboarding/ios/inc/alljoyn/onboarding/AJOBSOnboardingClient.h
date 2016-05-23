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

#import <Foundation/Foundation.h>
#import "AJNBusAttachment.h"
#import "AJOBSOnboarding.h"
#import "AJOBOnboardingClientListener.h"

/**
 * AJOBSOnboardingClient class
 */
@interface AJOBSOnboardingClient : NSObject

/**
 * Constructor of OnboardingClient
 * @param bus is a reference to BusAttachment
 * @param listener Onboarding connevtion signal listener
 */
-(id)initWithBus:(AJNBusAttachment*) bus listener:(id <AJOBOnboardingClientListener>) listener;

/**
 * Configure WiFi a specified bus name.
 * @param busName busName Unique or well-known name of AllJoyn node to retrieve Onboarding data from.
 * @param ajOBInfo reference to  OBInfo.
 * @param resultStatus the status of the request [out].
 * @param sessionId the session received  after joining alljoyn session
 * @return ER_OK if successful.
 */
-(QStatus)configureWiFi:(NSString*) busName obInfo:(AJOBInfo&) ajOBInfo resultStatus:(short&) resultStatus sessionId:(AJNSessionId) sessionId;

/**
 * Configure WiFi a specified bus name.
 * Since no sessionId has been specified - the service will find an existing route to end point rather than access directly.
 * @param busName busName Unique or well-known name of AllJoyn node to retrieve Onboarding data from.
 * @param ajOBInfo reference to  OBInfo
 * @param resultStatus the status of the request [out]
 * @return ER_OK if successful.
 */
-(QStatus)configureWiFi:(NSString*) busName obInfo:(AJOBInfo&) ajOBInfo resultStatus:(short&) resultStatus;

/**
 * Connect WiFi a specified bus name.
 * @param busName Unique or well-known name of AllJoyn node to retrieve Onboarding data from.
 * @param sessionId the session received  after joining alljoyn session
 * @return ER_OK if successful.
 */
-(QStatus)connectTo:(NSString*) busName  sessionId:(AJNSessionId) sessionId;

/**
 * Connect WiFi a specified bus name.
 * Since no sessionId has been specified - the service will find an existing route to end point rather than access directly.
 * @param busName Unique or well-known name of AllJoyn node to retrieve Onboarding data from.
 * @return ER_OK if successful.
 */
-(QStatus)connectTo:(NSString*) busName ;

/**
 * Offboard WiFi a specified bus name.
 * @param busName Unique or well-known name of AllJoyn node to retrieve Onboarding data from.
 * @param sessionId the session received  after joining alljoyn session
 * @return ER_OK if successful.
 */
-(QStatus)offboardFrom:(NSString*) busName  sessionId:(AJNSessionId) sessionId;


/**
 * Offboard WiFi a specified bus name.
 * Since no sessionId has been specified - the service will find an existing route to end point rather than access directly.
 * @param busName Unique or well-known name of AllJoyn node to retrieve Onboarding data from.
 * @return ER_OK if successful.
 */
-(QStatus)offboardFrom:(NSString*) busName ;

/**
 * GetVersion retrieves the Onboarding version
 * @param busName  Unique or well-known name of AllJoyn node to retrieve Onboarding data from.
 * @param version [out].
 * @param sessionId the session received  after joining alljoyn session
 * @return ER_OK if successful.
 */
-(QStatus)version:(NSString*) busName  version:(int&) version sessionId:(AJNSessionId) sessionId;

/**
 * GetVersion retrieves the Onboarding version
 * Since no sessionId has been specified - the service will find an existing route to end point rather than access directly.
 * @param busName  Unique or well-known name of AllJoyn node to retrieve Onboarding data from.
 * @param version [out].
 * @return ER_OK if successful.
 */
-(QStatus)version:(NSString*) busName  version:(int&) version;

/**
 * GetState retrieves  the last state of the WIFI connection attempt
 * @param busName Unique or well-known name of AllJoyn node to retrieve Onboarding data from.
 * @param state [out].
 * @param sessionId the session received  after joining alljoyn session
 * @return ER_OK if successful.
 */
-(QStatus)state:(NSString*) busName  state:(short&) state sessionId:(AJNSessionId) sessionId;

/**
 * GetState retrieves  the last state of the WIFI connection attempt
 * Since no sessionId has been specified - the service will find an existing route to end point rather than access directly.
 * @param busName Unique or well-known name of AllJoyn node to retrieve Onboarding data from.
 * @param state [out]
 * @return ER_OK if successful.
 */
-(QStatus)state:(NSString*) busName  state:(short&) state;

/**
 * GetLastError retrieves the last error of WIFI connection attempt
 * @param busName Unique or well-known name of AllJoyn node to retrieve Onboarding data from.
 * @param lastError [out].
 * @param sessionId the session received  after joining alljoyn session
 * @return ER_OK if successful.
 */
-(QStatus)lastError:(NSString*) busName lastError:(AJOBLastError&) lastError sessionId:(AJNSessionId) sessionId;

/**
 * GetLastError retrieves the last error of WIFI connection attempt
 * Since no sessionId has been specified - the service will find an existing route to end point rather than access directly.
 * @param busName Unique or well-known name of AllJoyn node to retrieve Onboarding data from.
 * @param lastError [out].
 * @return ER_OK if successful.
 */
-(QStatus)lastError:(NSString*) busName lastError:(AJOBLastError&) lastError;

@end
