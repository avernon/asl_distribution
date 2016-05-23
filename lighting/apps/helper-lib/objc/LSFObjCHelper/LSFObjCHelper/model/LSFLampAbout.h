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

/**
 * @warning *Note:* This class is not intended to be used by clients, and its interface may change
 * in subsequent releases of the SDK.
 */
@interface LSFLampAbout : NSObject

@property (nonatomic, strong) NSString *appID;
@property (nonatomic, strong) NSString *defaultLanguage;
@property (nonatomic, strong) NSString *deviceName;
@property (nonatomic, strong) NSString *deviceID;
@property (nonatomic, strong) NSString *appName;
@property (nonatomic, strong) NSString *manufacturer;
@property (nonatomic, strong) NSString *modelNumber;
@property (nonatomic, strong) NSString *supportedLanguages;
@property (nonatomic, strong) NSString *description;
@property (nonatomic, strong) NSString *dateOfManufacture;
@property (nonatomic, strong) NSString *softwareVersion;
@property (nonatomic, strong) NSString *ajSoftwareVersion;
@property (nonatomic, strong) NSString *hardwareVersion;
@property (nonatomic, strong) NSString *supportURL;

-(id)initWithAboutData: (LSFLampAbout *)aboutData;

@end
