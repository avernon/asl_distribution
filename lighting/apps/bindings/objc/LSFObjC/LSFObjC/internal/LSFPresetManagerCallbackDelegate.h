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
#import <LSFResponseCodes.h>
#import "LSFLampState.h"

using namespace lsf;

@protocol LSFPresetManagerCallbackDelegate <NSObject>

@required
-(void)getPresetReplyWithCode: (LSFResponseCode)rc presetID: (NSString *)presetID andPreset: (LSFLampState *)preset;
-(void)getAllPresetIDsReplyWithCode: (LSFResponseCode)rc andPresetIDs: (NSArray *)presetIDs;
-(void)getPresetNameReplyWithCode: (LSFResponseCode)rc presetID: (NSString *)presetID language: (NSString *)language andPresetName: (NSString *)presetName;
-(void)setPresetNameReplyWithCode: (LSFResponseCode)rc presetID: (NSString *)presetID andLanguage: (NSString *)language;
-(void)presetsNameChanged: (NSArray *)presetIDs;
-(void)createPresetReplyWithCode: (LSFResponseCode)rc andPresetID: (NSString *)presetID;
-(void)createPresetTrackingReplyWithCode: (LSFResponseCode)rc presetID: (NSString *)presetID andTrackingID: (unsigned int)trackingID;
-(void)presetsCreated: (NSArray *)presetIDs;
-(void)updatePresetReplyWithCode: (LSFResponseCode)rc andPresetID: (NSString *)presetID;
-(void)presetsUpdated: (NSArray *)presetIDs;
-(void)deletePresetReplyWithCode: (LSFResponseCode)rc andPresetID: (NSString *)presetID;
-(void)presetsDeleted: (NSArray *)presetIDs;
-(void)getDefaultLampStateReplyWithCode: (LSFResponseCode)rc andLampState: (LSFLampState *)defaultLampState;
-(void)setDefaultLampStateReplyWithCode: (LSFResponseCode)rc;
-(void)defaultLampStateChanged;

@end
