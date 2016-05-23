/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

#import "AJGWCAclWriteResponse.h"
#import "alljoyn/about/AJNConvertUtil.h"

@interface AJGWCAclWriteResponse ()

@property (nonatomic) ajn::gwc::AclWriteResponse* handle;

@end

@implementation AJGWCAclWriteResponse

- (id)initWithHandle:(ajn::gwc::AclWriteResponse *) handle
{
    self = [super init];
    if (self) {
        self.handle = (ajn::gwc::AclWriteResponse *)handle;
    }
    return self;
}

- (id)initWithAclId:(NSString*) aclId code:(AJGWCAclResponseCode) code invalidRules:(AJGWCAclRules *) invalidRules objPath:(NSString*) objPath
{
    self = [super init];
    if (self) {
        self.handle = new ajn::gwc::AclWriteResponse([AJNConvertUtil convertNSStringToQCCString:aclId], (ajn::gwc::AclResponseCode)code, [invalidRules handle], [AJNConvertUtil convertNSStringToQCCString:objPath]);
    }
    return self;
}

- (NSString*)aclId
{
    return [AJNConvertUtil convertQCCStringtoNSString:self.handle->getAclId()];
}

- (AJGWCAclResponseCode)responseCode
{
    return (AJGWCAclResponseCode)self.handle->getResponseCode();
}

- (AJGWCAclRules*)invalidRules
{
    return [[AJGWCAclRules alloc] initWithHandle:self.handle->getInvalidRules()];
}

- (NSString*)objectPath
{
    return [AJNConvertUtil convertQCCStringtoNSString:self.handle->getObjectPath()];
}


- (ajn::gwc::AclWriteResponse*)handle
{
    return _handle;
}
@end
