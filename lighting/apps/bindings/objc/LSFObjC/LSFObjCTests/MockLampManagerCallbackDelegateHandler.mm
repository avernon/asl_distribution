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

#import "MockLampManagerCallbackDelegateHandler.h"

@interface MockLampManagerCallbackDelegateHandler()

@property (nonatomic) NSMutableArray *dataArray;

@end

@implementation MockLampManagerCallbackDelegateHandler

@synthesize dataArray = _dataArray;

-(id)init
{
    self = [super init];
    
    if (self)
    {
        self.dataArray = [[NSMutableArray alloc] init];
    }
    
    return self;
}

-(NSArray *)getCallbackData
{
    return self.dataArray;
}

//Delegate methods
-(void)getAllLampIDsReplyWithCode: (LSFResponseCode)rc andLampIDs: (NSArray *)lampIDs
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"getAllLampIDs"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: lampIDs];
}

-(void)getLampNameReplyWithCode: (LSFResponseCode)rc lampID: (NSString*)lampID language: (NSString*)language andLampName: (NSString*)name
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"getLampName"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: lampID];
    [self.dataArray addObject: language];
    [self.dataArray addObject: name];
}

-(void)getLampManufacturerReplyWithCode: (LSFResponseCode)rc lampID: (NSString*)lampID language: (NSString*)language andManufacturer: (NSString*)manufacturer
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"getLampManufacturer"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: lampID];
    [self.dataArray addObject: language];
    [self.dataArray addObject: manufacturer];

}

-(void)setLampNameReplyWithCode: (LSFResponseCode)rc lampID: (NSString*)lampID andLanguage: (NSString*)language
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"setLampName"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: language];
    [self.dataArray addObject: lampID];
}

-(void)lampsNameChangedWithID: (NSString *)lampID andName: (NSString *)name
{
    [self.dataArray removeAllObjects];
    [self.dataArray addObject: @"lampNameChanged"];
    [self.dataArray addObject: lampID];
    [self.dataArray addObject: name];
}

-(void)lampsFound: (NSArray *)lampIDs
{
    [self.dataArray removeAllObjects];
    [self.dataArray addObject: @"lampsFound"];
    [self.dataArray addObject: lampIDs];
}

-(void)lampsLost: (NSArray *)lampIDs
{
    [self.dataArray removeAllObjects];
    [self.dataArray addObject: @"lampsLost"];
    [self.dataArray addObject: lampIDs];
}

-(void)getLampDetailsReplyWithCode: (LSFResponseCode)rc lampID: (NSString *)lampID andLampDetails: (LSFSDKLampDetails *)details
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"getLampDetails"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: lampID];
    NSNumber *make = [[NSNumber alloc] initWithInt: details.lampMake];
    NSNumber *model = [[NSNumber alloc] initWithInt: details.lampModel];
    NSNumber *type = [[NSNumber alloc] initWithInt: details.deviceType];
    NSNumber *lampType = [[NSNumber alloc] initWithInt: details.lampType];
    NSNumber *lampBaseType = [[NSNumber alloc] initWithInt: details.baseType];
    NSNumber *lampBeamAngle = [[NSNumber alloc] initWithUnsignedInt: details.lampBeamAngle];
    NSNumber *dimmable = [[NSNumber alloc] initWithBool: details.dimmable];
    NSNumber *color = [[NSNumber alloc] initWithBool: details.color];
    NSNumber *variableColorTemp = [[NSNumber alloc] initWithBool: details.variableColorTemp];
    NSNumber *hasEffects = [[NSNumber alloc] initWithBool: details.hasEffects];
    NSNumber *maxVoltage = [[NSNumber alloc] initWithUnsignedInt: details.maxVoltage];
    NSNumber *minVoltage = [[NSNumber alloc] initWithUnsignedInt: details.minVoltage];
    NSNumber *wattage = [[NSNumber alloc] initWithUnsignedInt: details.wattage];
    NSNumber *incandescentEquivalent = [[NSNumber alloc] initWithUnsignedInt: details.incandescentEquivalent];
    NSNumber *maxLumens = [[NSNumber alloc] initWithUnsignedInt: details.maxLumens];
    NSNumber *minTemp = [[NSNumber alloc] initWithUnsignedInt: details.minTemperature];
    NSNumber *maxTemp = [[NSNumber alloc] initWithUnsignedInt: details.maxTemperature];
    NSNumber *cri = [[NSNumber alloc] initWithUnsignedInt: details.colorRenderingIndex];
    [self.dataArray addObject: make];
    [self.dataArray addObject: model];
    [self.dataArray addObject: type];
    [self.dataArray addObject: lampType];
    [self.dataArray addObject: lampBaseType];
    [self.dataArray addObject: lampBeamAngle];
    [self.dataArray addObject: dimmable];
    [self.dataArray addObject: color];
    [self.dataArray addObject: variableColorTemp];
    [self.dataArray addObject: hasEffects];
    [self.dataArray addObject: maxVoltage];
    [self.dataArray addObject: minVoltage];
    [self.dataArray addObject: wattage];
    [self.dataArray addObject: incandescentEquivalent];
    [self.dataArray addObject: maxLumens];
    [self.dataArray addObject: minTemp];
    [self.dataArray addObject: maxTemp];
    [self.dataArray addObject: cri];
}

