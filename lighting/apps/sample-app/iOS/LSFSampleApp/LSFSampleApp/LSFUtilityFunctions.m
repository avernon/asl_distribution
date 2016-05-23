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

#import "LSFUtilityFunctions.h"
#import <LSFSDKLampValues.h>
#import <SystemConfiguration/CaptiveNetwork.h>
#import <LSFSDKLightingDirector.h>

@implementation LSFUtilityFunctions

NSString* const PRESET_NAME_PREFIX = @"LSF_PRE_";
NSString* const TRANSITION_NAME_PREFIX = @"LSF_TRN_";
NSString* const PULSE_NAME_PREFIX = @"LSF_PLS_";
NSString* const SCENE_ELEMENT_NAME_PREFIX = @"LSF_SEL_";

+(BOOL)checkNameEmpty: (NSString *)name entity: (NSString *)entity
{
    if ([name isEqualToString: @""])
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle: [NSString stringWithFormat: @"%@ Error", entity]
                                                        message: @"You need to provide a name in order to proceed."
                                                       delegate: self
                                              cancelButtonTitle: @"OK"
                                              otherButtonTitles: nil];
        [alert show];

        return NO;
    }

    return YES;
}

+(BOOL)checkNameLength: (NSString *)name entity: (NSString *)entity
{
    if ([name length] > LSF_MAX_NAME_LENGTH)
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle: [NSString stringWithFormat: @"%@ Error", entity]
                                                        message: [NSString stringWithFormat: @"Name has exceeded %d characters limit", LSF_MAX_NAME_LENGTH ]
                                                       delegate: self
                                              cancelButtonTitle: nil
                                              otherButtonTitles: @"OK", nil];
        [alert show];
        return NO;
    }
    return YES;
}

+(BOOL)checkWhiteSpaces: (NSString *)name entity: (NSString *)entity
{
    //only whitespaces
    if (([name stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]].length == 0) || [name hasPrefix:@" "])
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle: [NSString stringWithFormat: @"%@ Error", entity]
                                                        message: @"Name can't start or be only spaces"
                                                       delegate: self
                                              cancelButtonTitle: nil
                                              otherButtonTitles: @"OK", nil];
        [alert show];
        return NO;
    }
    return YES;
}

+(void)colorIndicatorSetup: (UIImageView*)colorIndicatorImage withColor: (LSFSDKColor*) color andCapabilityData: (LSFSDKCapabilityData *)capablity
{
    CAShapeLayer *circleShape = [CAShapeLayer layer];
    [circleShape setPosition:CGPointMake([colorIndicatorImage bounds].size.width/2.0f, [colorIndicatorImage bounds].size.height/2.0f)];
    [circleShape setBounds:CGRectMake(0.0f, 0.0f, [colorIndicatorImage bounds].size.width, [colorIndicatorImage bounds].size.height)];
    [circleShape setPath:[[UIBezierPath bezierPathWithRoundedRect:CGRectMake(0.0f, 0.0f, 10.0f, 10.0f) cornerRadius:10.0f]  CGPath]];
    [circleShape setLineWidth:0.3f];
    [circleShape setStrokeColor:[[UIColor colorWithRed:0.49 green:0.49 blue:0.49 alpha:1] CGColor]]; // #7d7d7d
    UIColor* fillColor = [self calcFillColor: color withCapability: capablity];
    [circleShape setFillColor: [fillColor CGColor]];
    [[colorIndicatorImage layer] addSublayer:circleShape];
}

