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
#import "AJNAnnouncementListener.h"

/**
 AJNAnnouncementReceiver enable registering an announcement listener to receive org.alljoyn.about Announce signals
 */
__deprecated
@interface AJNAnnouncementReceiver : NSObject

/**
 Designated initializer.
 Create an AJNAnnouncementReceiver Object using the passed announcementListener an an AJNBusAttachment.
 @param announcementListener A reference to an announcement listener.
 @param bus A reference to the AJNBusAttachment.
 @return ER_OK if successful.
 */
- (id)initWithAnnouncementListener:(id <AJNAnnouncementListener> )announcementListener andBus:(AJNBusAttachment *)bus __deprecated;

/**
 Register the announcement listener to receive org.alljoyn.about Announce signals.
 
 The handler is only called if all the interfaces are implemented.
 For example, if the handler should be called if both "com.example.Audio"
 *and* "com.example.Video" are implemented then call
 addAnnouncementHandler once:
     const char* interfaces[] = {"com.example.Audio", "com.example.Video"};
     RegisterAnnounceHandler(busAttachment, handler, interfaces,
                             sizeof(interfaces) / sizeof(interfaces[0]));
 
 If the handler should be called if "com.example.Audio" *or*
 "com.example.Video" is implemented then call
 addAnnouncementHandler multiple times:
     const char* audioInterface[] = {"com.example.Audio"};
     RegisterAnnounceHandler(busAttachment, handler, audioInterface,
                             sizeof(audioInterface) / sizeof(audioInterface[0]));
     const char* videoInterface[] = {"com.example.Video"};
     RegisterAnnounceHandler(busAttachment, handler, videoInterface,
                             sizeof(videoInterface) / sizeof(videoInterface[0]));
 
 The interface name may be a prefix followed by a `*`.  Using
 this, the example above could be written as:
     const char* exampleInterface[] = {"com.example.*"};
     RegisterAnnounceHandler(busAttachment, handler, exampleInterface,
                             sizeof(exampleInterface) / sizeof(exampleInterface[0]));
 The handler will receive any announcement that implements an interface
 beginning with the "com.example." name.
 
 If RegisterAnnounceHandler is called with lists of interfaces that overlap
 then multiple Announcements will be occur.
 For example given the following:
     const char* audioInterface[] = {"com.example.Audio"};
     RegisterAnnounceHandler(busAttachment, handler, audioInterface,
                             sizeof(audioInterface) / sizeof(audioInterface[0]));
     const char* audioVideoInterface[] = {"com.example.Audio", "com.example.Video"};
     RegisterAnnounceHandler(busAttachment, handler, audioVideoInterface,
                             sizeof(audioVideoInterface) / sizeof(audioVideoInterface[0]));

 If a BusAttachment is found that implements both `com.example.Audio` and
 interface `com.example.Video` the announce handler will be called twice.
 Once for the first registration that is looking for `com.example.Audio` and
 again for the second registration that is looking for both audio and video
 interfaces.

 If the same handler is used for for multiple interfaces then it is the
 handlers responsibility to parse through the reported interfaces to
 figure out what should be done in response to the Announce signal.

 @param interfaces A list of interfaces that the Announce signal reports as implmented.
               NULL to recieve all Announce signals regardless of interfaces
 @param numberInterfaces the number of interfaces in the interfaces list
 @return ER_OK if successful.
 */
- (QStatus)registerAnnouncementReceiverForInterfaces:(const char **)interfaces withNumberOfInterfaces:(size_t)numOfInterfaces __deprecated;

/**
 @deprecated This function has been deprecated please change your code
 to use registerAnnouncementReceiverForInterfaces where you specify the interface(s) that you
 are interested finding.

 Using this member function could have significant impact on network
 performance.

 @see registerAnnouncementReceiverForInterfaces(ajn::BusAttachment&, AnnounceHandler&, const char**, size_t)

 Registers a handler to receive the org.alljoyn.about Announce signal.

 @param[in] handler reference to AnnounceHandler

 @return ER_OK if successful.
 */
- (QStatus)registerAnnouncementReceiver __deprecated;

/**
 Unregister the announcement listener from receiving org.alljoyn.about Announce signal.
 @param interfaces A list of interfaces that the Announce signal reports as implmented.
               NULL to recieve all Announce signals regardless of interfaces
 @param numberInterfaces the number of interfaces in the interfaces list
 @return ER_OK if successful.
 */
- (QStatus)unRegisterAnnouncementReceiverForInterfaces:(const char  **)interfaces withNumberOfInterfaces:(size_t)numOfInterfaces __deprecated;

/**
 @deprecated This function has been deprecated in please change your code
 to use UnRegisterAnnounceHandler where you specify the interface(s).

 @see unRegisterAnnouncementReceiverForInterfaces(ajn::BusAttachment&, AnnounceHandler&, const char**, size_t)

 Unregisters the AnnounceHandler from receiving the org.alljoyn.about Announce signal.

 @return ER_OK if successful.
 */
- (QStatus)unRegisterAnnouncementReceiver __deprecated;

@end
