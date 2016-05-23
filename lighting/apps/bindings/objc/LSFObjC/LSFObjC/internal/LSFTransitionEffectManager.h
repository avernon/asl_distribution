/******************************************************************************
 * Copyright (c) AllSeen Alliance. All rights reserved.
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

#import "LSFObject.h"
#import "LSFControllerClient.h"
#import "LSFTransitionEffectManagerCallbackDelegate.h"

@interface LSFTransitionEffectManager : LSFObject

-(id)initWithControllerClient: (LSFControllerClient *)controllerClient andTransitionEffectManagerCallbackDelegate: (id<LSFTransitionEffectManagerCallbackDelegate>)temDelegate;
-(ControllerClientStatus)getAllTransitionEffectIDs;
-(ControllerClientStatus)getTransitionEffectWithID: (NSString *)transitionEffectID;
-(ControllerClientStatus)applyTranstionEffectWithID: (NSString *)transitionEffectID onLamps: (NSArray *)lampIDs;
-(ControllerClientStatus)applyTranstionEffectWithID: (NSString *)transitionEffectID onLampGroups: (NSArray *)lampGroupIDs;
-(ControllerClientStatus)getTransitionEffectNameWithID: (NSString *)transitionEffectID;
-(ControllerClientStatus)getTransitionEffectNameWithID: (NSString *)transitionEffectID andLanguage: (NSString *)language;
-(ControllerClientStatus)setTransitionEffectNameWithID: (NSString *)transitionEffectID transitionEffectName: (NSString *)transitionEffectName;
-(ControllerClientStatus)setTransitionEffectNameWithID: (NSString *)transitionEffectID transitionEffectName: (NSString *)transitionEffectName andLanguage: (NSString *)language;
-(ControllerClientStatus)createTransitionEffectWithTracking: (uint32_t *)trackingID transitionEffect: (LSFTransitionEffectV2 *)transitionEffect andTransitionEffectName: (NSString *)transitionEffectName;
-(ControllerClientStatus)createTransitionEffectWithTracking: (uint32_t *)trackingID transitionEffect: (LSFTransitionEffectV2 *)transitionEffect transitionEffectName: (NSString *)transitionEffectName andLanguage: (NSString *)language;
-(ControllerClientStatus)updateTransitionEffectWithID: (NSString *)transitionEffectID andTransitionEffect: (LSFTransitionEffectV2 *)transitionEffect;
-(ControllerClientStatus)deleteTransitionEffectWithID: (NSString *)transitionEffectID;
-(ControllerClientStatus)getTransitionEffectDataSetWithID: (NSString *)transitionEffectID;
-(ControllerClientStatus)getTransitionEffectDataSetWithID: (NSString *)transitionEffectID andLanguage: (NSString *)language;

@end