+(UIColor*)calcFillColor: (LSFSDKColor *) color withCapability: (LSFSDKCapabilityData *)capability
{
    LSFSDKLightingDirector *director = [LSFSDKLightingDirector getLightingDirector];
    CGFloat brightness, hue, saturation, colorTemp;

    if (capability == nil || capability.color > NONE)
    {
        //Type 4 (on/off, dimmable, full color, color temp)
        brightness = (CGFloat)[color brightness];
        hue = (CGFloat)[color hue];
        saturation = (CGFloat)[color saturation];
        colorTemp = (CGFloat)[color colorTemp];
    }
    else if (capability.temp > NONE)
    {
        //Type 3 (on/off, dimmable, color temp)
        brightness = (CGFloat)[color brightness];
        hue = [director HUE_MIN];
        saturation = [director SATURATION_MIN];
        colorTemp = (CGFloat)[color colorTemp];
    }
    else if (capability.dimmable > NONE)
    {
        //Type 2 (on/off, dimmable)
        brightness = (CGFloat)[color brightness];
        hue = [director HUE_MIN];
        saturation = [director SATURATION_MIN];
        colorTemp = (CGFloat)[color colorTemp];
    }
    else
    {
        //Type 1 (on/off)
        brightness = [director BRIGHTNESS_MAX];
        hue = [director HUE_MIN];
        saturation = [director SATURATION_MIN];
        colorTemp = (CGFloat)[color colorTemp];
    }

    //Create original color using hue, saturation, brightness
    UIColor* colorToFill = [UIColor colorWithHue: (hue / 360) saturation: (saturation / 100) brightness: (brightness / 100) alpha: 1.000];

    //Convert the original color to RGB format
    CGFloat colorToFillRed, colorToFillGreen, colorToFillBlue, colorToFillAlpha;
    [colorToFill getRed: &colorToFillRed green: &colorToFillGreen blue: &colorToFillBlue alpha: &colorToFillAlpha];

    //Scale original color RGB values
    colorToFillRed *= 255;
    colorToFillGreen *= 255;
    colorToFillBlue *= 255;

    //Convert colorTemp to RGB format
    UIColor* colorTempRGB = [self convertColorTempToRGB: colorTemp];
    CGFloat colorTempRed, colorTempGreen, colorTempBlue, colorTempAlpha;
    [colorTempRGB getRed:&colorTempRed green:&colorTempGreen blue:&colorTempBlue alpha:&colorTempAlpha];

    //Scale colorTemp RGB values
    colorTempRed *= 255;
    colorTempGreen *= 255;
    colorTempBlue *= 255;

    //Create a colorTemp factor
    int sum = (int) (colorTempRed + colorTempGreen + colorTempBlue);

    //Compute factors for RGB channels
    double ctR = (colorTempRed / sum * 3);
    double ctG = (colorTempGreen / sum * 3);
    double ctB = (colorTempBlue / sum * 3);

    //Multiply each channel in its factor
    int newR = (int)round(ctR * colorToFillRed);
    int newG = (int)round(ctG * colorToFillGreen);
    int newB = (int)round(ctB * colorToFillBlue);

    //Fix values if needed
    if(newR > 255) newR = 255;
    if(newG > 255) newG = 255;
    if(newB > 255) newB = 255;

    return [UIColor colorWithRed:(newR/255.0f) green:(newG/255.0f) blue:(newB/255.0f) alpha:1];
}

+(UIColor*)convertColorTempToRGB:(unsigned int) colorTemp
{
    double r = 0;
    double g = 0;
    double b = 0;

    if (colorTemp < 1000)
    colorTemp = 1000;

    if (colorTemp > 40000)
    colorTemp = 40000;

    double tmpKelvin = colorTemp/100;

    //Calculate red
    if(tmpKelvin <= 66)
    {
        r = 255;
    }
    else
    {
        //Note: the R-squared value for this approximation is .988
        double tmpCalc = tmpKelvin - 60;
        tmpCalc = 329.698727446 * (pow(tmpCalc, -0.1332047592));
        r = tmpCalc;
        if(r < 0)
        r = 0;
        if(r > 255)
        r = 255;
    }

    //Calculate green
    if(tmpKelvin <= 66)
    {
        //Note: the R-squared value for this approximation is .996
        double tmpCalc = tmpKelvin;
        tmpCalc = 99.4708025861 * log(tmpCalc) - 161.1195681661;
        g = tmpCalc;
        if(g < 0)
        g = 0;
        if(g > 255)
        g = 255;
    }
    else
    {
        //Note: the R-squared value for this approximation is .987
        double tmpCalc = tmpKelvin - 60;
        tmpCalc = 288.1221695283 * (pow(tmpCalc,-0.0755148492));
        g = tmpCalc;
        if(g < 0)
        g = 0;
        if(g > 255)
        g = 255;
    }

    //Calculate blue
    if(tmpKelvin >= 66)
    {
        b = 255;
    }
    else if(tmpKelvin <= 19)
    {
        b = 0;
    }
    else
    {
        //Note: the R-squared value for this approximation is .998
        double tmpCalc = tmpKelvin - 10;
        tmpCalc = 138.5177312231 * log(tmpCalc) - 305.0447927307;
        b = tmpCalc;
        if(b < 0)
        b = 0;
        if(b > 255)
        b = 255;
    }

    UIColor *colorTempRGB = [UIColor colorWithRed:(r/255.0f) green:(g/255.0f) blue:(b/255.0f) alpha:1];
    return colorTempRGB;
}

