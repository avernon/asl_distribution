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


#import "VisualAclRules.h"
#import "alljoyn/gateway/AJGWCRuleInterface.h"
#import "alljoyn/gateway/AJGWCRuleObjectPath.h"


@implementation VisualInterfaceInfo

-(id) init:(AJGWCRuleInterface *)interface isConfigured:(BOOL)configured enabled:(BOOL)enabled
{
    self = [super init];

    _interface = interface;

    _configured = configured;

    _enabled = enabled;

    return self;
}

- (id)copyWithZone:(NSZone *)zone {
    VisualInterfaceInfo *objectCopy = [[VisualInterfaceInfo allocWithZone:zone] init:self.interface isConfigured:self.configured enabled:self.enabled];

    return objectCopy;
}

- (NSUInteger)hash {
    return [self.interface hash];
}

- (BOOL)isEqual:(id)anObject {
    if (![anObject isKindOfClass:[VisualInterfaceInfo class]]) return NO;
    VisualInterfaceInfo *otherRuleInterface = (VisualInterfaceInfo *)anObject;

    return [otherRuleInterface.interface isEqual:self.interface];
}
@end

@implementation VisualObjPathInfo
-(id) init:(AJGWCRuleObjectPath *)objectPath isConfigured:(BOOL)configured enabled:(BOOL)enabled
{
    self = [super init];

    _objectPath = objectPath;

    _configured = configured;

    _enabled = enabled;

    return self;
}

- (id)copyWithZone:(NSZone *)zone {
    VisualObjPathInfo *objectCopy = [[VisualObjPathInfo allocWithZone:zone] init:self.objectPath isConfigured:self.configured enabled:self.enabled];


    return objectCopy;
}

- (NSUInteger)hash {
    return [self.objectPath hash];
}

- (BOOL)isEqual:(id)anObject {
    if (![anObject isKindOfClass:[VisualObjPathInfo class]]) return NO;
    VisualObjPathInfo *otherObjPathInfo = (VisualObjPathInfo *)anObject;

    return [otherObjPathInfo.objectPath isEqual:self.objectPath];
}


@end

@interface VisualAclRules()
@end

@implementation VisualAclRules

-(id)initWithArrayOfRuleObjectDescription:(NSArray *)arrayOfRuleObjectDescription
{
    self = [super init];

    self.aclRulesDictionary = [[NSMutableDictionary alloc]init];

    // Gather the object paths for each interface
    for (AJGWCRuleObjectDescription *objectDescription in arrayOfRuleObjectDescription) {
        NSSet *interfaces = [objectDescription interfaces];

        VisualObjPathInfo *objPathInfo = [[VisualObjPathInfo alloc] init:[objectDescription objectPath] isConfigured:[objectDescription isConfigured] enabled:YES] ;

        for (AJGWCRuleInterface *interface in interfaces) {

            VisualInterfaceInfo *interfaceInfo = [[VisualInterfaceInfo alloc]init:interface isConfigured:NO enabled:YES]; // we will populate the configured interfaces later in this function

            // check if this interface already has object paths connected to it
            NSMutableArray *array = (NSMutableArray *)[self objectPathsForInterface:interfaceInfo];

            // if not, allocate
            if ([array count] == 0) {
                array = [[NSMutableArray alloc] init];
            }

            // Gather the object paths for this interface into the array
            [array addObject:objPathInfo];

            // Sorting the object paths so the same entries will show at the same lines, only for aesthetics
            [array sortUsingComparator:^NSComparisonResult(id obj1, id obj2) {
                VisualObjPathInfo *objPathInfo1 = (VisualObjPathInfo *)obj1;
                VisualObjPathInfo *objPathInfo2 = (VisualObjPathInfo *)obj2;

                return [objPathInfo1.objectPath.path compare:objPathInfo2.objectPath.path];
            }];

            // Add the list of object paths to the interface. this is the important part.
            [self.aclRulesDictionary setObject:array forKey:interfaceInfo];
        }
    }

    // run through all of the interfaces and disable object paths that are all enabled under an interface. set that interface to be enabled
    for (VisualInterfaceInfo *interfaceInfo in [self.aclRulesDictionary allKeys]) {
        NSArray *array = [self objectPathsForInterface:interfaceInfo];

        BOOL allPathsAreConfigured = YES;
        for (VisualObjPathInfo *objPathInfo in array) {
            allPathsAreConfigured &= [objPathInfo configured];
        }

        if (allPathsAreConfigured) {
            [interfaceInfo setConfigured:YES];
            NSArray *array = [self objectPathsForInterface:interfaceInfo];

            for (VisualObjPathInfo *objPathInfo in array) {
                [objPathInfo setEnabled:NO];
            }

        }
    }

    return self;
}