-(void)getLampParametersReplyWithCode: (LSFResponseCode)rc lampID: (NSString *)lampID andLampParameters: (LSFSDKLampParameters *)params
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"getLampParameters"];
    [self.dataArray addObject: responseCode];
    NSNumber *eum = [[NSNumber alloc] initWithUnsignedInt: params.energyUsageMilliwatts];
    [self.dataArray addObject: lampID];
    [self.dataArray addObject: eum];
    NSNumber *lume = [[NSNumber alloc] initWithUnsignedInt: params.lumens];
    [self.dataArray addObject: lume];
}

-(void)getLampParametersEnergyUsageMilliwattsFieldReplyWithCode: (LSFResponseCode)rc lampID: (NSString*)lampID andEnergyUsage: (unsigned int)energyUsageMilliwatts
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"getLampParametersEnergyUsageMilliwatts"];
    [self.dataArray addObject: responseCode];
    NSNumber *eum = [[NSNumber alloc] initWithUnsignedInt: energyUsageMilliwatts];
    [self.dataArray addObject: lampID];
    [self.dataArray addObject: eum];
}

-(void)getLampParametersLumensFieldReplyWithCode: (LSFResponseCode)rc lampID: (NSString*)lampID andBrightnessLumens: (unsigned int)brightnessLumens;
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"getLampParametersLumens"];
    [self.dataArray addObject: responseCode];
    NSNumber *lume = [[NSNumber alloc] initWithUnsignedInt: brightnessLumens];
    [self.dataArray addObject: lume];
    [self.dataArray addObject: lampID];
}

-(void)getLampStateReplyWithCode: (LSFResponseCode)rc lampID: (NSString *)lampID andLampState: (LSFLampState *)state
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"getLampState"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: lampID];
    NSNumber *onOff = [[NSNumber alloc] initWithBool: state.onOff];
    NSNumber *brightness = [[NSNumber alloc] initWithUnsignedInt: state.brightness];
    NSNumber *hue = [[NSNumber alloc] initWithUnsignedInt: state.hue];
    NSNumber *saturation = [[NSNumber alloc] initWithUnsignedInt: state.saturation];
    NSNumber *colorTemp = [[NSNumber alloc] initWithUnsignedInt: state.colorTemp];
    [self.dataArray addObject: onOff];
    [self.dataArray addObject: brightness];
    [self.dataArray addObject: hue];
    [self.dataArray addObject: saturation];
    [self.dataArray addObject: colorTemp];
}

