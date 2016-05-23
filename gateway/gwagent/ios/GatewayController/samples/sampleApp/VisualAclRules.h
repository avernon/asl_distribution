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


#import <Foundation/Foundation.h>
#import "alljoyn/gateway/AJGWCRuleObjectDescription.h"

@interface VisualInterfaceInfo : NSObject <NSCopying>
@property (strong,nonatomic) AJGWCRuleInterface *interface;
@property (nonatomic) BOOL configured;              // is this interface configured to be included in the ACL - if YES, all object paths under it are included
@property (nonatomic) BOOL enabled;                 // can this interface be configured or was a parent configured for it?
@end

@interface VisualObjPathInfo : NSObject <NSCopying>
@property (strong,nonatomic) AJGWCRuleObjectPath *objectPath;
@property (nonatomic) BOOL enabled;                 // can this objPath be configured
@property (nonatomic) BOOL configured;              // is this path configured to be included in the ACL
@end

@interface VisualAclRules : NSObject
@property (nonatomic) BOOL configured;              // are these access rules configured to be included in the ACL
@property (strong,nonatomic) NSMutableDictionary *aclRulesDictionary; // key - VisualInterfaceInfo, value - array of VisualObjPathInfo

-(id)initWithArrayOfRuleObjectDescription:(NSArray *)arrayOfRuleObjectDescription;

// return array of AJGWCRuleInterface
- (NSArray *)interfaces;

// return array of AJGWCRuleObjectPath
- (NSArray *)objectPathsForInterface:(VisualInterfaceInfo *)interface;

-(void) switchAllAclRules;

-(void) switchInterfaceConfiguration:(VisualInterfaceInfo *)interfaceInfo;

-(void) switchObjectPathConfiguration:(VisualObjPathInfo *)objectPathInfo;

-(void) switchObjectPathAllowSubObjects:(VisualObjPathInfo *)objectPathInfo;

-(NSArray *) createAJGWCRuleObjectDescriptions;

@end

























