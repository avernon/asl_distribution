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

#import "LSFLampDetails.h"
#import "LSFTypes.h"

@interface LSFLampDetails()

@property (nonatomic, readonly) lsf::LampDetails *lampDetails;

//-(void)populateWithData;

@end

@implementation LSFLampDetails

@synthesize lampDetails = _lampDetails;

-(id)init
{
    self = [super init];
    
    if (self)
    {
        self.handle = new lsf::LampDetails();
        
        //TODO - remove
        //[self populateWithData];
    }
    
    return self;
}

-(void)setLampMake: (LampMake)lampMake
{
    self.lampDetails->make = lampMake;
}

-(LampMake)lampMake
{
    return self.lampDetails->make;
}

-(void)setLampModel: (LampModel)lampModel
{
    self.lampDetails->model = lampModel;
}

-(LampModel)lampModel
{
    return self.lampDetails->model;
}

-(void)setDeviceType: (DeviceType)deviceType
{
    self.lampDetails->type = deviceType;
}

-(DeviceType)deviceType
{
    return self.lampDetails->type;
}

-(void)setLampType: (LampType)lampType
{
    self.lampDetails->lampType = lampType;
}

-(LampType)lampType
{
    return self.lampDetails->lampType;
}

-(void)setBaseType: (BaseType)baseType
{
    self.lampDetails->lampBaseType = baseType;
}

-(BaseType)baseType
{
    return self.lampDetails->lampBaseType;
}

-(void)setLampBeamAngle: (unsigned int)lampBeamAngle
{
    self.lampDetails->lampBeamAngle = lampBeamAngle;
}

-(unsigned int)lampBeamAngle
{
    return self.lampDetails->lampBeamAngle;
}

-(void)setDimmable: (BOOL)dimmable
{
    if (dimmable)
    {
        self.lampDetails->dimmable = true;
    }
    else
    {
        self.lampDetails->dimmable = false;
    }
}

-(BOOL)dimmable
{
    bool dimmable = self.lampDetails->dimmable;
    
    if (dimmable)
    {
        return YES;
    }
    else
    {
        return NO;
    }
}

-(void)setColor: (BOOL)color
{
    if (color)
    {
        self.lampDetails->color = true;
    }
    else
    {
        self.lampDetails->color = false;
    }
}

-(BOOL)color
{
    bool color = self.lampDetails->color;
    
    if (color)
    {
        return YES;
    }
    else
    {
        return NO;
    }
}

-(void)setVariableColorTemp: (BOOL)variableColorTemp
{
    if (variableColorTemp)
    {
        self.lampDetails->variableColorTemp = true;
    }
    else
    {
        self.lampDetails->variableColorTemp = false;
    }
}

-(BOOL)variableColorTemp
{
    bool vct = self.lampDetails->variableColorTemp;
    
    if (vct)
    {
        return YES;
    }
    else
    {
        return NO;
    }
}

-(void)setHasEffects: (BOOL)hasEffects
{
    if (hasEffects)
    {
        self.lampDetails->hasEffects = true;
    }
    else
    {
        self.lampDetails->hasEffects = false;
    }
}

-(BOOL)hasEffects
{
    bool hasEffects = self.lampDetails->hasEffects;
    
    if (hasEffects)
    {
        return YES;
    }
    else
    {
        return NO;
    }
}

-(void)setMaxVoltage: (unsigned int)maxVoltage
{
    self.lampDetails->maxVoltage = maxVoltage;
}

-(unsigned int)maxVoltage
{
    return self.lampDetails->maxVoltage;
}

-(void)setMinVoltage: (unsigned int)minVoltage
{
    self.lampDetails->minVoltage = minVoltage;
}

-(unsigned int)minVoltage
{
    return self.lampDetails->minVoltage;
}

-(void)setWattage: (unsigned int)wattage
{
    self.lampDetails->wattage = wattage;
}

-(unsigned int)wattage
{
    return self.lampDetails->wattage;
}

-(void)setIncandescentEquivalent: (unsigned int)incandescentEquivalent
{
    self.lampDetails->incandescentEquivalent = incandescentEquivalent;
}

-(unsigned int)incandescentEquivalent
{
    return self.lampDetails->incandescentEquivalent;
}

-(void)setMaxLumens: (unsigned int)maxLumens
{
    self.lampDetails->maxLumens = maxLumens;
}

-(unsigned int)maxLumens
{
    return self.lampDetails->maxLumens;
}

-(void)setMinTemperature: (unsigned int)minTemperature
{
    self.lampDetails->minTemperature = minTemperature;
}

-(unsigned int)minTemperature
{
    return self.lampDetails->minTemperature;
}

-(void)setMaxTemperature: (unsigned int)maxTemperature
{
    self.lampDetails->maxTemperature = maxTemperature;
}

-(unsigned int)maxTemperature
{
    return self.lampDetails->maxTemperature;
}

-(void)setColorRenderingIndex: (unsigned int)colorRenderingIndex
{
    self.lampDetails->colorRenderingIndex = colorRenderingIndex;
}

-(unsigned int)colorRenderingIndex
{
    return self.lampDetails->colorRenderingIndex;
}

-(void)setLampID: (NSString *)lampID
{
    std::string lid([lampID UTF8String]);
    self.lampDetails->lampID = lid;
}

-(NSString *)lampID
{
    return [NSString stringWithUTF8String: (self.lampDetails->lampID).c_str()];
}

/*
 * Accessor for the internal C++ API object this objective-c class encapsulates
 */
- (lsf::LampDetails *)lampDetails
{
    return static_cast<lsf::LampDetails*>(self.handle);
}

/*
 * Private function
 */
//-(void)populateWithData
//{
//    self.lampDetails->make = MAKE_LIFX;
//    self.lampDetails->model = MODEL_LED;
//    self.lampDetails->type = TYPE_LAMP;
//    self.lampDetails->lampType = LAMPTYPE_PAR20;
//    self.lampDetails->lampBaseType = BASETYPE_E11;
//    self.lampDetails->lampBeamAngle = 100;
//    self.lampDetails->dimmable = true;
//    self.lampDetails->color = true;
//    self.lampDetails->variableColorTemp = true;
//    self.lampDetails->hasEffects = true;
//    self.lampDetails->maxVoltage = 120;
//    self.lampDetails->minVoltage = 120;
//    self.lampDetails->wattage = 60;
//    self.lampDetails->incandescentEquivalent = 9;
//    self.lampDetails->maxLumens = 600;
//    self.lampDetails->minTemperature = 2300;
//    self.lampDetails->maxTemperature = 5000;
//    self.lampDetails->colorRenderingIndex = 93;    
//}

@end
