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

#import "AJNAboutClient.h"
#import "AboutClient.h"
#import "AJNAboutDataConverter.h"
#import "AJNConvertUtil.h"

@interface AJNAboutClient ()

@property ajn::services::AboutClient *handle;

@end

@implementation AJNAboutClient

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
		self.handle = new ajn::services::AboutClient((ajn::BusAttachment&)(*bus.handle));
	}
	return self;
}

- (QStatus)objectDescriptionsWithBusName:(NSString *)busName
                   andObjectDescriptions:(NSMutableDictionary **)objectDescs
                            andSessionId:(uint32_t)sessionId
{
	ajn::services::AboutClient::ObjectDescriptions objectDescriptions;
	QStatus status = self.handle->GetObjectDescriptions([AJNConvertUtil convertNSStringToConstChar:busName], objectDescriptions, (ajn::SessionId)sessionId);
	*objectDescs = [AJNAboutDataConverter convertToObjectDescriptionsDictionary:objectDescriptions];
    
	return status;
}

- (QStatus)aboutDataWithBusName:(NSString *)busName
                 andLanguageTag:(NSString *)languageTag
                   andAboutData:(NSMutableDictionary **)data
                   andSessionId:(uint32_t)sessionId
{
	ajn::services::AboutClient::AboutData aboutData;
    
	QStatus status =  self.handle->GetAboutData([AJNConvertUtil convertNSStringToConstChar:busName], [AJNConvertUtil convertNSStringToConstChar:languageTag], aboutData, (ajn::SessionId)sessionId);
	*data = [AJNAboutDataConverter convertToAboutDataDictionary:aboutData];
	return status;
}

- (QStatus)versionWithBusName:(NSString *)busName
                   andVersion:(int)version
                 andSessionId:(AJNSessionId)sessionId
{
	return (self.handle->GetVersion([AJNConvertUtil convertNSStringToConstChar:busName], version, (ajn::SessionId)sessionId));
}

@end
