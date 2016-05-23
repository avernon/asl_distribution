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

#import "LSFGroupsCell.h"
#import "LSFDispatchQueue.h"
#import "LSFConstants.h"
#import "LSFAllJoynManager.h"
#import "LSFGroupModel.h"
#import "LSFGroupModelContainer.h"

@interface LSFGroupsCell()

@property (nonatomic) unsigned int previousBrightness;

-(void)sliderTapped: (UIGestureRecognizer *)gr;
-(void)setTimestampAndDelay;
-(void)postDelayedGroupRefresh: (unsigned int)delay;

@end

@implementation LSFGroupsCell

@synthesize groupID = _groupID;
@synthesize powerImage = _powerImage;
@synthesize nameLabel = _nameLabel;
@synthesize brightnessSlider = _brightnessSlider;
@synthesize brightnessSliderButton = _brightnessSliderButton;

-(void)awakeFromNib
{
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
    LSFGroupModelContainer *container = [LSFGroupModelContainer getGroupModelContainer];
    NSMutableDictionary *groups = container.groupContainer;
    LSFGroupModel *model = [groups valueForKey: self.groupID];

    if (model != nil && model.state.onOff)
    {
        dispatch_async(([LSFDispatchQueue getDispatchQueue]).queue, ^{
            LSFLampGroupManager *groupManager = ([LSFAllJoynManager getAllJoynManager]).lsfLampGroupManager;
            [groupManager transitionLampGroupID: self.groupID onOffField: NO];
        });
    }
    else
    {
        LSFConstants *constants = [LSFConstants getConstants];
        
        dispatch_async(([LSFDispatchQueue getDispatchQueue]).queue, ^{
            LSFLampGroupManager *groupManager = ([LSFAllJoynManager getAllJoynManager]).lsfLampGroupManager;

            if (model.state.brightness == 0)
            {
                unsigned int scaledBrightness = [constants scaleLampStateValue: 25 withMax: 100];
                [groupManager transitionLampGroupID: self.groupID brightnessField: scaledBrightness];
            }

            [groupManager transitionLampGroupID: self.groupID onOffField: YES];
        });
    }
}

-(IBAction)brightnessSliderChanged: (UISlider *)sender
{
    LSFConstants *constants = [LSFConstants getConstants];
        
    dispatch_async(([LSFDispatchQueue getDispatchQueue]).queue, ^{
        LSFLampGroupManager *groupManager = ([LSFAllJoynManager getAllJoynManager]).lsfLampGroupManager;
        unsigned int scaledBrightness = [constants scaleLampStateValue: (uint32_t)sender.value withMax: 100];
        [groupManager transitionLampGroupID: self.groupID brightnessField: scaledBrightness];
    });

    [self setTimestampAndDelay];
}

-(IBAction)brightnessSliderTouchedWhileDisabled: (UIButton *)sender
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"Error"
                                                    message: @"This group is not able to change its brightness since no lamps in the group are dimmable."
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
    
    unsigned int newBrightness = (uint32_t)value;
    self.brightnessSlider.value = newBrightness;
    
    dispatch_async(([LSFDispatchQueue getDispatchQueue]).queue, ^{
        LSFConstants *constants = [LSFConstants getConstants];

        LSFLampGroupManager *groupManager = ([LSFAllJoynManager getAllJoynManager]).lsfLampGroupManager;
        unsigned int scaledBrightness = [constants scaleLampStateValue: newBrightness withMax: 100];
        [groupManager transitionLampGroupID: self.groupID brightnessField: scaledBrightness];
    });

    [self setTimestampAndDelay];
}

-(void)setTimestampAndDelay
{
    LSFConstants *constants = [LSFConstants getConstants];

    LSFGroupModelContainer *container = [LSFGroupModelContainer getGroupModelContainer];
    NSMutableDictionary *groups = container.groupContainer;
    LSFGroupModel *model = [groups valueForKey: self.groupID];

    model.timestamp = (long long)([[NSDate date] timeIntervalSince1970] * 1000);

    unsigned int proposedDelay = (constants.UI_DELAY + (model.lamps.count * 50));
    model.delay = proposedDelay > 1000 ? 1000 : proposedDelay;

    [self postDelayedGroupRefresh: model.delay];
}

-(void)postDelayedGroupRefresh: (unsigned int)delay
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(((double)delay / 1000.0) * NSEC_PER_SEC)), ([LSFDispatchQueue getDispatchQueue]).queue, ^{
        LSFAllJoynManager *ajManager = [LSFAllJoynManager getAllJoynManager];
        [ajManager.slgmc refreshAllLampGroupIDs];
    });
}

@end
