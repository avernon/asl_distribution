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

#import "AJCPSDialog.h"
#import "alljoyn/about/AJNConvertUtil.h"

@interface AJCPSDialog ()

@end


@implementation AJCPSDialog

- (id)initWithHandle:(ajn::services::Dialog *)handle
{
	self = [super initWithHandle:handle];
	if (self) {
	}
	return self;
}

- (uint16_t)getNumActions
{
	return ((ajn::services::Dialog *)self.handle)->getNumActions();
}

- (NSString *)getMessage
{
	return [AJNConvertUtil convertQCCStringtoNSString:((ajn::services::Dialog *)self.handle)->getMessage()];
}

- (NSString *)getLabelAction1
{
	return [AJNConvertUtil convertQCCStringtoNSString:((ajn::services::Dialog *)self.handle)->getLabelAction1()];
}

- (NSString *)getLabelAction2
{
	return [AJNConvertUtil convertQCCStringtoNSString:((ajn::services::Dialog *)self.handle)->getLabelAction2()];
}

- (NSString *)getLabelAction3
{
	return [AJNConvertUtil convertQCCStringtoNSString:((ajn::services::Dialog *)self.handle)->getLabelAction3()];
}

- (QStatus)executeAction1
{
	return ((ajn::services::Dialog *)self.handle)->executeAction1();
}

- (QStatus)executeAction2
{
	return ((ajn::services::Dialog *)self.handle)->executeAction2();
}

- (QStatus)executeAction3
{
	return ((ajn::services::Dialog *)self.handle)->executeAction3();
}

@end
