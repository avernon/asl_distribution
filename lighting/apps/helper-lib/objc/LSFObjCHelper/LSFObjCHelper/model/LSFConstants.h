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
#import <SystemConfiguration/CaptiveNetwork.h>
#import <UIKit/UIKit.h>

/**
 * @warning *Note:* This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK.
 */
@interface LSFConstants : NSObject

@property (nonatomic, strong) NSDictionary *lampDetailsAboutData;
@property (nonatomic, strong) NSArray *lampDetailsFields;
@property (nonatomic, strong) NSArray *aboutFields;
@property (nonatomic, strong) NSString *lampServiceObjectDescription;
@property (nonatomic, strong) NSString *lampServiceInterfaceName;
@property (nonatomic, strong) NSString *lampStateInterfaceName;
@property (nonatomic, strong) NSString *lampParametersInterfaceName;
@property (nonatomic, strong) NSString *lampDetailsInterfaceName;
@property (nonatomic, strong) NSString *controllerServiceObjectDescription;
@property (nonatomic, strong) NSString *controllerServiceInterfaceName;
@property (nonatomic, strong) NSString *controllerServiceLampInterfaceName;
@property (nonatomic, strong) NSString *controllerServiceLampGroupInterfaceName;
@property (nonatomic, strong) NSString *controllerServicePresetInterfaceName;
@property (nonatomic, strong) NSString *controllerServiceSceneInterfaceName;
@property (nonatomic, strong) NSString *controllerServiceMasterSceneInterfaceName;
@property (nonatomic, strong) NSString *aboutInterfaceName;
@property (nonatomic, strong) NSString *configServiceInterfaceName;
@property (nonatomic, strong) NSString *defaultLanguage;
@property (nonatomic, strong) NSArray *supportedEffects;
@property (nonatomic, strong) NSArray *effectImages;
@property (nonatomic) unsigned int pollingDelaySeconds;
@property (nonatomic) unsigned int lampExperationMilliseconds;
@property (nonatomic) double RETRY_INTERVAL;
@property (nonatomic, strong) UIColor *uniformPowerGreen;
@property (nonatomic, strong) UIColor *midstatePowerOrange;
@property (nonatomic) unsigned int UI_DELAY;
@property (nonatomic, strong) NSMutableAttributedString *SOURCE_CODE_TEXT;
@property (nonatomic, strong) NSMutableAttributedString *TEAM_TEXT;
@property (nonatomic, strong) NSMutableAttributedString *NOTICE_TEXT;
@property (nonatomic) double MIN_BRIGHTNESS;
@property (nonatomic) double MAX_BRIGHTNESS;
@property (nonatomic) double MIN_HUE;
@property (nonatomic) double MAX_HUE;
@property (nonatomic) double MIN_SATURATION;
@property (nonatomic) double MAX_SATURATION;
@property (nonatomic) double MIN_COLOR_TEMP;
@property (nonatomic) double MAX_COLOR_TEMP;

+(LSFConstants *)getConstants;
-(unsigned int)scaleLampStateValue: (unsigned int)value withMax: (unsigned int)max;
-(unsigned int)unscaleLampStateValue: (unsigned int)value withMax: (unsigned int)max;
-(unsigned int)scaleColorTemp: (unsigned int)value;
-(unsigned int)unscaleColorTemp: (unsigned int)value;
-(NSString *)currentWifiSSID;

@end
