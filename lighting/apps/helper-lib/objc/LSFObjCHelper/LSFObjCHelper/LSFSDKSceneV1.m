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

#import "LSFSDKSceneV1.h"
#import "LSFSDKLightingDirector.h"

@implementation LSFSDKSceneV1

-(BOOL)hasPreset: (LSFSDKPreset *)preset
{
    NSString *errorContext = @"LSFSDKSceneV1 hasPreset: error";
    return ([self postInvalidArgIfNull: errorContext object: preset]) ? [self hasPresetWithID: preset.theID] : NO;
}

-(BOOL)hasGroup: (LSFSDKGroup *)group;
{
    NSString *errorContext = @"LSFSDKSceneV1 hasGroup: error";
    return ([self postInvalidArgIfNull: errorContext object: group]) ? [self hasPresetWithID: group.theID] : NO;
}

-(BOOL)hasPresetWithID: (NSString *)presetID;
{
    return [sceneModel containsPreset: presetID];
}

-(BOOL)hasGroupWithID: (NSString *)groupID
{
    return [sceneModel containsGroup: groupID];
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
    NSString *errorContext = @"LSFSDKSceneV1 hasComponent: error";
    return ([self postInvalidArgIfNull: errorContext object: item]) ? ([self hasPresetWithID: item.theID] || [self hasGroupWithID: item.theID]): NO;
}

-(void)postError:(NSString *)name status:(LSFResponseCode)status
{
    dispatch_async([[[LSFSDKLightingDirector getLightingDirector] lightingManager] dispatchQueue], ^{
        [[[[LSFSDKLightingDirector getLightingDirector] lightingManager] sceneCollectionManagerV1] sendErrorEvent: name statusCode: status itemID: sceneModel.theID];
    });
}

/*
 * Note: This method is not intended to be used by clients, and may change or be
 * removed in subsequent releases of the SDK.
 */
-(LSFSceneDataModel *)getSceneDataModel
{
    return sceneModel;
}

@end
