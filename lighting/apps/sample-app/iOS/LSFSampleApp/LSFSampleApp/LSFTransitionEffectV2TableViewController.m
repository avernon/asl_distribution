/******************************************************************************
 * Copyright (c) AllSeen Alliance. All rights reserved.
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

#import "LSFTransitionEffectV2TableViewController.h"
#import "LSFEffectV2NumericPropertyViewController.h"
#import "LSFSelectPresetTableViewController.h"
#import "LSFUtilityFunctions.h"
#import <LSFSDKLightingDirector.h>

@interface LSFTransitionEffectV2TableViewController ()

@end

@implementation LSFTransitionEffectV2TableViewController

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear: animated];

    [self updatePresetButtonTitle: self.presetButton];

    self.durationLabel.text = [NSString stringWithFormat:@"%@ seconds", [@(self.pendingEffect.duration / 1000.0) stringValue]];

    if (!self.pendingEffect.theID)
    {
        self.pendingEffect.name = [TRANSITION_NAME_PREFIX stringByAppendingString: [LSFUtilityFunctions generateRandomHexStringWithLength: 16]];
    }
}

-(NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    return (section == 0) ? [NSString stringWithFormat: @"Select the properties that %@ will transition to", [LSFUtilityFunctions memberStringForPendingSceneElement: self.pendingSceneElement]] : @"";
}

-(IBAction)doneButtonPressed:(id)sender
{
    NSLog(@"Done Button Pressed for TransitionEffect");
    [super doneButtonPressed: sender];
    [self dismissViewControllerAnimated: YES completion: nil];
}

-(IBAction)onSliderTouchUpInside: (UISlider *)slider
{
    [super onSliderTouchUpInside: slider];
    [self updatePresetButtonTitle: self.presetButton];
}

-(void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if ([segue.identifier isEqualToString: @"TransitionDuration"])
    {
        LSFEffectV2NumericPropertyViewController *enpvc = [segue destinationViewController];
        enpvc.pendingEffect = self.pendingEffect;
        enpvc.effectType = TRANSITION;
        enpvc.effectProperty = DURATION;
    }
    else if ([segue.identifier isEqualToString: @"TransitionPreset"])
    {
        // store the latest slider state into the pending effect
        self.pendingEffect.state = [self getSlidersState];

        LSFSelectPresetTableViewController *sptvc = [segue destinationViewController];
        sptvc.state = self.pendingEffect.state;
    }
}

@end