-(void)getLampStateOnOffFieldReplyWithCode: (LSFResponseCode)rc lampID: (NSString *)lampID andOnOff: (BOOL)onOff
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"getLampStateOnOffField"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: lampID];
    NSNumber *onOffField = [[NSNumber alloc] initWithBool: onOff];
    [self.dataArray addObject: onOffField];
}

-(void)getLampStateHueFieldReplyWithCode: (LSFResponseCode)rc lampID: (NSString *)lampID andHue: (unsigned int)hue
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"getLampStateHueField"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: lampID];
    NSNumber *hueField = [[NSNumber alloc] initWithUnsignedInt: hue];
    [self.dataArray addObject: hueField];
}

-(void)getLampStateSaturationFieldReplyWithCode: (LSFResponseCode)rc lampID: (NSString *)lampID andSaturation: (unsigned int)saturation
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"getLampStateSaturationField"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: lampID];
    NSNumber *saturationField = [[NSNumber alloc] initWithUnsignedInt: saturation];
    [self.dataArray addObject: saturationField];
}

-(void)getLampStateBrightnessFieldReplyWithCode: (LSFResponseCode)rc lampID: (NSString *)lampID andBrightness: (unsigned int)brightness
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"getLampStateBrightnessField"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: lampID];
    NSNumber *brightnessField = [[NSNumber alloc] initWithUnsignedInt: brightness];
    [self.dataArray addObject: brightnessField];
}

-(void)getLampStateColorTempFieldReplyWithCode: (LSFResponseCode)rc lampID: (NSString *)lampID andColorTemp: (unsigned int)colorTemp
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"getLampStateColorTempField"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: lampID];
    NSNumber *colorTempField = [[NSNumber alloc] initWithUnsignedInt: colorTemp];
    [self.dataArray addObject: colorTempField];
}

-(void)resetLampStateReplyWithCode: (LSFResponseCode)rc andLampID: (NSString *)lampID
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"resetLampState"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: lampID];
}

-(void)lampsStateChangedWithID: (NSString *)lampID andLampState: (LSFLampState *)state
{
    [self.dataArray removeAllObjects];
    [self.dataArray addObject: @"lampStateChanged"];
    [self.dataArray addObject: lampID];
    NSNumber *onOff = [[NSNumber alloc] initWithBool: state.onOff];
    NSNumber *brightness = [[NSNumber alloc] initWithUnsignedInt: state.brightness];
    NSNumber *hue = [[NSNumber alloc] initWithUnsignedInt: state.hue];
    NSNumber *saturation = [[NSNumber alloc] initWithUnsignedInt: state.saturation];
    NSNumber *colorTemp = [[NSNumber alloc] initWithUnsignedInt: state.colorTemp];
    [self.dataArray addObject: onOff];
    [self.dataArray addObject: brightness];
    [self.dataArray addObject: hue];
    [self.dataArray addObject: saturation];
    [self.dataArray addObject: colorTemp];
}

-(void)transitionLampStateReplyWithCode: (LSFResponseCode)rc andLampID: (NSString*)lampID
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"transitionLampState"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: lampID];
}

-(void)pulseLampWithStateReplyWithCode: (LSFResponseCode)rc andLampID: (NSString*)lampID
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"pulseWithState"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: lampID];
}

-(void)pulseLampWithPresetReplyWithCode: (LSFResponseCode)rc andLampID: (NSString*)lampID
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"pulseWithPreset"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: lampID];
}

-(void)transitionLampStateOnOffFieldReplyWithCode: (LSFResponseCode)rc andLampID: (NSString*)lampID
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"transitionLampStateOnOffField"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: lampID];
}

-(void)transitionLampStateHueFieldReplyWithCode: (LSFResponseCode)rc andLampID: (NSString*)lampID
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"transitionLampStateHueField"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: lampID];
}

