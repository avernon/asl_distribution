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
#import "AJNObject.h"
#import "AJNBusObject.h"
#import "AJNStatus.h"
#import "AJNAboutDataListener.h"
#import "AJNMessageArgument.h"

@protocol AJNBusObject;


@interface AJNAboutObject : AJNBusObject

/**
 * create a new About class
 *
 * The about class is responsible for transmitting information about the
 * interfaces that are available for other applications to use. It also
 * provides application specific information that is contained in the
 * AboutDataListener class
 *
 * It also provides mean for applications to respond to certain requests
 * concerning the interfaces.
 *
 * By default the org.alljoyn.About interface is excluded from the list of
 * announced interfaces. Since simply receiving the announce signal tells
 * the client that the service implements the org.alljoyn.About interface.
 * There are some legacy applications that expect the org.alljoyn.About
 * interface to be part of the announcement. Changing the isAnnounced flag
 * from UNANNOUNCED, its default, to ANNOUNCED will cause the org.alljoyn.About
 * interface to be part of the announce signal. Unless your application is
 * talking with a legacy application that expects the org.alljoyn.About
 * interface to be part of the announce signal it is best to leave the
 * isAnnounced to use its default value.
 *
 * @param[in] bus the BusAttachment that will contain the about information
 * @param[in] isAnnounced will the org.alljoyn.About interface be part of the
 *                        announced interfaces.
 */
- (id)initWithBusAttachment:(AJNBusAttachment *)busAttachment withAnnounceFlag:(AJNAnnounceFlag)announceFlag;



/**
 * This is used to send the Announce signal.  It announces the list of all
 * interfaces available at given object paths as well as the announced
 * fields from the AboutData.
 *
 * This method will automatically obtain the Announced ObjectDescription from the
 * BusAttachment that was used to create the AboutObj. Only BusObjects that have
 * marked their interfaces as announced and are registered with the
 * BusAttachment will be announced.
 *
 * @see BusAttachment::RegisterBusObject
 * @see BusObject::AddInterface
 *
 * @param sessionPort the session port the interfaces can be connected with
 * @param aboutDataListener the AboutDataListener that contains the AboutData for
 *                    this announce signal.
 *
 * @return ER_OK on success
 */

- (QStatus)announceForSessionPort:(AJNSessionPort)sessionPort withAboutDataListener:(id<AJNAboutDataListener>)aboutDataListener;

/**
 * Cancel the last announce signal sent. If no signals have been sent this
 * method call will return.
 *
 * @return
 *     - ER_OK on success
 *     - annother status indicating failure.
 */

- (QStatus)unannounce;

@end