- (NSArray *)interfaces
{
    return [self.aclRulesDictionary allKeys];
}


- (NSArray *)objectPathsForInterface:(VisualInterfaceInfo *)interface
{
    return (NSArray *)[self.aclRulesDictionary objectForKey:interface];
}

-(void) switchAllAclRules
{
    self.configured=!self.configured;

    if (self.configured==YES) { //configure all elements
        for (VisualInterfaceInfo *interfaceInfo in [self.aclRulesDictionary allKeys]) {
            NSArray *array = [self objectPathsForInterface:interfaceInfo];
            interfaceInfo.configured = YES;

            for (VisualObjPathInfo *objPathInfo in array) {
                objPathInfo.configured = YES;
            }
        }
    }

    [self changeAllAclRulesElements:!self.configured]; //this should be the opposite of the configured state at the top level. if all access rules should be configured in gui then all of the elements should be disabled, and vice versa.

}


-(void) changeAllAclRulesElements:(BOOL)enable
{
    for (VisualInterfaceInfo *interfaceInfo in [self.aclRulesDictionary allKeys]) {
        NSArray *array = [self objectPathsForInterface:interfaceInfo];
        interfaceInfo.enabled=enable;

        if ((!interfaceInfo.configured && (enable == YES)) || (enable == NO)) {
            for (VisualObjPathInfo *objPathInfo in array) {
                objPathInfo.enabled=enable;
            }
        }
    }
}

-(void) switchInterfaceConfiguration:(VisualInterfaceInfo *)interfaceInfo
{
    NSArray *array = [self objectPathsForInterface:interfaceInfo];
    interfaceInfo.configured=!interfaceInfo.configured;

    for (VisualObjPathInfo *objPathInfo in array) {
        objPathInfo.enabled=!interfaceInfo.configured;
    }
}

-(void) switchObjectPathConfiguration:(VisualObjPathInfo *)objectPathInfo
{
    objectPathInfo.configured = !objectPathInfo.configured;
}

-(void) switchObjectPathAllowSubObjects:(VisualObjPathInfo *)objectPathInfo
{
    [objectPathInfo.objectPath setPrefix:![objectPathInfo.objectPath isPrefix]];
}

-(NSArray *) createAJGWCRuleObjectDescriptions
{
    NSMutableArray *objectDescriptions = [[NSMutableArray alloc]init];

    NSMutableDictionary *objectPathToInterfaces = [[NSMutableDictionary alloc]init]; //key - VisualObjPathInfo, value - array of VisualInterfaceInfo

    for (VisualInterfaceInfo *interfaceInfo in [self.aclRulesDictionary allKeys]) {
        NSArray *array = [self objectPathsForInterface:interfaceInfo];

            for (VisualObjPathInfo *objPathInfo in array) {
                if (objPathInfo.configured == YES || interfaceInfo.configured == YES || self.configured == YES) {
                    NSMutableArray *arrayOfInterfaces = [objectPathToInterfaces objectForKey:objPathInfo];

                    if (arrayOfInterfaces==nil) {
                        arrayOfInterfaces = [[NSMutableArray alloc]init];
                    }

                    [arrayOfInterfaces addObject:interfaceInfo];

                    [objectPathToInterfaces setObject:arrayOfInterfaces forKey:objPathInfo];
                }
            }
    }

    for (VisualObjPathInfo *objPathInfo in [objectPathToInterfaces allKeys]) {
        NSArray *interfacesForObjPath = [objectPathToInterfaces objectForKey:objPathInfo];

        NSMutableSet *arrayOfInterfaces = [[NSMutableSet alloc]init];
        for (VisualInterfaceInfo *interfaceInfo in interfacesForObjPath) {
            [arrayOfInterfaces addObject:interfaceInfo.interface];
        }

        AJGWCRuleObjectDescription *objDesc = [[AJGWCRuleObjectDescription alloc]
                                                              initWithObjectPath:objPathInfo.objectPath interfaces:arrayOfInterfaces isConfigured:YES];


        [objectDescriptions addObject:objDesc];

    }

    return objectDescriptions;

}

@end
