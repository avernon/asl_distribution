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
#import "LSFObject.h"
#import "LSFControllerClient.h"
#import "LSFPresetManagerCallbackDelegate.h"
#import "LSFLampState.h"
#import "PresetManager.h"

@interface LSFPresetManager : LSFObject

-(id)initWithControllerClient: (LSFControllerClient *)controllerClient andPresetManagerCallbackDelegate: (id<LSFPresetManagerCallbackDelegate>)pmDelegate;
-(ControllerClientStatus)getAllPresetIDs;
-(ControllerClientStatus)getPresetWithID: (NSString *)presetID;
-(ControllerClientStatus)getPresetNameWithID: (NSString *)presetID;
-(ControllerClientStatus)getPresetNameWithID: (NSString *)presetID andLanguage: (NSString *)language;
-(ControllerClientStatus)setPresetNameWithID: (NSString *)presetID andPresetName: (NSString *)name;
-(ControllerClientStatus)setPresetNameWithID: (NSString *)presetID presetName: (NSString *)name andLanguage: (NSString *)language;
-(ControllerClientStatus)createPresetWithState: (LSFLampState *)preset andPresetName: (NSString *)name;
-(ControllerClientStatus)createPresetWithState: (LSFLampState *)preset presetName: (NSString *)name andLanguage: (NSString *)language;
-(ControllerClientStatus)updatePresetWithID: (NSString *)presetID andState: (LSFLampState *)preset;
-(ControllerClientStatus)deletePresetWithID: (NSString *)presetID;
-(ControllerClientStatus)getDefaultLampState;
-(ControllerClientStatus)setDefaultLampState: (LSFLampState *)defaultLampState;
-(ControllerClientStatus)getPresetDataSetWithID: (NSString *)presetID;
-(ControllerClientStatus)getPresetDataSetWithID: (NSString *)presetID andLanguage: (NSString *)language;

@end