+(NSString *)currentWifiSSID
{
    NSString *ssid = nil;
    NSArray *ifs = (__bridge_transfer id)CNCopySupportedInterfaces();

    for (NSString *ifnam in ifs)
    {
        NSDictionary *info = (__bridge_transfer id)CNCopyCurrentNetworkInfo((__bridge CFStringRef)ifnam);
        if (info[@"SSID"])
        {
            ssid = info[@"SSID"];
            //NSLog(@"SSID = %@", ssid);
        }
    }

    return ssid;
}

// Temporary fix - move definition from model to SDK level
+(NSArray *)getLampDetailsFields
{
    return [[NSArray alloc] initWithObjects: @"Lamp Make", @"Lamp Model", @"Device Type", @"Lamp Type", @"Base Type", @"Lamp Beam Angle",
            @"Dimmable", @"Supports Color", @"Supports Color Temperature", @"Supports Effects", @"Min Voltage", @"Max Voltage", @"Wattage",
            @"Incandescent Equivalent", @"Max Lumens", @"Min Temperature", @"Max Temperature", @"Color Rendering Index", nil];
}

// Temporary fix - move definition from model to SDK level
+(NSArray *)getLampAboutFields
{
    return [[NSArray alloc] initWithObjects: @"App ID", @"Default Language", @"Device Name", @"Device ID", @"App Name", @"Manufacturer",
            @"Model Number", @"Supported Languages", @"Description", @"Date of Manufacture", @"Software Version", @"AJ Software Version", @"Hardware Version", @"Support URL", nil];
}

+(NSArray *)getSupportedEffects
{
    return [NSArray arrayWithObjects: @"No Effect", @"Transition", @"Pulse", nil];
}

+(NSArray *)getEffectImages
{
    return [NSArray arrayWithObjects: @"list_constant_icon.png", @"list_transition_icon.png", @"list_pulse_icon.png", nil];
}

+(NSMutableAttributedString *)getSourceCodeText
{
    NSMutableAttributedString *sourceCodeText = [[NSMutableAttributedString alloc] initWithString: @"AllSeen Alliance Working Group"];
    [sourceCodeText addAttribute: NSLinkAttributeName value: @"https://wiki.allseenalliance.org/tsc/connected_lighting" range: NSMakeRange(0, sourceCodeText.length)];
    [sourceCodeText addAttribute: NSFontAttributeName value: [UIFont fontWithName: @"Helvetica Neue" size: 18.0f] range: NSMakeRange(0, sourceCodeText.length)];

    return sourceCodeText;
}

+(NSMutableAttributedString *)getTeamText
{
    NSMutableAttributedString *teamText = [[NSMutableAttributedString alloc] initWithString: @"AllSeen Alliance Working Group"];
    [teamText addAttribute: NSLinkAttributeName value: @"https://wiki.allseenalliance.org/tsc/connected_lighting" range: NSMakeRange(0, teamText.length)];
    [teamText addAttribute: NSFontAttributeName value: [UIFont fontWithName: @"Helvetica Neue" size: 18.0f] range: NSMakeRange(0, teamText.length)];

    return teamText;
}

+(NSMutableAttributedString *)getNoticeText
{
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
    Power lampStatePower = [state power];
    LSFSDKColor *lampStateColor = [state color];

    return
    presetPower == lampStatePower                       &&
    presetColor.hue == lampStateColor.hue               &&
    presetColor.saturation == lampStateColor.saturation &&
    presetColor.brightness == lampStateColor.brightness &&
    presetColor.colorTemp == lampStateColor.colorTemp;
}

