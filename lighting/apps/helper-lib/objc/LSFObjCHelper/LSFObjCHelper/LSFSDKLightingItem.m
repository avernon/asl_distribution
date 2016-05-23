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

#import "LSFSDKLightingItem.h"

@implementation LSFSDKLightingItem

@synthesize name = _name;

-(NSString *)theID
{
    return [[self getItemDataModel] theID];
}

-(NSString *)name
{
    return [[self getItemDataModel] name];
}

-(NSArray *)dependents
{
    return [[NSArray alloc] initWithArray: [self getDependentCollection]];
}

-(NSArray *)components
{
    return [[NSArray alloc] initWithArray: [self getComponentCollection]];
}

-(BOOL)isInitialized
{
    return [[self getItemDataModel] isInitialized];
}

-(BOOL)hasComponent: (LSFSDKLightingItem *) item
{
    return [[self getComponentCollection] containsObject: item];
}

-(NSArray *)getDependentCollection
{
    // Default implementation is an empty list -- subclass must override if they can be a component of another item
    return [[NSArray alloc] init];
}

-(NSArray *)getComponentCollection
{
    // Default implementation is an empty list -- sublass must override if they can be a component of another item
    return [[NSArray alloc] init];
}

-(BOOL)postInvalidArgIfNull: (NSString *)name object: (id)object
{
    if (object == nil)
    {
        [self postError: name status: LSF_ERR_INVALID_ARGS];
        return NO;
    }

    return YES;
}

-(BOOL)postErrorIfFailure: (NSString *)name status: (ControllerClientStatus)status
{
    if (status != CONTROLLER_CLIENT_OK)
    {
        [self postError: name status: LSF_ERR_FAILURE];
        return NO;
    }

    return YES;
}

-(void)rename: (NSString *)name
{
    @throw [NSException exceptionWithName: NSInternalInconsistencyException reason: [NSString stringWithFormat:@"You must override %@ in a subclass", NSStringFromSelector(_cmd)] userInfo: nil];
}

-(LSFModel *)getItemDataModel
{
    @throw [NSException exceptionWithName: NSInternalInconsistencyException reason: [NSString stringWithFormat:@"You must override %@ in a subclass", NSStringFromSelector(_cmd)] userInfo: nil];
}

-(void)postError: (NSString *)name status: (LSFResponseCode)status
{
    @throw [NSException exceptionWithName: NSInternalInconsistencyException reason: [NSString stringWithFormat:@"You must override %@ in a subclass", NSStringFromSelector(_cmd)] userInfo: nil];
}

@end
