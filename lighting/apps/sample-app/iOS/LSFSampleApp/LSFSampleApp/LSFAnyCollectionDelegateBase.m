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

#import "LSFAnyCollectionDelegateBase.h"
#import <LSFSDKLightingItem.h>

@implementation LSFAnyCollectionDelegateBase

-(void)onAnyInitializedWithTrackingID: (LSFSDKTrackingID *)trackingID andLightingItem: (id)item
{
    //Intentionally left blank
}

-(void)onAnyChanged: (id)item
{
    //Intentionally left blank
}

-(void)onAnyRemoved: (id)item
{
    //Intentionally left blank
}

-(void)onAnyError: (LSFSDKLightingItemErrorEvent *)error
{
    //Intentionally left blank
}

-(void)onLampInitialized: (LSFSDKLamp *)lamp
{
    [self onAnyInitializedWithTrackingID: nil andLightingItem: lamp];
}

-(void)onLampChanged: (LSFSDKLamp *)lamp
{
    [self onAnyChanged: lamp];
}

-(void)onLampRemoved: (LSFSDKLamp *)lamp
{
    [self onAnyRemoved: lamp];
}

-(void)onLampError: (LSFSDKLightingItemErrorEvent *)error
{
    [self onAnyError: error];
}

-(void)onGroupInitializedWithTrackingID: (LSFSDKTrackingID *)trackingID andGroup: (LSFSDKGroup *)group
{
    [self onAnyInitializedWithTrackingID: trackingID andLightingItem: group];
}

-(void)onGroupChanged: (LSFSDKGroup *)group
{
    [self onAnyChanged: group];
}

-(void)onGroupRemoved: (LSFSDKGroup *)group
{
    [self onAnyRemoved: group];
}

-(void)onGroupError: (LSFSDKLightingItemErrorEvent *)error
{
    [self onAnyError: error];
}

-(void)onPresetInitializedWithTrackingID: (LSFSDKTrackingID *)trackingID andPreset: (LSFSDKPreset *)preset
{
    [self onAnyInitializedWithTrackingID: trackingID andLightingItem: preset];
}

-(void)onPresetChanged: (LSFSDKPreset *)preset
{
    [self onAnyChanged: preset];
}

-(void)onPresetRemoved: (LSFSDKPreset *)preset
{
    [self onAnyRemoved: preset];
}

-(void)onPresetError: (LSFSDKLightingItemErrorEvent *)error
{
    [self onAnyError: error];
}

-(void)onTransitionEffectInitializedWithTrackingID: (LSFSDKTrackingID *)trackingID andTransitionEffect: (LSFSDKTransitionEffect *)transitionEffect;
{
    [self onAnyInitializedWithTrackingID: trackingID andLightingItem: transitionEffect];
}

-(void)onTransitionEffectChanged: (LSFSDKTransitionEffect *)transitionEffect
{
    [self onAnyChanged: transitionEffect];
}

-(void)onTransitionEffectRemoved: (LSFSDKTransitionEffect *)transitionEffect
{
    [self onAnyRemoved: transitionEffect];
}

-(void)onTransitionEffectError: (LSFSDKLightingItemErrorEvent *)error
{
    [self onAnyError: error];
}

-(void)onPulseEffectInitializedWithTrackingID: (LSFSDKTrackingID *)trackingID andPulseEffect: (LSFSDKPulseEffect *)pulseEffect;
{
    [self onAnyInitializedWithTrackingID: trackingID andLightingItem: pulseEffect];
}

-(void)onPulseEffectChanged: (LSFSDKPulseEffect *)pulseEffect
{
    [self onAnyChanged: pulseEffect];
}

-(void)onPulseEffectRemoved: (LSFSDKPulseEffect *)pulseEffect
{
    [self onAnyRemoved: pulseEffect];
}

-(void)onPulseEffectError: (LSFSDKLightingItemErrorEvent *)error
{
    [self onAnyError: error];
}

-(void)onSceneElementInitializedWithTrackingID: (LSFSDKTrackingID *)trackingID andSceneElement:(LSFSDKSceneElement *)sceneElement
{
    [self onAnyInitializedWithTrackingID: trackingID andLightingItem: sceneElement];
}

-(void)onSceneElementChanged: (LSFSDKSceneElement *)sceneElement
{
    [self onAnyChanged: sceneElement];
}

-(void)onSceneElementRemoved: (LSFSDKSceneElement *)sceneElement
{
    [self onAnyRemoved: sceneElement];
}

-(void)onSceneElementError: (LSFSDKLightingItemErrorEvent *)error
{
    [self onAnyError: error];
}

-(void)onSceneInitializedWithTrackingID: (LSFSDKTrackingID *)trackingID andScene: (LSFSDKScene *)scene
{
    [self onAnyInitializedWithTrackingID: trackingID andLightingItem: scene];
}

-(void)onSceneChanged: (LSFSDKScene *)scene
{
    [self onAnyChanged: scene];
}

-(void)onSceneRemoved: (LSFSDKScene *)scene
{
    [self onAnyRemoved: scene];
}

-(void)onSceneError: (LSFSDKLightingItemErrorEvent *)error
{
    [self onAnyError: error];
}

-(void)onMasterSceneInitializedWithTrackingID: (LSFSDKTrackingID *)trackingID andMasterScene: (LSFSDKMasterScene *)masterScene
{
    [self onAnyInitializedWithTrackingID: trackingID andLightingItem: masterScene];
}

-(void)onMasterSceneChanged: (LSFSDKMasterScene *)masterScene
{
    [self onAnyChanged: masterScene];
}

-(void)onMasterSceneRemoved: (LSFSDKMasterScene *)masterScene
{
    [self onAnyRemoved: masterScene];
}

-(void)onMasterSceneError: (LSFSDKLightingItemErrorEvent *)error
{
    [self onAnyError: error];
}

@end
