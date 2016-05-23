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

#import "AJNAnnouncementReceiver.h"
#import "BusAttachment.h"
#import "AJNAnnounceHandlerAdapter.h"
#import "AnnouncementRegistrar.h"

@interface AJNAnnouncementReceiver ()

@property id <AJNAnnouncementListener> AJNAnnouncementListener;
@property AJNAnnounceHandlerAdapter *announceHandlerAdapter;
@property ajn::BusAttachment *busAttachment;

@end

@implementation AJNAnnouncementReceiver

- (void)dealloc
{
	if (self.announceHandlerAdapter) {
		delete self.announceHandlerAdapter;
		self.announceHandlerAdapter = NULL;
	}
}

- (id)initWithAnnouncementListener:(id <AJNAnnouncementListener> )announcementListener
                            andBus:(AJNBusAttachment *)bus
{
	// Create announceHandlerAdapter and save a reference
	self.announceHandlerAdapter = new AJNAnnounceHandlerAdapter(announcementListener);
	// Save a reference to the BusAttachment
	self.busAttachment = (ajn::BusAttachment *)bus.handle;
    
	return self;
}

- (QStatus)registerAnnouncementReceiverForInterfaces:(const char  **)interfaces withNumberOfInterfaces:(size_t)numOfInterfaces
{
    NSLog(@"[%@] [%@] Calling %@", @"DEBUG", [[self class] description],NSStringFromSelector(_cmd));
    return ajn::services::AnnouncementRegistrar::RegisterAnnounceHandler((*(self.busAttachment)), *(self.announceHandlerAdapter), interfaces, numOfInterfaces);
}

- (QStatus)registerAnnouncementReceiver
{
    NSLog(@"[%@] [%@] Calling %@", @"DEBUG", [[self class] description],NSStringFromSelector(_cmd));
    return ajn::services::AnnouncementRegistrar::RegisterAnnounceHandler((*(self.busAttachment)), *(self.announceHandlerAdapter), NULL, 0);
}

- (QStatus)unRegisterAnnouncementReceiverForInterfaces:(const char  **)interfaces withNumberOfInterfaces:(size_t)numOfInterfaces
{
    NSLog(@"[%@] [%@] Calling %@", @"DEBUG", [[self class] description],NSStringFromSelector(_cmd));
	return ajn::services::AnnouncementRegistrar::UnRegisterAnnounceHandler(*(self.busAttachment), *(self.announceHandlerAdapter), interfaces, numOfInterfaces);
}

- (QStatus)unRegisterAnnouncementReceiver
{
    NSLog(@"[%@] [%@] Calling %@", @"DEBUG", [[self class] description],NSStringFromSelector(_cmd));
    return ajn::services::AnnouncementRegistrar::UnRegisterAnnounceHandler(*(self.busAttachment), *(self.announceHandlerAdapter), NULL, 0);
}

@end