-(void)transitionLampStateSaturationFieldReplyWithCode: (LSFResponseCode)rc andLampID: (NSString*)lampID
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"transitionLampStateSaturationField"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: lampID];
}

-(void)transitionLampStateBrightnessFieldReplyWithCode: (LSFResponseCode)rc andLampID: (NSString*)lampID
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"transitionLampStateBrightnessField"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: lampID];
}

-(void)transitionLampStateColorTempFieldReplyWithCode: (LSFResponseCode)rc andLampID: (NSString*)lampID
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"transitionLampStateColorTempField"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: lampID];
}

-(void)getLampFaultsReplyWithCode: (LSFResponseCode)rc lampID: (NSString *)lampID andFaultCodes: (NSArray *)codes;
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"getLampFaults"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: lampID];
    [self.dataArray addObject: codes];
}

-(void)getLampServiceVersionReplyWithCode: (LSFResponseCode)rc lampID: (NSString*)lampID andLampServiceVersion: (unsigned int)lampServiceVersion
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"getLampServiceVersion"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: lampID];
    NSNumber *version = [[NSNumber alloc] initWithUnsignedInt: lampServiceVersion];
    [self.dataArray addObject: version];
}

-(void)clearLampFaultReplyWithCode: (LSFResponseCode)rc lampID: (NSString*)lampID andFaultCode: (LampFaultCode)faultCode
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"clearLampFault"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: lampID];
    NSNumber *code = [[NSNumber alloc] initWithUnsignedInt: faultCode];
    [self.dataArray addObject: code];
}

-(void)resetLampStateOnOffFieldReplyWithCode: (LSFResponseCode)rc andLampID: (NSString*)lampID
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"resetLampStateOnOffField"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: lampID];
}

-(void)resetLampStateHueFieldReplyWithCode: (LSFResponseCode)rc andLampID: (NSString*)lampID
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"resetLampStateHueField"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: lampID];
}

-(void)resetLampStateSaturationFieldReplyWithCode: (LSFResponseCode)rc andLampID: (NSString*)lampID
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"resetLampStateSaturationField"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: lampID];
}

-(void)resetLampStateBrightnessFieldReplyWithCode: (LSFResponseCode)rc andLampID: (NSString*)lampID
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"resetLampStateBrightnessField"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: lampID];
}

-(void)resetLampStateColorTempFieldReplyWithCode: (LSFResponseCode)rc andLampID: (NSString*)lampID
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"resetLampStateColorTempField"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: lampID];
}

-(void)transitionLampStateToPresetReplyWithCode: (LSFResponseCode)rc andLampID: (NSString*)lampID
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"transitionLampStateToPreset"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: lampID];
}

-(void)getLampSupportedLanguagesReplyWithCode: (LSFResponseCode)rc lampID: (NSString*)lampID andSupportedLanguages: (NSArray*)supportedLanguages
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"getLampSupportedLanguages"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: lampID];
    [self.dataArray addObject: supportedLanguages];
}

-(void)setLampEffectReplyWithCode: (LSFResponseCode)rc lampID: (NSString *)lampID andEffectID: (NSString *)effectID
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    [self.dataArray addObject: @"setLampEffect"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: lampID];
    [self.dataArray addObject: effectID];
}

