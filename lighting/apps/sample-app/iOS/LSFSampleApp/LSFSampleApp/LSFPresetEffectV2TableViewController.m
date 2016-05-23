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

#import "LSFPresetEffectV2TableViewController.h"
#import "LSFUtilityFunctions.h"
#import <LSFSDKLightingDirector.h>

@interface LSFPresetEffectV2TableViewController ()

@end

@implementation LSFPresetEffectV2TableViewController

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear: animated];

    if (!self.pendingEffect.theID)
    {
        self.pendingEffect.name = [PRESET_NAME_PREFIX stringByAppendingString: [LSFUtilityFunctions generateRandomHexStringWithLength: 16]];
    }
}

-(NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    return (section == 0) ? [NSString stringWithFormat: @"Select the properties that %@ will change to", [LSFUtilityFunctions memberStringForPendingSceneElement: self.pendingSceneElement]] : @"";
}

-(IBAction)doneButtonPressed:(id)sender
{
    NSLog(@"Done Button Pressed for Preset");
    [super doneButtonPressed: sender];
    [self dismissViewControllerAnimated: YES completion: nil];
}

@end
