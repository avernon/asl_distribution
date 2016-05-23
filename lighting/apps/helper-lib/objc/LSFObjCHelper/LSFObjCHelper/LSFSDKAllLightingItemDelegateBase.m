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

#import "LSFSDKAllLightingItemDelegateBase.h"

@implementation LSFSDKAllLightingItemDelegateBase

-(void)onLampInitialized: (LSFSDKLamp *)lamp
{
    //Intentionally left blank
}

-(void)onLampChanged: (LSFSDKLamp *)lamp
{
    //Intentionally left blank
}

-(void)onLampRemoved: (LSFSDKLamp *)lamp
{
    //Intentionally left blank
}

-(void)onLampError: (LSFSDKLightingItemErrorEvent *)error
{
    //Intentionally left blank
}

-(void)onGroupInitializedWithTrackingID: (LSFSDKTrackingID *)trackingID andGroup: (LSFSDKGroup *)group
{
    //Intentionally left blank
}

-(void)onGroupChanged: (LSFSDKGroup *)group
{
    //Intentionally left blank
}
-(void)onGroupRemoved: (LSFSDKGroup *)group
{
    //Intentionally left blank
}

-(void)onGroupError: (LSFSDKLightingItemErrorEvent *)error
{
    //Intentionally left blank
}

-(void)onPresetInitializedWithTrackingID: (LSFSDKTrackingID *)trackingID andPreset: (LSFSDKPreset *)preset
{
    //Intentionally left blank
}

-(void)onPresetChanged: (LSFSDKPreset *)preset
{
    //Intentionally left blank
}
-(void)onPresetRemoved: (LSFSDKPreset *)preset
{
    //Intentionally left blank
}

-(void)onPresetError: (LSFSDKLightingItemErrorEvent *)error
{
    //Intentionally left blank
}

-(void)onTransitionEffectInitializedWithTrackingID: (LSFSDKTrackingID *)trackingID andTransitionEffect: (LSFSDKTransitionEffect *)transitionEffect;
{
    //Intentionally left blank
}

-(void)onTransitionEffectChanged: (LSFSDKTransitionEffect *)transitionEffect
{
    //Intentionally left blank
}

-(void)onTransitionEffectRemoved: (LSFSDKTransitionEffect *)transitionEffect
{
    //Intentionally left blank
}

-(void)onTransitionEffectError: (LSFSDKLightingItemErrorEvent *)error
{
    //Intentionally left blank
}

-(void)onPulseEffectInitializedWithTrackingID: (LSFSDKTrackingID *)trackingID andPulseEffect: (LSFSDKPulseEffect *)pulseEffect;
{
    //Intentionally left blank
}

-(void)onPulseEffectChanged: (LSFSDKPulseEffect *)pulseEffect
{
    //Intentionally left blank
}

-(void)onPulseEffectRemoved: (LSFSDKPulseEffect *)pulseEffect
{
    //Intentionally left blank
}

-(void)onPulseEffectError: (LSFSDKLightingItemErrorEvent *)error
{
    //Intentionally left blank
}

-(void)onSceneElementInitializedWithTrackingID: (LSFSDKTrackingID *)trackingID andSceneElement: (LSFSDKSceneElement *)sceneElement
{
    //Intentionally left blank
}

-(void)onSceneElementChanged: (LSFSDKSceneElement *)sceneElement
{
    //Intentionally left blank
}

-(void)onSceneElementRemoved: (LSFSDKSceneElement *)sceneElement
{
    //Intentionally left blank
}

-(void)onSceneElementError: (LSFSDKLightingItemErrorEvent *)error
{
    //Intentionally left blank
}

-(void)onSceneInitializedWithTrackingID: (LSFSDKTrackingID *)trackingID andScene: (LSFSDKScene *)scene
{
    //Intentionally left blank
}

-(void)onSceneChanged: (LSFSDKScene *)scene
{
    //Intentionally left blank
}

-(void)onSceneRemoved: (LSFSDKScene *)scene
{
    //Intentionally left blank
}

-(void)onSceneError: (LSFSDKLightingItemErrorEvent *)error
{
    //Intentionally left blank
}

-(void)onMasterSceneInitializedWithTrackingID: (LSFSDKTrackingID *)trackingID andMasterScene: (LSFSDKMasterScene *)masterScene
{
    //Intentionally left blank
}

-(void)onMasterSceneChanged: (LSFSDKMasterScene *)masterScene
{
    //Intentionally left blank
}

-(void)onMasterSceneRemoved: (LSFSDKMasterScene *)masterScene
{
    //Intentionally left blank
}

-(void)onMasterSceneError: (LSFSDKLightingItemErrorEvent *)error
{
    //Intentionally left blank
}

-(void)onLeaderChange: (LSFSDKController *)leader
{
    //Intentionally left blank
}

-(void)onControllerError: (LSFSDKControllerErrorEvent *)errorEvent
{
    //Intentionally left blank
}

@end
