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

#import "LSFLightsCell.h"
#import <LSFSDKLightingDirector.h>

@interface LSFLightsCell()

-(void)sliderTapped: (UIGestureRecognizer *)gr;

@end

@implementation LSFLightsCell

@synthesize lampID = _lampID;
@synthesize powerImage = _powerImage;
@synthesize nameLabel = _nameLabel;
@synthesize brightnessSlider = _brightnessSlider;
@synthesize brightnessSliderButton = _brightnessSliderButton;

-(void)awakeFromNib
{
    self.colorIndicatorImage.layer.rasterizationScale = [UIScreen mainScreen].scale;
    self.colorIndicatorImage.layer.shouldRasterize = YES;

    [self.brightnessSlider setThumbImage: [UIImage imageNamed: @"power_slider_normal_icon.png"] forState: UIControlStateNormal];
    [self.brightnessSlider setThumbImage: [UIImage imageNamed: @"power_slider_pressed_icon.png"] forState: UIControlStateHighlighted];

    UITapGestureRecognizer *tapGestureRecognizer = [[UITapGestureRecognizer alloc] initWithTarget: self action: @selector(sliderTapped:)];
    [self.brightnessSlider addGestureRecognizer: tapGestureRecognizer];

    unsigned int c;
    NSString *color = @"f4f4f4";
    if ([color characterAtIndex: 0] == '#')
    {
        [[NSScanner scannerWithString: [color substringFromIndex: 1]] scanHexInt: &c];
    }
    else
    {
        [[NSScanner scannerWithString: color] scanHexInt: &c];
    }
    self.backgroundColor = [UIColor colorWithRed: ((c & 0xff0000) >> 16) / 255.0 green: ((c & 0xff00) >> 8) / 255.0 blue: (c & 0xff) / 255.0 alpha: 1.0];
}

-(IBAction)powerImagePressed: (UIButton *)sender
{
    LSFSDKLamp *lamp = [[LSFSDKLightingDirector getLightingDirector] getLampWithID: self.lampID];

    if (lamp != nil && [lamp getPowerOn])
    {
        dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
            [lamp setPowerOn: NO];
        });
    }
    else
    {
        dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
            if ([[lamp getColor] brightness] == 0 && [[lamp details] dimmable])
            {
                LSFSDKColor *color = [lamp getColor];
                color.brightness = 25;
                [lamp setColor: color];
            }

            [lamp setPowerOn: YES];
        });
    }
}

-(IBAction)brightnessSliderChanged: (UISlider *)sender
{
    LSFSDKLamp *lamp = [[LSFSDKLightingDirector getLightingDirector] getLampWithID:self.lampID];

    dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
        LSFSDKColor *color = [lamp getColor];
        color.brightness = (uint32_t)sender.value;
        [lamp setColor: color];

        if ([[lamp getColor] brightness] == 0)
        {
            [lamp setPowerOn: YES];
        }
    });
}

-(IBAction)brightnessSliderTouchedWhileDisabled: (UIButton *)sender
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error"
                                                    message: @"This Lamp is not able to change its brightness."
                                                   delegate: nil
                                          cancelButtonTitle: @"OK"
                                          otherButtonTitles: nil];
    [alert show];
}

/*
 * Private functions
 */
-(void)sliderTapped: (UIGestureRecognizer *)gr
{
    UISlider *s = (UISlider *)gr.view;

    if (s.highlighted)
    {
        //tap on thumb, let slider deal with it
        return;
    }

    CGPoint pt = [gr locationInView: s];
    CGFloat percentage = pt.x / s.bounds.size.width;
    CGFloat delta = percentage * (s.maximumValue - s.minimumValue);
    CGFloat value = round(s.minimumValue + delta);

    dispatch_async([[LSFSDKLightingDirector getLightingDirector] queue], ^{
        LSFSDKLamp *lamp = [[LSFSDKLightingDirector getLightingDirector] getLampWithID:self.lampID];
        LSFSDKColor *color = [lamp getColor];
        color.brightness = (uint32_t)value;
        [lamp setColor: color];

        if ([[lamp getColor] brightness] == 0)
        {
            [lamp setPowerOn: YES];
        }
    });
}

@end