+(NSArray *)getPresetsWithMyLampState: (LSFSDKMyLampState *)state
{
    NSMutableArray *presetsArray = [[NSMutableArray alloc] init];
    for (LSFSDKPreset *preset in [[LSFSDKLightingDirector getLightingDirector] presets])
    {
        if (![preset.name hasPrefix: PRESET_NAME_PREFIX])
        {
            BOOL matchesPreset = [self preset: preset matchesMyLampState: state];

            if (matchesPreset)
            {
                [presetsArray addObject: preset];
            }
        }
    }

    return presetsArray;
}

+(NSArray *)sortLightingItemsByName: (NSArray *)items
{
    NSMutableArray *sortedArray = [NSMutableArray arrayWithArray: [items sortedArrayUsingComparator: ^NSComparisonResult(id a, id b) {
        NSString *first = [(LSFSDKLightingItem *)a name];
        NSString *second = [(LSFSDKLightingItem *)b name];

        NSComparisonResult result = [first localizedCaseInsensitiveCompare: second];
        if (result == NSOrderedSame)
        {
            result = [((LSFSDKLightingItem *)a).theID localizedCaseInsensitiveCompare: ((LSFSDKLightingItem *)b).theID];
        }

        return result;
    }]];

    return sortedArray;
}

+(void)disableActionSheet: (UIActionSheet *)actionSheet buttonAtIndex: (NSInteger)index
{
    NSInteger buttonCount = 0;

    for (UIView *view in [actionSheet subviews])
    {
        if ([view isKindOfClass:[UIButton class]])
        {
            if (buttonCount == index)
            {
                if ([view respondsToSelector:@selector(setEnabled:)])
                {
                    UIButton *button = (UIButton *)view;
                    button.enabled = NO;
                }
            }

            buttonCount++;
        }
    }
}

+(NSString *)memberStringForPendingSceneElement: (LSFPendingSceneElement *)sceneElement
{
    NSMutableString *memberString = [[NSMutableString alloc] init];
    NSUInteger numMembers = sceneElement.members.count;

    if (numMembers > 0)
    {
        [memberString appendString: [[sceneElement.members objectAtIndex: 0] name]];

        if (sceneElement.members.count > 1)
        {
            [memberString appendString: [NSString stringWithFormat: @" (and %lu more)", (unsigned long)sceneElement.members.count - 1]];
        }
    }

    return memberString;
}

+(NSString *) generateRandomHexStringWithLength: (int)len
{
    NSString *digits = @"0123456789ABCDEF";
    NSMutableString *randomString = [NSMutableString stringWithCapacity: len];

    for (int i = 0; i < len; i++)
    {
        unichar c = [digits characterAtIndex: (arc4random() % [digits length])];
        [randomString appendFormat: @"%C", c];
    }

    return randomString;
}

+(LSFSDKTrackingID *)createEffectFromPendingItem: (LSFPendingEffect *)effect
{
    NSArray* matchingPresets = nil;
    id<LSFSDKLampState> effectLampState = nil;
    id<LSFSDKLampState> effectEndLampState = nil;

    switch (effect.type)
    {
        case PRESET:
            return [[LSFSDKLightingDirector getLightingDirector] createPresetWithPower: effect.state.power color: effect.state.color presetName: effect.name];
            break;
        case TRANSITION:
            matchingPresets = [LSFUtilityFunctions getPresetsWithMyLampState: effect.state];
            effectLampState = (matchingPresets.count > 0)? [matchingPresets objectAtIndex: 0] : effect.state;

            return [[LSFSDKLightingDirector getLightingDirector] createTransitionEffectWithLampState: effectLampState duration: effect.duration name: effect.name];
        case PULSE:
            matchingPresets = [LSFUtilityFunctions getPresetsWithMyLampState: effect.state];
            effectLampState = (matchingPresets.count > 0)? [matchingPresets objectAtIndex: 0] : effect.state;

            matchingPresets = [LSFUtilityFunctions getPresetsWithMyLampState: effect.endState];
            effectEndLampState = (matchingPresets.count > 0)? [matchingPresets objectAtIndex: 0] : effect.endState;

            return [[LSFSDKLightingDirector getLightingDirector] createPulseEffectWithFromState: effectLampState toState: effectEndLampState period: effect.period duration: effect.duration count: effect.pulses name: effect.name];
        default:
            return nil;
    }
}

