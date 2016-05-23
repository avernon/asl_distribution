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

#import "LSFSDKSceneV2.h"
#import "LSFSDKLightingItemUtil.h"
#import "LSFSDKLightingDirector.h"
#import "manager/LSFSDKAllJoynManager.h"
#import "model/LSFSDKLightingItemHasComponentFilter.h"

@implementation LSFSDKSceneV2

-(void)modify: (NSArray *)sceneElements
{
    NSString *errorContext = @"LSFSDKSceneV2 modify: error";

    if ([self postInvalidArgIfNull: errorContext object: sceneElements])
    {
        NSMutableArray *sceneElementIDs = [[NSMutableArray alloc] init];
        for (LSFSDKSceneElement *sceneElement in sceneElements)
        {
            [sceneElementIDs addObject: [sceneElement theID]];
        }

        [self postErrorIfFailure: errorContext status: [[LSFSDKAllJoynManager getSceneManager] updateSceneWithSceneElementsWithID: sceneModel.theID withSceneWithSceneElements: [LSFSDKLightingItemUtil createSceneWithSceneElements: sceneElementIDs]]];
    }
}

-(void)add: (LSFSDKSceneElement *)sceneElement
{
    NSString *errorContext = @"LSFSDKSceneV2 add: error";

    if ([self postInvalidArgIfNull: errorContext object: sceneElement])
    {
        NSMutableSet *sceneElementIDs = [[NSMutableSet alloc] initWithArray: [[sceneModel sceneWithSceneElements] sceneElements]];
        [sceneElementIDs addObject: [sceneElement theID]];

        [self postErrorIfFailure: errorContext status: [[LSFSDKAllJoynManager getSceneManager] updateSceneWithSceneElementsWithID: sceneModel.theID withSceneWithSceneElements: [LSFSDKLightingItemUtil createSceneWithSceneElements: [sceneElementIDs allObjects]]]];
    }
}

-(void)remove: (LSFSDKSceneElement *)sceneElement
{
    NSString *errorContext = @"LSFSDKSceneV2 remove: error";

    if ([self postInvalidArgIfNull: errorContext object: sceneElement])
    {
        NSMutableSet *sceneElementIDs = [[NSMutableSet alloc] initWithArray: [[sceneModel sceneWithSceneElements] sceneElements]];
        [sceneElementIDs removeObject: [sceneElement theID]];

        [self postErrorIfFailure: errorContext status: [[LSFSDKAllJoynManager getSceneManager] updateSceneWithSceneElementsWithID: sceneModel.theID withSceneWithSceneElements: [LSFSDKLightingItemUtil createSceneWithSceneElements: [sceneElementIDs allObjects]]]];
    }
}

-(BOOL)hasSceneElement:(LSFSDKSceneElement *)sceneElement
{
    NSString *errorContext = @"LSFSDKSceneV2 hasSceneElement: error";
    return ([self postInvalidArgIfNull: errorContext object: sceneElement]) ? [self hasSceneElementWithID: sceneElement.theID] : NO;
}

-(BOOL)hasSceneElementWithID:(NSString *)sceneElementID
{
    return [sceneModel containsSceneElement: sceneElementID];
}

/*
 * Override base class functions
 */
-(LSFModel *)getItemDataModel
{
    return [self getSceneDataModel];
}

-(BOOL)hasComponent:(LSFSDKLightingItem *)item
{
    NSString *errorContext = @"LSFSDKSceneV2 hasComponent: error";
    return ([self postInvalidArgIfNull: errorContext object: item]) ? [self hasSceneElementWithID: item.theID] : NO;
}

-(NSArray *)getSceneElementIDs
{
    return sceneModel.sceneWithSceneElements.sceneElements;
}

-(NSArray *)getSceneElements
{
    NSMutableArray *collection = [[NSMutableArray alloc] init];

    NSArray *sceneElementIDs = [self getSceneElementIDs];
    for (NSString *sceneElementID in sceneElementIDs)
    {
        LSFSDKSceneElement *sceneElement = [[LSFSDKLightingDirector getLightingDirector] getSceneElementWithID: sceneElementID];
        if (sceneElement != nil)
        {
            [collection addObject: sceneElement];
        }
    }

    return collection;
}

-(NSArray *)getComponentCollection
{
    return [self getSceneElements];
}

-(void)postError:(NSString *)name status:(LSFResponseCode)status
{
    dispatch_async([[[LSFSDKLightingDirector getLightingDirector] lightingManager] dispatchQueue], ^{
        [[[[LSFSDKLightingDirector getLightingDirector] lightingManager] sceneCollectionManager] sendErrorEvent: name statusCode: status itemID: sceneModel.theID];
    });
}

/*
 * Note: This method is not intended to be used by clients, and may change or be
 * removed in subsequent releases of the SDK.
 */
-(LSFSceneDataModelV2 *)getSceneDataModel
{
    return sceneModel;
}

@end
