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
#import "LSFPulseEffectManagerCallbackDelegate.h"

@interface LSFPulseEffectManager : LSFObject

-(id)initWithControllerClient: (LSFControllerClient *)controllerClient andPulseEffectManagerCallbackDelegate: (id<LSFPulseEffectManagerCallbackDelegate>)pemDelegate;
-(ControllerClientStatus)getAllPulseEffectIDs;
-(ControllerClientStatus)getPulseEffectWithID: (NSString *)pulseEffectID;
-(ControllerClientStatus)applyPulseEffectWithID: (NSString *)pulseEffectID onLamps: (NSArray *)lampIDs;
-(ControllerClientStatus)applyPulseEffectWithID: (NSString *)pulseEffectID onLampGroups: (NSArray *)lampGroupIDs;
-(ControllerClientStatus)getPulseEffectNameWithID: (NSString *)pulseEffectID;
-(ControllerClientStatus)getPulseEffectNameWithID: (NSString *)pulseEffectID andLanguage: (NSString *)language;
-(ControllerClientStatus)setPulseEffectNameWithID: (NSString *)pulseEffectID pulseEffectName: (NSString *)pulseEffectName;
-(ControllerClientStatus)setPulseEffectNameWithID: (NSString *)pulseEffectID pulseEffectName: (NSString *)pulseEffectName andLanguage: (NSString *)language;
-(ControllerClientStatus)createPulseEffectWithTracking: (uint32_t *)trackingID pulseEffect: (LSFPulseEffectV2 *)pulseEffect andPulseEffectName: (NSString *)pulseEffectName;
-(ControllerClientStatus)createPulseEffectWithTracking: (uint32_t *)trackingID pulseEffect: (LSFPulseEffectV2 *)pulseEffect pulseEffectName: (NSString *)pulseEffectName andLanguage: (NSString *)language;
-(ControllerClientStatus)updatePulseEffectWithID: (NSString *)pulseEffectID andPulseEffect: (LSFPulseEffectV2 *)pulseEffect;
-(ControllerClientStatus)deletePulseEffectWithID: (NSString *)pulseEffectID;
-(ControllerClientStatus)getPulseEffectDataSetWithID: (NSString *)pulseEffectID;
-(ControllerClientStatus)getPulseEffectDataSetWithID: (NSString *)pulseEffectID andLanguage: (NSString *)language;

@end