+(LSFSDKTrackingID *)createSceneElementFromPendingItem: (LSFPendingSceneElement *)sceneElement
{
    id<LSFSDKEffect> effect = [[LSFSDKLightingDirector getLightingDirector] getEffectWithID: sceneElement.pendingEffect.theID];

    return [[LSFSDKLightingDirector getLightingDirector] createSceneElementWithEffect: effect groupMembers: sceneElement.members name: sceneElement.name];
}

+(LSFSDKTrackingID *)createSceneFromPendingItem: (LSFPendingSceneV2 *)scene
{
    NSArray *sceneElementIDs = [scene.pendingSceneElements valueForKeyPath: @"theID"];
    NSMutableArray *sceneElements = [[NSMutableArray alloc] init];
    for (NSString *elementID in sceneElementIDs)
    {
        [sceneElements addObject: [[LSFSDKLightingDirector getLightingDirector] getSceneElementWithID: elementID]];
    }

    return [[LSFSDKLightingDirector getLightingDirector] createSceneWithSceneElements: sceneElements name: scene.name];
}

+(void)updateSceneElementWithID: (NSString *)elementID pendingItem: (LSFPendingSceneElement *)pendingElement
{
    LSFSDKSceneElement *element = [[LSFSDKLightingDirector getLightingDirector] getSceneElementWithID: elementID];
    id<LSFSDKEffect> effect = [[LSFSDKLightingDirector getLightingDirector] getEffectWithID: pendingElement.pendingEffect.theID];
    [element modifyWithEffect: effect groupMembers: pendingElement.members];
}

+(void)updateEffectWithID: (NSString *)effectID pendingItem: (LSFPendingEffect *)pendingEffect
{
    id<LSFSDKEffect> effect = [[LSFSDKLightingDirector getLightingDirector] getEffectWithID: effectID];

    if ([effect isKindOfClass: [LSFSDKPreset class]])
    {
        dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
            LSFSDKPreset *preset = (LSFSDKPreset *)effect;
            [preset modifyWithPower: pendingEffect.state.power color: pendingEffect.state.color];
        });
    }
    else if ([effect isKindOfClass: [LSFSDKTransitionEffect class]])
    {
        dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
            LSFSDKTransitionEffect *transition = (LSFSDKTransitionEffect *)effect;

            NSArray *matchingPresets = [LSFUtilityFunctions getPresetsWithMyLampState: pendingEffect.state];
            id<LSFSDKLampState> effectLampState = (matchingPresets.count > 0)? [matchingPresets objectAtIndex: 0] : pendingEffect.state;

            [transition modify: effectLampState duration: pendingEffect.duration];
        });
    }
    else if ([effect isKindOfClass: [LSFSDKPulseEffect class]])
    {
        dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
            LSFSDKPulseEffect *pulse = (LSFSDKPulseEffect *)effect;

            NSArray *matchingPresets = [LSFUtilityFunctions getPresetsWithMyLampState: pendingEffect.state];
            id<LSFSDKLampState> effectLampState = (matchingPresets.count > 0)? [matchingPresets objectAtIndex: 0] : pendingEffect.state;

            matchingPresets = [LSFUtilityFunctions getPresetsWithMyLampState: pendingEffect.endState];
            id<LSFSDKLampState> effectEndLampState = (matchingPresets.count >0)? [matchingPresets objectAtIndex: 0] : pendingEffect.endState;

            [pulse modifyFromState: effectLampState toState: effectEndLampState period: pendingEffect.period duration: pendingEffect.duration count: pendingEffect.pulses];
        });
    }
}

+(int)getBoundedMinColorTempForMembers: (NSArray *)members
{
    int minTemp = INT_MIN;

    for (id member in members)
    {
        if ([member isKindOfClass: [LSFSDKGroupMember class]])
        {
            minTemp = MAX(minTemp, [member colorTempMin]);
        }
    }

    return minTemp;
}

+(int)getBoundedMaxColorTempForMembers: (NSArray *)members
{
    int maxTemp = INT_MAX;

    for (id member in members)
    {
        if ([member isKindOfClass: [LSFSDKGroupMember class]])
        {
            maxTemp = MIN(maxTemp, [member colorTempMax]);
        }
    }

    return maxTemp;
}

@end