-(void)getConsolidatedLampDataSetReplyWithCode: (LSFResponseCode)rc lampID: (NSString *)lampID language:(NSString *)language lampName: (NSString *)lampName lampDetails:(LSFSDKLampDetails *)lampDetails lampState: (LSFLampState *)lampState andLampParameters: (LSFSDKLampParameters *)lampParameters
{
    [self.dataArray removeAllObjects];
    NSNumber *responseCode = [[NSNumber alloc] initWithInt: rc];
    NSNumber *make = [[NSNumber alloc] initWithInt: lampDetails.lampMake];
    NSNumber *model = [[NSNumber alloc] initWithInt: lampDetails.lampModel];
    NSNumber *type = [[NSNumber alloc] initWithInt: lampDetails.deviceType];
    NSNumber *lampType = [[NSNumber alloc] initWithInt: lampDetails.lampType];
    NSNumber *lampBaseType = [[NSNumber alloc] initWithInt: lampDetails.baseType];
    NSNumber *lampBeamAngle = [[NSNumber alloc] initWithUnsignedInt: lampDetails.lampBeamAngle];
    NSNumber *dimmable = [[NSNumber alloc] initWithBool: lampDetails.dimmable];
    NSNumber *color = [[NSNumber alloc] initWithBool: lampDetails.color];
    NSNumber *variableColorTemp = [[NSNumber alloc] initWithBool: lampDetails.variableColorTemp];
    NSNumber *hasEffects = [[NSNumber alloc] initWithBool: lampDetails.hasEffects];
    NSNumber *maxVoltage = [[NSNumber alloc] initWithUnsignedInt: lampDetails.maxVoltage];
    NSNumber *minVoltage = [[NSNumber alloc] initWithUnsignedInt: lampDetails.minVoltage];
    NSNumber *wattage = [[NSNumber alloc] initWithUnsignedInt: lampDetails.wattage];
    NSNumber *incandescentEquivalent = [[NSNumber alloc] initWithUnsignedInt: lampDetails.incandescentEquivalent];
    NSNumber *maxLumens = [[NSNumber alloc] initWithUnsignedInt: lampDetails.maxLumens];
    NSNumber *minTemp = [[NSNumber alloc] initWithUnsignedInt: lampDetails.minTemperature];
    NSNumber *maxTemp = [[NSNumber alloc] initWithUnsignedInt: lampDetails.maxTemperature];
    NSNumber *cri = [[NSNumber alloc] initWithUnsignedInt: lampDetails.colorRenderingIndex];
    NSNumber *onOff = [[NSNumber alloc] initWithBool: lampState.onOff];
    NSNumber *brightness = [[NSNumber alloc] initWithUnsignedInt: lampState.brightness];
    NSNumber *hue = [[NSNumber alloc] initWithUnsignedInt: lampState.hue];
    NSNumber *saturation = [[NSNumber alloc] initWithUnsignedInt: lampState.saturation];
    NSNumber *colorTemp = [[NSNumber alloc] initWithUnsignedInt: lampState.colorTemp];
    NSNumber *eum = [[NSNumber alloc] initWithUnsignedInt: lampParameters.energyUsageMilliwatts];
    NSNumber *lume = [[NSNumber alloc] initWithUnsignedInt: lampParameters.lumens];
    [self.dataArray addObject: @"getConsolidatedLampDataSet"];
    [self.dataArray addObject: responseCode];
    [self.dataArray addObject: lampID];
    [self.dataArray addObject: language];
    [self.dataArray addObject: lampName];
    [self.dataArray addObject: onOff];
    [self.dataArray addObject: brightness];
    [self.dataArray addObject: hue];
    [self.dataArray addObject: saturation];
    [self.dataArray addObject: colorTemp];
    [self.dataArray addObject: eum];
    [self.dataArray addObject: lume];
    [self.dataArray addObject: make];
    [self.dataArray addObject: model];
    [self.dataArray addObject: type];
    [self.dataArray addObject: lampType];
    [self.dataArray addObject: lampBaseType];
    [self.dataArray addObject: lampBeamAngle];
    [self.dataArray addObject: dimmable];
    [self.dataArray addObject: color];
    [self.dataArray addObject: variableColorTemp];
    [self.dataArray addObject: hasEffects];
    [self.dataArray addObject: maxVoltage];
    [self.dataArray addObject: minVoltage];
    [self.dataArray addObject: wattage];
    [self.dataArray addObject: incandescentEquivalent];
    [self.dataArray addObject: maxLumens];
    [self.dataArray addObject: minTemp];
    [self.dataArray addObject: maxTemp];
    [self.dataArray addObject: cri];
}

@end
