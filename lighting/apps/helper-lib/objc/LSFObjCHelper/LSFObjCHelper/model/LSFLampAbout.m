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

#import "LSFLampAbout.h"

@implementation LSFLampAbout

@synthesize appID = _appID;
@synthesize defaultLanguage = _defaultLanguage;
@synthesize deviceName = _deviceName;
@synthesize deviceID = _deviceID;
@synthesize appName = _appName;
@synthesize manufacturer = _manufacturer;
@synthesize modelNumber = _modelNumber;
@synthesize supportedLanguages = _supportedLanguages;
@synthesize description = _description;
@synthesize dateOfManufacture = _dateOfManufacture;
@synthesize softwareVersion = _softwareVersion;
@synthesize ajSoftwareVersion = _ajSoftwareVersion;
@synthesize hardwareVersion = _hardwareVersion;
@synthesize supportURL = _supportURL;

-(id)init
{
    self = [super init];
    
    if (self)
    {
        self.appID = @"-";
        self.defaultLanguage = @"-";
        self.deviceName = @"-";
        self.deviceID = @"-";
        self.appName = @"-";
        self.manufacturer = @"-";
        self.modelNumber = @"-";
        self.supportedLanguages = @"-";
        self.description = @"-";
        self.dateOfManufacture = @"-";
        self.softwareVersion = @"-";
        self.ajSoftwareVersion = @"-";
        self.hardwareVersion = @"-";
        self.supportURL = @"-";
    }
    
    return self;
}

-(id)initWithAboutData: (LSFLampAbout *)aboutData
{
    self = [super init];

    if (self)
    {
        self.appID = aboutData.appID;
        self.defaultLanguage = aboutData.defaultLanguage;
        self.deviceName = aboutData.deviceName;
        self.deviceID = aboutData.deviceID;
        self.appName = aboutData.appName;
        self.manufacturer = aboutData.manufacturer;
        self.modelNumber = aboutData.modelNumber;
        self.supportedLanguages = aboutData.supportedLanguages;
        self.description = aboutData.description;
        self.dateOfManufacture = aboutData.dateOfManufacture;
        self.softwareVersion = aboutData.softwareVersion;
        self.ajSoftwareVersion = aboutData.ajSoftwareVersion;
        self.hardwareVersion = aboutData.hardwareVersion;
        self.supportURL = aboutData.supportURL;
    }

    return self;
}

@end
