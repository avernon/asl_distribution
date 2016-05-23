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

#import "AJNAboutIconClient.h"
#import "AboutIconClient.h"
#import "AJNConvertUtil.h"

static int SESSIONID=0;

@interface AJNAboutIconClient ()
@property ajn::services::AboutIconClient *handle;

@end
@implementation AJNAboutIconClient

- (void)dealloc
{
	if (self.handle) {
		delete self.handle;
		self.handle = NULL;
	}
}

- (id)initWithBus:(AJNBusAttachment *)bus
{
	self = [super init];
	if (self) {
		self.handle = new ajn::services::AboutIconClient((ajn::BusAttachment&)(*bus.handle));
	}
	return self;
}

- (QStatus)urlFromBusName:(NSString *)busName
                      url:(NSString **)url
{
	return [self urlFromBusName:busName url:url sessionId:SESSIONID];
}

- (QStatus)urlFromBusName:(NSString *)busName
                      url:(NSString **)url
                sessionId:(AJNSessionId)sessionId
{
	QStatus status;
	const char *tBus = const_cast <char *>([AJNConvertUtil convertNSStringToConstChar:busName]);
	qcc::String tUrl;
    
	status = self.handle->GetUrl(tBus, tUrl, sessionId);
	// Convert the url
	*url = [AJNConvertUtil convertQCCStringtoNSString:tUrl];
	return status;
}

- (QStatus)contentFromBusName:(NSString *)busName
                      content:(uint8_t **)content
                  contentSize:(size_t&)contentSize
{
	return [self contentFromBusName:busName content:content contentSize:contentSize sessionId:SESSIONID];
}

- (QStatus)contentFromBusName:(NSString *)busName
                      content:(uint8_t **)content
                  contentSize:(size_t&)contentSize
                    sessionId:(AJNSessionId)sessionId
{
	const char *tBus = const_cast <char *>([AJNConvertUtil convertNSStringToConstChar:busName]);
	return self.handle->GetContent(tBus, content, contentSize, sessionId);
}

- (QStatus)versionFromBusName:(NSString *)busName
                      version:(int&)version
{
	return [self versionFromBusName:busName version:version sessionId:SESSIONID];
}

- (QStatus)versionFromBusName:(NSString *)busName
                      version:(int&)version
                    sessionId:(AJNSessionId)sessionId
{
	const char *tBus = const_cast <char *>([AJNConvertUtil convertNSStringToConstChar:busName]);
	return self.handle->GetVersion(tBus, version, sessionId);
}

- (QStatus)mimeTypeFromBusName:(NSString *)busName
                      mimeType:(NSString **)mimeType
{
	return [self mimeTypeFromBusName:busName mimeType:mimeType sessionId:SESSIONID];
}

- (QStatus)mimeTypeFromBusName:(NSString *)busName
                      mimeType:(NSString **)mimeType
                     sessionId:(AJNSessionId)sessionId
{
	QStatus status;
	const char *tBus = const_cast <char *>([AJNConvertUtil convertNSStringToConstChar:busName]);
	qcc::String tMimeType;
    
	status = self.handle->GetMimeType(tBus, tMimeType, sessionId);
    
	*mimeType = [AJNConvertUtil convertQCCStringtoNSString:tMimeType];
    
	return status;
}

- (QStatus)sizeFromBusName:(NSString *)busName
                      size:(size_t&)size
{
	return [self sizeFromBusName:busName size:size sessionId:SESSIONID];
}

- (QStatus)sizeFromBusName:(NSString *)busName
                      size:(size_t&)size
                 sessionId:(AJNSessionId)sessionId
{
	const char *tBus = const_cast <char *>([AJNConvertUtil convertNSStringToConstChar:busName]);
	return self.handle->GetSize(tBus, size, sessionId);
}

@end
